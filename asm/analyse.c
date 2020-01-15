/************************************************************************
 *
 * EBEL DLX Simulator
 * Copyright (c) 2001 by
 * Etienne Bergeron <bergeret@iro.umontreal.ca>
 * and Eric Lesage <lesagee@iro.umontreal.ca>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see file COPYING); if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "asm.h"
#include "analyse.h"
#include "symbols.h"

int asm_tree_changed;
int asm_tree_incomplet;

void changed()
{
  asm_tree_changed = 1;
}

Node *asm_check_tree(Node *node, symbols_t *s)
{
  Node *next;
  int i;

  if (node == NULL)
    return NULL;

  switch (node->type)
  {
  case A_LABEL:
    yyerror_printf2("Can't resolve label %s\n", node->line_no, node->identifier);
    next = node->next;
    node->next = NULL;
    asm_delete_tree(node);
    return asm_check_tree(next, s);

  case A_CMDEQU:
  case A_CMDDATA:
  case A_CMDORG:
    if (node->param[0]->type != A_VALUE &&
        node->param[0]->type != A_FVALUE)
    {
      yyerror_printf2("Can't resolve symbol %s\n", node->line_no, node->identifier);
      next = node->next;
      node->next = NULL;
      asm_delete_tree(node);
      return asm_check_tree(next, s);
    }
    break;

  case A_INSTR:
  {
    int param_count = 0;
    for (i = 0; i < 3; i++)
    {
      if (node->param[i])
        param_count++;

      if (node->param[i] &&
          node->param[i]->type != A_VALUE &&
          node->param[i]->type != A_FVALUE &&
          node->param[i]->type != A_RREG &&
          node->param[i]->type != A_FREG)
      {
        yyerror_printf2("Can't resolve param %d of instruction %s\n",
                        node->line_no, param_count, node->instr->opname);
        next = node->next;
        node->next = NULL;
        asm_delete_tree(node);
        return asm_check_tree(next, s);
      }
    }
  }
  break;
  }

  node->next = asm_check_tree(node->next, s);
  return node;
}

Node *asm_simplify_tree(Node *node, int offset, symbols_t *s)
{
  Node *next;

  if (node == NULL)
    return NULL;

  node->param[0] = asm_simplify_tree(node->param[0], offset, s);
  node->param[1] = asm_simplify_tree(node->param[1], offset, s);
  node->param[2] = asm_simplify_tree(node->param[2], offset, s);

  switch (node->type)
  {
  case A_CMDRES:
    if ((node->param[0]->type == A_VALUE ||
         node->param[0]->type == A_FVALUE) &&
        (node->param[1]->type == A_VALUE) &&
        (node->param[2] == NULL ||
         node->param[2]->type == A_VALUE ||
         node->param[2]->type == A_FVALUE))
    {
      int i;
      Node *last = NULL;
      Node *head = NULL;

      for (i = 0; i < node->param[1]->value; i++)
      {
        Node *tmp = node->param[0];

        while (tmp != NULL)
        {
          Node *n = makeNode(tmp->type);
          n->value = tmp->value;
          n->fvalue = tmp->fvalue;
          n->line_no = tmp->line_no;

          if (head == NULL)
          {
            head = n;
            last = n;
          }
          else
          {
            last->next = n;
            last = n;
          }
          tmp = tmp->next;
        }
      }

      if (last)
        last->next = node->param[2];
      node->param[2] = NULL;

      asm_delete_tree(node);

      return head;
    }
    break;

  case A_CMDDATA:
    if (offset >= 0 &&
        (node->param[0]->type == A_VALUE ||
         node->param[0]->type == A_FVALUE))
    {
      Node *n;
      int data_length;

      if (node->identifier != NULL)
      {
        if ((n = symbols_get(s, node->identifier)) == NULL)
        {
          n = makeNode(A_VALUE);
          n->value = offset;
          symbols_add(s, node->identifier, n);
          asm_delete_tree(n);
          changed();
        }
        else if (n->type != A_VALUE || n->value != offset)
        {
          yyerror_printf2("Symbol %s already define.\n", node->line_no, node->identifier);
          next = node->next;
          node->next = NULL;
          asm_delete_tree(node);
          return asm_simplify_tree(next, offset, s);
        }
      }

      n = node->param[0];
      data_length = node->param[1]->value;
      while (n != NULL)
      {
        offset += data_length;
        n = n->next;
      }
    }
    else
      offset = -1;
    break;

  case A_CMDEQU:
    if (node->param[0]->type == A_VALUE)
    {
      Node *n = symbols_get(s, node->identifier);
      if (n == NULL)
      {
        symbols_add(s, node->identifier, node->param[0]);
        changed();
      }
      else
      {
        yyerror_printf2(" Symbol %s already define.\n", node->line_no, node->identifier);
      }
      next = node->next;
      node->next = NULL;
      asm_delete_tree(node);

      return asm_simplify_tree(next, offset, s);
    }
    break;

  case A_CMDORG:
    offset = -1;
    if (node->param[0]->type == A_VALUE)
    {
      offset = node->param[0]->value;
    }
    break;

  case A_OPADD:
    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_VALUE);
      n->value = node->param[0]->value + node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue + node->param[1]->fvalue;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue + node->param[1]->value;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->line_no = node->line_no;
      n->fvalue = node->param[0]->value + node->param[1]->fvalue;
      asm_delete_tree(node);
      changed();
      return n;
    }
    break;

  case A_OPSUB:
    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_VALUE);
      n->value = node->param[0]->value - node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue - node->param[1]->fvalue;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue - node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->value - node->param[1]->fvalue;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }
    break;

  case A_OPMUL:
    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_VALUE);
      n->value = node->param[0]->value * node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue * node->param[1]->fvalue;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue * node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->value * node->param[1]->fvalue;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }
    break;

  case A_OPDIV:
    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_VALUE);
      n->value = node->param[0]->value / node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue / node->param[1]->fvalue;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_FVALUE &&
        node->param[1]->type == A_VALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->fvalue / node->param[1]->value;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }

    if (node->param[0]->type == A_VALUE &&
        node->param[1]->type == A_FVALUE)
    {
      Node *n = makeNode(A_FVALUE);
      n->fvalue = node->param[0]->value / node->param[1]->fvalue;
      n->line_no = node->line_no;
      asm_delete_tree(node);
      changed();
      return n;
    }
    break;

  case A_LABEL:
    if (offset >= 0)
    {
      Node *n;

      n = symbols_get(s, node->identifier);
      if (n == NULL)
      {
        n = makeNode(A_VALUE);
        n->value = offset;
        symbols_add(s, node->identifier, n);
        asm_delete_tree(n);
        changed();
      }
      else
      {
        yyerror_printf2("Symbol %s already define.\n", node->line_no, node->identifier);
      }

      next = node->next;
      node->next = NULL;
      asm_delete_tree(node);

      return asm_simplify_tree(next, offset, s);
    }
    break;

  case A_RREG:
    break;
  case A_FREG:
    break;
  case A_FVALUE:
    return node;
    break;
  case A_VALUE:
    return node;
    break;
  case A_IDENT:
  {
    Node *n;
    if (strcasecmp(node->identifier, "%OFFSET") == 0)
    {
      if (offset >= 0)
      {
        asm_delete_tree(node);
        node = makeNode(A_VALUE);
        node->value = offset;
        changed();
      }
      return node;
    }
    else if ((n = symbols_get(s, node->identifier)) != NULL)
    {
      asm_delete_tree(node);
      node = makeNode(n->type);
      node->fvalue = n->fvalue;
      node->value = n->value;
      changed();
      return node;
    }
  }
  break;
  case A_INSTR:
    node->next = asm_simplify_tree(node->next, ((offset >= 0) ? offset + 4 : -1), s);
    return node;
  }

  node->next = asm_simplify_tree(node->next, offset, s);
  return node;
}

Node *asm_analyse_tree(Node *node, symbols_t *s)
{
  do
  {
    asm_tree_changed = 0;
    node = asm_simplify_tree(node, 0, s);
  } while (asm_tree_changed);
  node = asm_check_tree(node, s);

  return node;
};

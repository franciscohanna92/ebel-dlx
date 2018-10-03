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
                                                                              
#ifndef __DLXTYPES_H__
#define __DLXTYPES_H__

//--- DLX Type ---//
typedef char DLX_BYTE;
typedef unsigned char DLX_UBYTE;

typedef short DLX_HALFWORD;
typedef unsigned short DLX_UHALFWORD;
typedef short DLX_SHORT;
typedef unsigned short DLX_USHORT;

typedef int DLX_WORD;
typedef unsigned int DLX_UWORD;
typedef int DLX_INT;
typedef unsigned int DLX_UINT;

typedef float DLX_FLOAT;
typedef double DLX_DOUBLE;


#define STORE_LONG_TO_BYTE( ptr, x ) ((*(ptr))= x)
#define STORE_INT_TO_BYTE( ptr, x ) ((ptr)[0]=(((x)&0xFF000000)>>24),(ptr)[1]=(((x)&0xFF0000)>>16),(ptr)[2]=(((x)&0xFF00)>>8),(ptr)[3]=((x)&0xFF))
#define STORE_WORD_TO_BYTE STORE_INT_TO_BYTE
#define STORE_SHORT_TO_BYTE( ptr, x ) ((ptr)[0]=(((x)&0xFF00)>>8),(ptr)[1]=((x)&0xFF))
#define STORE_BYTE_TO_BYTE( ptr, x ) ((ptr)[0]=((x)&0xFF))

#define STORE_FLOAT_TO_BYTE( ptr, x )  ((*((DLX_FLOAT*)ptr)) = ((DLX_FLOAT)(x)))
#define STORE_DOUBLE_TO_BYTE( ptr, x ) ((*((DLX_DOUBLE*)ptr)) = ((DLX_DOUBLE)(x)))

#define LOAD_BYTE_TO_INT( ptr )    ( ((ptr)[0]<<24) | ((ptr)[1]<<16) | ((ptr)[2]<<8) | (ptr)[3] )
#define LOAD_BYTE_TO_WORD LOAD_BYTE_TO_INT
#define LOAD_BYTE_TO_SHORT( ptr )   ( ((ptr)[0]<<8) | (ptr)[1] )
#define LOAD_BYTE_TO_BYTE( ptr )    ( (ptr)[0] )


#endif

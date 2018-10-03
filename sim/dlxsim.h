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
                                                                              
#ifndef __DLXSIM_H__
#define __DLXSIM_H__


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef SIM_DEBUG_LEVEL
#define SIM_DEBUG_LEVEL 3
#endif

#include "../lib/dlxinstset.h"
#include "../lib/dlxtypes.h"
#include "../lib/dlxdebug.h"



void sim_version();

void sim_init();
void sim_run();
void sim_done();



#endif

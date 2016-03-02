/***************************************************************************
 *   Copyright (C) 2015 by Wojciech Domski                                 *
 *   Wojciech.Domski@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef JR3API_HEADER

#define JR3API_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <rtdm/rtdm.h>
#include <xeno_config.h>
#include <analogy/analogy.h>

#include "jr3pci-devicename.h"
#include "jr3pci-ioctl.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
  char * DeviceName;

  int device;
} tjr3;

tjr3 * jr3_init(const char * nDeviceName);

int jr3_deinit(tjr3 * jr3);

int jr3_open(tjr3 * jr3);

int jr3_close(tjr3 * jr3);

int jr3_ioctl(tjr3 * jr3, int request, void * data);

#ifdef __cplusplus
}
#endif

#endif


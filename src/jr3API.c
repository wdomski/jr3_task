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

#include "jr3API.h"

tjr3 * jr3_init(const char * nDeviceName)
{
  tjr3 * jr3;

  jr3 = malloc(sizeof(tjr3));

  jr3->DeviceName = malloc(strlen(nDeviceName) + 1);
  strcpy(jr3->DeviceName, nDeviceName);

  return jr3;
}

int jr3_deinit(tjr3 * jr3) {

  free(jr3->DeviceName);

  free(jr3);

  return 0;
}

int jr3_open(tjr3 * jr3) {
  int err = 0;

  jr3->device = rt_dev_open(jr3->DeviceName, 0);
	if (jr3->device < 0) {
		err = -jr3->device;
	}

  return err;
}

int jr3_close(tjr3 * jr3) {

  int err = 0;

  err = rt_dev_close(jr3->device);

  return err;
}

int jr3_ioctl(tjr3 * jr3, int request, void * data)
{
	int err = 0;

	err = rt_dev_ioctl(jr3->device, request, data);

	return err;
}

































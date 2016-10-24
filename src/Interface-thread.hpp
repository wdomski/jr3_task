/**
 * \file Interface-thread.hpp
 *
 * \author Wojciech Domski
 *
 */

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

#ifndef INTERFACE_THREAD_HPP
#define INTERFACE_THREAD_HPP

#include <string>
#include <vector>

#include <rtt/RTT.hpp>
#include <rtt/os/main.h>
#include <rtt/os/Mutex.hpp>
#include <rtt/os/Thread.hpp>

#include "jr3API.h"

class Interface_thread: public RTT::os::Thread {
public:

	Interface_thread(int scheduler, int priority, double period,
			unsigned int cpu_affinity, std::string name);

	//one spin of measurements
	void step(void);

	//gets scale
	int getScale( void);

	//get forces
	int getForce( void);

	//get forces to a vector
	void getForce( std::vector<float> & v);

	//set filter
	void setFilter( int f);
	//set device
	void setDevice( int d);

	//reset driver
	void resetDevice(void);

	//reset offsets and gets full scale
	void resetOffsets(void);

	//reet driver with specific name
	int resetDriver(std::string Device);

	//stop driver
	int stopDriver(void);

private:

	int runLoop;

	RTT::os::Mutex mutexCard;
	RTT::os::Mutex mutexData;
	RTT::os::Mutex mutexConf;

	tjr3 * jr3;

	int err;

	int filter;
	int device;

	jr3_force_array scale;
	float force[6];
	jr3_six_axis_array force_raw;

};
#endif

/**
 * \file Interface-thread.cpp
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

#include "Interface-thread.hpp"

Interface_thread::Interface_thread(int scheduler, int priority, double period,
		unsigned int cpu_affinity, std::string name) :
		Thread(scheduler, priority, period, cpu_affinity, name), jr3(NULL),
		device(0), filter(0){

}

void Interface_thread::step(void) {
	int err;
	int td, tf;

	mutexConf.lock();
	tf = filter;
	td = device;
	mutexConf.unlock();

	/*
	 //time measure service

	 RTIME t1 = rt_timer_read();
	 */

	mutexCard.lock();
		err = jr3_ioctl(jr3, IOCTLx_JR3_FILTER(td, tf), (void *)&force_raw);

		//scale data
		for( int i = 0; i < 3; ++i)
		{
			force.f[i] = force_raw.f[i]*scale.f[i]/16384;
			force.m[i] = force_raw.m[i]*scale.m[i]/16384;
		}

	mutexCard.unlock();

	/*
	 //time measure service

	 RTIME t2 = rt_timer_read();
	 std::cout << (float) (t2 - t1) / 1000.0 << " us\n";
	 */

}

void Interface_thread::resetDevice(void)
{
	int td;

	mutexConf.lock();
	td = device;
	mutexConf.unlock();

	mutexCard.lock();
	err = jr3_ioctl(jr3, IOCTLx_JR3_RESET(td), (void *)NULL);
	mutexCard.unlock();
}

void Interface_thread::resetOffsets(void)
{
	int td;

	mutexConf.lock();
	td = device;
	mutexConf.unlock();

	mutexCard.lock();
	err = jr3_ioctl(jr3, IOCTLx_JR3_ZEROOFFS(td), (void *)NULL);
	mutexCard.unlock();
}

void Interface_thread::setFilter( int f)
{
	mutexConf.lock();
	filter = f;
	mutexConf.unlock();
}

void Interface_thread::setDevice( int d)
{
	mutexConf.lock();
	device = d;
	mutexConf.unlock();
}

int Interface_thread::resetDriver(std::string Device) {

	err = stopDriver();

	mutexCard.lock();

	if (err < 0) {
		mutexCard.unlock();
		return -1;
	}

	char * DeviceChar;

	DeviceChar = new char[Device.size()];
	strcpy(DeviceChar, Device.c_str());

	std::cout << "On device " << DeviceChar << "\n";

	jr3 = jr3_init( DeviceChar);

	delete[] DeviceChar;

	err = jr3_open(jr3);

	if (err < 0) {
		mutexCard.unlock();
		return -1;
	}

	mutexCard.unlock();

	return 0;
}

int Interface_thread::stopDriver(void) {

	mutexCard.lock();

	if (jr3) {
		err = jr3_close(jr3);

		if (err < 0) {
			mutexCard.unlock();
			return -1;
		}

		jr3_deinit(jr3);

		jr3 = NULL;
	}

	mutexCard.unlock();

	return 0;
}

void Interface_thread::getForce( std::vector<int> & v)
{
	mutexData.lock();
	for(int i = 0; i < 3; ++i)
		v.push_back(force.f[i]);
	for(int i = 0; i < 3; ++i)
		v.push_back(force.m[i]);
	mutexData.unlock();
}

/**
\author Wojciech Domski
*/

#include "jr3_task-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>

Jr3_task::Jr3_task(std::string const& name) : TaskContext(name){

	this->addOperation("prepareDriver", &Jr3_task::prepareDriver, this, RTT::OwnThread).doc(
				"Prepare driver").arg("nDevice", "Device name");

	this->addOperation("setDevice", &Jr3_task::setDevice, this, RTT::OwnThread).doc(
				"Sets device").arg("nr", "Device number 0 or 1, default 0");

	this->addOperation("setFilter", &Jr3_task::setFilter, this, RTT::OwnThread).doc(
				"Sets filter").arg("nr", "Filter number 0 to 6, default 0");

	this->addOperation("resetOffsets", &Jr3_task::resetOffsets, this, RTT::OwnThread).doc(
				"Reset offsets and retrieves full scale");

	this->ports()->addPort("ForceOutputPort", ForceOutputPort).doc(
			"Data output port (force and torque)");

	//create thread
	Interface = new Interface_thread(ORO_SCHED_RT, 10, 0.001, 1,
			"jr3Interface");

  std::cout << "Jr3_task constructed !" << std::endl;

}

bool Jr3_task::configureHook(){
  std::cout << "Jr3_task configured !" <<std::endl;
  return true;
}

bool Jr3_task::startHook(){
	Interface->start();

  std::cout << "Jr3_task started !" <<std::endl;
  return true;
}

int Jr3_task::prepareDriver(std::string nDevice) {
	Device = nDevice;

	Interface->resetDriver(nDevice);

	return 0;
}

void Jr3_task::updateHook(){
  //std::cout << "Jr3_task executes updateHook !" <<std::endl;

	std::vector <float> v;

	Interface->getForce(v);

	ForceOutputPort.write(v);
}

void Jr3_task::stopHook() {
  std::cout << "Jr3_task executes stopping !" <<std::endl;

  Interface->stop();
}

void Jr3_task::cleanupHook() {
  std::cout << "Jr3_task cleaning up !" <<std::endl;

  Interface->stopDriver();
}

void Jr3_task::setDevice( int d)
{
	Interface->setDevice(d);
}

void Jr3_task::setFilter( int f)
{
	Interface->setFilter(f);
}

void Jr3_task::resetOffsets( void)
{
	Interface->resetOffsets();
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Jr3_task)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Jr3_task)

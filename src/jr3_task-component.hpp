/**
\author Wojciech Domski
*/

#ifndef OROCOS_JR3_TASK_COMPONENT_HPP
#define OROCOS_JR3_TASK_COMPONENT_HPP

#include <rtt/RTT.hpp>

#include "Interface-thread.hpp"

#include <string>

class Jr3_task: public RTT::TaskContext {
public:
	Jr3_task(std::string const& name);
	bool configureHook();
	bool startHook();
	void updateHook();
	void stopHook();
	void cleanupHook();

	/**
	 * \brief prepare driver
	 *
	 * Prepares driver for a specific device
	 *
	 * \param[in] nDevice
	 * 						Name of a device which should be handled
	 *
	 * \return 0 for success
	 */
	int prepareDriver(std::string nDevice);

	/**
	 * \brief set filter
	 *
	 * Sets filter
	 *
	 * \param[in] f	filter number
	 */
	void setFilter(int f);

	/**
	 * \brief set device
	 *
	 * Sets device
	 *
	 * \param[in] d device number
	 */
	void setDevice(int d);

	/**
	 * \brief reset offsets
	 *
	 * Reset offsets for force and torques
	 */
	void resetOffsets( void);

	/**
	 * \brief output port with readings
	 *
	 * Vector of integers. The typical size is equal to 6.
	 * It has two triplets. The first one
	 * has measurements of force for X, Y and Z axis,
	 * while the second one has torques for X, Y and Z axis.
	 *
	 * F_x, F_y, F_z, M_x, M_y, M_z
	 */
	RTT::OutputPort<std::vector<int> > ForceOutputPort;

private:

	Interface_thread * Interface;
	std::string Device;
};
#endif

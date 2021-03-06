/*
 * Copyright  2008-2009 INRIA/SensLab
 *
 * <dev-team@senslab.info>
 *
 * This software is a set of libraries designed to develop applications
 * for the WSN430 embedded hardware platform.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */

/**
 * \file
 * \brief Pliing task header
 * \author Clément Burin des Roziers
 * \date 2009
 */

#ifndef _POLLINGTASK_H
#define _POLLINGTASK_H

void pollingTask_create(uint16_t priority);

enum powerMode {
	OFF = 0x0, BATTERY = 0x1, DC = 0x2, DIFF = 0x3
};

enum minPeriod {
	POWER_MIN_PERIOD = 5, RADIO_MIN_PERIOD = 1, SENSOR_MIN_PERIOD = 1
};

enum sensorBits {
	RSSI_BIT = 0,
	TEMPERATURE_BIT = 1,
	LUMINOSITY_BIT = 2,
	VOLTAGE_BIT = 3,
	CURRENT_BIT = 4,
	POWER_BIT = 5
};


uint16_t set_power_polling_sensors(uint8_t voltage, uint8_t current,
		uint8_t power);
uint16_t set_power_polling_period(uint16_t period);
uint16_t set_sensor_polling_sensors(uint8_t temperature, uint8_t luminosity);
uint16_t set_sensor_polling_period(uint16_t period);
uint16_t set_radio_polling(uint16_t period);
#endif

/*
 * Copyright  2008-2009 INRIA/SensTools
 *
 * <dev-team@sentools.info>
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

#ifndef _MAC_H
#define _MAC_H

/**
 * Maximum packet size. Should not exceed 60.
 */
#define MAX_PACKET_LENGTH 48

/**
 * Initialize and create the MAC task.
 * \param xSPIMutex mutex handle for preventing SPI access confusion
 * \param usPriority priority the task should run at
 */
void vCreateMacTask(xSemaphoreHandle xSPIMutex, uint16_t usPriority);

/**
 * Function to get the list of nodes.
 * \param nodeList pointer that will point to the list
 * \return the number of attached nodes
 */
uint16_t xGetAttachedNodes(uint8_t** nodeList);

/**
 * Request the MAC sublayer to send a packet to a node
 * \param dstAddr packet destination node address
 * \param pktLength the size of the packet
 * \param pkt a pointer to the packet
 * \return 1 if the packet will be sent, 0 if it won't
 */
uint16_t xSendPacketTo(uint8_t dstAddr, uint16_t pktLength, uint8_t* pkt);

/**
 * Function that should be provided outside of the 'mac' module.
 * It will be called when a packet is received.
 * \param srcAddr packet source node address
 * \param pktLength length of the packet
 * \param pkt pointer to the packet
 */
extern void vPacketReceivedFrom(uint8_t srcAddr, uint16_t pktLength, uint8_t* pkt);

#endif

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
//#include "leds.h"

#include <string.h>

#define DEBUG DEBUG_PRINT
#include "net/uip-debug.h"

#define UDP_IP_BUF   ((struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN])

#define MAX_PAYLOAD_LEN 120

static struct uip_udp_conn *server_conn;

PROCESS(udp_server_process, "UDP server process");
AUTOSTART_PROCESSES(&udp_server_process);
/*---------------------------------------------------------------------------*/
static void
tcpip_handler(void)
{
	static int seq_id;
	char buf[MAX_PAYLOAD_LEN];

	if(uip_newdata()) {
		((char *)uip_appdata)[uip_datalen()] = 0;
		PRINTF("Server received: '%s' from ", (char *)uip_appdata);
		PRINT6ADDR(&UDP_IP_BUF->srcipaddr);
		PRINTF("\n");

		uip_ipaddr_copy(&server_conn->ripaddr, &UDP_IP_BUF->srcipaddr);
		server_conn->rport = UDP_IP_BUF->srcport;



		PRINTF("Responding with message: ");
		sprintf(buf, "Hello from the server! (%d)", ++seq_id);
		PRINTF("%s\n", buf);

		uip_udp_packet_send(server_conn, buf, strlen(buf));
		/* Restore server connection to allow data from any node */
		memset(&server_conn->ripaddr, 0, sizeof(server_conn->ripaddr));
		server_conn->rport = 0;
	}
}
/*---------------------------------------------------------------------------*/
static void
print_local_addresses(void)
{
	int i;
	uint8_t state;

	PRINTF("Server IPv6 addresses: ");
	for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
		state = uip_ds6_if.addr_list[i].state;
		if(uip_ds6_if.addr_list[i].isused &&
				(state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
			PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
			PRINTF("\n");
		}
	}
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_server_process, ev, data)
{
	static struct etimer timer;

	PROCESS_BEGIN();
	PRINTF("UDP server started\n");

	//	while (1)
	//	{
	//		// we set the timer from here every time
	//		etimer_set(&timer, CLOCK_CONF_SECOND);
	//
	//		// and wait until the vent we receive is the one we're waiting for
	//		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
	//
	//		// update the LEDs
	//		leds_toggle(1);
	//	}

	// wait 3 second, in order to have the IP addresses well configured
	  etimer_set(&timer, CLOCK_CONF_SECOND*5);

	  // wait until the timer has expired
	  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

	print_local_addresses();

	server_conn = udp_new(NULL, UIP_HTONS(0), NULL);
	udp_bind(server_conn, UIP_HTONS(3000));

	PRINTF("Server listening on UDP port %u\n", UIP_HTONS(server_conn->lport));

	while(1) {
		PROCESS_YIELD();
		if(ev == tcpip_event) {
			tcpip_handler();
		}
	}

	PROCESS_END();
}
/*---------------------------------------------------------------------------*/

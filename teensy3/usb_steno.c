/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2016 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "usb_dev.h"
#include "usb_steno.h"
#include "core_pins.h" // for yield()
//#include "HardwareSerial.h"
#include <string.h> // for memcpy()

#ifdef STENO_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

// which modifier keys are currently pressed
// 1=left ctrl,	   2=left shift,   4=left alt,	  8=left gui
// 16=right ctrl, 32=right shift, 64=right alt, 128=right gui
uint8_t steno_keys[5]={0, 0, 0, 0, 0};

// the idle configuration, how often we send the report to the
// host (ms * 4) even when it hasn't changed
uint8_t stenotype_idle_config=125;

// count until idle timeout
uint8_t stenotype_idle_count=0;



void usb_stenotype_press_key(uint8_t key_index)
{
	int i;

    uint8_t key_byte = key_index / 8;
    uint8_t key_bit = key_index % 8;

    if ( !(steno_keys[key_byte] & (1 << key_bit)) )
    {
        steno_keys[key_byte] |= 1 << key_bit;
        usb_stenotype_send();
    }
}


void usb_stenotype_release_key(uint8_t key_index)
{
	int i;

    uint8_t key_byte = key_index / 8;
    uint8_t key_bit = key_index % 8;

    if ( steno_keys[key_byte] & (1 << key_bit) )
    {
        steno_keys[key_byte] &= ~(1 << key_bit);
        usb_stenotype_send();
    }
}


// Maximum number of transmit packets to queue so we don't starve other endpoints for memory
#define TX_PACKET_LIMIT 4

static uint8_t transmit_previous_timeout=0;

// When the PC isn't listening, how long do we wait before discarding data?
#define TX_TIMEOUT_MSEC 50

#if F_CPU == 240000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1600)
#elif F_CPU == 216000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1440)
#elif F_CPU == 192000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1280)
#elif F_CPU == 180000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1200)
#elif F_CPU == 168000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 1100)
#elif F_CPU == 144000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 932)
#elif F_CPU == 120000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 764)
#elif F_CPU == 96000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 596)
#elif F_CPU == 72000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 512)
#elif F_CPU == 48000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 428)
#elif F_CPU == 24000000
  #define TX_TIMEOUT (TX_TIMEOUT_MSEC * 262)
#endif


// send the contents of steno_keys
int usb_stenotype_send(void)
{
#if 0
	serial_print("Send:");
	serial_phex(keyboard_modifier_keys);
	serial_phex(keyboard_keys[0]);
	serial_phex(keyboard_keys[1]);
	serial_phex(keyboard_keys[2]);
	serial_phex(keyboard_keys[3]);
	serial_phex(keyboard_keys[4]);
	serial_phex(keyboard_keys[5]);
	serial_print("\n");
#endif
#if 1
	uint32_t wait_count=0;
	usb_packet_t *tx_packet;

	while (1) {
		if (!usb_configuration) {
			return -1;
		}
		if (usb_tx_packet_count(STENO_ENDPOINT) < TX_PACKET_LIMIT) {
			tx_packet = usb_malloc();
			if (tx_packet) break;
		}
		if (++wait_count > TX_TIMEOUT || transmit_previous_timeout) {
			transmit_previous_timeout = 1;
			return -1;
		}
		yield();
	}
	*(tx_packet->buf) = steno_keys[0];
	*(tx_packet->buf + 1) = steno_keys[1];
	*(tx_packet->buf + 2) = steno_keys[2];
	*(tx_packet->buf + 3) = steno_keys[3];
	*(tx_packet->buf + 4) = steno_keys[4];

	tx_packet->len = 5;
	usb_tx(STENO_ENDPOINT, tx_packet);
#endif
	return 0;
}




#endif // F_CPU
#endif // STENO_INTERFACE

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

#ifndef USBsteno_h_
#define USBsteno_h_

#include "usb_desc.h"

#if defined(STENO_INTERFACE)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_stenotype_press_key(uint8_t key_index);
void usb_stenotype_release_key(uint8_t key_index);
int usb_stenotype_send(void);
extern uint8_t steno_keys[5];
extern uint8_t keyboard_idle_config;
extern uint8_t keyboard_idle_count;

// key constants
extern const uint8_t STENO_RIGHT_S;
extern const uint8_t STENO_RIGHT_G;
extern const uint8_t STENO_RIGHT_B;
extern const uint8_t STENO_RIGHT_R;
extern const uint8_t STENO_LEFT_R;
extern const uint8_t STENO_LEFT_W;
extern const uint8_t STENO_LEFT_K;

extern const uint8_t STENO_RIGHT_D;
extern const uint8_t STENO_RIGHT_T;
extern const uint8_t STENO_RIGHT_L;
extern const uint8_t STENO_RIGHT_P;
extern const uint8_t STENO_RIGHT_F;
extern const uint8_t STENO_ASTERISK;

extern const uint8_t STENO_LEFT_H;
extern const uint8_t STENO_LEFT_P;
extern const uint8_t STENO_LEFT_T;
extern const uint8_t STENO_LEFT_S;
extern const uint8_t STENO_NUMBAR;

extern const uint8_t STENO_U;
extern const uint8_t STENO_E;
extern const uint8_t STENO_O;
extern const uint8_t STENO_A;
extern const uint8_t STENO_RIGHT_Z;

#ifdef __cplusplus
}
#endif



// C++ interface
#ifdef __cplusplus
#include "Stream.h"
class usb_stenotype_class
{
public:
	void begin(void) { }
	void end(void) { }
	void send_now(void) { usb_stenotype_send(); }
	void press(uint8_t key_index) { usb_stenotype_press_key(key_index); }
	void release(uint8_t key_index) { usb_stenotype_release_key(key_index); }
};

extern usb_stenotype_class Stenotype;

#endif // __cplusplus

#endif // STENO_INTERFACE

#endif // USBsteno_h_

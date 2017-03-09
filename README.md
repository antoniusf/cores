Teensy 2.0, 3.x, LC core libraries for Arduino.

The latest stable version of Teensy's core library is always available in the Teensyduino installer, at this page:

http://www.pjrc.com/teensy/td_download.html


## HID Stenotype

A quick overview of the Treal-compatible USB HID interface I added here: The full 6-byte Treal key state (i.e. what is sent over USB, as defined in https://github.com/openstenoproject/plover/blob/master/plover/machine/treal.py) is accessible via the `uint8_t steno_keys[6]` array. When this has been changed, the updated array can be sent out using `Stenotype.send()`. For convenience, the `Stenotype.press(uint8_t bit_index)` and `Stenotype.release(uint8_t bit_index)` may be used, which will resend the array automatically if necessary. Furthermore, constants like `STENO_LEFT_H`, `STENO_O` and `STENO_RIGHT_P`, are provided, such that those calls can be written like this: `Stenotype.press(STENO_LEFT_H)`. Similarly to other interfaces, `Stenotype.begin()` should be called during setup. See below for the "Hello world" example program.

Currently, these modifications will only work for the 3rd generation teensies like the teensy 3.2 or the teensy-LC. If you wish to use them, copy the changes into the `hardware/teensy/avr/cores/` folder of your arduino/teensyduino installation. To be able to use the new code from the arduino IDE, you will also need to edit the boards.txt file in the `hardware/teensy/avr` folder: Find the section for your teensy board where all the usb options are listed (`.menu.usb`). Then, copy one of the existing options (for example the lines for the USB keyboard), and replace `USB_KEYBOARD` with `USB_STENO`, as well as all instances of `keyboard` with `stenotype`. This is what I added to mine:

```
teensyLC.menu.usb.stenotype=Stenotype
teensyLC.menu.usb.stenotype.build.usbtype=USB_STENO
teensyLC.menu.usb.stenotype.fake_serial=teensy_gateway
```

Unfortunately, I do not know to which extent this file is platform independent, so I hope the solution above provides an acceptable compromise.

Once you have done this, you can select "Stenotype" as the USB Type in the arduino IDE and compile your code with it!

### Hello world example

```C
int led = 13;

void setup() {
  Stenotype.begin();
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, LOW);
  delay(5000);
  digitalWrite(led, HIGH);
  
  Stenotype.press(STENO_LEFT_H);
  Stenotype.press(STENO_E);
  Stenotype.press(STENO_RIGHT_L);
  Stenotype.press(STENO_NUMBAR);
  Stenotype.press(STENO_ASTERISK);
  
  steno_keys[1] = 0;
  steno_keys[2] = 0;
  steno_keys[4] = 0;
  Stenotype.send_now();
  

  Stenotype.press(STENO_LEFT_H);
  Stenotype.press(STENO_LEFT_R);
  Stenotype.press(STENO_O);
  
  steno_keys[0] = steno_keys[2] = steno_keys[4] = 0;
  Stenotype.send_now();
  

  Stenotype.press(STENO_LEFT_W);
  Stenotype.press(STENO_O);
  Stenotype.press(STENO_RIGHT_R);
  Stenotype.press(STENO_RIGHT_L);
  Stenotype.press(STENO_RIGHT_D);
  
  steno_keys[0] = steno_keys[1] = steno_keys[4] = 0;
  Stenotype.send_now();
  
  
  delay(60000);
}
```

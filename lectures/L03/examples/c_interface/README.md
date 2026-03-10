# Implementation of interfaces in C

Implementation of interfaces as well as concrete types (real driver and stub) in C using structs and vtables.

This example is aimed particularly at C programmers and demonstrates how interfaces can be implemented manually using structs and vtables. The purpose is to provide an understanding of how the C++ compiler implements virtual functions "under the hood".

The implementation is written for compilation on an ATmega328P in Microchip Studio.

## Files
* [driver/gpio/interface.h](./include/driver/gpio/interface.h): 
    * Contains the interface `gpio_interface_t`, a struct with a pointer to a vtable.
* [driver/gpio/atmega328p.h](./include/driver/gpio/atmega328p.h): 
    * Constructor function that creates a GPIO interface based on an ATmega328p driver.
    * The corresponding implementation can be found [here](./source/driver/gpio/atmega328p.c).
* [driver/gpio/stub.h](./include/driver/gpio/stub.h): 
    * Constructor function that creates a GPIO interface based on a stub driver.
    * The corresponding implementation can be found [here](./source/driver/gpio/stub.c).
* [main.c](./main.c): 
    * Toggles an LED connected to the ATmega328p via a simulated push button.

---

# Demonstration of an interface in C++
Demonstration of an interface `driver::led::Interface`, which is used to easily work with
different types of LEDs, for example LEDs from different processors, via subclasses.

## Files
* [driver/led/interface.h](./include/driver/led/interface.h) constitutes the interface itself in the form of the base class `driver::led::Interface`.
* [driver/led/atmega328p.h](./include/driver/led/atmega328p.h) constitutes an implementation of LEDs for the processor `ATmega328P` via the subclass `driver::led::Atmega328p`:
    * The corresponding source code can be found [here](./source/driver/led/atmega328p.cpp).
* [driver/led/esp32s3.h](./include/driver/led/esp32s3.h) constitutes an implementation of LEDs for the processor `ESP32-S3` via the subclass `driver::led::Esp32s3`:
    * The corresponding source code can be found [here](./source/driver/led/esp32s3.cpp).
* In [main.cpp](./source/main.cpp), LEDs for each processor are created (via the previously mentioned subclasses) and blink at different frequencies:
    * This is achieved through a shared blink function that expects a reference to an LED interface (`driver::led::Interface`). 
    * Since both subclasses inherit `driver::led::Interface`, this works perfectly.

## Compiling and running the program
Compile and run the program with the following command (in this directory):


```bash
make
```

You can also build the program without running it afterwards with the following command:

```bash
make build
```

You can run the program without compiling beforehand with the following command:

```bash
make run
```

You can also remove compiled files with the following command:

```bash
make clean
```

---

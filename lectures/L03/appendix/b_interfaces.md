# Appendix B

## Interfaces in C++
An interface in C++ is an abstract base class that (normally) only contains pure virtual methods, i.e. methods that have no implementation. The purpose of an interface is to define a common set of methods that different classes can implement in their own way depending on their needs.

### Advantages of interfaces
Using interfaces has several advantages:
* **Abstraction:** You can write code that works against an abstraction rather than a concrete class. This makes it easier to replace implementations without changing the rest of the code.
* **Replaceability:** Different implementations can be used depending on the need, for example different hardware drivers or test classes.
* **Reusability:** Code that uses interfaces becomes more general and can be reused in different contexts.
* **Testability:** By using interfaces, you can easily create mock or fake classes for unit testing.

### Structure of an interface
Below the structure of an interface for timer circuits is shown. This interface is named `driver::timer::Interface`. To keep the code compact, no comments are used in this example:

```cpp
namespace driver::timer
{
class Interface
{
public:
    virtual ~Interface() noexcept = default;
    virtual void start() noexcept = 0;
    virtual void stop() noexcept = 0;
    virtual bool isRunning() const noexcept = 0;
    virtual void reset() noexcept = 0;
};
} // namespace driver::timer
```

Through the interface above, a timer can be started, stopped, and reset via the methods `start()`, `stop()`, and `reset()`. It is also possible to check whether the timer is active or not via the method `isRunning()`.

A few things to note:
* The destructor is marked as `virtual`:
    * This ensures that the correct destructor is called when an instance of a subclass is deleted through a pointer or reference to the interface.
    * This is crucial for avoiding memory leaks and for correctly cleaning up resources in both the derived class and the base class.
* The destructor is defined as `= default`:
    * This results in an empty, automatic implementation:
    * It is good practice to declare the destructor as virtual in an interface. Otherwise, objects of subclasses that are deleted through a pointer or reference to the interface may exhibit undefined behavior.
    * Since the interface has nothing to clean up, a default implementation is sufficient here.
* All methods that are meant to be overridden in subclasses are marked with `virtual` and end with `= 0`:
    * This makes them pure virtual methods without implementation in the interface.
* All virtual methods are here marked `noexcept`:
    * This forces all concrete implementations in the subclasses to not be able to throw exceptions.
    * This is advantageous in an embedded system, but if you do not want to enforce this it is fine to omit `noexcept` here.

---

### Structure of a concrete subclass
Below is an example of a concrete subclass `driver::timer::Atmega328p`, which represents a concrete implementation for timer circuits for the ATmega328p microcontroller:

```cpp
namespace driver::timer
{
class Atmega328p final : public Interface
{
public:
    // Example constructor.
    explicit Atmega328p(std::uint16_t duration_ms) noexcept;

    // Overridden methods.
    ~Atmega328p() noexcept override;
    void start() noexcept override;
    void stop() noexcept override;
    bool isRunning() const noexcept override;
    void reset() noexcept override;

    // Additional ATmega328P-specific methods (if any).

    // Deleted constructors and assignment operators.
    Atmega328p()                             = delete;
    Atmega328p(const Atmega328p&)            = delete;
    Atmega328p(Atmega328p&&)                 = delete;
    Atmega328p& operator=(const Atmega328p&) = delete;
    Atmega328p& operator=(Atmega328p&&)      = delete;

private:
    // Timer implementation details.
};
} // namespace driver::timer
```

Some things we saw earlier in the section on inheritance also appear here:
* The keyword `final` is used to ensure that the class `driver::timer::Atmega328p` cannot be inherited; this is the final implementation:
    * As a rule of thumb, this is good to do if the class is not intended to be inherited.
    * However, in some cases it may be desirable to inherit the implementation for testing, and in that case this keyword must be omitted.
* The class `driver::timer::Atmega328p` inherits the class `driver::timer::Interface` by writing `: public Interface` after the class name. Writing `public` means that everything that is public (or protected) in the interface is also public (or protected) in this derived class.

Some new things to note:
* The overridden methods are marked with `override` precisely to indicate that these are concrete implementations of overridden virtual methods.
* The destructor is also marked with `override` to clearly show that it replaces the virtual destructor in the interface. This ensures that the correct destructor is called during polymorphic destruction and helps the compiler detect possible mistakes in the signature.
* The constructor has nothing to do with the interface and is therefore neither marked `virtual` nor `override`.

### Example of using interfaces
Below an interface `driver::led::Interface` is shown. This interface should be usable for
various LEDs, for example from different microprocessors:

```cpp
/**
 * @brief LED driver interface.
 */
#pragma once

#include <cstdint>

namespace driver::led
{
/**
 * @brief LED driver interface.
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Get the pin the LED is connected to.
     * 
     * @return The pin the LED is connected to.
     */
    virtual std::uint8_t pin() const noexcept = 0;

    /**
     * @brief Check whether the LED is enabled.
     * 
     * @return True if the LED is enabled, false otherwise.
     */
    virtual bool isEnabled() const noexcept = 0;

    /**
     * @brief Enable/disable the LED.
     * 
     * @param[in] enable True if the LED is to be enabled, false otherwise.
     */
    virtual void setEnabled(bool enable) noexcept = 0;

    /**
     * @brief Toggle the LED.
     */
    virtual void toggle() noexcept = 0;
};
} // namespace driver::led
```

Below the subclass `driver::led::Atmega328p` is shown, which inherits the interface `driver::led::Interface` and is implemented to easily control LEDs connected to the ATmega328P microcontroller:

```cpp
namespace driver::led
{
/**
 * @brief LED driver for ATmega328P.
 * 
 *        This class is non-copyable and non-movable.
 */
class Atmega328p final : public Interface
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] pin The pin the LED is connected to.
     */
    explicit Atmega328p(std::uint8_t pin) noexcept;

    /**
     * @brief Destructor.
     */
    ~Atmega328p() noexcept override;

    /**
     * @brief Get the pin the LED is connected to.
     * 
     * @return The pin the LED is connected to.
     */
    std::uint8_t pin() const noexcept override;

    /**
     * @brief Check whether the LED is enabled.
     * 
     * @return True if the LED is enabled, false otherwise.
     */
    bool isEnabled() const noexcept override;

    /**
     * @brief Enable/disable the LED.
     * 
     * @param[in] enable True if the LED is to be enabled, false otherwise.
     */
    void setEnabled(bool enable) noexcept override;

    /**
     * @brief Toggle the LED.
     */
    void toggle() noexcept override;

    Atmega328p()                             = delete; // No default constructor.
    Atmega328p(const Atmega328p&)            = delete; // No copy constructor.
    Atmega328p(Atmega328p&&)                 = delete; // No move constructor.
    Atmega328p& operator=(const Atmega328p&) = delete; // No copy assignment.
    Atmega328p& operator=(Atmega328p&&)      = delete; // No move assignment.

private:
    /** The pin the LED is connected to. */
    std::uint8_t myPin;

    /** Indicate whether the LED is enabled. */
    bool myIsEnabled;
};
} // namespace driver::led
```

Genom att använda pekare eller referenser till `driver::led::Interface` kan man skriva kod som fungerar med alla underklasser. Som exempel, nedan demonstreras en funktion döpt `blinkLed()`, som används för att blinka en given LED. Notera att: 
* Ingående argument `led` utgörs av en referens till ett `driver::led::Interface`.
* Därmed kan lysdioden utgöras av en instans en godtycklig underklass.
* Exempelvis kan detta vara en instans av den tidigare demonstrerade klassen `driver::led::Atmega328p`, alternativt kan det vara en instans av klass för en lysdiod på en ESP32-S3-processor eller dylikt.

```cpp
/**
 * @brief Blink the given LED.
 * 
 * @param[in] led The LED to blink.
 * @param[in] blinkTimeMs The blink time in milliseconds.
 */
void blinkLed(driver::led::Interface& led, const std::uint16_t blinkTimeMs) noexcept
{
    // Toggle the LED, then delay the calling thread.
    led.toggle();
    std::this_thread::sleep_for(std::chrono::milliseconds(blinkTimeMs));
    
    // Toggle the LED again, then delay the calling thread.
    led.toggle();
    std::this_thread::sleep_for(std::chrono::milliseconds(blinkTimeMs));
}
```

När funktionen ovan anropas kan vi använda en av underklasserna direkt, exempelvis vår klass
`driver::led::Atmega328p`. Antag att vi har implementerat en lysdiod ansluten till pin 9 på en Arduino Uno  via en instans döpt `led1`:

```cpp
driver::led::Atmega328p led1{9U};
```

Vi kan blinka denna lysdiod med en blinktid på exempelvis `1000 ms` genom att kalla på funktionen `blinkLed()`. Eftersom `driver::led::Atmega328p` utgör en underklass till `driver::led::Interface` kan vi passera `led1` direkt:

```cpp
blinkLed(led1, 1000U);
```

Assume that we have also created a subclass `driver::led::Esp32s3` to implement LEDs for an ESP32-S3 processor, as shown below.

Note that:
* The implementation is slightly different this time; most notably, the user has the possibility to set the LED's initial state directly via a call to the constructor.
* This class also has a private method named `init()`.
* This is demonstrated to show that subclasses can be tailored according to specific needs:

```cpp
namespace driver::led
{
/**
 * @brief LED driver for ESP32-S3.
 * 
 *        This class is non-copyable and non-movable.
 */
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] pin The pin the LED is connected to.
     * @param[in] initialState Initial state of the LED (default = off).
     */
    explicit Esp32s3(std::uint8_t pin, bool initialState = false) noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override;

    /**
     * @brief Get the pin the LED is connected to.
     * 
     * @return The pin the LED is connected to.
     */
    std::uint8_t pin() const noexcept override;

    /**
     * @brief Check whether the LED is enabled.
     * 
     * @return True if the LED is enabled, false otherwise.
     */
    bool isEnabled() const noexcept override;

    /**
     * @brief Enable/disable the LED.
     * 
     * @param[in] enable True if the LED is to be enabled, false otherwise.
     */
    void setEnabled(bool enable) noexcept override;

    /**
     * @brief Toggle the LED.
     */
    void toggle() noexcept override;

    Esp32s3()                          = delete; // No default constructor.
    Esp32s3(const Esp32s3&)            = delete; // No copy constructor.
    Esp32s3(Esp32s3&&)                 = delete; // No move constructor.
    Esp32s3& operator=(const Esp32s3&) = delete; // No copy assignment.
    Esp32s3& operator=(Esp32s3&&)      = delete; // No move assignment.

private:
    /**
     * @brief Initialize the LED.
     */
    void init(bool initialState) noexcept;

    /** The pin the LED is connected to. */
    std::uint8_t myPin;

    /** Indicate whether the LED is enabled. */
    bool myIsEnabled;
};
} // namespace driver::led
```

Assume that we have implemented an LED connected to pin 20 on an ESP32-S3 processor via an instance named `led2`. We turn on the LED directly at startup:

```cpp
driver::led::Esp32s3 led2{20U, true};
```

We can also blink this LED by calling the function `blinkLed()`, since the class `driver::led::Esp32s3` is a subclass of `driver::led::Interface`. For example, to blink this LED every 500 milliseconds, the following call can be made:

```cpp
blinkLed(led2, 500U);
```

See the full example [here](../examples/cpp_interface/README.md).

See also the following [C implementation](../examples/c_interface/README.md) to understand how interfaces work "under the hood".

---
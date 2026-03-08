
# Appendix C

## Exercises
These exercises practice concepts from [Appendix B](./b_from_c_to_cpp.md).

---

## Exercise Set 1 – Default Arguments and Functions

### Exercise 1.1 – Debug Logger
Create a namespace called `debug` containing a function:

```cpp
void log(const char* message, std::uint8_t level = 0U);
```

Tasks:
1. Implement the function so it prints the message using `std::printf` from `<cstdio>`.
2. Include the log level in the output.
3. Mark the function `noexcept`.

Example usage:

```cpp
debug::log("System started");
debug::log("Sensor failure", 2U);
```

Example output:

```text
System started, log level = 0
Sensor failure, log level = 2
```

---

### Exercise 1.2 – System Delay
In the same program as in Exercise 1.1, create a function that simulates a simple software delay:

```cpp
void delay_ms(std::uint32_t ms = 1U);
```

Tasks:
1. Place the function inside namespace `system`.   
2. Mark the function `noexcept`.  
3. Inside the function, define a `constexpr` constant named `maxCount` and assign it the value `10000000UL`.  
4. Implement a delay using nested loops:
    * The outer loop should iterate `ms` times.
    * The inner loop should iterate up to `maxCount`.
    * To reduce the risk of the compiler optimizing the loop away, add a volatile dummy variable `volatile std::uint32_t dummy` inside the function and increment it inside the inner loop.
5. Use this function to simulate a software delay of `100 ms` between the debug prints in exercise 1.1.

---

## Exercise Set 2 – Struct Drivers

### Exercise 2.1 – UART Stub Driver
In a new program, create a simple UART driver:

```cpp
namespace driver
{
struct Uart
{
    const std::uint32_t baudrate;
    bool initialized;

    void init() noexcept;
    void send(std::uint8_t byte) const noexcept;
};
} // namespace driver
```

Tasks:
1. Implement the two methods:
   * `init()` shall set `initialized` to `true`.
   * `send()` shall print the given byte using `std::printf` from `<cstdio>`:
     * Only print the byte if the UART is initialized, i.e. if `initialized` is `true`.
     * Print the byte as an unsigned integer using format specifier `%u`.

2. Create a UART object:

```cpp
driver::Uart uart{9600U, false};
```

3. Try to send a few bytes before initializing the UART.  
Ensure that nothing is printed in the terminal.

4. Call `init()` and send a few bytes again.  
Ensure that the bytes are printed in the terminal.

---

### Exercise 2.2 – Sensor Driver
In the same program as in Exercise 2.1, create a simple digital sensor stub:

```cpp
namespace driver
{
struct Sensor
{
    std::int16_t value;
    bool enabled;

    void enable() noexcept;
    void disable() noexcept;
    std::int16_t read() const noexcept;
};
} // namespace driver
```

Tasks:
1. Implement the three methods:
    * `enable()` shall set `enabled` to `true`.
    * `disable()` shall set `enabled` to `false`.
    * `read()` shall return `value` if `enabled` is `true`, otherwise `0`.
2. Create a sensor instance:
    * Name the instance `tempSensor`.
    * Set the sensor value to `25`.
    * Set the sensor to disabled at startup.
3. Create a UART instance from Exercise 2.1 and initialize it so that the temperature can be printed.
4. Read the value. Ensure that the value is `0`, since the sensor is disabled.
5. Enable the sensor and read the value again. Ensure that the value is `25`.


Example output:

```text
Temperature reading 1: 0
Temperature reading 2: 25
```

---

### Exercise 2.3 – Software Timer
Create a simple timer driver:

```cpp
namespace driver
{
struct Timer
{
    const std::uint32_t timeout_ms;
    std::uint32_t counter_ms;
    bool running;

    void start() noexcept;
    void stop() noexcept;
    void toggle() noexcept;
    void tick() noexcept;
    bool timeout() noexcept;
};
} // namespace driver
```

Tasks:
1. Implement the five methods:
    * `start()` shall set `running` to `true`.
    * `stop()` shall set `running` to `false`.
    * `toggle()` shall toggle `running`.
    * `tick()` shall increment `counter_ms` if `running` is `true`, otherwise do nothing.
    * `timeout()` shall return `true` if `counter_ms >= timeout_ms`, otherwise `false`:
        * `counter_ms` shall be reset to `0` if `counter_ms >= timeout_ms`.
2. Create a timer instance:
    * Name the instance `timer`.
    * Set the timeout to `1000 ms`.
    * Initialize the internal counter to `0`.
    * Set the timer to running at startup.
3. Create a loop that runs for 5000 iterations:
    * Call `tick()` each iteration.
    * Call `timeout()` to check whether the timer has expired.
    * Print `Timeout!` using `std::printf` from `<cstdio>` whenever the timer generates a timeout.

---

## Exercise Set 3 – References

### Exercise 3.1 – Assign value
In a new program, implement the following function in an anonymous namespace:

```cpp
constexpr void assign(std::uint8_t& byte) noexcept;
```

Tasks:
1. Assign the value `0xFFU` to `byte`.
2. Test the function using:

```cpp
std::uint8_t num{};
assign(num);
std::printf("num = %u\n", static_cast<unsigned>(num));
```

Expected output:

```cpp
num = 255
```

---

### Exercise 3.2 – Swap Values
Implement the following function in the same anonymous namespace as in Exercise 3.1:

```cpp
constexpr void swap(std::uint32_t& a, std::uint32_t& b) noexcept;
```

Tasks:
1. Swap the values using a temporary variable `temp`.
2. Test the function with two variables.

Example output:

```text
Before swap: a = 3, b = 10
After swap: a = 10, b = 3
```

---

## Exercise Set 4 – Bit Manipulation Templates

### Exercise 4.1 – Clear Bit
In a new file, create a function template inside an anonymous namespace that clears a bit in a register:

```cpp
template<typename T>
constexpr void clear(T& reg, std::uint8_t bit) noexcept;
```

Tasks:
1. Use `static_assert` in combination with `std::is_integral<T>::value` from `<type_traits>` to ensure that `T` is an integral type.
2. Use the error message `Cannot perform bit operation with non-integral type!` in the `static_assert`.
3. Clear the selected bit in the register.
4. Print the result in binary using C++ I/O functionality:
    * Output stream `std::cout` from `<iostream>` for printing.
    * `std::bitset<N>` from `<bitset>` to generate a bitset representation.

Example usage:

```cpp
std::uint8_t reg{0xFFU};
clear(reg, 2U);
std::cout << "Register content: " << std::bitset<8>(reg) << "\n";
```

Expected output:

```text
Register content: 11111011
```

---

### Exercise 4.2 – Toggle Bit
Create a function template for toggling one or several bits in a register using a parameter pack in the same anonymous namespace as in Exercise 4.1:

```cpp
template<typename T, typename... Bits>
void toggle(T& reg, const Bits&... bits) noexcept;
```

Tasks:
1. Use a parameter pack.
2. Ensure the type is integral as in Exercise 4.1.
3. Iterate over the bits (for example using `{bits...}`).
4. Toggle all specified bits in the register.
5. Print the result in binary using C++ I/O functionality:
    * Output stream `std::cout` from `<iostream>` for printing.
    * `std::bitset<N>` from `<bitset>` to generate a bitset representation.

Example usage:

```cpp
std::uint8_t reg{0xFFU};
clear(reg, 2U);
toggle(reg, 0U, 2U, 4U, 6U);
std::cout << "Register content: " << std::bitset<8>(reg) << "\n";
```

Expected output:

```text
Register content: 10100101
```

---

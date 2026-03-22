/**
 * @brief Solution for exercise set 2.
 */
#include <cstdint>
#include <cstdio>

#include "driver/timer.h"

/**
 * @brief Create and run a timer instance.
 * 
 * @return Exit status (0 = success).
 */
int main()
{
    constexpr std::uint16_t timeout_ms{1000U};
    constexpr std::uint16_t iterationCount{5000U};
    driver::Timer timer{timeout_ms, true};

    // Simulate periodic timer ticks (one tick = 1 ms).
    for (std::uint16_t i{}; i < iterationCount; ++i)
    {
        timer.tick();

        // Print a message on timeout.
        if (timer.hasTimedOut())
        {
            std::printf("Timeout after %u ms!\n", timer.timeout_ms());
        }
    }
    return 0;
}

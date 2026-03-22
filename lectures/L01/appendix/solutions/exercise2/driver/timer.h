/**
 * @brief Timer driver.
 */
#pragma once

#include <cstdint>
#include <cstdio>

namespace driver
{
/**
 * @brief Timer driver.
 */
struct Timer
{
    /**
     * @brief Constructor.
     * 
     * @param[in] timeout_ms Timeout in milliseconds.
     * @param[in] initialState Initial running state (default = stopped).
     */
    Timer(const std::uint16_t timeout_ms, const bool initialState = false) noexcept
        : myTimeout_ms{timeout_ms}
        , myCounter_ms{}
        , myRunning{false}
    {
        std::printf("Creating timer!\n");
        if (initialState) { start(); }
    }

    /** 
     * @brief Destructor. 
     */
    ~Timer() noexcept
    {
        stop();
        std::printf("Destroying timer!\n");
    }

    /**
     * @brief Get the timeout in milliseconds.
     * 
     * @return The configured timeout in milliseconds.
     */
    std::uint16_t timeout_ms() const noexcept { return myTimeout_ms; }

    /**
     * @brief Check whether the timer is running.
     * 
     * @return True if the timer is running, false otherwise.
     */
    bool isRunning() const noexcept { return myRunning; }

    /**
     * @brief Start the timer.
     */
    void start() noexcept
    {
        myRunning = true;
        std::printf("Starting timer!\n");
    }

    /**
     * @brief Stop the timer.
     */
    void stop() noexcept
    {
        myRunning = false;
        std::printf("Stopping timer!\n");
    }

    /**
     * @brief Toggle the timer.
     */
    void toggle() noexcept
    {
        myRunning = !myRunning;
        const char* state{myRunning ? "running" : "stopped"};
        std::printf("Toggling timer: %s!\n", state);
    }

    /**
     * @brief Tick the timer.
     * 
     *        Advance the timer by one millisecond if it is running.
     */
    void tick() noexcept
    {
        if (myRunning) { myCounter_ms++; }
    }

    /**
     * @brief Check if the timer has timed out.
     * 
     *        Reset the internal counter when a timeout occurs.
     * 
     * @return True if the timer has timed out, false otherwise.
     */
    bool hasTimedOut() noexcept
    {
        const bool timeout{myTimeout_ms <= myCounter_ms};
        if (timeout) { myCounter_ms = 0U; }
        return timeout;
    }

private:
    /** Timeout in milliseconds. */
    const std::uint16_t myTimeout_ms;

    /** Internal tick counter. */
    std::uint16_t myCounter_ms;

    /** Indicate whether the timer is running. */
    bool myRunning;
};
} // namespace driver

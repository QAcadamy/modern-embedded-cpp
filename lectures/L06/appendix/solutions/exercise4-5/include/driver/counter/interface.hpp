/**
 * @file Counter interface.
 */
#pragma once

#include <cstdint>

namespace driver::counter
{
/**
 * @brief Counter interface.
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Check if the counter is initialized.
     *
     * @return True if initialized, false otherwise.
     */
    [[nodiscard]] virtual bool isInitialized() const noexcept = 0;

    /**
     * @brief Increment the counter by one.
     */
    virtual void increment() noexcept = 0;

    /**
     * @brief Get the current counter value.
     *
     * @return The current counter value.
     */
    [[nodiscard]] virtual std::uint32_t value() const noexcept = 0;

    /**
     * @brief Reset the counter to zero.
     */
    virtual void reset() noexcept = 0;
};
} // namespace driver::counter

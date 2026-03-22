/**
 * @brief Solution for exercise set 3.
 */
#include <cstdint>
#include <cstdio>

namespace
{
/**
 * @brief Swap values.
 * 
 * @param[in, out] a The first value.
 * @param[in, out] b The second value.
 */
constexpr void swap(std::uint32_t& a, std::uint32_t& b) noexcept
{
    const std::uint32_t temp{a};
    a = b;
    b = temp;
}
} // namespace

/**
 * @brief Swap two variables.
 * 
 *        Print the content of each variable before and after the swap.
 *
 * @return Exit status (0 = success).
 */
int main()
{
    std::uint32_t a{3U}, b{10U};
    std::printf("Before swap: a = %u, b = %u\n", a, b);
    swap(a, b);
    std::printf("After swap: a = %u, b = %u\n", a, b);
    return 0;
}

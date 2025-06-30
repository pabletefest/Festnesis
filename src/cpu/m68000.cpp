#include "cpu/m68000.hpp"

#include <bit>
#include <endian.h>

M68000::M68000() {}

auto M68000::reset() -> void {}

auto M68000::runInstruction() -> std::uint8_t {
  return std::uint8_t();
}

template<std::unsigned_integral T>
auto M68000::read(std::uint32_t address) const -> T {
  T value = T();
  
  if constexpr (std::endian::native == std::endian::little) {
    return std::byteswap(value);
  }

  return value;
}

template<std::unsigned_integral T>
auto M68000::write(std::uint32_t address, T value) -> void {
  if constexpr (std::endian::native == std::endian::little) {
    std::byteswap(value);
  }
}

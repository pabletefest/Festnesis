#pragma once

#include "m68000_regs.hpp"
#include <concepts>

class M68000 {
public:
  M68000();
  ~M68000() = default;

  auto reset() -> void;
  auto fetch() -> std::uint16_t;
  auto runInstruction() -> std::uint8_t;

  template<std::unsigned_integral T>
  auto read(std::uint32_t address) const -> T;

  template<std::unsigned_integral T>
  auto write(std::uint32_t address, T) -> void;

private:
  M68000Regs regs{};
};

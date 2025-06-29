#pragma once

#include "m68000_regs.hpp"

class M68000 {
public:
  M68000();
  ~M68000() = default;

  auto reset() -> void;
  auto runInstruction() -> std::uint8_t;

private:
  M68000Regs regs{};
};

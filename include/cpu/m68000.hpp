#pragma once

#include "common/helper_types.hpp"
#include "m68000_addressing.hpp"
#include "m68000_regs.hpp"

using namespace Festnesis;

class M68000 {
public:
  M68000();
  ~M68000() = default;

  auto reset() -> void;
  auto fetch() -> u16;
  auto runInstruction() -> u8;

  template <typename T> auto read(u32 address) const -> T;

  template <typename T> auto write(u32 address, T value) -> void;

private:
  auto getAddressingMode(u8 M, u8 Xn) -> AddressingMode;

  // Addressing modes
  auto dataRegister() -> u32;
  auto addressRegister() -> u32;
  auto address() -> u32;
  auto addressPostincrement() -> u32;
  auto addressPredecrement() -> u32;
  auto addressDisplacement() -> u32;
  auto addressIndex() -> u32;
  auto PCDisplacement() -> u32;
  auto PCIndex() -> u32;
  auto absoluteShort() -> u32;
  auto absoluteLong() -> u32;
  auto immediate() -> u32;

private:
  M68000Regs regs{};
};

#pragma once

#include "common/helper_types.hpp"

#include <array>
#include <cstdint>

class M68000Regs {
public:
  M68000Regs() = default;
  ~M68000Regs() = default;

  inline auto getDataReg(std::size_t index) -> u32 {
    return D_REGS[index];
  }
  inline auto setDataReg(std::size_t index, u32 value) -> void {
    D_REGS[index] = value;
  }

  inline auto getAddressReg(std::size_t index) -> u32 {
    return A_REGS[index];
  }
  inline auto setAddressReg(std::size_t index, u32 value) -> void {
    A_REGS[index] = value & 0x00FFFFFF; // MSB is always 0 for m68k cpu
  }

  inline auto getSP() const -> u32 { return A_REGS[7]; }
  inline auto setSP(u32 value) -> void { A_REGS[7] = value; }

  inline auto getPC() const -> u32 { return PC; }
  inline auto setPC(u32 value) -> void { PC = value; }

  inline auto getUSP() const -> u32 { return USP; }
  inline auto setUSP(u32 value) -> void { USP = value; }

  inline auto getSSP() const -> u32 { return SSP; }
  inline auto setSSP(u32 value) -> void { SSP = value; }

  inline auto getCCR() const -> u8 { return SR.CCR; }
  inline auto setCCR(u8 value) -> void { SR.CCR = value; }

  inline auto getSystemSR() const -> u8 { return SR.system; }
  inline auto setSystemSR(u8 value) -> void { SR.system = value; }

private:
  std::array<u32, 8> D_REGS{}; // Data registers
  std::array<u32, 8> A_REGS{}; // Address registers

  u32 USP{}; // User Stack Pointer
  u32 SSP{}; // Supervisor Stack Pointer

  u32 PC{}; // Program Counter

  struct StatusRegister {
    u8 CCR;    // User Byte (Low)
    u8 system; // System Byte (High)
  } SR{};
};

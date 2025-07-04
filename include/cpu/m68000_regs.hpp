#pragma once

#include <array>
#include <cstdint>

class M68000Regs {
public:
  M68000Regs() = default;
  ~M68000Regs() = default;

  inline auto getDataReg(std::size_t index) -> std::uint32_t {
    return D_REGS[index];
  }
  inline auto setDataReg(std::size_t index, std::uint32_t value) -> void {
    D_REGS[index] = value;
  }

  inline auto getAddressReg(std::size_t index) -> std::uint32_t {
    return A_REGS[index];
  }
  inline auto setAddressReg(std::size_t index, std::uint32_t value) -> void {
    A_REGS[index] = value & 0x00FFFFFF; // MSB is always 0 for m68k cpu
  }

  inline auto getSP() const -> std::uint32_t { return A_REGS[7]; }
  inline auto setSP(std::uint32_t value) -> void { A_REGS[7] = value; }

  inline auto getPC() const -> std::uint32_t { return PC; }
  inline auto setPC(std::uint32_t value) -> void { PC = value; }

  inline auto getUSP() const -> std::uint32_t { return USP; }
  inline auto setUSP(std::uint32_t value) -> void { USP = value; }

  inline auto getSSP() const -> std::uint32_t { return SSP; }
  inline auto setSSP(std::uint32_t value) -> void { SSP = value; }

  inline auto getCCR() const -> std::uint8_t { return SR.CCR; }
  inline auto setCCR(std::uint8_t value) -> void { SR.CCR = value; }

  inline auto getSystemSR() const -> std::uint8_t { return SR.system; }
  inline auto setSystemSR(std::uint8_t value) -> void { SR.system = value; }

private:
  std::array<std::uint32_t, 8> D_REGS{}; // Data registers
  std::array<std::uint32_t, 8> A_REGS{}; // Address registers

  std::uint32_t USP{}; // User Stack Pointer
  std::uint32_t SSP{}; // Supervisor Stack Pointer

  std::uint32_t PC{}; // Program Counter

  struct StatusRegister {
    std::uint8_t CCR;    // User Byte (Low)
    std::uint8_t system; // System Byte (High)
  } SR{};
};

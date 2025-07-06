#include "cpu/m68000.hpp"
#include "cpu/m68000_regs.hpp"

#include <bit>
#include <cstring>
#include <type_traits>

M68000::M68000() {}

auto M68000::reset() -> void { std::memset(&regs, 0, sizeof(M68000Regs)); }

auto M68000::fetch() -> std::uint16_t {
  std::uint16_t word = read<std::uint16_t>(regs.getPC());
  regs.setPC(regs.getPC() + 2);
  return word;
}

auto M68000::runInstruction() -> std::uint8_t { return std::uint8_t(); }

template <typename T> auto M68000::read(std::uint32_t address) const -> T {
  static_assert(std::is_unsigned_v<T> == true);

  T value = T();

  if constexpr (std::endian::native == std::endian::little) {
    return std::byteswap(value);
  }

  return value;
}

template <typename T>
auto M68000::write(std::uint32_t address, T value) -> void {
  static_assert(std::is_unsigned_v<T> == true);

  if constexpr (std::endian::native == std::endian::little) {
    std::byteswap(value);
  }
}

auto M68000::getAddressingMode(std::uint8_t M, std::uint8_t Xn)
    -> AddressingMode {

  switch (M) {
  case 0b000:
    return {"Data register", "Dn", [this]() -> u32 { return dataRegister(); }};

  case 0b001:
    return {"Address register", "An",
            [this]() -> u32 { return addressRegister(); }};

  case 0b010:
    return {"Address", "(An)", [this]() -> u32 { return address(); }};

  case 0b011:
    return {"Address with Postincrement", "(An)+", [this]() -> u32 { return addressPostincrement(); }};

  case 0b100:
    return {"Address with Predecrement", "-(An)", [this]() -> u32 { return addressPredecrement(); }};

  case 0b101:
    return {"Address with Displacement", "(d16, An)", [this]() -> u32 { return addressDisplacement(); }};

  case 0b110:
    return {"Address with Index", "(d16, An, Xn)", [this]() -> u32 { return addressIndex(); }};

  case 0b111:
    switch (Xn) {
    case 0b010:
      return {"Program Counter with Displacement", "(d16, PC)", [this]() { return PCDisplacement(); }};

    case 0b011:
      return {"Program Counter with Index", "(d16, PC, Xn)", [this]() { return PCIndex(); }};

    case 0b000:
      return {"Absolute short", "(xxx).W", [this]() { return absoluteShort(); }};

    case 0b001:
      return {"Absolute long", "(xxx).L", [this]() { return absoluteLong(); }};

    case 0b100:
      return {"Immediate", "#Imm", [this]() { return immediate(); }};
    }
  default:
    break;
  }

  // TODO: logging
  return AddressingMode();
}

auto M68000::dataRegister() -> std::uint32_t {}
auto M68000::addressRegister() -> std::uint32_t {}
auto M68000::address() -> std::uint32_t {}
auto M68000::addressPostincrement() -> std::uint32_t {}
auto M68000::addressPredecrement() -> std::uint32_t {}
auto M68000::addressDisplacement() -> std::uint32_t {}
auto M68000::addressIndex() -> std::uint32_t {}
auto M68000::PCDisplacement() -> std::uint32_t {}
auto M68000::PCIndex() -> std::uint32_t {}
auto M68000::absoluteShort() -> std::uint32_t {}
auto M68000::absoluteLong() -> std::uint32_t {}
auto M68000::immediate() -> std::uint32_t {}

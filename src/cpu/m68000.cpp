#include "cpu/m68000.hpp"
#include "cpu/m68000_regs.hpp"

#include <bit>
#include <cstring>
#include <type_traits>

M68000::M68000() {}

auto M68000::reset() -> void { std::memset(&regs, 0, sizeof(M68000Regs)); }

auto M68000::fetch() -> u16 {
  u16 word = read<u16>(regs.getPC());
  regs.setPC(regs.getPC() + 2);
  return word;
}

auto M68000::runInstruction() -> u8 { return u8(); }

template <typename T> auto M68000::read(u32 address) const -> T {
  static_assert(std::is_unsigned_v<T> == true);

  T value = T();

  if constexpr (std::endian::native == std::endian::little) {
    return std::byteswap(value);
  }

  return value;
}

template <typename T>
auto M68000::write(u32 address, T value) -> void {
  static_assert(std::is_unsigned_v<T> == true);

  if constexpr (std::endian::native == std::endian::little) {
    std::byteswap(value);
  }
}

auto M68000::getAddressingMode(u8 M, u8 Xn)
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

auto M68000::dataRegister() -> u32 {}
auto M68000::addressRegister() -> u32 {}
auto M68000::address() -> u32 {}
auto M68000::addressPostincrement() -> u32 {}
auto M68000::addressPredecrement() -> u32 {}
auto M68000::addressDisplacement() -> u32 {}
auto M68000::addressIndex() -> u32 {}
auto M68000::PCDisplacement() -> u32 {}
auto M68000::PCIndex() -> u32 {}
auto M68000::absoluteShort() -> u32 {}
auto M68000::absoluteLong() -> u32 {}
auto M68000::immediate() -> u32 {}

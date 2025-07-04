#pragma once

#include <cstdint>
#include <functional>
#include <string>

class M68000;

struct AddressingMode {
  std::string name;
  std::string format;
  std::function<std::uint32_t(M68000 &)> addressing;
};

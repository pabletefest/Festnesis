#pragma once

#include "common/helper_types.hpp"

#include <cstdint>
#include <functional>
#include <string>

namespace Festnesis {

class M68000;

struct AddressingMode {
  std::string name;
  std::string format;
  std::function<u32(void)> addressing;
};

};

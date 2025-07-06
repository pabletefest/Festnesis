#include <cstdint>
#include <memory>

namespace Festnesis {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using f32 = float;
using f64 = double;

template <class T> using Scope = std::unique_ptr<T>;

template <class T> using Ref = std::shared_ptr<T>;

template <class T> using Weak = std::weak_ptr<T>;

}; // namespace Festnesis

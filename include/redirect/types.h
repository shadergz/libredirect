#pragma once

#include <cstring>
#include <cstdint>

namespace redirect {
    using Pointer = std::uintptr_t;
    using u8 = std::uint8_t;
    using i32 = std::int32_t;
    using u32 = std::uint32_t;

    template <typename T>
    using Class = std::add_pointer_t<T>;

    auto Addr(auto&& function) {
        Pointer addr;
        std::memcpy(&addr, reinterpret_cast<void*>(&function), sizeof(addr));

        return addr;
    }
    template<typename T>
    auto MkHostPtr(auto&& object) {
        return reinterpret_cast<T>(object);
    }
    auto MkPtr(auto&& object) {
        return MkHostPtr<void*>(object);
    }
}

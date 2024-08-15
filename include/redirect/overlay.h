#pragma once
#include <string>
#include <vector>

#include <redirect/types.h>
namespace redirect {
    struct Overlay {
        std::string member;

        std::vector<u8> original;
        std::vector<u8> code;

        Pointer address;
        Pointer replace;
    };

    void writeProcessMemory(const Overlay& over);
}

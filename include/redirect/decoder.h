#pragma once

#include <ios>
#include <redirect/types.h>
namespace redirect {
    enum JmpMode {
        RelativeCall,
        Relative8BitsJump,
        Relative32BitsJump,
        JumpIfZero,
        Jcc8BitImm,
        Jcc32BitImm,
    };
    class Decoder {
        public:
        explicit Decoder(Pointer code);

        [[nodiscard]] auto instSize() const {
            return sz;
        }
    private:
        u8 opcode{};
        std::streamsize sz{};
    };
}
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

#include <redirect/api.h>
#include <redirect/decoder.h>
namespace redirect {
    RelocatableImpl::RelocatableImpl() {
        memory = std::fstream("/proc/self/mem", std::ios::in | std::ios::binary);
    }
    RelocatableImpl::~RelocatableImpl() {
        if (memory)
            memory.close();
    }

    void RelocatableImpl::placeOverlay(const Overlay& mimic) {
        if (memory.is_open()) {
            writeProcessMemory(mimic);
            return;
        }
        if (isUnprotected(mimic.address)) {
            turnPageWritable(mimic.address);
        }

        if (!empty(mimic.code))
            std::memcpy(MkPtr(mimic.address), &mimic.code[0], mimic.code.size());
        protectPage(mimic.address);
    }

    Pointer RelocatableImpl::install(const Pointer function, const Pointer replace) {
        if (function == replace)
            return {};

        Overlay mimic;
        mimic.address = function;
        mimic.replace = replace;

        const Pointer range{function + 12};
        for (Pointer text{function}; text < range; text++) {
            Decoder dec(text);
            text += dec.instSize();
        }
        placeOverlay(mimic);
        installed.push_back(mimic);

        return {};
    }

    bool RelocatableImpl::isUnprotected(Pointer target) {
        target &= cleanPage;
        for (const auto& [address] : pages) {
            if (address == target)
                return true;
        }
        return {};
    }

    void RelocatableImpl::turnPageWritable(Pointer rep) {
        rep &= cleanPage;
        void* src{};
        std::memcpy(&src, &rep, sizeof(src));
        mprotect(src, 4096, PROT_READ | PROT_WRITE | PROT_EXEC);

        pages.emplace_back(rep);
    }

    void RelocatableImpl::protectPage(Pointer pointer) {
        for (const auto& [address] : pages) {
            if (address == pointer) {
                mprotect(MkPtr(pointer), 4096, PROT_READ | PROT_WRITE);
            }
        }
    }
}

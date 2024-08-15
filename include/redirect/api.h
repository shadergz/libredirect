#pragma once
#include <fstream>
#include <vector>

#include <redirect/unprotected.h>
#include <redirect/overlay.h>
namespace redirect {
    constexpr auto cleanPage{static_cast<Pointer>(~4095)};
    class RelocatableImpl {
    public:
        RelocatableImpl();
        ~RelocatableImpl();

        void placeOverlay(const Overlay& mimic);

        Pointer install(Pointer function, Pointer replace);
        auto install(auto&& function, auto&& replace) {
            return install(Addr(function), Addr(replace));
        }

    private:
        bool isUnprotected(Pointer target);
        void turnPageWritable(Pointer rep);
        void protectPage(Pointer pointer);

        std::fstream memory;
        std::vector<Unprotected> pages;
        std::vector<Overlay> installed;
    };
}

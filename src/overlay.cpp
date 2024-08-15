#include <string>
#include <filesystem>
#include <format>
#include <unistd.h>

#include <redirect/overlay.h>
namespace redirect {
    void writeProcessMemory(const Overlay& over) {
        std::vector<char> backing(100);

        const std::filesystem::directory_iterator walker("/proc/self/fd");

        i32 descriptor{};
        for (const auto& fd : walker) {
            const auto& ioPath{fd.path().string()};

            if (!readlink(ioPath.c_str(), &backing[0], backing.size()))
                break;
            const std::string_view path{&backing[0], std::strlen(&backing[0])};

            if (path != std::format("/proc/{}/mem", getpid()))
                continue;

            std::stringstream ss;
            ss << ioPath.substr(ioPath.find_last_of('/') + 1);
            ss >> descriptor;
        }
        if (!descriptor)
            return;
        if (!empty(over.code))
            pwrite64(descriptor, &over.code[0], over.code.size(), static_cast<off64_t>(over.address));
    }
}
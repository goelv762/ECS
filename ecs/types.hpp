#pragma once
// can change to 64 if more types are needed
#include <cstdint>
using Bitmask = uint32_t;
using ID = uint32_t;

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#include <memory>
#endif


template <typename T>
inline std::string getTypeName() {
    const char* name = typeid(T).name();

#if defined(__GNUC__) || defined(__clang__)
    int status = 0;
    std::unique_ptr<char, void(*)(void*)> demangled(
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free
    );
    return (status == 0) ? demangled.get() : name;
#else
    return name; // MSVC returns readable names (windows)
#endif
}

#pragma once

/*
 * Usage:
 * class X : private foxglove::utils::NonCopyable { ... }
 */

namespace foxglove::utils {
    class NonCopyable {
    public:
        NonCopyable(const NonCopyable &other) = delete;
        NonCopyable& operator=(const NonCopyable &other) = delete;
        
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
    };
}

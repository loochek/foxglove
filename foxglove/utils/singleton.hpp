#pragma once

#include <utils/non_copyable.hpp>

/*
 * Usage:
 * class X : public foxglove::utils::Singleton<X> { ... }
 */

#include <utils/common.hpp>

namespace foxglove::utils {
    template<typename T>
    class Singleton : private NonCopyable {
    public:
        Singleton() {
            FXG_ASSERT(instance_ == nullptr);
            instance_ = static_cast<T*>(this);
        }

        static T* Instance() {
            return instance_;
        }
        
    private:
        static T* instance_;
    };

    template<typename T>
    inline T* Singleton<T>::instance_ = nullptr;
}

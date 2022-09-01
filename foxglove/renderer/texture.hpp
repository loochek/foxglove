#pragma once

#include <utils/common.hpp>
#include <utils/non_copyable.hpp>
#include <math/vector.hpp>
#include <renderer/hardware_texture.hpp>

namespace foxglove::renderer {
    class Texture : public utils::NonCopyable {
    public:
        Texture(const math::Vec2i& size);
        ~Texture() = default;

        void SetData(const void* data, int size);
        void CommitToGPU(bool generate_mipmap = true);

        int GetRawDataSize() const;

        HardwareTexture* GetHardwareTexture() const {
            return hw_texture_.get();
        }

    private:
        math::Vec2i size_;

        std::unique_ptr<uint8_t[]> raw_texture_data_;
        int raw_data_size_;

        std::unique_ptr<HardwareTexture> hw_texture_;
    };
}

#include "texture.hpp"
#include <cstring>

namespace foxglove::renderer {
    Texture::Texture(const math::Vec2i& size) : size_(size), hw_texture_(nullptr) {
        raw_texture_data_ = std::unique_ptr<uint8_t[]>(new uint8_t[GetRawDataSize()]);
    }

    void Texture::SetData(const void* data, int size) {
        int raw_size = GetRawDataSize();
        FXG_ASSERT(size == raw_size);
        memcpy(raw_texture_data_.get(), data, raw_size);
    }

    void Texture::CommitToGPU(bool generate_mipmap) {
        hw_texture_ = std::make_unique<HardwareTexture>(size_);
        hw_texture_->SetData(raw_texture_data_.get(), size_);
        hw_texture_->GenerateMipmap();
    }

    int Texture::GetRawDataSize() const {
        /// TODO: different texture formats
        return size_.x * size_.y * 3; // RGB
    }
}

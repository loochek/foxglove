#pragma once

#include <string>
#include <asset/asset.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handler_base.hpp>

namespace foxglove::renderer {
    class Shader;
}

namespace foxglove::asset {
    struct ShaderAsset : AssetBase {
        std::unique_ptr<renderer::Shader> shader;
        std::string vs_src;
        std::string fs_src;
    };

    class ShaderAssetHandler : public AssetHandlerBase<ShaderAsset> {
        friend const renderer::Shader* AssetPtr<renderer::Shader>::Access();

    public:
        ShaderAssetHandler() = default;

    private:
        virtual void Load(const std::string& name) override;
        virtual void Initialize(const std::string& name) override;

        static std::string ReadFile(const std::string& path);
    };

    template<>
    inline const renderer::Shader* AssetPtr<renderer::Shader>::Access() {
        return const_cast<const renderer::Shader*>(static_cast<ShaderAsset*>(asset_)->shader.get());
    }
}

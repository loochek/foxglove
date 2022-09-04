#pragma once

#include <string>
#include <asset/asset.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handlers/handler_base.hpp>

namespace foxglove::renderer {
    class Model;
    class Mesh;
    class Material;
}

class aiMesh;
class aiNode;
class aiScene;
class aiMaterial;

namespace foxglove::asset {
    struct ModelAsset : AssetBase {
        std::unique_ptr<renderer::Model> model;
        std::vector<std::unique_ptr<renderer::Mesh>> meshes;

        // dependencies
        std::vector<AssetPtr<renderer::Material>> materials;

        // temporary cross-state data
        std::vector<int> mesh_mtl_idxs;

        ModelAsset() = delete;
        ModelAsset(std::string name) : AssetBase(std::move(name)) {}
    };

    class ModelAssetHandler : public AssetHandlerBase<ModelAsset> {
        friend const renderer::Model* AssetPtr<renderer::Model>::Access();

    public:
        ModelAssetHandler(AssetManager& asset_mgr);

    private:
        void Load(ModelAsset& asset) override;
        void Initialize(ModelAsset& asset) override;

        static void ProcessMesh(ModelAsset& asset, std::ifstream& model_file);
    };
}

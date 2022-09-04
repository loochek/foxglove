#include "model_handler.hpp"

#include <fstream>
#include <fmt/core.h>

#include <fxg_model.hpp>
#include <math/vector.hpp>
#include <renderer/mesh.hpp>
#include <renderer/model.hpp>

namespace foxglove::asset {
    ModelAssetHandler::ModelAssetHandler(AssetManager &asset_mgr) : AssetHandlerBase(asset_mgr) {}

    void ModelAssetHandler::Load(ModelAsset &asset) {
        std::string path = fmt::format("assets/models/{}", asset.name);

        std::ifstream model_file(path, std::ios::binary);

        // Read header
        model_import::FXGModelHeader header;
        model_file.read(reinterpret_cast<char*>(&header), sizeof(header));
        if (strncmp(header.signature, "FXGMODEL", sizeof(header.signature)) != 0) {
            throw std::runtime_error(fmt::format("{} is not a valid model file", path));
        }

        // Read material table
        for (int i = 0 ; i < header.mtl_count; i++) {
            char mtl_name[model_import::MTL_NAME_LENGTH] = "";
            model_file.read(mtl_name, model_import::MTL_NAME_LENGTH);
            asset.materials.push_back(asset_mgr_.GetAsset<renderer::Material>(mtl_name, AssetState::Uninitialized));
        }

        for (int i = 0; i < header.mesh_count; i++) {
            ProcessMesh(asset, model_file);
        }

        asset.state = AssetState::Uninitialized;
    }

    void ModelAssetHandler::Initialize(ModelAsset &asset) {
        for (auto material : asset.materials) {
            asset_mgr_.Initialize(material);
        }

        asset.model = std::make_unique<renderer::Model>();
        for (int i = 0; i < asset.meshes.size(); i++) {
            auto& mesh_ptr = asset.meshes[i];
            mesh_ptr->CommitToGPU();
            asset.model->AddMesh(mesh_ptr.get(), asset.materials[asset.mesh_mtl_idxs[i]].Get());
        }

        asset.state = AssetState::ReadyToUse;
    }

    void ModelAssetHandler::ProcessMesh(ModelAsset &asset, std::ifstream &model_file) {
        // Read header
        model_import::FXGMeshHeader header;
        model_file.read(reinterpret_cast<char*>(&header), sizeof(header));
        if (strncmp(header.signature, "FXGMESH\0", sizeof(header.signature)) != 0) {
            throw std::runtime_error(fmt::format("Bad model file"));
        }

        // Read contents
        std::vector<math::Vec3f> vertices(header.vertices_count);
        model_file.read(reinterpret_cast<char*>(vertices.data()), sizeof(math::Vec3f) * header.vertices_count);

        auto mesh_ptr = std::make_unique<renderer::Mesh>(std::move(vertices));

        static_assert(sizeof(unsigned short) == 2);
        std::vector<unsigned short> indices(header.indices_count);
        model_file.read(reinterpret_cast<char*>(indices.data()), sizeof(unsigned short) * header.indices_count);

        mesh_ptr->SetIndices(std::move(indices));

        if (header.flags & model_import::FXGMESH_HAS_NORMALS) {
            std::vector<math::Vec3f> normals(header.vertices_count);
            model_file.read(reinterpret_cast<char*>(normals.data()), sizeof(math::Vec3f) * header.vertices_count);

            mesh_ptr->SetNormals(std::move(normals));
        }

        if (header.flags & model_import::FXGMESH_HAS_TEX_COORDS) {
            std::vector<math::Vec2f> tex_coords(header.vertices_count);
            model_file.read(reinterpret_cast<char*>(tex_coords.data()), sizeof(math::Vec2f) * header.vertices_count);

            mesh_ptr->SetTexCoords(std::move(tex_coords));
        }

        asset.meshes.emplace_back(std::move(mesh_ptr));
        asset.mesh_mtl_idxs.push_back(header.mtl_index);
    }

    template<>
    const renderer::Model* AssetPtr<renderer::Model>::Access() {
        return const_cast<const renderer::Model*>(static_cast<ModelAsset*>(asset_)->model.get());
    }
}
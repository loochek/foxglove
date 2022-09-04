#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <math/vector.hpp>
#include <fxg_model.hpp>

#include <json.hpp>
#include <fmt/core.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace foxglove::model_import {
    void ProcessModel(const aiScene *scene, const std::string& file_path);
    void ProcessMesh(std::ofstream& out_model, aiMesh *ai_mesh, const aiScene *scene);
    int ProcessNode(std::ofstream& out_model, aiNode *node, const aiScene *scene);
    void ProcessMaterials(std::ofstream& out_model, const aiScene *scene);
    void ImportMaterial(std::ofstream& out_model, aiMaterial *ai_material);

    void ImportModel(const std::string& file_path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(file_path, aiProcess_Triangulate);
        if (scene == nullptr || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || scene->mRootNode == nullptr) {
            throw std::runtime_error(fmt::format("Assimp error: {}", importer.GetErrorString()));
        }

        ProcessModel(scene, file_path);
    }

    void ProcessModel(const aiScene *scene, const std::string& file_path) {
        std::string model_name = fs::path(file_path).stem();
        std::string imported_path = fmt::format("assets/models/{}", model_name);
        fmt::print("Importing model {}\n", model_name);

        std::ofstream out_model(imported_path, std::ios::binary);
        // We will write header later - not enough information at the moment
        int header_pos = out_model.tellp();
        out_model.seekp(sizeof(FXGModelHeader), std::ios::cur);

        // Write materials table
        ProcessMaterials(out_model, scene);

        // Write meshes
        int mesh_count = ProcessNode(out_model, scene->mRootNode, scene);

        // Prepare and write model header now

        FXGModelHeader header;
        strncpy(header.signature, "FXGMODEL", sizeof(header.signature));
        header.mesh_count = mesh_count;
        header.mtl_count = scene->mNumMaterials;

        out_model.seekp(header_pos);
        out_model.write(reinterpret_cast<char*>(&header), sizeof(header));
        out_model.seekp(0, std::ios::end);
    }

    int ProcessNode(std::ofstream& out_model, aiNode *node, const aiScene *scene) {
        int mesh_count = 0;

        // Process all the node's meshes (if any)
        for (int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            ProcessMesh(out_model, mesh, scene);
            mesh_count++;
        }

        // Then do the same for each of its children
        for (int i = 0; i < node->mNumChildren; i++) {
            mesh_count += ProcessNode(out_model, node->mChildren[i], scene);
        }

        return mesh_count;
    }

    void ProcessMesh(std::ofstream& out_model, aiMesh *ai_mesh, const aiScene *scene) {
        if (!ai_mesh->HasPositions()) {
            throw std::runtime_error("Assimp: bad model");
        }

        fmt::print("----Importing mesh with {} vertices------\n", ai_mesh->mNumVertices);

        // We will write header later - not enough information at the moment
        int header_pos = out_model.tellp();
        out_model.seekp(sizeof(FXGMeshHeader), std::ios::cur);

        uint16_t out_mesh_flags = 0;

        std::vector<math::Vec3f> vertices;
        for (int i = 0; i < ai_mesh->mNumVertices; i++) {
            auto& vertex = ai_mesh->mVertices[i];
            vertices.emplace_back(vertex.x, vertex.y, vertex.z);
        }

        out_model.write(reinterpret_cast<char*>(vertices.data()), sizeof(math::Vec3f) * ai_mesh->mNumVertices);
        fmt::print("Wrote {} bytes of vertices\n", sizeof(math::Vec3f) * ai_mesh->mNumVertices);

        std::vector<uint16_t> indices;
        for (int i = 0; i < ai_mesh->mNumFaces; i++) {
            aiFace face = ai_mesh->mFaces[i];
            FXG_ASSERT(face.mNumIndices == 3);
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);

        }

        fmt::print("Mesh has {} indices\n", indices.size());
        out_model.write(reinterpret_cast<char*>(indices.data()), sizeof(uint16_t) * indices.size());
        fmt::print("Wrote {} bytes of indices\n", sizeof(uint16_t) * indices.size());

        if (ai_mesh->HasNormals()) {
            fmt::print("Mesh has normals\n");

            std::vector<math::Vec3f> normals;
            for (int i = 0; i < ai_mesh->mNumVertices; i++) {
                auto& normal = ai_mesh->mNormals[i];
                normals.emplace_back(normal.x, normal.y, normal.z);
            }

            out_mesh_flags |= FXGMESH_HAS_NORMALS;
            out_model.write(reinterpret_cast<char*>(normals.data()), sizeof(math::Vec3f) * ai_mesh->mNumVertices);
            fmt::print("Wrote {} bytes of normals\n", sizeof(math::Vec3f) * ai_mesh->mNumVertices);
        }

        if (ai_mesh->mTextureCoords[0]) {
            fmt::print("Mesh has tex coords\n");

            std::vector<math::Vec2f> uvs;
            for (int i = 0; i < ai_mesh->mNumVertices; i++) {
                auto& tex_coord = ai_mesh->mTextureCoords[0][i];
                uvs.emplace_back(tex_coord.x, tex_coord.y);
            }

            out_mesh_flags |= FXGMESH_HAS_TEX_COORDS;
            out_model.write(reinterpret_cast<char*>(uvs.data()), sizeof(math::Vec2f) * ai_mesh->mNumVertices);
            fmt::print("Wrote {} bytes of tex coords\n", sizeof(math::Vec2f) * ai_mesh->mNumVertices);
        }

        // prepare and write mesh header now

        fmt::print("Writing mesh header\n");

        FXGMeshHeader header;
        strncpy(header.signature, "FXGMESH\0", sizeof(header.signature));
        header.vertices_count = ai_mesh->mNumVertices;
        header.indices_count = indices.size();
        header.mtl_index = ai_mesh->mMaterialIndex;
        header.flags = out_mesh_flags;

        out_model.seekp(header_pos);
        out_model.write(reinterpret_cast<char*>(&header), sizeof(header));
        out_model.seekp(0, std::ios::end);
    }

    void ProcessMaterials(std::ofstream& out_model, const aiScene *scene) {
        for (int i = 0; i < scene->mNumMaterials; i++) {
            ImportMaterial(out_model, scene->mMaterials[i]);
        }
    }

    void ImportMaterial(std::ofstream& out_model, aiMaterial *ai_material) {
        char mtl_name[MTL_NAME_LENGTH] = "default";

        aiString ai_mtl_name;
        aiReturn ret = ai_material->Get(AI_MATKEY_NAME, ai_mtl_name);
        if (ret != AI_SUCCESS || strcmp(ai_mtl_name.C_Str(), "DefaultMaterial") == 0) {
            // use default material
            out_model.write(mtl_name, sizeof(mtl_name));
            return;
        } else {
            strncpy(mtl_name, ai_mtl_name.C_Str(), MTL_NAME_LENGTH);
            out_model.write(mtl_name, sizeof(mtl_name));
        }

        fmt::print("Importing material {}\n", mtl_name);

        // now import material
        // prepare json

        json material_json;
        material_json["shader"] = "lol";

#define SAMPLER_IMPORT(AI_TEX_TYPE, SHADER_PREFIX) \
    for (int i = 0; i < ai_material->GetTextureCount(AI_TEX_TYPE); i++) { \
        aiString texture_name; \
        ai_material->GetTexture(AI_TEX_TYPE, i, &texture_name); \
        material_json["samplers"][fmt::format(SHADER_PREFIX "{}", i)] = texture_name.C_Str(); \
    }

        SAMPLER_IMPORT(aiTextureType_DIFFUSE, "texture_diff");
        SAMPLER_IMPORT(aiTextureType_SPECULAR, "texture_spec");
        SAMPLER_IMPORT(aiTextureType_NORMALS, "texture_norm");

        float shininess = 1.0f;
        ai_material->Get(AI_MATKEY_SHININESS, shininess);
        material_json["shininess"] = shininess;

        // write material file

        std::string imported_path = fmt::format("assets/materials/{}", mtl_name);
        std::ofstream out_mtl(imported_path);
        out_mtl << material_json.dump(4);
        out_mtl.close();
    }
}

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        fmt::print("Usage: {} <model path>\n", argv[0]);
        return 0;
    }

    foxglove::model_import::ImportModel(argv[1]);
    return 0;
}
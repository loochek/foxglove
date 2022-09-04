#pragma once

#include <cstdint>
#include <type_traits>

namespace foxglove::model_import {
    struct FXGModelHeader {
        char signature[8];   // FXGMODEL
        uint16_t mesh_count;
        uint16_t mtl_count;
    };

    static_assert(sizeof(FXGModelHeader) == 12);

    constexpr int MTL_NAME_LENGTH = 64;

    // model file = FXGModelHeader + materials table + meshes

    // materials table: char[MTL_NAME_LENGTH] x mtl_count - null-terminated strings

    enum MeshFlags {
        FXGMESH_HAS_NORMALS = 1,
        FXGMESH_HAS_TEX_COORDS = 2
    };

    struct FXGMeshHeader {
        char signature[8];      // FXGMESH\0
        uint16_t vertices_count;
        uint16_t indices_count;
        uint16_t mtl_index;     // Material name (lookup index for material table)
        uint16_t flags;         // bit 0 - has normals, bit 1 - has tex coords
    };

    static_assert(sizeof(FXGMeshHeader) == 16);

    // mesh = FXGMeshHeader + raw data

    // raw data:
    // math::Vec3f x vertices_count (vertices)
    // uint16_t x indices_count (indices)
    // math::Vec3f x vertices_count (normals) - optional
    // math::Vec2f x vertices_count (tex coords) - optional
}
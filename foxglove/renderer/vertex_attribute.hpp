#pragma once

#include <vector>
#include <utils/common.hpp>

namespace foxglove::renderer {
    enum class VertexAttributeType {
        Position,
        Normal,
        TexCoord,
        Color
    };

    inline int GetVertexAttributeDim(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::TexCoord:
                return 2;

            case VertexAttributeType::Position:
            case VertexAttributeType::Normal:
            case VertexAttributeType::Color:
                return 3;

                /// TODO: FXG_ASSERT error message
            default:
                FXG_ASSERT(false && "Unknown vertex attribute type");
        }

        return 0;
    }

    inline int GetVertexAttributeSize(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::TexCoord:
                return sizeof(float) * 2;

            case VertexAttributeType::Position:
            case VertexAttributeType::Normal:
            case VertexAttributeType::Color:
                return sizeof(float) * 3;

                /// TODO: FXG_ASSERT error message
            default:
                FXG_ASSERT(false && "Unknown vertex attribute type");
        }

        return 0;
    }

    inline GLenum GetVertexAttributeGLType(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::Position:
            case VertexAttributeType::Normal:
            case VertexAttributeType::Color:
            case VertexAttributeType::TexCoord:
                return GL_FLOAT;

                /// TODO: FXG_ASSERT error message
            default:
                FXG_ASSERT(false && "Unknown vertex attribute type");
        }

        return 0;
    }

    /// Abstract base for describing how vertex data is mapped to vertex shader input
    class VertexAttributeMapping {
    public:
        VertexAttributeMapping() : attr_count_(0) {}

        int GetAttributeCount() const {
            return attr_types_.size();
        }

        VertexAttributeType GetAttributeType(int arg_num) const {
            FXG_ASSERT(arg_num <= attr_types_.size());
            return attr_types_[arg_num];
        }

        virtual int GetAttributeStride(int arg_num) const = 0;

        virtual int GetAttributeOffset(int arg_num) const = 0;

    protected:
        std::vector<VertexAttributeType> attr_types_;
        int attr_count_;
    };

    /// XYZXYZXYZ mapping, no stride/alignment
    class InterleavedAttributeMapping : public VertexAttributeMapping {
    public:
        InterleavedAttributeMapping() : one_vertex_size_(0) {}

        void AppendAttribute(VertexAttributeType type) {
            attr_types_.push_back(type);
            attr_offsets_.push_back(one_vertex_size_);

            one_vertex_size_ += GetVertexAttributeSize(type);
        }

        int GetOneVertexSize() const {
            return one_vertex_size_;
        }

        virtual int GetAttributeStride(int arg_num) const override {
            return one_vertex_size_;
        }

        virtual int GetAttributeOffset(int arg_num) const override {
            FXG_ASSERT(arg_num <= attr_offsets_.size());
            return attr_offsets_[arg_num];
        };

    protected:
        std::vector<int> attr_offsets_;
        int one_vertex_size_;
    };

    /// XXXYYYZZZ mapping, no stride/alignment
    class ContinuousAttributeMapping : public VertexAttributeMapping {
    public:
        ContinuousAttributeMapping(int vert_count) : curr_offset_(0), vert_count_(vert_count) {}

        void AppendAttribute(VertexAttributeType type) {
            attr_types_.push_back(type);

            attr_offsets_.push_back(curr_offset_);
            curr_offset_ += GetVertexAttributeSize(type) * vert_count_;
        }

        virtual int GetAttributeStride(int arg_num) const override {
            return 0;
        }

        virtual int GetAttributeOffset(int arg_num) const override {
            FXG_ASSERT(arg_num <= attr_offsets_.size());
            return attr_offsets_[arg_num];
        };

    protected:
        std::vector<int> attr_offsets_;
        int curr_offset_;
        int vert_count_;
    };
}

#pragma once

#include <engine.hpp>
#include <core/event_bus.hpp>
#include <core/events.hpp>
#include <math/3d_stuff.hpp>
#include <utils/singleton.hpp>
#include <renderer/renderer.hpp>
#include <renderer/vertex_attribute.hpp>
#include <asset/asset_manager.hpp>

namespace foxglove::ecs {
    class RenderSystem :
        public core::IEventListener<core::MainLoopRenderEvent> {
    public:
        RenderSystem() {
            renderer_ = Engine::Instance()->renderer_;
            Engine::Instance()->events_->Subscribe<core::MainLoopRenderEvent>(this);

                                   // coord
            math::Vec3f data[] = { math::Vec3f(-0.5f, -0.5f, 0.0f), 
                                   math::Vec3f(0.5f, -0.5f, 0.0f),
                                   math::Vec3f(0.0f,  0.5f, 0.0f),
                                   // color
                                   math::Vec3f(1.0f,  0.0f, 0.0f),
                                   math::Vec3f(0.0f,  1.0f, 0.0f),
                                   math::Vec3f(0.0f,  0.0f, 1.0f) };

                                    // uv
            math::Vec2f data2[] = { math::Vec2f(0.0f, 0.0f),
                                    math::Vec2f(1.0f, 0.0f),
                                    math::Vec2f(0.5f, 1.0f) };
                                   

            renderer::ContiniousAttributeMapping mapping(3);
            mapping.AppendAttribute(renderer::VertexAttributeType::FloatVec3);
            mapping.AppendAttribute(renderer::VertexAttributeType::FloatVec3);
            mapping.AppendAttribute(renderer::VertexAttributeType::FloatVec2);

            // geometry_ = new renderer::VertexData(sizeof(data) + sizeof(data2), 3);
            // geometry_->SetVertexData(data[0].RawData(), sizeof(data));
            // geometry_->SetVertexData(data2[0].RawData(), sizeof(data2), sizeof(data));
            // geometry_->SetVertexAttributeMapping(mapping);

            // math::Vec3f kek = math::Vec3f(0.6f, -0.6f, 0.0f);
            // shader->SetUniform("kek", kek);
            texture_ = Engine::Instance()->assets_->GetAsset<renderer::Texture>("wall");
            shader_ = Engine::Instance()->assets_->GetAsset<renderer::Shader>("lol");
            Engine::Instance()->assets_->Precache();
        }

        ~RenderSystem() {
            // delete geometry_;
        }

        virtual void OnEvent(const core::MainLoopRenderEvent&) override {
            renderer_->Clear();
            static float angle = 0.0f;
            angle += 0.01f;
            shader_->SetUniform("transform", math::Rotate(math::Vec3f(0.0f, 0.0f, 1.0f), angle));
            // renderer_->DrawTriangles(*geometry_, *shader);
            renderer_->SwapBuffers();
        }

    public:
        renderer::Renderer* renderer_;

        // renderer::VertexData* geometry_;

        asset::AssetPtr<renderer::Shader> shader_;
        asset::AssetPtr<renderer::Texture> texture_;
    };
};

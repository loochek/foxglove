#pragma once

#include <renderer/model.hpp>

namespace foxglove::game {
    struct ModelRendererComponent {
        const renderer::Model* model;

        ModelRendererComponent() : model(nullptr) {}
        explicit ModelRendererComponent(const renderer::Model* model) : model(model) {}
    };
}
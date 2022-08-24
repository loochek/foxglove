#include <core/application.hpp>

namespace foxglove {
    extern core::Application* CreateApplication();
}

int main() {
    foxglove::core::Application* app = foxglove::CreateApplication();
    app->Run();
    delete app;
    
    return 0;
}

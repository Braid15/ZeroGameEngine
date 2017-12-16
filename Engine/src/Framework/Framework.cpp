#include "Framework.h"

namespace ZeroEngine {

    const AFramework* ZeroFramework::_framework = nullptr;

    Tick ZeroFramework::get_ticks() {
        assert(_framework != nullptr);
        return _framework->get_current_time();
    }

    StringRepr ZeroFramework::to_string() {
        assert(_framework != nullptr);
        return _framework->to_string();
    }

    void ZeroFramework::set_framework(const AFramework* framework) {
        if (_framework == nullptr) {
            _framework = framework;
        } else {
            std::cout << "Framework is alread set. ZeroFramework::set_framework\n";
        }
    }

    IRenderer::ptr ZeroFramework::get_renderer() {
        assert(_framework != nullptr);
        return _framework->get_renderer();
    }
}
#pragma once

#include <imgui.h>
#include <string>
#include <functional>

namespace unilib {
namespace gui {

class ImGuiWrapper {
public:
    static void Init();
    static void NewFrame();
    static void Render();
    static void Shutdown();

    static void ShowDemoWindow(bool* p_open = nullptr);
    static void AddSimpleWindow(const std::string& title, std::function<void()> content);
};

} // namespace gui
} // namespace unilib
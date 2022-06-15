#pragma once
// include GUI before GLAD and GLFW
#include "external/imgui/imgui.h"

class GUI
{
public:
    GUI();
    ~GUI();

    void Init();
    void Begin();
    void End();

private:
    GUI(GUI const&) = delete;
    void operator=(GUI const&) = delete;
};

#include "InputPolling.h"
#include "GLFW/glfw3.h"
#include "src/Core/App.h"

bool Input::IsKeyPressed(KeyCode key)
{   
    auto window = App::GetInstance().GetWindow()->getGLFWwindow();
    auto state = glfwGetKey(window, static_cast<int>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(MouseCode button)
{
    auto window = App::GetInstance().GetWindow()->getGLFWwindow();
    auto state = glfwGetMouseButton(window, static_cast<int>(button));
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
    auto window = App::GetInstance().GetWindow()->getGLFWwindow();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return glm::vec2(xpos, ypos);
}

float Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Input::GetMouseY()
{
    return GetMousePosition().y;
}

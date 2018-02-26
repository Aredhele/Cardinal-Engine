#include "Rendering/CameraManager.hpp"

#include "Runtime/Rendering/Context/Window.hpp"

/// Constructor 
CameraManager::CameraManager(void) :
    m_state(EStates::Free)
{
    
}

/// Update
void CameraManager::Update(cardinal::Window * p_Window, float dt)
{
    // Change mode
    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_F1) == true)
    {
        m_state = EStates::FPS;
    }
    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_F2) == true)
    {
        m_state = EStates::Free;
    }
    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_F3) == true)
    {
        m_state = EStates::TPS;
    }
    //

    glm::tvec3<double> mouse;
    glm::tvec3<double> delta;
    glfwGetCursorPos(p_Window->GetContext(), &mouse.x, &mouse.y);

    delta = mouse - m_lastMouse;


    glm::vec2 mousePos(mouse.x, mouse.y);
    glm::vec2 windowSize(1600.0f, 900.0f);
    glm::vec2 windowCenter(windowSize.x / 2, windowSize.y / 2);

    // Block mouse
    bool bFreeMouse = false;

    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_LEFT_ALT))
    {
        bFreeMouse = true;
    }
    float maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 2.0f;

    if (glm::distance(mousePos, windowCenter) > maxMousePosRadius)
    {
        if (bFreeMouse == false)
        {
            // Re-center the mouse
            glfwSetCursorPos(p_Window->GetContext(), windowCenter.x, windowCenter.y);
            m_lastMouse.x = windowCenter.x;
            m_lastMouse.y = windowCenter.y;
        }
    }
    else
    {
        m_lastMouse.x = mousePos.x;
        m_lastMouse.y = mousePos.y;
    }
    //

    // Keyboard Inputs
    int yDirection  =  (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_UP)      == GLFW_PRESS);
    yDirection      -= (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_DOWN)    == GLFW_PRESS);

    int xDirection  =  (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_RIGHT)   == GLFW_PRESS);
    xDirection      -= (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_LEFT)    == GLFW_PRESS);
    //


    // Conditionnal move
    switch (m_state)
    {
        case EStates::Free:
        {
            m_camera->Rotate(static_cast<float>(-delta.x * m_sensitivity));
            m_camera->RotateUp(static_cast<float>(-delta.y * m_sensitivity));

            m_camera->Translate( (m_camera->GetDirection() * yDirection + m_camera->GetRight() * xDirection) * dt * m_speed );
        }break;

        case EStates::FPS:
        {
            m_camera->SetPosition(m_character->GetPosition());

            m_camera->Rotate(static_cast<float>(-delta.x * m_sensitivity));
            m_camera->RotateUp(static_cast<float>(-delta.y * m_sensitivity));

        }break;

        case EStates::TPS:
        {
            m_camera->SetPosition(m_character->GetPosition() - m_camera->GetDirection() * m_tpsRange);

            m_camera->RotateAround(static_cast<float>(-delta.x * m_sensitivity));
            m_camera->RotateUpAround(static_cast<float>(-delta.y * m_sensitivity));

        }break;


        default: break;
    }
}

/// Destructor
CameraManager::~CameraManager(void)
{

}
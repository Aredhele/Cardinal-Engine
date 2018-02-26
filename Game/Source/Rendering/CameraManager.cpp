#include "Rendering/CameraManager.hpp"

#include "Runtime/Rendering/Context/Window.hpp"

/// \brief Constructor 
CameraManager::CameraManager(void) :
    m_state(EStates::Free)
{
    
}

/// \brief Update
void CameraManager::Update(cardinal::Window * p_Window, float dt)
{
    // Change mode
    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_F1) == GLFW_PRESS)
    {
        m_state = EStates::FPS;
        m_camera->LookAt(m_character->GetPosition() + m_camera->GetDirection());
        m_camera->SetPosition(m_character->GetPosition());
    }
    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_F2) == GLFW_PRESS)
    {
        m_state = EStates::Free;
    }
    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_F3) == GLFW_PRESS)
    {
        m_state = EStates::TPS;
        m_camera->LookAt(m_character->GetPosition());
        m_camera->SetPosition(m_character->GetPosition() - m_tpsRange * m_camera->GetDirection());

    }
    //

    glm::tvec3<double> mouse;
    glm::tvec3<double> deltaMouse;
    glm::tvec3<double> deltaCharacter;
    glfwGetCursorPos(p_Window->GetContext(), &mouse.x, &mouse.y);

    deltaMouse      = mouse - m_lastMouse;
    deltaCharacter  = m_character->GetPosition() - m_lastCharacterPosition;

    glm::vec2 mousePos(mouse.x, mouse.y);
    glm::vec2 windowSize(1600.0f, 900.0f);
    glm::vec2 windowCenter(windowSize.x / 2, windowSize.y / 2);

    // Block mouse
    bool bFreeMouse = false;

    if (glfwGetKey(p_Window->GetContext(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS && m_state == EStates::Free)
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
    int yDirection  =  (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_W)       == GLFW_PRESS);
    yDirection      -= (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_S)       == GLFW_PRESS);

    int xDirection  =  (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_D)       == GLFW_PRESS);
    xDirection      -= (glfwGetKey(p_Window->GetContext(),    GLFW_KEY_A)       == GLFW_PRESS);
    //

    m_speedCoefficient = m_state == EStates::Free 
                        && glfwGetKey(p_Window->GetContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
                        ? 2.f : 1.f;

    // Conditionnal move
    switch (m_state)
    {
        case EStates::Free:
        {
            if (bFreeMouse == false)
            {
                m_camera->Rotate    (static_cast<float>(-deltaMouse.x * m_sensitivity));
                m_camera->RotateUp  (static_cast<float>(-deltaMouse.y * m_sensitivity));
            }

            m_camera->Translate( (m_camera->GetDirection() * yDirection + m_camera->GetRight() * xDirection) * dt * m_speed * m_speedCoefficient );
        }break;

        case EStates::FPS:
        {
            m_camera->Rotate    (static_cast<float>(-deltaMouse.x * m_sensitivity));
            m_camera->RotateUp  (static_cast<float>(-deltaMouse.y * m_sensitivity));

            m_camera->Translate( deltaCharacter);

        }break;

        case EStates::TPS:
        {
            m_camera->RotateAround  (static_cast<float>(-deltaMouse.x * m_sensitivity));
            m_camera->RotateUpAround(static_cast<float>(-deltaMouse.y * m_sensitivity));

            m_camera->Translate(deltaCharacter);
        }break;


        default: break;
    }

    // Keep track
    m_lastCharacterPosition = m_character->GetPosition();
}

/// \brief Destructor
CameraManager::~CameraManager(void)
{

}
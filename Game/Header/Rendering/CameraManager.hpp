#ifndef CAMERA_MANAGER_HPP
#define CAMERA_MANAGER_HPP

#include "Runtime/Rendering/Camera/Camera.hpp"
#include "Runtime/Rendering/Context/Window.hpp"
#include "Character/Character.hpp"

class CameraManager
{
    public:
        /// States
        enum class EStates
        {
            TPS,
            FPS,
            Free,
        };

        /// \brief Constructor
        CameraManager(void);

        /// \brief Update
        void Update(cardinal::Window * p_Window, float dt);

        /// \brief Set the camera
        inline void SetCamera(cardinal::Camera* p_camera)
            {m_camera = p_camera;}
        
        /// \brief Set the character
        inline void SetCharacter(const Character* p_character)
            {m_character = p_character;}
        

        /// \brief Destructor
        ~CameraManager(void);
    
    private:
        cardinal::Camera* m_camera = nullptr;   ///< The engine camera
        const Character* m_character = nullptr; ///< The game character
        
        EStates m_state;                        ///< Current mode (FPS|TPS|Free)
        bool m_isMouseFree = true;              ///< True to enable free mouse (and disable scrolling)

        
        glm::tvec3<double> m_lastMouse;         ///< Keeps mouse position in mind
        glm::vec3 m_lastCharacterPosition;      ///< Keeps character position in mind

        const float m_speed = 50.0f;            ///< The camera speed
        const float m_sensitivity = 0.002f;     ///< The mouse sensitivity
        const float m_tpsRange = 10.f;          ///< The distance from character in TPS mode
        
        float m_speedCoefficient = 2.f;         ///< In Free mode, allows to move quickly

};

#endif // CAMERA_MANAGER_HPP
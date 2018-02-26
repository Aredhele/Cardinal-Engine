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

        /// Constructor
        CameraManager(void);

        /// Update
        void Update(cardinal::Window * p_Window, float dt);

        /// Getters / Setters
        // Camera
        inline void SetCamera(cardinal::Camera* p_camera)
            {m_camera = p_camera;}
        
        // Character
        inline void SetCharacter(const Character* p_character)
            {m_character = p_character;}
        ///

        /// Destructor
        ~CameraManager(void);
    
    private:
        /// Game camera
        cardinal::Camera* m_camera = nullptr;

        /// Character
        const Character* m_character = nullptr;

        /// State
        EStates m_state;

        /// Memory
        glm::tvec3<double> m_lastMouse;

        /// Paramaters
        const float m_speed = 50.0f;
        const float m_sensitivity = 0.002f;
        const float m_tpsRange = 10.f;
};

#endif // CAMERA_MANAGER_HPP
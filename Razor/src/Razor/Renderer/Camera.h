#pragma once

#include "glm/glm.hpp"

namespace Razor
{
    /********* Orthographic Camera  ****************************/
    class OrthographicCamera
    {
    public:
        enum class ZoomDirection
        {
            ZOOM_IN = 0,
            ZOOM_OUT
        };

    public:
        OrthographicCamera(float Left, float Right, float Bottom, float Top,
            float NearClip = -1.0f, float FarClip = 1.0f);

        void SetPosition(const glm::vec3& Position);
        inline const glm::vec3& GetPosition() const
        {
            return m_Position;
        }

        void SetRotation(float Rotation);
        inline float GetRotation() const
        {
            return m_Rotation;
        }

        inline const glm::mat4& GetProjectionMatrix() const
        {
            return m_ProjectionMatrix;
        }
        inline const glm::mat4& GetViewMatrix() const
        {
            return m_ViewMatrix;
        }
        inline const glm::mat4& GetProjectionViewMatrix() const
        {
            return m_ProjectionViewMatrix;
        }

        void Zoom(ZoomDirection Direction, float ZoomAmount);

    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);

        glm::vec3 m_Position = glm::vec3(0.0f);
        float m_Rotation = 0.0f;
    };
}
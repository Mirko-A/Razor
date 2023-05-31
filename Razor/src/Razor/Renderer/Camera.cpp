#include "rzr_pch.h"

#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Razor
{
    /********* Orthographic Camera implementation *************************/
    OrthographicCamera::OrthographicCamera(float Left, float Right, float Bottom, float Top,
                                           float NearClip, float FarClip)
        : m_ProjectionMatrix(glm::ortho(Left, Right, Bottom, Top, NearClip, FarClip))
    {
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& Position)
    {
        m_Position = Position;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetRotation(float Rotation)
    {
        m_Rotation = Rotation;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::Zoom(ZoomDirection Direction, float ZoomAmount)
    {
        if (Direction == ZoomDirection::ZOOM_IN)
        {
            m_ProjectionMatrix -= ZoomAmount;
        }
        else
        {
            m_ProjectionMatrix += ZoomAmount;
        }

        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 Transform = glm::translate(glm::mat4(1.0f), 
                                             m_Position) *
                              glm::rotate(glm::mat4(1.0f), 
                                          m_Rotation, 
                                          glm::vec3(0.0f, 0.0f, 1.0f));
        
        m_ViewMatrix = glm::inverse(Transform);
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
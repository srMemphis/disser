#include "FPSCamera.h"
#include <glm/gtc/matrix_transform.hpp>

FPSCamera::FPSCamera()
{
    m_Pitch = glm::asin(m_Front.y);
    m_Yaw = glm::asin(m_Front.z / glm::cos(m_Pitch));
}

FPSCamera::FPSCamera(const glm::vec3& pos, const glm::vec3& target, float fow)
{
    m_FOV = fow;
    m_Position = pos;
    m_Front = glm::normalize(m_Position - target);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::cross(m_Right, m_Front);

    m_Pitch = glm::asin(-m_Front.y);
    m_Yaw = glm::asin(-m_Front.z / glm::cos(m_Pitch));
}

void FPSCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
{
    m_FOV = verticalFOV;
    m_Near = nearClip;
    m_Far = farClip;
}

void FPSCamera::SetPos(const glm::vec3& pos)
{
	m_Position = pos;
}

void FPSCamera::SetFOV(float fov)
{
	m_FOV = fov;
}

void FPSCamera::SetAspectRatio(float aspect)
{
    m_Aspect = aspect;
}

void FPSCamera::Turn(float dYaw, float dPitch)
{
    m_Yaw += dYaw;
    m_Pitch += dPitch;

    if (m_Pitch > glm::radians(89.0f))
        m_Pitch = glm::radians(89.0f);
    if (m_Pitch < glm::radians(-89.0f))
        m_Pitch = glm::radians(-89.0f);

    UpdateDirectionalVectors();
}

void FPSCamera::Move(float dX, float dY, float dZ)
{
    m_Position += glm::vec3(dX, dY, dZ);
}

#include <iostream>
void FPSCamera::Move(glm::vec3 dPos)
{
    m_Position += dPos;
}

const glm::vec3& FPSCamera::GetFront() const
{
    return m_Front;
}

const glm::vec3& FPSCamera::GetRight() const
{
    return m_Right;
}

const glm::vec3& FPSCamera::GetUp() const
{
    return m_Up;
}

glm::mat4 FPSCamera::GetView() const
{
    return glm::lookAt(m_Position, m_Front + m_Position, m_Up);
}

glm::mat4 FPSCamera::GetProjection() const
{
    return glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
}

glm::mat4 FPSCamera::GetVPMatrix() const
{
    return GetProjection() * GetView();
}

void FPSCamera::UpdateDirectionalVectors()
{
    glm::vec3 front(0);
    front.x = cos(m_Yaw) * cos(m_Pitch);
    front.y = sin(m_Pitch);
    front.z = sin(m_Yaw) * cos(m_Pitch);

    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

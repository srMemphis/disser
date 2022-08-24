#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    m_Pitch = glm::asin(-m_Front.y);
    m_Yaw = glm::asin(-m_Front.z / glm::cos(m_Pitch));
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& target, float fow)
{
    m_FOV = fow;
    m_Position = pos;
    m_Front = glm::normalize(m_Position - target);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::cross(m_Right, m_Front);

    m_Pitch = glm::asin(-m_Front.y);
    m_Yaw = glm::asin(-m_Front.z / glm::cos(m_Pitch));
}

void Camera::SetPerspective(float verticalFOV, float nearClip, float farClip)
{
    m_FOV = verticalFOV;
    m_Near = nearClip;
    m_Far = farClip;
}

void Camera::SetPos(const glm::vec3& pos)
{
	m_Position = pos;
}

void Camera::SetFOV(float fov)
{
	m_FOV = fov;
}

void Camera::SetAspectRatio(float aspect)
{
    m_Aspect = aspect;
}

void Camera::Turn(float dYaw, float dPitch)
{
    m_Yaw += dYaw;
    m_Pitch += dPitch;

    if (m_Pitch > glm::radians(89.0f))
        m_Pitch = glm::radians(89.0f);
    if (m_Pitch < glm::radians(-89.0f))
        m_Pitch = glm::radians(-89.0f);

    UpdateDirectionalVectors();
}

void Camera::Move(float dX, float dY, float dZ)
{
    m_Position += glm::vec3(dX, dY, dZ);
}

#include <iostream>
void Camera::Move(glm::vec3 dPos)
{
    m_Position += dPos;
}

const glm::vec3& Camera::GetFront() const
{
    return m_Front;
}

const glm::vec3& Camera::GetRight() const
{
    return m_Right;
}

const glm::vec3& Camera::GetUp() const
{
    return m_Up;
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(m_Position, m_Front + m_Position, m_Up);
}

glm::mat4 Camera::GetProjection() const
{
    return glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
}

glm::mat4 Camera::GetVPMatrix() const
{
    return GetProjection() * GetView();
}

void Camera::UpdateDirectionalVectors()
{
    glm::vec3 front;
    front.x = cos(m_Yaw) * cos(m_Pitch);
    front.y = sin(m_Pitch);
    front.z = sin(m_Yaw) * cos(m_Pitch);

    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

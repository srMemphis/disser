#include "Camera.h"

Camera::Camera()
	: m_NearClip(0.01f), m_FarClip(1000.f),
	  m_ViewWidth(16.f), m_ViewHeight(9.f),
	  m_Pos(0), m_VPMatrix(1), m_VertFOV(45.f)
{
}

void Camera::SetFOV(float_t fov)
{
	m_VertFOV = fov;
}

void Camera::SetPos(const glm::vec3& pos)
{
	m_Pos = pos;
}

void Camera::SetView(float_t width, float_t height)
{
	m_ViewWidth = width;
	m_ViewHeight = height;
}

void Camera::SetClip(float_t near, float_t far)
{
	m_NearClip = near;
	m_FarClip = far;
}

const glm::mat4& Camera::GetVPMatrix() const
{
	return m_VPMatrix;
}

float_t Camera::GetViewWidth() const
{
	return m_ViewWidth;
}

float_t Camera::GetFOV() const
{
	return m_VertFOV;
}

float_t Camera::GetViewHeight() const
{
	return m_ViewHeight;
}

const glm::vec3& Camera::GetPosition() const
{
	return m_Pos;
}

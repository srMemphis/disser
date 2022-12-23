#include "fmepch.h"
#include "MVCamera.h"
#include "external/glm/glm/gtx/quaternion.hpp"

MVCamera::MVCamera(const glm::vec3& target, float_t yaw, float_t pitch, float_t dist)
{
	m_FocalPoint = target;
	m_Distance = dist;

	m_Yaw = yaw;
	m_Pitch = pitch;

	UpdateVPMatrix();
}

void MVCamera::UpdateProjection()
{
	float_t aspectRatio = m_ViewWidth / m_ViewHeight;
	m_Projection = glm::perspective(glm::radians(m_VertFOV), aspectRatio, m_NearClip, m_FarClip);
}

void MVCamera::UpdateView()
{
	m_Pos = CalculatePosition();

	glm::quat orientation = GetOrientation();
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Pos) * glm::toMat4(orientation);
	m_ViewMatrix = glm::inverse(m_ViewMatrix);
}

void MVCamera::UpdateVPMatrix()
{
	UpdateProjection();
	UpdateView();
	m_VPMatrix = m_Projection * m_ViewMatrix;
}

glm::vec3 MVCamera::GetUpDirection() const
{
	return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 MVCamera::GetRightDirection() const
{
	return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 MVCamera::GetForwardDirection() const
{
	return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 MVCamera::CalculatePosition() const
{
	return m_FocalPoint - GetForwardDirection() * m_Distance;
}

glm::quat MVCamera::GetOrientation() const
{
	return glm::quat(glm::vec3(-m_Yaw, -m_Pitch, 0.0f));
}

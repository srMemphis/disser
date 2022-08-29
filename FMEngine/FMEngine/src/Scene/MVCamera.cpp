#include "MVCamera.h"
#include "external/glm/glm/gtx/quaternion.hpp"

MVCamera::MVCamera(const glm::vec3& position, const glm::vec3& target)
{
	m_Pos = position;
	m_FocalPoint = target;

	glm::vec3 front = glm::normalize(position - target);

	m_Pitch = glm::asin(front.y);
	m_Yaw = glm::asin(front.z / glm::cos(m_Pitch));

	glm::quat orientation = GetOrientation();
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Pos) * glm::toMat4(orientation);
	m_ViewMatrix = glm::inverse(m_ViewMatrix);

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

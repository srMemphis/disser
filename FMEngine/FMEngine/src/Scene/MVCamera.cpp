#include "MVCamera.h"

MVCamera::MVCamera()
{
	m_Pitch = glm::asin(-m_Front.y);
	m_Yaw = glm::asin(-m_Front.z / glm::cos(m_Pitch));
}

MVCamera::MVCamera(const glm::vec3& cameraPos, const glm::vec3& targetPos)
{
}

void MVCamera::UpdateVPMatrix()
{
}

void MVCamera::UpdateDirectionalVectors()
{
}

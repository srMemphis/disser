#pragma once
#include "src/Scene/Camera.h"








class MVCamera : public Camera
{
public:

	MVCamera();
	MVCamera(const glm::vec3& cameraPos, const glm::vec3& targetPos);
	~MVCamera() = default;

	virtual void UpdateVPMatrix() override;

private:
	glm::vec3 m_FocalPoint{0, 0, 0};

	glm::vec3 m_Front{ 0, 0, -1 };
	glm::vec3 m_Right{ 1, 0, 0 };
	glm::vec3 m_Up{ 0, 1, 0 };

	float m_Yaw;					// horizontal rotation
	float m_Pitch;					// vertical rotation

	const glm::vec3 m_WorldUp{ 0, 1, 0 };
private:
	void UpdateDirectionalVectors();
};

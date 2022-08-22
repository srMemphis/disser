#pragma once
#include "external/glm/glm/glm.hpp"

class Camera
{
public:

	Camera();
	Camera(const glm::vec3& pos, const glm::vec3& target, float fow);
	~Camera() = default;
	
	// Modifiers //
	void SetPos(const glm::vec3& pos);
	void SetPerspective(float verticalFOV, float nearClip, float farClip);
	void SetAspectRatio(float aspect);
	void SetFOV(float fov);

	void Turn(float dYaw, float dPitch);
	void Move(float dX, float dY, float dZ);
	void Move(glm::vec3 dPos);

	// Accessors //
	const glm::vec3& GetFront() const;
	const glm::vec3& GetRight() const;
	const glm::vec3& GetUp() const;

	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
	glm::mat4 GetVPMatrix() const;

private:
	glm::vec3 m_Position{ 0, 0, 0 };
	glm::vec3 m_Front{ 0, 0, -1 };
	glm::vec3 m_Right{ 1, 0, 0 };
	glm::vec3 m_Up{ 0, 1, 0 };

	glm::vec3 m_WorldUp{ 0, 1, 0 };

	float m_Aspect{ 16.0f / 9.0f }; // aspect ratio
	float m_FOV{ 45 };
	float m_Yaw;					// horizontal rotation
	float m_Pitch;					// vertical rotation
	float m_Far{ 0.01f };			// far clipping plane
	float m_Near{ 1000.0f };		// near clipping plane
private:
	void UpdateDirectionalVectors();
};

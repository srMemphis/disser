#pragma once
#include "src/Scene/Camera.h"

class MVCamera : public Camera
{
public:
	MVCamera() = default;
	virtual ~MVCamera() = default;
	MVCamera(const glm::vec3& position, const glm::vec3& terget);

	virtual void UpdateVPMatrix() override;

	float_t GetDistance() const { return m_Distance; }
	void SetDistance(float_t distance) { m_Distance = distance; }

	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

	glm::vec3 GetUpDirection() const;
	glm::vec3 GetRightDirection() const;
	glm::vec3 GetForwardDirection() const;
	const glm::vec3& GetPosition() const { return m_Pos; }
	glm::quat GetOrientation() const;

	const glm::vec3& GetFocalPoint() const { return m_FocalPoint; }
	void SetFocalPoint(const glm::vec3& target) { m_FocalPoint = target; };

	float_t GetPitch() const { return m_Pitch; }
	float_t GetYaw() const { return m_Yaw; }
	void SetPitch(float_t pitch) { m_Pitch = pitch; }
	void SetYaw(float_t yaw) { m_Yaw = yaw; }


private:
	void UpdateProjection();
	void UpdateView();

	glm::vec3 CalculatePosition() const;

private:
	glm::mat4 m_Projection;
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

	float_t m_Distance = 0;
	float_t m_Pitch = 0.0f, m_Yaw = 0.0f;

};

/*****************************************************************//**
 * \file   Camera.h
 * \brief  Base Camera class
 * 
 * \author user
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "external/glm/glm/glm.hpp"
#include "external/glm/glm/gtc/matrix_transform.hpp"
#include "external/glm/glm/gtx/quaternion.hpp"

class Camera
{
public:
	Camera();
	virtual ~Camera() = default;

	// Modifiers //
	void SetFOV(float_t fov);
	void SetPos(const glm::vec3& pos);
	void SetView(float_t width, float_t height);
	void SetClip(float_t near, float_t far);

	// Accessors //
	const glm::mat4& GetVPMatrix() const;
	const glm::vec3& GetPosition() const;
	float_t GetViewHeight() const;
	float_t GetViewWidth() const;
	float_t GetFOV() const;

	virtual void UpdateVPMatrix() = 0;

protected:
	float_t m_VertFOV;

	float_t m_NearClip;
	float_t m_FarClip;

	float_t m_ViewWidth;
	float_t m_ViewHeight;

	glm::vec3 m_Pos;
	glm::mat4 m_VPMatrix;
};

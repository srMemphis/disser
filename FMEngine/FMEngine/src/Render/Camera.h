#pragma once
#include "external/glm/glm/glm.hpp"

class Camera
{
public:

	Camera();
	~Camera();

	void SetView();
	void SetProjection();
	void SetFOV();

	glm::mat4 GetProjectionMatrix();

private:
	glm::mat4 m_ProjectionMatrix;

};

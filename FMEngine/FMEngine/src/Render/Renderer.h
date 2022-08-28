#include <memory>

#include "src/Render/OpenGL/OpenGLBuffer.h"
#include "src/Render/OpenGL/OpenGLContext.h"
#include "src/Render/OpenGL/OpenGLShader.h"
#include "src/Render/OpenGL/OpenGLVertexArray.h"
#include "src/Scene/FPSCamera.h"
#include "src/Render/Shader.h"

#include "src/Render/RendererAPI.h"

#include "src/Scene/Model.h"

class Renderer
{
public:
	static void Init();
	static void Shutdown();

	static void OnWindowResize(uint32_t width, uint32_t height);

	static void BeginScene(FPSCamera& camera);
	static void EndScene();

	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Model>& model, const glm::mat4& transform);

	static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
private:
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};

	static SceneData* s_SceneData;
};

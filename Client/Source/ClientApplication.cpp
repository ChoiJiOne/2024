#include "ClientApplication.h"

ClientApplication::~ClientApplication()
{
	Shutdown();
}

void ClientApplication::Setup()
{
	IGameFramework::Setup();
	clientPath_ = rootPath_ + L"Client/";

	auto clientResizeEvent = [&]() {
		int32_t width;
		int32_t height;
		window_->GetSize(width, height);
		glViewport(0, 0, width, height);
	};

	InputManager::Get().AddWindowEventAction("ClientResizeEvent",   EWindowEvent::Resize,       clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMinimize",  EWindowEvent::ExitMinimize, clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientEnterMaximize", EWindowEvent::EnterMaximize,clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMaximize",  EWindowEvent::ExitMaximize, clientResizeEvent, true);
}

void ClientApplication::Shutdown()
{
}

void ClientApplication::Run()
{
	Vector3f cameraPosition = Vector3f(0.0f, 5.0f, 5.0f);
	Vector3f pointLight = Vector3f(0.0f, 5.0f, 0.0f);
	Vector3f lightPosition;

	std::vector<StaticMesh::Vertex> vertices;
	std::vector<uint32_t> indices;

	GeometryGenerator::CreateCube(Vector3f(1.0f, 1.0f, 1.0f), vertices, indices);
	StaticMesh* cube = ResourceManager::Get().CreateResource<StaticMesh>("cube");
	cube->Initialize(vertices, indices);

	GeometryGenerator::CreateSphere(0.5f, 30, vertices, indices);
	StaticMesh* sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
	sphere->Initialize(vertices, indices);

	Shader* light = ResourceManager::Get().CreateResource<Shader>("light");
	light->Initialize(clientPath_ + L"Shader/Light.vert", clientPath_ + L"Shader/Light.frag");

	Shader* lightView = ResourceManager::Get().CreateResource<Shader>("lightView");
	lightView->Initialize(clientPath_ + L"Shader/LightView.vert", clientPath_ + L"Shader/LightView.frag");

	std::vector<Vector3f> positions = {
		Vector3f(-3.0f, +0.0f, -3.0f),
		Vector3f(-2.0f, +0.0f, -3.0f),
		Vector3f(-1.0f, +0.0f, -3.0f),
		Vector3f(+0.0f, +0.0f, -3.0f),
		Vector3f(+1.0f, +0.0f, -3.0f),
		Vector3f(+2.0f, +0.0f, -3.0f),
		Vector3f(+3.0f, +0.0f, -3.0f),

		Vector3f(-3.0f, +0.0f, -2.0f),
		Vector3f(-2.0f, +0.0f, -2.0f),
		Vector3f(-1.0f, +0.0f, -2.0f),
		Vector3f(+0.0f, +0.0f, -2.0f),
		Vector3f(+1.0f, +0.0f, -2.0f),
		Vector3f(+2.0f, +0.0f, -2.0f),
		Vector3f(+3.0f, +0.0f, -2.0f),

		Vector3f(-3.0f, +0.0f, -1.0f),
		Vector3f(-2.0f, +0.0f, -1.0f),
		Vector3f(-1.0f, +0.0f, -1.0f),
		Vector3f(+0.0f, +0.0f, -1.0f),
		Vector3f(+1.0f, +0.0f, -1.0f),
		Vector3f(+2.0f, +0.0f, -1.0f),
		Vector3f(+3.0f, +0.0f, -1.0f),

		Vector3f(-3.0f, +0.0f, +0.0f),
		Vector3f(-2.0f, +0.0f, +0.0f),
		Vector3f(-1.0f, +0.0f, +0.0f),
		Vector3f(+0.0f, +0.0f, +0.0f),
		Vector3f(+1.0f, +0.0f, +0.0f),
		Vector3f(+2.0f, +0.0f, +0.0f),
		Vector3f(+3.0f, +0.0f, +0.0f),

		Vector3f(-3.0f, +0.0f, +1.0f),
		Vector3f(-2.0f, +0.0f, +1.0f),
		Vector3f(-1.0f, +0.0f, +1.0f),
		Vector3f(+0.0f, +0.0f, +1.0f),
		Vector3f(+1.0f, +0.0f, +1.0f),
		Vector3f(+2.0f, +0.0f, +1.0f),
		Vector3f(+3.0f, +0.0f, +1.0f),

		Vector3f(-3.0f, +0.0f, +2.0f),
		Vector3f(-2.0f, +0.0f, +2.0f),
		Vector3f(-1.0f, +0.0f, +2.0f),
		Vector3f(+0.0f, +0.0f, +2.0f),
		Vector3f(+1.0f, +0.0f, +2.0f),
		Vector3f(+2.0f, +0.0f, +2.0f),
		Vector3f(+3.0f, +0.0f, +2.0f),

		Vector3f(-3.0f, +0.0f, +3.0f),
		Vector3f(-2.0f, +0.0f, +3.0f),
		Vector3f(-1.0f, +0.0f, +3.0f),
		Vector3f(+0.0f, +0.0f, +3.0f),
		Vector3f(+1.0f, +0.0f, +3.0f),
		Vector3f(+2.0f, +0.0f, +3.0f),
		Vector3f(+3.0f, +0.0f, +3.0f),
	};

	timer_.Reset();
	while (!bIsDoneLoop_)
	{
		timer_.Tick();
		InputManager::Get().Tick();

		lightPosition = Vector3f(3.0f * MathUtils::Sin(timer_.GetTotalSeconds()), 3.0f, 3.0f * MathUtils::Cos(timer_.GetTotalSeconds()));

		Matrix4x4f view = MathUtils::CreateLookAt(cameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), window_->GetAspectSize(), 0.01f, 1000.0f);
		
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		{
			light->Bind();
			light->SetUniform("view", view);
			light->SetUniform("projection", projection);
			light->SetUniform("viewPosition", cameraPosition);

			light->SetUniform("m.ambientRGB", Vector3f(0.329412f, 0.223529f, 0.027451f));
			light->SetUniform("m.diffuseRGB", Vector3f(0.780392f, 0.568627f, 0.113725f));
			light->SetUniform("m.specularRGB", Vector3f(0.992157f, 0.941176f, 0.807843f));
			light->SetUniform("m.shininess", 128.0f * 0.21794872f);
			
			light->SetUniform("directionalLight.direction", Vector3f(-1.0f, -1.0f, +0.0f));
			light->SetUniform("directionalLight.ambientRGB", Vector3f(0.2f, 0.2f, 0.2f));
			light->SetUniform("directionalLight.diffuseRGB", Vector3f(0.5f, 0.5f, 0.5f));
			light->SetUniform("directionalLight.specularRGB", Vector3f(1.0f, 1.0f, 1.0f));
			
			light->SetUniform("pointLight.position", pointLight);
			light->SetUniform("pointLight.ambientRGB", Vector3f(0.2f, 0.2f, 0.2f));
			light->SetUniform("pointLight.diffuseRGB", Vector3f(0.5f, 0.5f, 0.5f));
			light->SetUniform("pointLight.specularRGB", Vector3f(0.5f, 0.5f, 0.5f));
			light->SetUniform("pointLight.constant", 1.0f);
			light->SetUniform("pointLight.linear", 0.09f);
			light->SetUniform("pointLight.quadratic", 0.032f);

			light->SetUniform("spotLight.position", lightPosition);
			light->SetUniform("spotLight.direction", Vector3f(0.0f, -1.0f, 0.0f));
			light->SetUniform("spotLight.cutOff", MathUtils::Cos(MathUtils::ToRadian(15.0f)));
			light->SetUniform("spotLight.outerCutOff", MathUtils::Cos(MathUtils::ToRadian(30.0f)));
			light->SetUniform("spotLight.ambientRGB", Vector3f(0.2f, 0.2f, 0.2f));
			light->SetUniform("spotLight.diffuseRGB", Vector3f(0.5f, 0.5f, 0.5f));
			light->SetUniform("spotLight.specularRGB", Vector3f(0.5f, 0.5f, 0.5f));
			light->SetUniform("spotLight.constant", 1.0f);
			light->SetUniform("spotLight.linear", 0.09f);
			light->SetUniform("spotLight.quadratic", 0.032f);

			glBindVertexArray(sphere->GetVertexArrayObject());
			for (const auto& position : positions)
			{
				light->SetUniform("world", MathUtils::CreateTranslation(position));
				glDrawElements(GL_TRIANGLES, sphere->GetIndexCount(), GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);
			light->Unbind();
		}
		{
			lightView->Bind();

			lightView->SetUniform("world", MathUtils::CreateTranslation(lightPosition));
			lightView->SetUniform("view", view);
			lightView->SetUniform("projection", projection);

			glBindVertexArray(sphere->GetVertexArrayObject());
			glDrawElements(GL_TRIANGLES, sphere->GetIndexCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			lightView->Unbind();
		}

		RenderManager::Get().RenderGrid3D(view, projection, -5.0f, 5.0f, 1.0f, -5.0f, 5.0f, 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.4f));
		RenderManager::Get().EndFrame();
	}
}
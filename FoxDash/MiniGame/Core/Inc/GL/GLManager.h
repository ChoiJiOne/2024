#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glfw/glfw3.h>

#include "GL/GLResource.h"
#include "Utils/Macro.h"

/**
 * 그리기 모드입니다.
 * 참조: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
 */
enum class EDrawMode : int32_t
{
	POINTS       = 0x0000,
	LINES        = 0x0001,
	LINE_STRIP   = 0x0003,
	TRIANGLES    = 0x0004,
	TRIANGLE_FAN = 0x0006,
	NONE         = 0xFFFF,
};

/**
 * OpenGL 및 렌더링 관련 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GLManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLManager);

	/** GL 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GLManager& GetRef();

	/** GL 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GLManager* GetPtr();

	/** 프레임 렌더링을 시작합니다. */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);

	/** 프레임 렌더링을 종료합니다. */
	void EndFrame();

	/** Viewport를 설정합니다. */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

	/** OpenGL의 전역 상태 머신 설정을 수행합니다. */
	void SetVsyncMode(bool bIsEnable);
	void SetDepthMode(bool bIsEnable);
	void SetStencilMode(bool bIsEnable);
	void SetAlphaBlendMode(bool bIsEnable);
	void SetCullFaceMode(bool bIsEnable);
	
	/** 에러 코드에 대응하는 에러 메시지를 C 스타일로 얻습니다. */
	const char* GetErrorMessage(uint32_t code) const;

	/** OpenGL 리소스를 생성합니다. */
	template <typename TResource, typename... Args>
	TResource* Create(Args&&... args)
	{
		int32_t resourceID = -1;
		for (uint32_t index = 0; index < resources_.size(); ++index)
		{
			if (!resources_[index].first && !resources_[index].second)
			{
				resourceID = static_cast<int32_t>(index);
				break;
			}
		}

		if (resourceID == -1)
		{
			resourceID = resources_.size();
			resources_.push_back({ nullptr, true });
			resources_[resourceID].first = std::make_unique<TResource>(args...);
		}
		else
		{
			resources_[resourceID].second = true;
			resources_[resourceID].first = std::make_unique<TResource>(args...);
		}

		return reinterpret_cast<TResource*>(resources_[resourceID].first.get());
	}

	/** 생성한 OpenGL 리소스를 파괴합니다. */
	void Destroy(const GLResource* resource);

	/** 리소스를 GL 매니저에 등록합니다. */
	void Register(const std::string& name, GLResource* resource);

	/** 리소스 이름이 등록 되었는지 확인합니다. */
	bool IsRegistration(const std::string& name);

	/** GL 매니저에 등록을 해제합니다. */
	void Unregister(const std::string& name);

	/** 이름에 대응하는 리소스를 얻습니다. */
	template <typename TResource>
	TResource* GetByName(const std::string& name)
	{
		auto it = namedResources_.find(name);
		if (it == namedResources_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TResource*>(it->second);
	}

private:
	/** IApp에서 GL 매니저의 내부에 접근할 수 있도록 설정. */
	friend class IApp;

	/**
	 * GL 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GLManager() = default;
	virtual ~GLManager() {}

	/** GL 매니저의 초기화 및 해제는 IApp 내부에서만 수행됩니다. */
	void Startup();
	void Shutdown();

private:
	/** GL 매니저의 싱글턴 객체입니다. */
	static GLManager singleton_;

	/** 렌더링 대상이 되는 윈도우입니다. */
	GLFWwindow* renderTargetWindow_ = nullptr;

	/** 렌더링 대상이 되는 윈도우의 가로/세로 크기입니다. */
	int32_t renderTargetWindowWidth_ = 0;
	int32_t renderTargetWindowHeight_ = 0;

	/** OpenGL 에러 코드에 대응하는 에러 메시지입니다. */
	std::map<uint32_t, std::string> errorMessages_;

	/** OpenGL 리소스의 버퍼와 해당 버퍼의 현재 사용여부입니다. */
	std::vector< std::pair<std::unique_ptr<GLResource>, bool>> resources_;

	/** 이름을 가진 리소스입니다. */
	std::map<std::string, GLResource*> namedResources_;
};
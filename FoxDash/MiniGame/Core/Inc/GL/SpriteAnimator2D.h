#pragma once

#include <string>
#include <vector>

#include "GL/GLResource.h"

class TextureAtlas2D;

/**
 * 2D 스프라이트 애니메이션 리소스입니다.
 * 이 스프라이트 애니메이션 리소스는 텍스처 아틀라스 기반으로 동작합니다.
 */
class SpriteAnimator2D : public GLResource
{
public:
	/** 생성자의 인자 중 이름 목록은 애니메이션 순서와 일치하며, 이 이름은 아틀라스 요소의 이름과 동일해야 합니다. */
	SpriteAnimator2D(TextureAtlas2D* textureAtlas, std::vector<std::string>& names, float animationTime, bool bIsDuration);
	virtual ~SpriteAnimator2D();

	DISALLOW_COPY_AND_ASSIGN(SpriteAnimator2D);
	
	virtual void Release() override;

	/** 스프라이트 애니메이션을 업데이트합니다. */
	void Update(float deltaSeconds);

	/** 스프라이트 애니메이션의 프로퍼티에 대한 Getter입니다. */
	TextureAtlas2D* GetTextureAtlas() { return textureAtlas_; }
	const std::string& GetCurrentClipName() { return animationClips_.at(currentClipIndex_).name; }
	float GetTime() { return time_; }
	float GetAnimationTime() { return animationTime_; }

	/** 애니메이션의 반복 여부를 얻습니다. */
	bool IsDuration() const { return bIsDuration_; }

	/** 애니메이션의 반복 여부를 설정합니다. */
	void SetDuration(bool bIsDuration) { bIsDuration_ = bIsDuration; }

	/** 전체 상태를 초기화합니다. */
	void Reset();
	
private:
	/** 애니메이션 클립입니다. */
	struct Clip
	{
		std::string name; /** 이 이름은 아틀라스 내의 요소와 일치해야 합니다. */
		float startTime = 0.0f;
		float endTime = 0.0f;
	};

private:
	/** 스프라이트 애니메이션을 수행할 텍스처 아틀라스입니다. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** 애니메이션 클립 목록입니다. */
	std::vector<Clip> animationClips_;

	/** 현재 애니메이션된 시간입니다. */
	float time_ = 0.0f;

	/** 전체 애니메이션 시간입니다. */
	float animationTime_ = 0.0f;

	/** 현재 애니메이션 클립 인덱스입니다. */
	uint32_t currentClipIndex_ = 0;

	/** 애니메이션의 반복 여부입니다. */
	bool bIsDuration_ = false;
};
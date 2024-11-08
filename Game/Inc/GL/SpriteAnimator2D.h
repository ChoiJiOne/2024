#pragma once

#include <string>
#include <vector>

#include "GL/GLResource.h"

class TextureAtlas2D;

/**
 * 2D ��������Ʈ �ִϸ��̼� ���ҽ��Դϴ�.
 * �� ��������Ʈ �ִϸ��̼� ���ҽ��� �ؽ�ó ��Ʋ�� ������� �����մϴ�.
 */
class SpriteAnimator2D : public GLResource
{
public:
	/** �������� ���� �� �̸� ����� �ִϸ��̼� ������ ��ġ�ϸ�, �� �̸��� ��Ʋ�� ����� �̸��� �����ؾ� �մϴ�. */
	SpriteAnimator2D(TextureAtlas2D* textureAtlas, std::vector<std::string>& names, float animationTime, bool bIsDuration);
	virtual ~SpriteAnimator2D();

	DISALLOW_COPY_AND_ASSIGN(SpriteAnimator2D);
	
	virtual void Release() override;

	/** ��������Ʈ �ִϸ��̼��� ������Ʈ�մϴ�. */
	void Update(float deltaSeconds);

	/** ��������Ʈ �ִϸ��̼��� ������Ƽ�� ���� Getter�Դϴ�. */
	TextureAtlas2D* GetTextureAtlas() { return textureAtlas_; }
	const std::string& GetCurrentClipName() { return animationClips_.at(currentClipIndex_).name; }
	float GetTime() { return time_; }
	float GetAnimationTime() { return animationTime_; }

	/** �ִϸ��̼��� �ݺ� ���θ� ����ϴ�. */
	bool IsDuration() const { return bIsDuration_; }

	/** �ִϸ��̼��� �ݺ� ���θ� �����մϴ�. */
	void SetDuration(bool bIsDuration) { bIsDuration_ = bIsDuration; }

	/** ��ü ���¸� �ʱ�ȭ�մϴ�. */
	void Reset();
	
private:
	/** �ִϸ��̼� Ŭ���Դϴ�. */
	struct Clip
	{
		std::string name; /** �� �̸��� ��Ʋ�� ���� ��ҿ� ��ġ�ؾ� �մϴ�. */
		float startTime = 0.0f;
		float endTime = 0.0f;
	};

private:
	/** ��������Ʈ �ִϸ��̼��� ������ �ؽ�ó ��Ʋ���Դϴ�. */
	TextureAtlas2D* textureAtlas_ = nullptr;

	/** �ִϸ��̼� Ŭ�� ����Դϴ�. */
	std::vector<Clip> animationClips_;

	/** ���� �ִϸ��̼ǵ� �ð��Դϴ�. */
	float time_ = 0.0f;

	/** ��ü �ִϸ��̼� �ð��Դϴ�. */
	float animationTime_ = 0.0f;

	/** ���� �ִϸ��̼� Ŭ�� �ε����Դϴ�. */
	uint32_t currentClipIndex_ = 0;

	/** �ִϸ��̼��� �ݺ� �����Դϴ�. */
	bool bIsDuration_ = false;
};
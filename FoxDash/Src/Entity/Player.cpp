#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>

#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Entity/EntityManager.h"
#include "Entity/GamePlayRecorder.h"
#include "Entity/Player.h"
#include "Entity/Playground.h"
#include "Entity/UIBar.h"
#include "Entity/UICamera.h"
#include "Entity/UISkill.h"
#include "Game/GameManager.h"
#include "GL/GLManager.h"
#include "GL/SpriteAnimator2D.h"
#include "GL/TextureAtlas2D.h"
#include "GL/TTFont.h"
#include "GLFW/GLFWManager.h"
#include "Scene/GamePlayScene.h"
#include "Scene/SceneManager.h"
#include "Utils/Assertion.h"
#include "Utils/Math.h"

Player::Player()
{
	textureAtlas_ = GLManager::GetRef().GetByName<TextureAtlas2D>("TextureAtlas");
	gamePlayRecorder_ = EntityManager::GetRef().GetByName<GamePlayRecorder>("GamePlayRecorder");
	playground_ = EntityManager::GetRef().GetByName<Playground>("Playground");
	gamePlayScene_ = SceneManager::GetRef().GetByName<GamePlayScene>("GamePlayScene");
	renderBound_ = Rect2D(glm::vec2(0.0f, 0.0f), glm::vec2(66.0f, 64.0f));
	collisionBound_.radius = 22.0f;
	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

	shadow_.scale = 0.5f;
	shadow_.bound = renderBound_;
	shadow_.bound.size.y *= shadow_.scale;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
	shadow_.option.blend = glm::vec3(0.0f, 0.0f, 0.0f);
	shadow_.option.factor = 1.0f;
	shadow_.option.transparent = 0.3f;
	shadow_.option.bIsFlipV = true;

	direction_ = glm::vec2(0.0f, -1.0f);
	speed_ = GameManager::GetRef().GetConfigValue<float>("Player.speed");
	
	bIsDashing_ = false;
	dashSpeed_ = speed_;
	maxDashSpeed_ = speed_ * 3.0f;
	dashLength_ = GameManager::GetRef().GetConfigValue<float>("Player.dashLength");

	skillMpCosts_ =
	{
		{ ESkill::DASH,          GameManager::GetRef().GetConfigValue<float>("Player.dashMpCost")          },
		{ ESkill::INVINCIBILITY, GameManager::GetRef().GetConfigValue<float>("Player.invincibilityMpCost") },
	};

	LoadAnimations();
	LoadUIs();
	LoadSounds();

	invincibilityColor_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	lostHpColor_ = glm::vec4(1.0f, 0.5f, 0.1f, 1.0f);

	maxLostHpEffectCount_ = GameManager::GetRef().GetConfigValue<int32_t>("Player.maxLostHpEffectCount");
	maxLostHpEffectTime_ = GameManager::GetRef().GetConfigValue<float>("Player.maxLostHpEffectTime");

	bIsInitialized_ = true;
}

Player::~Player()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Player::Tick(float deltaSeconds)
{
	if (state_ == EState::HURT)
	{
		animations_.at(state_)->Update(deltaSeconds);
		return;
	}

	static const std::map<EKey, ESkill> KEY_SKILLS =
	{
		{ EKey::KEY_Z, ESkill::DASH          },
		{ EKey::KEY_X, ESkill::INVINCIBILITY },
	};

	GLFWManager& glfwManager = GLFWManager::GetRef();
	for (const auto& keySkill : KEY_SKILLS)
	{
		UISkill* skill = skills_.at(keySkill.second);
		if (glfwManager.GetKeyPress(keySkill.first) == EPress::PRESSED && !skill->IsRemainCoolTime())
		{
			float skillMp = skillMpCosts_.at(keySkill.second);
			float playerMp = GetMP();
			if (playerMp >= skillMp)
			{
				playerMp -= skillMp;
				SetMP(playerMp);
				skills_.at(keySkill.second)->Start();
				gamePlayRecorder_->AddRecord<int32_t>(GamePlayRecorder::ERecordType::USE_SKILL, 1);

				if (keySkill.second == ESkill::DASH)
				{
					dashSound_->Start();
					bIsDashing_ = true;
				}
			}
		}
	}

	UseDashSkill(deltaSeconds);
	LostHpEffect(deltaSeconds);

	glm::vec2 countDirection = glm::normalize(-direction_);
	float radian = GetRadianVec2(countDirection);
	float xoff = dashLength_ * glm::cos(radian);
	float yoff = dashLength_ * glm::sin(radian);

	prevPosition_ = renderBound_.center + glm::vec2(xoff, yoff);
	currPosition_ = renderBound_.center;
	
	if (hpBar_->GetBar() <= 0.0f)
	{
		bIsDashing_ = false;
		hurtSound_->Start();
		state_ = EState::HURT;
	}

	animations_.at(state_)->Update(deltaSeconds);
}

void Player::Render()
{
	if (bIsLostHp_ && state_ != EState::HURT)
	{
		renderOption_.blend = glm::vec3(lostHpColor_.x, lostHpColor_.y, lostHpColor_.z);
		renderOption_.factor = lostHpEffectTime_ / maxLostHpEffectTime_;
	}
	else
	{
		renderOption_.blend = glm::vec3(0.0f, 0.0f, 0.0f);
		renderOption_.factor = 0.0f;
	}

	TextureAtlas2D* animationTexture = animations_.at(state_)->GetTextureAtlas();
	const std::string& animationClipName = animations_.at(state_)->GetCurrentClipName();

	if (bIsDashing_)
	{
		RenderPlayerAfterImage(animationTexture, animationClipName);
	}

	RenderPlayer(animationTexture, animationClipName);
}

void Player::Release()
{
	CHECK(bIsInitialized_);

	UnloadSounds();
	UnloadUIs();
	UnloadAnimations();
	gamePlayScene_ = nullptr;
	playground_ = nullptr;
	gamePlayRecorder_ = nullptr;
	textureAtlas_ = nullptr;

	bIsInitialized_ = false;
}

const glm::vec2 Player::GetPosition() const
{
	return renderBound_.center;
}

float Player::GetHP() const
{
	return hpBar_->GetBar();
}

void Player::SetHP(float hp)
{
	if (state_ != EState::IDLE && state_ != EState::RUN)
	{
		return;
	}

	float currentHp = hpBar_->GetBar();
	if (skills_.at(ESkill::INVINCIBILITY)->IsRemainCoolTime() && hp < currentHp)
	{
		return;
	}

	hp = glm::clamp<float>(hp, 0.0f, hpBar_->GetMaxBar());
	if (hp < currentHp)
	{
		bIsLostHp_ = true;
		lostHpEffectCount_ = 0;
		lostHpEffectTime_ = maxLostHpEffectTime_;

		float lostHp = currentHp - hp;
		gamePlayRecorder_->AddRecord<float>(GamePlayRecorder::ERecordType::LOST_HP, lostHp);
	}
	else // hp > currentHp
	{
		chargeSound_->Start();
		float healHp = hp - currentHp;
		gamePlayRecorder_->AddRecord<float>(GamePlayRecorder::ERecordType::HEAL_HP, healHp);
	}

	hpBar_->SetBar(hp);
}

float Player::GetMaxHP() const
{
	return hpBar_->GetMaxBar();
}

void Player::SetMaxHP(float maxHp)
{
	if (state_ != EState::IDLE && state_ != EState::RUN)
	{
		return;
	}

	hpBar_->SetMaxBar(maxHp);
}

float Player::GetMP() const
{
	return mpBar_->GetBar();
}

void Player::SetMP(float mp)
{
	if (state_ != EState::IDLE && state_ != EState::RUN)
	{
		return;
	}

	float currentMp = mpBar_->GetBar();
	mp = glm::clamp<float>(mp, 0.0f, mpBar_->GetMaxBar());
	if (mp < currentMp)
	{
		float lostMp = currentMp - mp;
		gamePlayRecorder_->AddRecord<float>(GamePlayRecorder::ERecordType::LOST_MP, lostMp);
	}
	else // hp > currentMp
	{
		chargeSound_->Start();
		float healMp = mp - currentMp;
		gamePlayRecorder_->AddRecord<float>(GamePlayRecorder::ERecordType::HEAL_MP, healMp);
	}

	mpBar_->SetBar(mp);
}

float Player::GetMaxMP() const
{
	return mpBar_->GetMaxBar();
}

void Player::SetMaxMP(float maxMP)
{
	if (state_ != EState::IDLE && state_ != EState::RUN)
	{
		return;
	}

	mpBar_->SetMaxBar(maxMP);
}

void Player::AddCoin()
{
	coin_++;
	gamePlayRecorder_->AddRecord<int32_t>(GamePlayRecorder::ERecordType::GET_COIN, 1);
}

void Player::LoadAnimations()
{
	GLManager& glManager = GLManager::GetRef();

	std::vector<std::string> idleClipNames =
	{
		"Foxy_Idle_1",
		"Foxy_Idle_2",
		"Foxy_Idle_3",
		"Foxy_Idle_4",
	};
	SpriteAnimator2D* idleAnimation = glManager.Create<SpriteAnimator2D>(textureAtlas_, idleClipNames, 0.5f, true);
	animations_.insert( { EState::IDLE, idleAnimation } );

	std::vector<std::string> runClipNames =
	{
		"Foxy_Run_1",
		"Foxy_Run_2",
		"Foxy_Run_3",
		"Foxy_Run_4",
		"Foxy_Run_5",
		"Foxy_Run_6",
	};
	SpriteAnimator2D* runAnimation = glManager.Create<SpriteAnimator2D>(textureAtlas_, runClipNames, 0.5f, true);
	animations_.insert({ EState::RUN, runAnimation });

	std::vector<std::string> hurtClipNames =
	{
		"Foxy_Hurt_1",
		"Foxy_Hurt_2",
	};
	SpriteAnimator2D* hurtAnimation = glManager.Create<SpriteAnimator2D>(textureAtlas_, hurtClipNames, 0.3f, true);
	animations_.insert({ EState::HURT, hurtAnimation });
}

void Player::UnloadAnimations()
{
	GLManager& glManager = GLManager::GetRef();
	for (auto& animation : animations_)
	{
		glManager.Destroy(animation.second);
	}
}

void Player::LoadUIs()
{
	EntityManager& entityManager = EntityManager::GetRef();
	GLManager& glManager = GLManager::GetRef();

	TTFont* font24 = glManager.GetByName<TTFont>("Font24");

	hpBar_ = entityManager.Create<UIBar>("Resource\\UI\\Player\\HP.bar", font24);
	gamePlayScene_->AddEntity(hpBar_,52, 52);

	mpBar_ = entityManager.Create<UIBar>("Resource\\UI\\Player\\MP.bar", font24);
	gamePlayScene_->AddEntity(mpBar_, 52, 52);

	UISkill* dash = entityManager.Create<UISkill>("Resource\\UI\\Player\\Dash.skill", font24);
	gamePlayScene_->AddEntity(dash, 52, 52);

	UISkill* invincibility = entityManager.Create<UISkill>("Resource\\UI\\Player\\Invincibility.skill", font24);
	gamePlayScene_->AddEntity(invincibility, 52, 52);

	skills_.insert({ ESkill::NONE,          nullptr       });
	skills_.insert({ ESkill::DASH,          dash          });
	skills_.insert({ ESkill::INVINCIBILITY, invincibility });
}

void Player::UnloadUIs()
{
	mpBar_ = nullptr;
	hpBar_ = nullptr;
}

void Player::LoadSounds()
{
	AudioManager& audioManager = AudioManager::GetRef();

	chargeSound_ = audioManager.GetByName<Sound>("Charge");
	dashSound_ = audioManager.GetByName<Sound>("Dash");
	hurtSound_ = audioManager.GetByName<Sound>("EndSound");
}

void Player::UnloadSounds()
{
	hurtSound_ = nullptr;
	dashSound_ = nullptr;
	chargeSound_ = nullptr;
}

void Player::UseDashSkill(float deltaSeconds)
{
	if (bIsDashing_)
	{
		UISkill* dash = skills_.at(ESkill::DASH);
		float scale = dash->GetSkillCoolTime() / dash->GetMaxSkillCoolTime();
		dashSpeed_ = glm::lerp(speed_, maxDashSpeed_, scale);

		if (!dash->IsRemainCoolTime())
		{
			bIsDashing_ = false;
		}
	}

	Move(deltaSeconds, dashSpeed_);
}

void Player::LostHpEffect(float deltaSeconds)
{
	if (!bIsLostHp_)
	{
		return;
	}

	lostHpEffectTime_ -= deltaSeconds;
	lostHpEffectTime_ = glm::clamp<float>(lostHpEffectTime_, 0.0f, maxLostHpEffectTime_);

	if (lostHpEffectTime_ > 0.0f)
	{
		return;
	}

	// lostHpEffectTime_ <= 0.0f
	lostHpEffectCount_++;
	if (lostHpEffectCount_ >= maxLostHpEffectCount_)
	{
		bIsLostHp_ = false;
	}
	else
	{
		lostHpEffectTime_ = maxLostHpEffectTime_;
	}
}

void Player::Move(float deltaSeconds, float speed)
{
	bool bIsPress = false;
	const static std::map<EKey, glm::vec2> KEY_DIRECTIONS =
	{
		{ EKey::KEY_LEFT,  glm::vec2(-1.0f, +0.0f) },
		{ EKey::KEY_UP,    glm::vec2(+0.0f, +1.0f) },
		{ EKey::KEY_RIGHT, glm::vec2(+1.0f, +0.0f) },
		{ EKey::KEY_DOWN,  glm::vec2(+0.0f, -1.0f) },
	};

	GLFWManager& glfwManager = GLFWManager::GetRef();
	direction_ = glm::vec2(0.0f, 0.0f);
	for (const auto& keyDirection : KEY_DIRECTIONS)
	{
		if (glfwManager.GetKeyPress(keyDirection.first) == EPress::HELD)
		{
			direction_ += keyDirection.second;
			bIsPress = true;
		}
	}

	if (bIsPress)
	{
		state_ = EState::RUN;

		glm::vec2 originPosition = renderBound_.center;
		glm::vec2 movePosition = originPosition + direction_ * speed * deltaSeconds;

		AdjustPosition(movePosition);
		if (!collisionBound_.Intersect(playground_->GetSafeBound()))
		{
			AdjustPosition(originPosition);
		}

		if (glm::epsilonNotEqual<float>(direction_.x, 0.0f, glm::epsilon<float>()))
		{
			renderOption_.bIsFlipH = (direction_.x < 0.0f);
			shadow_.option.bIsFlipH = renderOption_.bIsFlipH;
		}
	}
	else
	{
		state_ = EState::IDLE;
	}
}

void Player::AdjustPosition(const glm::vec2& position)
{
	renderBound_.center = position;

	// 충돌 영역 위치 조정.
	collisionBound_.center = renderBound_.center;
	collisionBound_.center.y += -renderBound_.size.y * 0.5f + collisionBound_.radius;

	// 그림자 위치 조정.
	shadow_.bound.center = renderBound_.center;
	shadow_.bound.center.y += (-renderBound_.size.y * 0.5f) + (-shadow_.bound.size.y * 0.5f);
}

void Player::RenderPlayerAfterImage(TextureAtlas2D* animationTexture, const std::string& animationClipName)
{
	for (uint32_t count = 0; count <= DASH_AFTER_IMAGE_COUNT; ++count)
	{
		float scale = static_cast<float>(count) / static_cast<float>(DASH_AFTER_IMAGE_COUNT);
		glm::vec2 position = glm::lerp(prevPosition_, currPosition_, scale);

		renderOption_.transparent = scale * scale;
		if (skills_.at(ESkill::INVINCIBILITY)->IsRemainCoolTime())
		{
			renderManager_->DrawTextureAtlas(animationTexture, animationClipName, position, renderBound_.size.x, renderBound_.size.y, 0.0f, invincibilityColor_, renderOption_);
		}
		else
		{
			renderManager_->DrawTextureAtlas(animationTexture, animationClipName, position, renderBound_.size.x, renderBound_.size.y, 0.0f, renderOption_);
		}
	}
}

void Player::RenderPlayer(TextureAtlas2D* animationTexture, const std::string& animationClipName)
{
	renderOption_.transparent = 1.0f;
	if (skills_.at(ESkill::INVINCIBILITY)->IsRemainCoolTime())
	{
		renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f, invincibilityColor_, renderOption_);
	}
	else
	{
		renderManager_->DrawTextureAtlas(animationTexture, animationClipName, renderBound_.center, renderBound_.size.x, renderBound_.size.y, 0.0f, renderOption_);
	}

	renderManager_->DrawTextureAtlas(animationTexture, animationClipName, shadow_.bound.center, shadow_.bound.size.x, shadow_.bound.size.y, 0.0f, shadow_.option);
}
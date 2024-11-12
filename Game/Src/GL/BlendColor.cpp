#include <glm/glm.hpp>

#include "GL/BlendColor.h"
#include "GL/GLAssertion.h"
#include "GL/GLManager.h"
#include "GL/UniformBuffer.h"

BlendColor::BlendColor(const std::string& vsSource, const std::string& fsSource)
	: PostProcessor(vsSource, fsSource)
{
	uint32_t uniformBufferByteSize = static_cast<uint32_t>(sizeof(BlendColorUBO));
	UniformBuffer::EUsage uniformBufferUsage = UniformBuffer::EUsage::DYNAMIC;
	uniformBuffer_ = GLManager::GetRef().Create<UniformBuffer>(uniformBufferByteSize, uniformBufferUsage);
}

BlendColor::~BlendColor()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void BlendColor::SetBlendColor(const glm::vec3& color, float factor)
{
	bIsNeedUpdate_ = true;
	blendColor_.color = glm::vec4(color, factor);
}

void BlendColor::Release()
{
	if (uniformBuffer_)
	{
		GLManager::GetRef().Destroy(uniformBuffer_);
		uniformBuffer_ = nullptr;
	}

	PostProcessor::Release();
}

void BlendColor::Blit(FrameBuffer* frameBuffer)
{
	if (bIsNeedUpdate_)
	{
		uniformBuffer_->SetBufferData(&blendColor_, static_cast<uint32_t>(sizeof(BlendColorUBO)));
		bIsNeedUpdate_ = false;
	}

	uniformBuffer_->BindSlot(UNIFORM_BUFFER_BIND_SLOT);
	PostProcessor::Blit(frameBuffer);
}
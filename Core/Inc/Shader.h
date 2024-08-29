#pragma once

#include <map>
#include <string>
#include <vector>

#include "GameError.h"
#include "GameMath.h"
#include "IResource.h"

class Shader : public IResource
{
public:
	Shader();
	virtual ~Shader();

	DISALLOW_COPY_AND_ASSIGN(Shader);

	virtual void Release() override;

	GameError LoadFromFile(const std::string& csPath);
	GameError LoadFromFile(const std::string& vsPath, const std::string& fsPath);
	GameError LoadFromFile(const std::string& vsPath, const std::string& gsPath, const std::string& fsPath);
	
	void Bind();
	void Unbind();

	void SetUniform(const std::string& name, bool value);
	void SetUniform(const std::string& name, int32_t value);
	void SetUniform(const std::string& name, const int32_t* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, const float* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, const GameMath::Vec2f& value);
	void SetUniform(const std::string& name, const GameMath::Vec2f* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, float x, float y);
	void SetUniform(const std::string& name, const GameMath::Vec2i& value);
	void SetUniform(const std::string& name, const GameMath::Vec2i* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, int32_t x, int32_t y);
	void SetUniform(const std::string& name, const GameMath::Vec3f& value);
	void SetUniform(const std::string& name, const GameMath::Vec3f* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, float x, float y, float z);
	void SetUniform(const std::string& name, const GameMath::Vec3i& value);
	void SetUniform(const std::string& name, const GameMath::Vec3i* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z);
	void SetUniform(const std::string& name, const GameMath::Vec4f& value);
	void SetUniform(const std::string& name, const GameMath::Vec4f* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, float x, float y, float z, float w);
	void SetUniform(const std::string& name, const GameMath::Vec4i& value);
	void SetUniform(const std::string& name, const GameMath::Vec4i* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w);
	void SetUniform(const std::string& name, const GameMath::Mat2x2& value);
	void SetUniform(const std::string& name, const GameMath::Mat2x2* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, const GameMath::Mat3x3& value);
	void SetUniform(const std::string& name, const GameMath::Mat3x3* bufferPtr, uint32_t count);
	void SetUniform(const std::string& name, const GameMath::Mat4x4& value);
	void SetUniform(const std::string& name, const GameMath::Mat4x4* bufferPtr, uint32_t count);

protected:
	enum class Type : int32_t
	{
		VERTEX     = 0x8B31,
		CONTROL    = 0x8E88,
		EVALUATION = 0x8E87,
		GEOMETRY   = 0x8DD9,
		FRAGMENT   = 0x8B30,
		COMPUTE    = 0x91B9,
	};

	int32_t GetUniformLocation(const std::string& name);
	uint32_t CreateShader(const Type& type, const char* sourcePtr);
	uint32_t CreateProgram(const std::vector<uint32_t>& shaderIDs);

protected:
	uint32_t programID_ = 0;
	std::map<std::string, uint32_t> uniformLocationCache_;
};
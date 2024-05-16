#pragma once

#include <map>
#include <string>
#include <vector>

#include "Mat.h"
#include "Vec.h"

#include "IResource.h"


/**
 * @brief GLSL ���̴��� �������ϰ� ���̴� ���α׷��� �����մϴ�.
 */
class Shader : public IResource
{
public:
	/**
	 * @brief ���̴� ������ �о� ���̴� ���α׷��� �����մϴ�.
	 * 
	 * @param csPath ��ǻƮ ���̴�(Compute Shader)�� ����Դϴ�.
	 */
	explicit Shader(const std::string& csPath);


	/**
	 * @brief ���̴� ������ �о� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsPath ���ؽ� ���̴�(Vertex Shader)�� ����Դϴ�.
	 * @param fsPath �����׸�Ʈ ���̴�(Fragment Shader)�� ����Դϴ�.
	 */
	explicit Shader(const std::string& vsPath, const std::string& fsPath);


	/**
	 * @brief ���̴� ������ �о� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsPath ���ؽ� ���̴�(Vertex Shader)�� ����Դϴ�.
	 * @param gsFile ������Ʈ�� ���̴��� Ȯ����(.geom)�� ������ ����Դϴ�.
	 * @param fsPath �����׸�Ʈ ���̴�(Fragment Shader)�� ����Դϴ�.
	 */
	explicit Shader(const std::string& vsPath, const std::string& gsPath, const std::string& fsPath);


	/**
	 * @brief ���̴��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Shader();


	/**
	 * @brief ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Shader);


	/**
	 * @brief ���̴� ���ο��� �Ҵ�� ���ҽ��� �Ҵ��� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���̴��� ���������ο� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ���̴��� ���ε� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ���̴� ���� boolean Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, bool value);


	/**
	 * @brief ���̴� ���� int Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, int32_t value);


	/**
	 * @brief ���̴� ���� float Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, float value);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Vec2f& value);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 */
	void SetUniform(const std::string& name, float x, float y);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Vec2i& value);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 */
	void SetUniform(const std::string& name, int32_t x, int32_t y);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Vec3f& value);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 */
	void SetUniform(const std::string& name, float x, float y, float z);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Vec3i& value);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 */
	void SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Vec4f& value);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 * @param w ������ ������ w ���Դϴ�.
	 */
	void SetUniform(const std::string& name, float x, float y, float z, float w);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Vec4i& value);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 * @param w ������ ������ w ���Դϴ�.
	 */
	void SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w);


	/**
	 * @brief ���̴� ���� 2x2 Ÿ���� ��� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Mat2x2& value);


	/**
	 * @brief ���̴� ���� 3x3 Ÿ���� ��� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Mat3x3& value);


	/**
	 * @brief ���̴� ���� 4x4 Ÿ���� ��� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetUniform(const std::string& name, const Mat4x4& value);


protected:
	/**
	 * @brief ���̴��� �����Դϴ�.
	 */
	enum class EType : int32_t
	{
		Vertex     = 0x8B31,
		Control    = 0x8E88,
		Evaluation = 0x8E87,
		Geometry   = 0x8DD9,
		Fragment   = 0x8B30,
		Compute    = 0x91B9,
	};


	/**
	 * @brief ���̴� �� ������ ��ü�� ��ġ�� ����ϴ�.
	 *
	 * @param name ��ġ�� ã�� ���̴� �� ������ �̸��Դϴ�.
	 *
	 * @return ���̴� �� ������ ��ü�� ��ġ�� ��ȯ�մϴ�. ã�� ���ϸ� -1�� ��ȯ�մϴ�.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml
	 */
	int32_t GetUniformLocation(const std::string& name);

	
	/**
	 * @brief ���̴� ������Ʈ�� �����մϴ�.
	 *
	 * @note ���̴� ��ü ������ �����ϸ� 0�� �ƴ� ���� ��ȯ�մϴ�.
	 *
	 * @param type ���̴� Ÿ���Դϴ�.
	 * @param path ���̴� ������ ����Դϴ�.
	 * @param entryPoint ���̴��� ���� �����Դϴ�. �⺻ ���� main�Դϴ�.
	 *
	 * @return ������ ���̴� ��ü�� ���̵� ��ȯ�մϴ�.
	 */
	uint32_t CreateShader(const EType& type, const std::string& path, const char* entryPoint = "main");


	/**
	 * @brief ���̴� ���α׷��� �����մϴ�.
	 * 
	 * @note ���̴� ���α׷� ������ �����ϸ� 0�� �ƴ� ���� ��ȯ�մϴ�.
	 * 
	 * @param shaderIDs ���̴� ���α׷��� �߰��� ���̴� ID ����Դϴ�.
	 * 
	 * @return ������ ���̴� ���α׷� ��ü�� ���̵� ��ȯ�մϴ�.
	 */
	uint32_t CreateProgram(const std::vector<uint32_t>& shaderIDs);

	
protected:
	/**
	 * @brief ���̴� ���α׷��� ���̵��Դϴ�.
	 */
	uint32_t programID_ = 0;


	/**
	 * @brief ������ ������ ��ġ���Դϴ�.
	 */
	std::map<std::string, uint32_t> uniformLocationCache_;
};
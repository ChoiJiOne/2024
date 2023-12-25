#pragma once

#include <string>

#include "IResource.h"


/**
 * @brief �̹��� ������ �ε��ϰ� OpenGL ���������ο� ���ε� ������ �ؽ�ó ���ҽ��� ���� �� �����մϴ�.
 * 
 * @note
 * - �̹��� ������ .jpeg, .jpg, .png, .tga, .bmp �� �����մϴ�.
 * - ���� ������ ASTC�� DXT(S3TC) ������ �����մϴ�.
 * - ASTC ���� ������ ��� �ݵ�� astcenc.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
 * - DXT ���� ������ ��� �ݵ�� texconv.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
 */
class Texture2D : public IResource
{
public:
	/**
	 * @brief �ؽ�ó�� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Texture2D() = default;


	/**
	 * @brief �ؽ�ó�� ���� �Ҹ����Դϴ�.
	 *
	 * @note �ؽ�ó ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Texture2D();


	/**
	 * @brief �ؽ�ó�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2D);


	/**
	 * @brief �̹��� ������ �а� �ؽ�ó ���ҽ��� �����մϴ�.
	 *
	 * @param path �̹��� ������ ����Դϴ�.
	 * 
	 * @note
	 * - �̹��� ������ .jpeg, .jpg, .png, .tga, .bmp �� �����մϴ�.
	 * - ASTC ���� ������ �ݵ�� astcenc.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
	 * - ASTC ���� ������ Ȯ���ڴ� .astc�� �Ǿ� �־�� �մϴ�.
	 * - DXT ���� ������ �ݵ�� texconv.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
	 * - DXT ���� ������ Ȯ���ڴ� .dds�� �Ǿ� �־�� �մϴ�.
	 */
	void Initialize(const std::wstring& path);


	/**
	 * @brief �ؽ�ó�� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit) const;


private:
	/**
	 * @brief �̹��� ������ Ȯ���ڰ� ���� ������ �������� �˻��մϴ�.
	 * 
	 * @param ���� ������ �������� �˻��� �ؽ�ó ���� ����Դϴ�.
	 * 
	 * @return �ؽ�ó ������ ���� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsSupportExtension(const std::wstring& path);


	/**
	 * @brief �̹��� ���� �̸����� ASTC �� ũ�⸦ ã���ϴ�.
	 * 
	 * @param ASTC �� ũ�⸦ ã�� �̹��� ������ ����Դϴ�.
	 * 
	 * @return ASTC �� ũ�⸦ ��ȯ�մϴ�.
	 * 
	 * @note �̹��� ����(PNG, JPG ...)�� ASTC�� ��ȯ�� �� �ݵ�� �̸��� 4x4, 6x6�� ���Եǵ��� ��ȯ�ؾ� �մϴ�.
	 */
	uint32_t FindAstcBlockSizeFromFile(const std::wstring& path);


	/**
	 * @brief ����� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 * 
	 * @return �ؽ�ó ���ҽ��� ID�� ��ȯ�մϴ�.
	 */
	uint32_t CreateNonCompressionTexture(const std::wstring& path);


	/**
	 * @brief ASTC ���� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 *
	 * @return �ؽ�ó ���ҽ��� ID�� ��ȯ�մϴ�.
	 */
	uint32_t CreateAstcCompressionTexture(const std::wstring& path);


	/**
	 * @brief DXT ���� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 * 
	 * @return �ؽ�ó ���ҽ��� ID�� ��ȯ�մϴ�.
	 */
	uint32_t CreateDxtCompressionTexture(const std::wstring& path);


private:
	/**
	 * @brief �ؽ�ó ���ҽ��� ID�Դϴ�.
	 */
	uint32_t textureID_ = 0;
};
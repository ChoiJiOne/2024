#pragma once

#include <cstdint>
#include <string>
#include <vector>



/**
 * @brief ASTC ������ ����Դϴ�.
 *
 * @note
 * - astcenc.exe�� �̿��ؼ� ������ ���� �����Դϴ�.
 * - https://github.com/ARM-software/astc-encoder/blob/main/Docs/FileFormat.md
 */
struct AstcFileHeader
{
	uint8_t magic[4];
	uint8_t blockdimX;
	uint8_t blockdimY;
	uint8_t blockdimZ;
	uint8_t xsize[3];
	uint8_t ysize[3];
	uint8_t zsize[3];
};


/**
 * @brief ASTC ��� ũ�⸦ ��Ÿ���� �������Դϴ�.
 *
 * @note 
 * - OpenGL�� GL_COMPRESSED_RGBA_ASTC_<SIZE>x<SIZE>_KHR ����� �ϴ��� �����մϴ�.
 *  - https://www.khronos.org/opengl/wiki/ASTC_Texture_Compression
 */
enum class EAstcBlockSize
{
	ASTC_4x4 = 0x93B0,
	ASTC_5x4 = 0x93B1,
	ASTC_5x5 = 0x93B2,
	ASTC_6x5 = 0x93B3,
	ASTC_6x6 = 0x93B4,
	ASTC_8x5 = 0x93B5,
	ASTC_8x6 = 0x93B6,
	ASTC_8x8 = 0x93B7,
	ASTC_10x5 = 0x93B8,
	ASTC_10x6 = 0x93B9,
	ASTC_10x8 = 0x93BA,
	ASTC_10x10 = 0x93BB,
	ASTC_12x10 = 0x93BC,
	ASTC_12x12 = 0x93BD,
	None = 0xFFFF,
};


/**
 * @brief �ؽ�ó�� ���� Ȯ�� ����� �����մϴ�.
 */
class TextureUtils
{
public:
	/**
	 * @brief ���� �̸����κ��� ASTC�� ���� ��� ũ�⸦ ����ϴ�.
	 * 
	 * @param path ASTC�� ���� ��� ũ�⸦ ���� ���� �ؽ�ó ���� ����Դϴ�.
	 * 
	 * @note 
	 * - ���� �̸� ���ο� �ݵ�� ���� �� ũ�Ⱑ �־�� �մϴ�.
	 * - ex. example_4x4.astc, example_6x6.astc
	 * - �ݵ�� astcenc.exe ���Ϸ� ������ �����̿��� �մϴ�.
	 */
	static EAstcBlockSize FindAstcBlockSizeFromFile(const std::wstring& path);


	/**
	 * @brief ASTC ���� �ؽ�ó ������ �ε��մϴ�.
	 * 
	 * @param path ASTC ���� �ؽ�ó ������ ����Դϴ�.
	 * @param outAstcBuffer ASTC ���� �ؽ�ó ������ �����Դϴ�.
	 * @param outBlockSize ASTC ���� �ؽ�ó�� ���� ��� ũ���Դϴ�.
	 * 
	 * @note 
	 * - ���� �̸� ���ο� �ݵ�� ���� �� ũ�Ⱑ �־�� �մϴ�.
	 * - ex. example_4x4.astc, example_6x6.astc
	 * - �ݵ�� astcenc.exe ���Ϸ� ������ �����̿��� �մϴ�.
	 */
	static void LoadAstcFromFile(const std::wstring& path, std::vector<uint8_t>& outAstcBuffer, EAstcBlockSize& outBlockSize);
};
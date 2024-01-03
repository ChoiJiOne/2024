#pragma once

#include <cstdint>
#include <string>
#include <vector>


#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844


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
 * @brief DDS ������ ����Դϴ�.
 *
 * @see https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dds-header
 */
struct DDSFileHeader
{
	uint8_t  magic[4];
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	uint32_t dwReserved1[11];
	uint32_t dwPixelSize;
	uint32_t dwPixelFlags;
	uint32_t dwFourCC;
	uint32_t dwRGBBitCount;
	uint32_t dwRBitMask;
	uint32_t dwGBitMask;
	uint32_t dwBBitMask;
	uint32_t dwABitMask;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
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
	 * @brief �̹��� ������ Ȯ���ڰ� ���� ������ �������� �˻��մϴ�.
	 *
	 * @param ���� ������ �������� �˻��� �ؽ�ó ���� ����Դϴ�.
	 *
	 * @return �ؽ�ó ������ ���� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 * 
	 * @note
	 * - �̹��� ������ .jpeg, .jpg, .png, .tga, .bmp �� �����մϴ�.
	 * - ���� ������ ASTC�� DXT(S3TC) ������ �����մϴ�.
	 * - ASTC ���� ������ ��� �ݵ�� astcenc.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
	 * - DXT ���� ������ ��� �ݵ�� texconv.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
	 */
	bool IsSupportExtension(const std::wstring& path);


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
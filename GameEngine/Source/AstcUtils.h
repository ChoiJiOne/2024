#pragma once

#include <cstdint>


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
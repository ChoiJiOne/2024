#pragma once

#include <cstdint>
#include <string>
#include <vector>


/**
 * @brief ���� �� ���丮 ����� �����մϴ�.
 */
class FileModule
{
public:
	/**
	 * @brief ���� ����� ���� ����Դϴ�.
	 */
	enum class Errors
	{
		OK         = 0x00, // ���� ����
		FAILED     = 0x01, // �Ϲ����� ����
		ERR_CREATE = 0x02, // ���� ���� ����
		ERR_OPEN   = 0x03, // ���� ���� ����
		ERR_WRITE  = 0x04, // ���� ���� ����
		ERR_READ   = 0x05, // ���� �б� ����
		ERR_CLOSE  = 0x06, // ���� �ݱ� ����
		ERR_API    = 0x07, // API ȣ�� ����
	};


	/**
	 * @brief ���� ����� ���� �ֱ� ���� �޽����� ����ϴ�.
	 *
	 * @return ���� ����� ���� �������� �߻��� ���� �޽����� ��ȯ�մϴ�.
	 */
	static const char* GetLastErrorMessage();


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 *
	 * @param path ������ ����Դϴ�.
	 * @param outBuffer ������ ������ ������ �����Դϴ�.
	 *
	 * @return ������ �о� ���ۿ� �����ϴ� �� �����ϸ� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	static Errors ReadFile(const std::string& path, std::vector<uint8_t>& outBuffer);


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 *
	 * @param path ������ ����Դϴ�.
	 * @param outBuffer ������ ������ ������ �����Դϴ�.
	 *
	 * @return ������ �о� ���ۿ� �����ϴ� �� �����ϸ� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	static Errors ReadFile(const std::wstring& path, std::vector<uint8_t>& outBuffer);


	/**
	 * @brief ���۸� ���Ͽ� ���ϴ�.
	 *
	 * @param path ���۸� �� ������ ����Դϴ�.
	 * @param buffer ���Ͽ� �� �����Դϴ�.
	 *
	 * @return ���۸� ���Ͽ� ���� �� �����ϸ� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	static Errors WriteFile(const std::string& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief ���۸� ���Ͽ� ���ϴ�.
	 *
	 * @param path ���۸� �� ������ ����Դϴ�.
	 * @param buffer ���Ͽ� �� �����Դϴ�.
	 *
	 * @return ���۸� ���Ͽ� ���� �� �����ϸ� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	static Errors WriteFile(const std::wstring& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief ���丮�� �����մϴ�.
	 *
	 * @param path ���丮�� ������ ����Դϴ�.
	 *
	 * @return ���丮 ������ �����ߴٸ� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/winbase/nf-winbase-createdirectory
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createdirectoryw
	 */
	static Errors MakeDirectory(const std::string& path);


	/**
	 * @brief ���丮�� �����մϴ�.
	 *
	 * @param path ���丮�� ������ ����Դϴ�.
	 *
	 * @return ���丮 ������ �����ߴٸ� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/winbase/nf-winbase-createdirectory
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createdirectoryw
	 */
	static Errors MakeDirectory(const std::wstring& path);


	/**
	 * @brief ���� Ȥ�� ���丮�� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param path ��ȿ���� Ȯ���� ���� Ȥ�� ���丮 ����Դϴ�.
	 *
	 * @return ���� Ȥ�� ���丮�� ��ȿ�ϴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool IsValidPath(const std::string& path);


	/**
	 * @brief ���� Ȥ�� ���丮�� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param path ��ȿ���� Ȯ���� ���� Ȥ�� ���丮 ����Դϴ�.
	 *
	 * @return ���� Ȥ�� ���丮�� ��ȿ�ϴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool IsValidPath(const std::wstring& path);


	/**
	 * @brief ��ο��� �����̳� ���丮 �̸��� ������ ��θ� ����ϴ�.
	 *
	 * @param path �����̳� ���丮 ����Դϴ�.
	 *
	 * @return �����̳� ���丮 �̸��� ������ ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 */
	static std::string GetBasePath(const std::string& path);


	/**
	 * @brief ��ο��� �����̳� ���丮 �̸��� ������ ��θ� ����ϴ�.
	 *
	 * @param path �����̳� ���丮 ����Դϴ�.
	 *
	 * @return �����̳� ���丮 �̸��� ������ ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 */
	static std::wstring GetBasePath(const std::wstring& path);


	/**
	 * @brief ��ü �����̳� ���丮 ��ο��� ���̽� ��θ� �����մϴ�.
	 *
	 * @param path ���̽� ��θ� ������ ��ü �����̳� ���丮 ����Դϴ�.
	 *
	 * @return ���̽� ��ΰ� ������ ���� ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "CCC.a" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "CCC" �Դϴ�.
	 */
	static std::string RemoveBasePath(const std::string& path);


	/**
	 * @brief ��ü �����̳� ���丮 ��ο��� ���̽� ��θ� �����մϴ�.
	 *
	 * @param path ���̽� ��θ� ������ ��ü �����̳� ���丮 ����Դϴ�.
	 *
	 * @return ���̽� ��ΰ� ������ ���� ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "CCC.a" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "CCC" �Դϴ�.
	 */
	static std::wstring RemoveBasePath(const std::wstring& path);


	/**
	 * @brief ��ü ���� ��ο��� ���� Ȯ���ڸ� ����ϴ�.
	 *
	 * @param path ���� Ȯ���ڸ� ���� ��ü ���� ����Դϴ�.
	 *
	 * @return ��ü ���� ����� ���� Ȯ���ڸ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 * - ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 */
	static std::string GetFileExtension(const std::string& path);


	/**
	 * @brief ��ü ���� ��ο��� ���� Ȯ���ڸ� ����ϴ�.
	 *
	 * @param path ���� Ȯ���ڸ� ���� ��ü ���� ����Դϴ�.
	 *
	 * @return ��ü ���� ����� ���� Ȯ���ڸ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 * - ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 */
	static std::wstring GetFileExtension(const std::wstring& path);


private:
	/**
	 * @brief ���� �޽����� �����մϴ�.
	 *
	 * @note ������ �������� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 */
	static void SetLastErrorMessage();


private:
	/**
	 * @brief ���ڿ� ������ �ִ� ũ���Դϴ�.
	 */
	static const uint32_t MAX_BUFFER_SIZE = 1024;


	/**
	 * @brief ���� ������ ���� �޽����� �����ϴ� �����Դϴ�.
	 */
	static char lastErrorMessage[MAX_BUFFER_SIZE];
};
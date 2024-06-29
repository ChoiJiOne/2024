#pragma once

#include <cstdint>
#include <string>
#include <vector>


namespace GameMaker
{
/**
 * @brief ���� �� ���丮 ����� �����մϴ�.
 * 
 * @note �� Ŭ������ ��� ���� �� �޼���� ��� ����(static) Ÿ���Դϴ�.
 */
class FileUtils
{
public:
	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 *
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return ���� ���� ���͸� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	static std::vector<uint8_t> ReadFile(const std::string& path);


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 *
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return ���� ���� ���͸� ��ȯ�մϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	static std::vector<uint8_t> ReadFile(const std::wstring& path);


	/**
	 * @brief ���۸� ���Ͽ� ���ϴ�.
	 *
	 * @param path ���۸� �� ������ ����Դϴ�.
	 * @param buffer ���Ͽ� �� �����Դϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	static void WriteFile(const std::string& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief ���۸� ���Ͽ� ���ϴ�.
	 *
	 * @param path ���۸� �� ������ ����Դϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	static void WriteFile(const std::wstring& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief ���丮�� �����մϴ�.
	 *
	 * @param path ���丮�� ������ ����Դϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/winbase/nf-winbase-createdirectory
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createdirectoryw
	 */
	static void MakeDirectory(const std::string& path);


	/**
	 * @brief ���丮�� �����մϴ�.
	 *
	 * @param path ���丮�� ������ ����Դϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/winbase/nf-winbase-createdirectory
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createdirectoryw
	 */
	static void MakeDirectory(const std::wstring& path);


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
};

}
#pragma once

#include <cstdint>
#include <string>
#include <vector>


namespace GameMaker
{
class FileUtils
{
public:
	static std::vector<uint8_t> ReadFile(const std::string& path);
	static std::vector<uint8_t> ReadFile(const std::wstring& path);
	static void WriteFile(const std::string& path, const std::vector<uint8_t>& buffer);
	static void WriteFile(const std::wstring& path, const std::vector<uint8_t>& buffer);
	static void MakeDirectory(const std::string& path);
	static void MakeDirectory(const std::wstring& path);
	static bool IsValidPath(const std::string& path);
	static bool IsValidPath(const std::wstring& path);

	/** 
	 * ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 * ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 */
	static std::string GetBasePath(const std::string& path);

	/**
	 * ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 * ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 */
	static std::wstring GetBasePath(const std::wstring& path);

	/**
	 * ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "CCC.a" �Դϴ�.
	 * ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "CCC" �Դϴ�.
	 */
	static std::string RemoveBasePath(const std::string& path);

	/**
	 * ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "CCC.a" �Դϴ�.
	 * ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "CCC" �Դϴ�.
	 */
	static std::wstring RemoveBasePath(const std::wstring& path);

	/**
	 * ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 * ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 */
	static std::string GetFileExtension(const std::string& path);

	/**
	 * ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 * ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 */
	static std::wstring GetFileExtension(const std::wstring& path);
};

}
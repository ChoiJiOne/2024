#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <windows.h>

#include <json/json.h>

#include "IManager.h"


/**
 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class FileManager : public IManager
{
public:
	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(FileManager);


	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return ���� �� ���丮 ó���� �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static FileManager& Get()
	{
		static FileManager instance;
		return instance;
	}


	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 *
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� ���� ��θ� ����ϴ�.
	 * 
	 * @return ���� ���� ��θ� ��ȯ�մϴ�.
	 */
	const std::wstring& GetExecutePath() const { return executePath_; }


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return ������ ���� ���͸� ��ȯ�մϴ�.
	 * 
	 * @see 
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	std::vector<uint8_t> ReadBufferFromFile(const std::string& path);


	/**
	 * @brief ������ �а� ���ۿ� �����մϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return ������ ���� ���͸� ��ȯ�մϴ�.
	 * 
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	std::vector<uint8_t> ReadBufferFromFile(const std::wstring& path);


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
	void WriteBufferToFile(const std::string& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief ���۸� ���Ͽ� ���ϴ�.
	 *
	 * @param path ���۸� �� ������ ����Դϴ�.
	 * @param buffer ���Ͽ� �� �����Դϴ�.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	void WriteBufferToFile(const std::wstring& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief ���� Ȥ�� ���丮�� ��ȿ���� Ȯ���մϴ�.
	 * 
	 * @param path ��ȿ���� Ȯ���� ���� Ȥ�� ���丮 ����Դϴ�.
	 * 
	 * @return ���� Ȥ�� ���丮�� ��ȿ�ϴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsValidPath(const std::string& path);
	

	/**
	 * @brief ���� Ȥ�� ���丮�� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param path ��ȿ���� Ȯ���� ���� Ȥ�� ���丮 ����Դϴ�.
	 *
	 * @return ���� Ȥ�� ���丮�� ��ȿ�ϴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsValidPath(const std::wstring& path);


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
	std::string GetBasePath(const std::string& path);


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
	std::wstring GetBasePath(const std::wstring& path);


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
	std::string RemoveBasePath(const std::string& path);


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
	std::wstring RemoveBasePath(const std::wstring& path);


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
	std::string GetFileExtension(const std::string& path);


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
	std::wstring GetFileExtension(const std::wstring& path);


	/**
	 * @brief Json ������ Json ��ü�� ����ϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return Json ��ü�� ��ȯ�մϴ�.
	 */
	Json::Value ReadJsonFromFile(const std::string& path);


	/**
	 * @brief Json ������ Json ��ü�� ����ϴ�.
	 *
	 * @param path ������ ����Դϴ�.
	 *
	 * @return Json ��ü�� ��ȯ�մϴ�.
	 */
	Json::Value ReadJsonFromFile(const std::wstring& path);


private:
	/**
	 * @brief ���� �� ���丮 ó���� �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(FileManager);


private:
	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	std::wstring executePath_;
};
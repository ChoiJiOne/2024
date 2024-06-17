#pragma once

#include <array>
#include <memory>
#include <string>

struct ma_engine;
struct ma_sound;


/**
 * @brief ���� ���ҽ��� ID�Դϴ�.
 */
using SoundID = int32_t;


/**
 * @brief ����� ���� ����� �����ϴ� ����Դϴ�.
 */
class AudioModule
{
public:
	/**
	 * @brief ����� ��� ���� ����Դϴ�.
	 */
	enum class Errors
	{
		OK     = 0,
		FAILED = -1,  /* A generic error. */
		ERR_INVALID_ARGS = -2,
		ERR_INVALID_OPERATION = -3,
		ERR_OUT_OF_MEMORY = -4,
		ERR_OUT_OF_RANGE = -5,
		ERR_ACCESS_DENIED = -6,
		ERR_DOES_NOT_EXIST = -7,
		ERR_ALREADY_EXISTS = -8,
		ERR_TOO_MANY_OPEN_FILES = -9,
		ERR_INVALID_FILE = -10,
		ERR_TOO_BIG = -11,
		ERR_PATH_TOO_LONG = -12,
		ERR_NAME_TOO_LONG = -13,
		ERR_NOT_DIRECTORY = -14,
		ERR_IS_DIRECTORY = -15,
		ERR_DIRECTORY_NOT_EMPTY = -16,
		ERR_AT_END = -17,
		ERR_NO_SPACE = -18,
		ERR_BUSY = -19,
		ERR_IO_ERROR = -20,
		ERR_INTERRUPT = -21,
		ERR_UNAVAILABLE = -22,
		ERR_ALREADY_IN_USE = -23,
		ERR_BAD_ADDRESS = -24,
		ERR_BAD_SEEK = -25,
		ERR_BAD_PIPE = -26,
		ERR_DEADLOCK = -27,
		ERR_TOO_MANY_LINKS = -28,
		ERR_NOT_IMPLEMENTED = -29,
		ERR_NO_MESSAGE = -30,
		ERR_BAD_MESSAGE = -31,
		ERR_NO_DATA_AVAILABLE = -32,
		ERR_INVALID_DATA = -33,
		ERR_TIMEOUT = -34,
		ERR_NO_NETWORK = -35,
		ERR_NOT_UNIQUE = -36,
		ERR_NOT_SOCKET = -37,
		ERR_NO_ADDRESS = -38,
		ERR_BAD_PROTOCOL = -39,
		ERR_PROTOCOL_UNAVAILABLE = -40,
		ERR_PROTOCOL_NOT_SUPPORTED = -41,
		ERR_PROTOCOL_FAMILY_NOT_SUPPORTED = -42,
		ERR_ADDRESS_FAMILY_NOT_SUPPORTED = -43,
		ERR_SOCKET_NOT_SUPPORTED = -44,
		ERR_CONNECTION_RESET = -45,
		ERR_ALREADY_CONNECTED = -46,
		ERR_NOT_CONNECTED = -47,
		ERR_CONNECTION_REFUSED = -48,
		ERR_NO_HOST = -49,
		ERR_IN_PROGRESS = -50,
		ERR_CANCELLED = -51,
		ERR_MEMORY_ALREADY_MAPPED = -52,
		ERR_CRC_MISMATCH = -100, /* General non-standard errors. */
		ERR_FORMAT_NOT_SUPPORTED = -200, /* General miniaudio-specific errors. */
		ERR_DEVICE_TYPE_NOT_SUPPORTED = -201,
		ERR_SHARE_MODE_NOT_SUPPORTED = -202,
		ERR_NO_BACKEND = -203,
		ERR_NO_DEVICE = -204,
		ERR_API_NOT_FOUND = -205,
		ERR_INVALID_DEVICE_CONFIG = -206,
		ERR_LOOP = -207,
		ERR_BACKEND_NOT_ENABLED = -208,
		ERR_DEVICE_NOT_INITIALIZED = -300, /* State errors. */
		ERR_DEVICE_ALREADY_INITIALIZED = -301,
		ERR_DEVICE_NOT_STARTED = -302,
		ERR_DEVICE_NOT_STOPPED = -303,
		ERR_FAILED_TO_INIT_BACKEND = -400, /* Operation errors. */
		ERR_FAILED_TO_OPEN_BACKEND_DEVICE = -401,
		ERR_FAILED_TO_START_BACKEND_DEVICE = -402,
		ERR_FAILED_TO_STOP_BACKEND_DEVICE = -403
	};


	/**
	 * @brief ����� ����� �ʱ�ȭ�մϴ�.
	 * 
	 * @return ����� ��� �ʱ�ȭ�� �����ϸ� Errors �������� OK, �׷��� ������ �� ���� ���� ��ȯ�մϴ�.
	 */
	static Errors Init();


	/**
	 * @brief ����� ����� �ʱ�ȭ�� �����մϴ�.
	 */
	static void Uninit();


	/**
	 * @brief ���� ���ҽ��� �����մϴ�.
	 * 
	 * @param path ���� ���ҽ��� ����Դϴ�.
	 * 
	 * @return ������ ���� ���ҽ��� ID�� ��ȯ�մϴ�.
	 */
	static SoundID CreateSound(const std::string& path);


	/**
	 * @brief ���� ���ҽ��� �ı��մϴ�.
	 * 
	 * @param soundID �ı��� ���� ���ҽ��� ID�Դϴ�.
	 */
	static void DestroySound(const SoundID& soundID);


	/**
	 * @brief ������ ũ�⸦ �����մϴ�.
	 *
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 * @param volume ������ ũ���Դϴ�. ������ 0.0 ~ 1.0 �Դϴ�.
	 */
	static void SetVolume(const SoundID& soundID, float volume);


	/**
	 * @brief ���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 * 
	 * @return ������ ũ�⸦ ����ϴ�.
	 * 
	 * @note ���� ũ���� ������ 0.0 ~ 1.0 �Դϴ�.
	 */
	static float GetVolume(const SoundID& soundID);


	/**
	 * @brief ������ �ݺ� ���θ� �����մϴ�.
	 *
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 * @param bIsLoop ���� �ݺ� �����Դϴ�.
	 */
	static void SetLooping(const SoundID& soundID, bool bIsLoop);


	/**
	 * @brief ������ �ݺ� ���θ� ����ϴ�.
	 *
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 * 
	 * @return ���尡 �ݺ��Ѵٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool IsLooping(const SoundID& soundID);


	/**
	 * @brief ���带 �÷����մϴ�.
	 * 
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 *
	 * @note ������ ������ ���� �ִٸ� ������ �������� �÷��̵˴ϴ�.
	 */
	static void Play(const SoundID& soundID);


	/**
	 * @brief ���尡 �÷��������� Ȯ���մϴ�.
	 * 
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 *
	 * @return ���尡 �÷��� ���̶�� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool IsPlaying(const SoundID& soundID);


	/**
	 * @brief ���� �÷��̰� �������� Ȯ���մϴ�.
	 * 
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 *
	 * @return ���� �÷��̰� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool IsDone(const SoundID& soundID);


	/**
	 * @brief ���� �÷��̸� �����մϴ�.
	 * 
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 */
	static void Stop(const SoundID& soundID);


	/**
	 * @brief ���� �÷��̰� ���� �Ǿ����� Ȯ���մϴ�.
	 * 
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 *
	 * @return ���� �÷��̰� ���� �Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsStopping(const SoundID& soundID);


	/**
	 * @brief ���带 �ʱ�ȭ�մϴ�.
	 * 
	 * @param soundID ���� ���ҽ��� ID�Դϴ�.
	 */
	static void Reset(const SoundID& soundID);

	
private:
	/**
	 * @brief ����� ����� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	static bool bIsInitialize;


	/**
	 * @brief ����� �����Դϴ�.
	 */
	static std::unique_ptr<ma_engine> engine;


	/**
	 * @brief ���� ���ҽ��� �ִ� ���� ���Դϴ�.
	 */
	static const uint32_t MAX_SOUND_RESOURCE_SIZE = 200;


	/**
	 * @brief ĳ�� ũ���Դϴ�.
	 */
	static uint32_t cacheSize;


	/**
	 * @brief ���� ���ҽ��� ĳ���Դϴ�.
	 */
	static std::array<std::unique_ptr<ma_sound>, MAX_SOUND_RESOURCE_SIZE> cache;
};
#include "Assertion.h"
#include "EntityManager.h"
#include "GameUtils.h"
#include "GameTimer.h"
#include "RenderManager2D.h"

#include "GameHistoryTracker.h"

struct GameHistoryHeader
{
	uint32_t chunkCount;
};

struct GameHistoryChunk
{
	static const uint32_t MAX_STRING_SIZE = 101;
	int32_t score;
	wchar_t time[MAX_STRING_SIZE];
};

GameHistoryTracker::GameHistoryTracker()
{
	high_.score = -1;

	LoadGameHistoryFile(L"Cache\\GameHistory.bin");
	if (bSucceedLoadGameHistoryFile_)
	{
		for (const auto& history : histories_)
		{
			if (history.score > high_.score)
			{
				high_.score = history.score;
				high_.time = history.time;
			}
		}
	}

	bIsInitialized_ = true;
}

GameHistoryTracker::~GameHistoryTracker()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GameHistoryTracker::Tick(float deltaSeconds)
{
}

void GameHistoryTracker::Release()
{
	CHECK(bIsInitialized_);

	if (!GameUtils::IsValidPath("Cache"))
	{
		GameUtils::MakeDirectory("Cache");
	}

	SaveGameHistoryFile(L"Cache\\GameHistory.bin");
	
	bIsInitialized_ = false;
}

void GameHistoryTracker::AddScore(int32_t score)
{
	History newHistory;
	newHistory.score = score;

	int32_t year = 0;
	int32_t month = 0;
	int32_t day = 0;
	int32_t hour = 0;
	int32_t minute = 0;
	int32_t second = 0;
	GameTimer::GetCurrentSystemTime(year, month, day, hour, minute, second);
	newHistory.time = GameUtils::PrintF(L"%d.%02d.%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

	recent_.score = score;
	recent_.time = newHistory.time;

	if (histories_.empty())
	{
		high_.score = score;
		high_.time = newHistory.time;
		bIsHighScoreBroken_ = true;
	}
	else
	{
		bIsHighScoreBroken_ = false;
		if (score > high_.score)
		{
			high_.score = score;
			high_.time = newHistory.time;
			bIsHighScoreBroken_ = true;
		}
	}
	
	histories_.push_back(newHistory);
}

void GameHistoryTracker::LoadGameHistoryFile(const std::wstring& path)
{
	if (!GameUtils::IsValidPath(path))
	{
		return;
	}

	std::vector<uint8_t> buffer = GameUtils::ReadFile(path);

	GameHistoryHeader* header = reinterpret_cast<GameHistoryHeader*>(buffer.data());
	GameHistoryChunk* chunkPtr = reinterpret_cast<GameHistoryChunk*>(buffer.data() + sizeof(GameHistoryHeader));
	for (uint32_t index = 0; index < header->chunkCount; ++index)
	{
		History history;
		history.score = chunkPtr[index].score;
		history.time = chunkPtr[index].time;

		histories_.push_back(history);
	}

	bSucceedLoadGameHistoryFile_ = true;
}

void GameHistoryTracker::SaveGameHistoryFile(const std::wstring& path)
{
	uint32_t chunkCount = static_cast<uint32_t>(histories_.size());
	uint32_t byteSize = 0;
	uint32_t headerByteSize = sizeof(GameHistoryHeader);
	uint32_t sourceByteSize = sizeof(GameHistoryChunk) * chunkCount;

	byteSize += headerByteSize;
	byteSize += sourceByteSize;
	std::vector<uint8_t> buffer(byteSize);
	uint8_t* bufferPtr = buffer.data();

	GameHistoryHeader header;
	header.chunkCount = chunkCount;

	std::memcpy(bufferPtr, reinterpret_cast<void*>(&header), headerByteSize);
	bufferPtr += headerByteSize;

	std::vector<GameHistoryChunk> chunks(chunkCount);
	std::list<History>::iterator historyIt = histories_.begin();
	for (uint32_t index = 0; index < chunks.size(); ++index, ++historyIt)
	{
		chunks[index].score = historyIt->score;
		wcscpy_s(chunks[index].time, GameHistoryChunk::MAX_STRING_SIZE, historyIt->time.data());
	}

	std::memcpy(bufferPtr, chunks.data(), sourceByteSize);

	GameUtils::WriteFile(path, buffer);
}
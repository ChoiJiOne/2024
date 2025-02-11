#pragma once

#include <map>

#include "GameMath.h"
#include "Texture2D.h"

class Atlas2D : public Texture2D
{
public:
	struct Block /** �ؽ�ó ���� ���Դϴ�. */
	{
		Vec2i pos;
		Vec2i size;
	};

public:
	Atlas2D(const std::string& imagePath, const std::string& jsonPath, const Filter& filter);
	virtual ~Atlas2D();

	DISALLOW_COPY_AND_ASSIGN(Atlas2D);

	virtual void Release() override;

	const std::vector<std::string>& GetKeys() const { return keys_; }
	const Block& GetByName(const std::string& name) const;

private:
	std::vector<std::string> keys_;
	std::map<std::string, Block> blocks_;
};
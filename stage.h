#pragma once
#include <vector>
#include <string>

class Player;
class Object;
class GameManeger;

const int stageWidth = 11;		// ステージの幅
const int stageHeight = 11;	// ステージの高さ

class Stage
{
	public:
	int stageHandle[3];	// ステージのハンドル
	char* map[stageWidth*stageHeight];	// ステージのマップデータ
	int currentStage; // 現在のステージ番号
	std::vector<std::vector<std::string>> maps; // 全ステージのマップデータ
	Stage();
	~Stage();
	void Initialize(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game);
	void Update();
	void Draw();
	bool isHit(int x, int y);
};
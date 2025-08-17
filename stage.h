#pragma once

class Player;
class Object;

const int stageWidth = 11;		// ステージの幅
const int stageHeight = 11;	// ステージの高さ

class Stage
{
	public:
	int stageHandle[3];	// ステージのハンドル
	char* map[stageWidth*stageHeight];	// ステージのマップデータ
	Stage();
	~Stage();
	void Initialize(std::shared_ptr<Player> player, std::shared_ptr<Object> object);
	void Update();
	void Draw();

	bool isHit(int x, int y);

};
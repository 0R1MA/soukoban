#pragma once

class player;
class Object;

class GameManeger
{
public:
	std::vector<VECTOR> goalPosition;
	bool isClear;
	bool undo;
	bool reset;

	GameManeger();
	~GameManeger();
	void Initialize(int Index, VECTOR Pos);
	void Update(std::vector<std::shared_ptr<Object>> objects);
	void ClearCheck(std::vector<std::shared_ptr<Object>> objects);
	void Undo();
	void Draw();
};
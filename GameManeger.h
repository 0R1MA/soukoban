#pragma once
#include <stack>

class Stage;
class Player;
class Object;

struct GameState {
	VECTOR playerPos;
	std::vector<VECTOR> objectPositions;
};

class GameManeger
{
public:
	std::vector<VECTOR> goalPosition;
	std::stack<GameState> history;
	bool isClear;
	bool _next;
	bool undo;

	GameManeger();
	~GameManeger();
	void Initialize();
	void SetGoal(int Index, VECTOR Pos);
	void Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects);
	void ClearCheck(std::vector<std::shared_ptr<Object>> objects);
	void SaveState(VECTOR player, const std::vector<std::shared_ptr<Object>>& objects);
	void Undo(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects);
	bool Reset();
	bool NextStage();
	void PreviousStage();
	void Draw();
};
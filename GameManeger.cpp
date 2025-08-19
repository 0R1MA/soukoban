#include "DxLib.h"
#include <memory>
#include <vector>
#include <stack>
#include "GameManeger.h"
#include "stage.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"

GameManeger::GameManeger()
{
	isClear = false;
	_next	= false;
	undo	= false;
}

GameManeger::~GameManeger()
{
	
}

void GameManeger::Initialize()
{

}

void GameManeger::SetGoal(int Index, VECTOR Pos)
{
	goalPosition.emplace_back(Pos);
}

void GameManeger::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects)
{
	
	if (CheckHitKey(KEY_INPUT_B))
	{
		if (!undo)
		{
			undo = true; // Bキーが押されたらUndoフラグを立てる
			Undo(player, objects); // Bキーが押されたらUndoを実行
		}
	}
	else
	{
		undo = false; // Bキーが押されていない場合はUndoフラグを下ろす
	}
	ClearCheck(objects);
}

void GameManeger::ClearCheck(std::vector<std::shared_ptr<Object>> objects)
{
	//　ゴール地点上にあるオブジェクトの数を数える
	int count = 0;
	for (auto obj : objects)
	{
		for (auto Goal : goalPosition)
		{
			if (obj->position.x == Goal.x && obj->position.y == Goal.y)
			{
				obj->onGoal = true; // オブジェクトがゴールに到達したとマーク
				++count;
				break; // 一つのゴールに到達したら次のオブジェクトへ
			}
			else
			{
				obj->onGoal = false; // オブジェクトがゴールに到達していないとマーク
			}
		}
	}

	if (count == goalPosition.size())
	{
		isClear = true;
	}
	else
	{
		isClear = false;
	}
}

void GameManeger::SaveState(VECTOR player, const std::vector<std::shared_ptr<Object>>& objects)
{
	GameState state;
	state.playerPos = player;
	for (auto& obj : objects) {
		state.objectPositions.push_back(obj->position);
	}
	history.push(state);
}

void GameManeger::Undo(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects)
{
	if (!history.empty()) {
		GameState state = history.top();
		history.pop();
		player->SetPosition(state.playerPos);
		for (size_t i = 0; i < objects.size(); ++i) {
			objects[i]->SetPosition(state.objectPositions[i]);
			if (objects[i]->position.x == 0 && objects[i]->position.y == 0)
				objects[i]->modelHandle = -1;
		}
	}
}

bool GameManeger::Reset()
{
	// ここにリセット処理を実装
	if(CheckHitKey(KEY_INPUT_R))
	{
		goalPosition.clear();
		history = std::stack<GameState>(); // 履歴をクリア
		return true; // リセットが成功した場合
	}
	else
	{
		return false; // リセットが行われなかった場合
	}
	
}

bool GameManeger::NextStage()
{

	if (CheckHitKey(KEY_INPUT_LSHIFT) && CheckHitKey(KEY_INPUT_N))
	{
		if (!_next)
		{
			_next = true;
			goalPosition.clear();
			history = std::stack<GameState>(); // 履歴をクリア
			return true; // ステージクリアで次のステージへ進む
		}
	}
	else
	{
		_next = false;
	}

	// 次のステージへ進む処理を実装
	if (isClear && CheckHitKey(KEY_INPUT_RETURN))
	{
		history = std::stack<GameState>(); // 履歴をクリア
		goalPosition.clear();
		return true; // ステージクリアで次のステージへ進む
	}
	else
	{
		return false; // まだ次のステージに進めない
	}
}

void GameManeger::PreviousStage()
{
	// 数字入力で選んだステージにいける
}

void GameManeger::Draw()
{
	if (isClear)
	{
		SetFontSize(150);		// フォントのサイズを設定
		DrawString(140, 250, "CLEAR", 0xFAFA0A);
	}
}
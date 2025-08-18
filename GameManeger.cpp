#include "DxLib.h"
#include <memory>
#include <vector>
#include "GameManeger.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"

GameManeger::GameManeger()
{
	isClear = false;
	undo	= false;
	reset	= false;
}

GameManeger::~GameManeger()
{
	
}

void GameManeger::Initialize(int Index, VECTOR Pos)
{
	goalPosition.emplace_back(Pos);
}

void GameManeger::Update(std::vector<std::shared_ptr<Object>> objects)
{
	ClearCheck(objects);
	Undo();
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
				++count;
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

void GameManeger::Undo()
{

}

void GameManeger::Draw()
{
	if (isClear)
	{
		DrawString(220, 220, "CLEAR", 0xFAFA0A);
	}
}
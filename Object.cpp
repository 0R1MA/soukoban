#include "DxLib.h"
#include <memory>
#include "Object.h"
#include "Stage.h"

Object::Object()
{
	modelHandle = LoadGraph("date/WoodenCrate.png"); // モデルのハンドルをロード
	position = VGet(0.0f, 0.0f, 0.0f); // 初期位置を設定
	nextPosition = position; // 次の位置も初期位置に設定
	speed = 8.0f; // 移動速度を設定
	Initialize(VGet(300, 300, 0)); // 初期化関数を呼び出す
}

Object::~Object()
{
	// デストラクタの後始末処理
	if (modelHandle != -1)
	{
		DeleteGraph(modelHandle); // モデルのハンドルを削除
	}
}

void Object::Initialize(VECTOR pos)
{
	position = pos; // 位置を設定
	nextPosition = position; // 次の位置も初期位置に設定
}

void Object::Update()
{
	// オブジェクトの更新処理
	if(position.x != nextPosition.x || position.y != nextPosition.y)
	{
		//positionをnextPositonに速度に応じて移動させる
		if (position.x < nextPosition.x)
		{
			position.x += speed;
			if (position.x > nextPosition.x) position.x = nextPosition.x; // オーバーシュート防止
		}
		else if (position.x > nextPosition.x)
		{
			position.x -= speed;
			if (position.x < nextPosition.x) position.x = nextPosition.x; // オーバーシュート防止
		}
		if (position.y < nextPosition.y)
		{
			position.y += speed;
			if (position.y > nextPosition.y) position.y = nextPosition.y; // オーバーシュート防止
		}
		else if (position.y > nextPosition.y)
		{
			position.y -= speed;
			if (position.y < nextPosition.y) position.y = nextPosition.y; // オーバーシュート防止
		}
	}
}

void Object::Draw()
{
	// オブジェクトの描画処理
	if (modelHandle != -1)
	{
		DrawRotaGraph3((int)position.x-0.1f, (int)position.y+3, 16, 44, 1.9f, 1.5f, 0, modelHandle, TRUE, FALSE);
	}
}
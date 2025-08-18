#include "DxLib.h"
#include <memory>
#include <vector>
#include "Anim.h"
#include "Player.h"
#include "Stage.h"
#include "Object.h"

Player::Player() :Anim("date/IdleAnimations.png", "date/WalkAnimations.png")
{
	state = Idle;
	position = VGet(0.0f, 0.0f, 0.0f);
	nextPosition = VGet(0.0f, 0.0f, 0.0f);
	direction = VGet(0.0f, 0.0f, 0.0f);
	speed = 0.0f;
	onKey = false;
}

Player::~Player()
{
	
}

void Player::Initialize(VECTOR pos)
{
	position = pos;
	direction = VGet(0.0f, 0.0f, 0.0f);
	nextPosition = position; // 初期位置を次のポジションに設定
	speed = 4.0f;
}

void Player::Update(std::shared_ptr<Stage> stage, std::vector<std::shared_ptr<Object>> objects)
{
	if(position.x == nextPosition.x && position.y == nextPosition.y)
	{
		state = Idle; // 静止状態にする
		if (!CheckHitKeyAll())
		{
			onKey = false;
		}
	}
	else
	{
		state = Walk; // 歩き状態にする
		onKey = true; // キー入力がある状態にする
	}
	// キー入力は一度だけ受け付ける　入力がなくなった時に次の移動を受け付ける
	// マップチップ上を格子点移動する
	if ((CheckHitKey(KEY_INPUT_UP)||CheckHitKey(KEY_INPUT_W)) && !onKey)
	{
		direction = VGet(0.0f, -60.0f, 0.0f);
		dir = 3; // 上方向
		SetNextPosition(direction);
	}
	else if ((CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) && !onKey)
	{
		direction = VGet(0.0f, 60.0f, 0.0f);
		dir = 0; // 下方向
		SetNextPosition(direction);
	}
	else if ((CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) && !onKey)
	{
		direction = VGet(-60.0f, 0.0f, 0.0f);
		dir = 2; // 左方向
		SetNextPosition(direction);
	}
	else if ((CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) && !onKey)
	{
		direction = VGet(60.0f, 0.0f, 0.0f);
		dir = 1; // 右方向
		SetNextPosition(direction);
	}
	else if (!CheckHitKeyAll())
	{
		onKey = false;
	}


	// ステージの衝突判定
	bool ismove = stage->isHit((int)nextPosition.x, (int)nextPosition.y); 
	if (ismove)
	{
		nextPosition = position; // 衝突している場合は元の位置に戻す
	}

	for (auto obj : objects)
	{
		if (nextPosition.x == obj->position.x && nextPosition.y == obj->position.y)
		{
			// オブジェクトとの衝突判定
			ObjectCollision(stage, obj, objects);
		}
	}
	

	// 移動処理
	Move();
	Anim::Update(); // アニメーションの更新
}

void Player::ObjectCollision(std::shared_ptr<Stage> stage, std::shared_ptr<Object> object, std::vector<std::shared_ptr<Object>> objects)
{
	VECTOR nextObjctPos = VAdd(object->position, direction); // オブジェクトの次の位置を計算
	// オブジェクトの移動可能かどうかを判定
	bool ismove = stage->isHit((int)nextObjctPos.x, (int)nextObjctPos.y);
	for (auto obj : objects)
	{
		if (obj->position.x == nextObjctPos.x && obj->position.y == nextObjctPos.y)
		{
			ismove = true;
		}
	}
	if (!ismove)
	{
		// オブジェクトが移動可能な場合
		object->nextPosition = nextObjctPos; // オブジェクトの位置を更新
	}
	else
	{
		nextPosition = position; // オブジェクトが移動できない場合はプレイヤーの位置を元に戻す
	}
}

void Player::Draw()
{
	Anim::Draw(position); // アニメーションの描画
	//DrawBoxAA(position.x - 30, position.y - 30, position.x + 30, position.y + 30, GetColor(255, 0, 0), false); // プレイヤーの位置を赤い四角で表示
}

void Player::SetNextPosition(VECTOR dir)
{
	nextPosition = VAdd(position, dir);
	onKey = true;
}

void Player::Move()
{
	// 移動処理 次のポジションに向かって移動
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
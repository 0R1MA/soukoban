#pragma once

class Stage;

class Object
{
	public:
	int modelHandle;	// モデルのハンドル
	VECTOR position;	// 位置
	VECTOR nextPosition;	// 次の位置
	float speed;		// 移動速度
	bool onGoal;	// ゴールに到達したかどうか

	Object();
	~Object();
	void Initialize();
	void SetPosition(VECTOR pos);
	void Update();
	void Draw();
};
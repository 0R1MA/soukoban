#pragma once

class Stage;

class Object
{
	public:
	int modelHandle;	// モデルのハンドル
	VECTOR position;	// 位置
	VECTOR nextPosition;	// 次の位置
	float speed;		// 移動速度

	Object();
	~Object();
	void Initialize(VECTOR pos);
	void Update();
	void Draw();
};
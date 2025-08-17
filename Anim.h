#pragma once

class Anim
{
	public:

	enum
	{
		Idle,	// 静止
		Walk,	// 歩き
	};

	Anim(const char* path1, const char* path2);
	~Anim();
	void Update();
	void Draw(VECTOR Pos);

protected:
	const int IdleMax = 4;			// 最大フレーム数
	const int WalkMax = 6;			// 最大フレーム数
	int IdleModelHandle[16];		// 静止
	int WalkModelHandle[24];		// 歩き
	int state;						// 現在の状態
	int dir;						// アニメーションの方向
	int frame;						// 現在のフレーム
	int NowAnimation; 				// 現在のアニメーション
	int NowPattern;					// 現在のパターン
	float modelsize; 				// モデルのサイズ
	float time;						// 時間計測用
	const float FPS = 60.0f;		// フレームレート
};
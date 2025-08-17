#include "DxLib.h"
#include "Anim.h"

Anim::Anim(const char* path1, const char* path2)
{
	dir				= 0; // 初期方向
	frame			= 0; // 初期フレーム
	state			= Idle;
	time			= 0.0f;
	NowAnimation	= 0;
	NowPattern		= 0;
	modelsize		= 1.3f; // モデルのサイズ
	LoadDivGraph(path1, 16, 4, 4, 80, 80, IdleModelHandle);
	LoadDivGraph(path2, 24, 5, 5, 80, 80, WalkModelHandle);
}

Anim::~Anim()
{

}

void Anim::Update()
{
	time += 1.0f / FPS; // 時間を更新
	if(time >= 10.0f / FPS)
	{
		frame++; // フレームを進める
		time = 0.0f; // 時間をリセット
		if(frame >= (state == Idle ? IdleMax : WalkMax))
		{
			frame = 0; // フレームをリセット
		}
	}
	if(state == Idle && frame >= IdleMax)
	{
		frame = 0;
	}
	else if(state == Walk && frame >= WalkMax)
	{
		frame = 0; 
	}

	// アニメーションの更新処理をここに実装
	if (state == Idle)
	{
		NowPattern = dir * IdleMax + frame; // 現在のパターンを計算
		NowAnimation = IdleModelHandle[NowPattern];
	}
	else if (state == Walk)
	{
		NowPattern = dir * WalkMax + frame; // 現在のパターンを計算
		NowAnimation = WalkModelHandle[NowPattern];
	}
}

void Anim::Draw(VECTOR Pos)
{
	// アニメーションの描画処理をここに実装
	DrawRotaGraph3(Pos.x, Pos.y, 40, 40, modelsize, modelsize, 0, NowAnimation, TRUE, FALSE);
}
#include "DxLib.h"
#include <iostream>
#include <math.h>
#include <memory>
#include "Anim.h"
#include "Player.h"
#include "Stage.h"
#include "Object.h"

const int ScreenX = 660;
const int ScreenY = 660;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);
	SetGraphMode(ScreenX, ScreenY, 32);
	// 初期化
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	// 初期化
	std::shared_ptr<Player> player	= std::make_shared<Player>();
	std::shared_ptr<Stage> stage	= std::make_shared<Stage>();
	std::shared_ptr<Object> object	= std::make_shared<Object>();
	
	stage->Initialize(player, object); // ステージの初期化

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// ＥＳＣキーが押されるか、ウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// 処理が始まる前の時間

		// 画面をクリア
		ClearDrawScreen();

		object->Update();				// オブジェクトの更新処理
		player->Update(stage, object);	// プレイヤーの更新処理

		stage->Draw();					// ステージの描画処理
		object->Draw();					// オブジェクトの描画処理
		player->Draw();					// プレイヤーの描画処理

		// 裏画面の内容を表画面に反映
		ScreenFlip();

		// 雑なfps固定処理
		// 差を求めて、1回の画面更新が1/60秒になるようにwhileループ回して待つ
		auto afterTime = GetNowHiPerformanceCount(); // 処理が終わった後の時間
		while (afterTime - prevTime < 16667)
		{
			afterTime = GetNowHiPerformanceCount();
		}
	}

	// 後始末
	player	= nullptr;
	object	= nullptr;
	stage	= nullptr;
	DxLib_End();

	// ソフト終了
	return 0;
}
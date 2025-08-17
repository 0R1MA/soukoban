#include "DxLib.h"
#include <math.h>
#include <memory>
#include "Stage.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"

Stage::Stage()
{
	// コンストラクタの初期化処理
	LoadDivGraph("date/Tile.png", 3, 3, 1, 32, 32, stageHandle);
}

Stage::~Stage()
{
	// デストラクタの後始末処理
}

void Stage::Initialize(std::shared_ptr<Player> player, std::shared_ptr<Object> object)
{
	// ステージの初期化処理
	// ここで必要なリソースのロードや初期設定を行う
	// 空白＝床　＃＝壁　.＝ゴール　$＝箱　@＝プレイヤー
	const char* Map[] =
	{
		"###########",
		"#    .    #",
		"#         #",
		"#    $    #",
		"#         #",
		"#    @    #",
		"#         #",
		"#         #",
		"#         #",
		"#         #",
		"###########",
	};
	// マップデータの初期化
	for (int y = 0; y < stageHeight; ++y)
	{
		map[y] = new char[stageWidth + 1]; // 各行のマップデータを確保
		for (int x = 0; x < stageWidth; ++x)
		{
			map[y][x] = Map[y][x]; // マップデータをコピー
			// プレイヤーと箱の位置を設定
			if (map[y][x] == '@') // プレイヤーの位置
			{
				// プレイヤーの初期位置を設定
				player->Initialize(VGet(x * 60 + 30, y * 60 + 30, 0.0f)); // プレイヤーの初期位置を設定
			}
			else if (map[y][x] == '$') // 箱の位置
			{
				// 箱の初期位置を設定
				object->Initialize(VGet(x * 60 + 30, y * 60 + 30, 0.0f)); // オブジェクトの初期位置を設定
			}
		}
		map[y][stageWidth] = '\0'; // 行末にヌル文字を追加
	}
}

void Stage::Update()
{
	// ステージの更新処理
	// ここでゲームのロジックや状態の更新を行う
}

void Stage::Draw()
{
	// ステージの描画処理
	// ここでステージの背景やオブジェクトを描画する
	for (int y = 0; y < stageHeight; ++y)
	{
		for (int x = 0; x < stageWidth; ++x)
		{
			int tileType = map[y][x]; // タイルの種類を取得
			int tileIndex = -1; // タイルのインデックスを初期化
			switch (tileType)
			{
				case '#': // 壁
					tileIndex = 0;
					break;
				case ' ': // 床
					tileIndex = 1;
					break;
				case '.': // ゴール
					tileIndex = 2;
					break;
				case '$': // 箱
					tileIndex = 1; // 箱は床と同じタイルを使用
					break;
				case '@': // プレイヤー
					tileIndex = 1; // プレイヤーも床と同じタイルを使用
					break;
			}
			if (tileIndex != -1)
			{
				DrawRotaGraph3(x * 60 + 30, y * 60 + 30, 16, 16, 2.f, 2.f, 0, stageHandle[tileIndex], TRUE, FALSE); // タイルを描画
			}
		}
	}
}

bool Stage::isHit(int x, int y)
{
	// 指定された座標がステージの壁に衝突しているかどうかを判定
	int tileX = x / 60; // タイルのX座標
	int tileY = y / 60; // タイルのY座標
	// 範囲外チェック
	if (tileX < 0 || tileX >= stageWidth || tileY < 0 || tileY >= stageHeight)
	{
		return false; // 範囲外の場合は衝突しない
	}
	// タイルが壁の場合は衝突
	if (map[tileY][tileX] == '#')
	{
		return true; // 衝突している
	}
	return false; // 衝突していない
}
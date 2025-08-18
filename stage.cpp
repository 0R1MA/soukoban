#include "DxLib.h"
#include <memory>
#include "Stage.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"
#include "GameManeger.h"

Stage::Stage()
	: currentStage(0)
{
	// コンストラクタの初期化処理
	maps = {
	   {
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXX###XXXX",
		   "XXXX#.#XXXX",
		   "XXXX# #XXXX",
		   "XXXX#$#XXXX",
		   "XXXX# #XXXX",
		   "XXXX# #XXXX",
		   "XXXX#@#XXXX",
		   "XXXX###XXXX",
		   "XXXXXXXXXXX",
	   }, {
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X#########X",
		   "X#@      #X",
		   "X#       #X",
		   "X# .  $  #X",
		   "X#       #X",
		   "X#    $ .#X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X########XX",
		   "X#@     ##X",
		   "X#.  $*  #X",
		   "X#    #  #X",
		   "X#       #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X########XX",
		   "X#@     ##X",
		   "X#  $$   #X",
		   "X#  #.  .#X",
		   "X#       #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXX####XX",
		   "X#####  #XX",
		   "X#@   .$##X",
		   "X#     $ #X",
		   "X# #  .  #X",
		   "X#       #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XX#######XX",
		   "X##  @  ##X",
		   "X#   #   #X",
		   "X#  $*$  #X",
		   "X#   .   #X",
		   "X##  .  ##X",
		   "XX#######XX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X#######XXX",
		   "X#     ###X",
		   "X#    .. #X",
		   "X#  $$$@ #X",
		   "X#   # . #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXX#####XX",
		   "XX###  @#XX",
		   "XX#. *# #XX",
		   "XX#   $ #XX",
		   "XX# $. ##XX",
		   "XX######XXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XX######XXX",
		   "XX#@ ..#XXX",
		   "XX# #$ ##XX",
		   "XX# #   #XX",
		   "XX#  $# #XX",
		   "XX#  *  #XX",
		   "XX#######XX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		},
		 {
		   "###########",
		   "# ***     #",
		   "#*        #",
		   "#* ***    #",
		   "#*   *    #",
		   "# *** *** #",
		   "#    *    #",
		   "#    * ***#",
		   "#    *   *#",
		   "#@   $.** #",
		   "###########",
		 }
	};
	LoadDivGraph("date/Tile.png", 3, 3, 1, 32, 32, stageHandle);
}

Stage::~Stage()
{
	// デストラクタの後始末処理
}

void Stage::Initialize()
{
	// ステージの初期化処理
}

void Stage::SetStage(int stageIndex, std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game)
{
	// ステージを設定する処理
	if (stageIndex < 0 || stageIndex >= maps.size())
	{
		return; // 無効なステージインデックスの場合は何もしない
	}
	currentStage = stageIndex;

	const std::vector<std::string>& Map = maps[currentStage];
	int object_count = 0, clearPos_count = 0;
	for (int y = 0; y < stageHeight; ++y)
	{
		map[y] = new char[stageWidth + 1];
		for (int x = 0; x < stageWidth; ++x)
		{
			map[y][x] = Map[y][x];
			if (map[y][x] == '@' || map[y][x] == '+')
				player->SetPosition(VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
			if (map[y][x] == '$' || map[y][x] == '*')
			{
				objects.at(object_count)->SetPosition(VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
				++object_count;
			}
			if (map[y][x] == '.' || map[y][x] == '*' || map[y][x] == '+')
			{
				game->SetGoal(clearPos_count, VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
				++clearPos_count;
			}
		}
		map[y][stageWidth] = '\0';
	}
	for (auto obj : objects)
	{
		if (obj->position.x == 0 && obj->position.y == 0)
			obj->modelHandle = -1;
	}
}

void Stage::Update()
{
	// ステージの更新処理
	// ここでゲームのロジックや状態の更新を行う
}

void Stage::NextStage(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game)
{
	// 次のステージに進む処理
	currentStage = (currentStage + 1) % maps.size();
	for (int y = 0; y < stageHeight; ++y)
	{
		delete[] map[y];
	}
	for (auto obj : objects){
		obj->Initialize(); // オブジェクトの初期化
	}
	SetStage(currentStage, player, objects, game); // 必要なインスタンスを渡して初期化
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
				case '+': //　プレイヤーとゴール
					tileIndex = 2; // プレイヤーとゴールが重なっている場合はゴールタイルを使用
					break;
				case '*': // 箱とゴール
					tileIndex = 2; // 箱とゴールが重なっている場合はゴールタイルを使用
					break;
				case 'X': // ステージ外のタイル
					tileIndex = -1; // 表示しない
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
		return false;	// 範囲外の場合は衝突しない
	}
	// タイルが壁の場合は衝突
	if (map[tileY][tileX] == '#')
	{
		return true;	// 衝突している
	}
	return false;		// 衝突していない
}
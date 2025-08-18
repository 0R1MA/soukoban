#pragma once

class Stage;
class Object;
class GameManeger;

class Player : public Anim
{
public:
	Player();
	~Player();
	void Initialize();
	void SetPosition(VECTOR pos);	// 位置を設定
	void Update(std::shared_ptr<GameManeger> game, std::shared_ptr<Stage> stage, std::vector<std::shared_ptr<Object>> objects);
	void ObjectCollision(std::shared_ptr<Stage> stage, std::shared_ptr<Object> object, std::vector<std::shared_ptr<Object>> objects);	// オブジェクトとの衝突判定
	void Draw();

	VECTOR GetPosition() const { return position; }	// 現在の位置を取得

private:
	VECTOR position;	// ポジション
	VECTOR direction;	// 方向ベクトル
	VECTOR nextPosition;	// 次のポジション
	float speed;		// 移動速度
	bool onKey;		// キー入力フラグ
	bool onMove;	// 移動中フラグ

	void SetNextPosition(VECTOR dir);	// 次のポジションを設定
	void Move();		// 移動処理
};
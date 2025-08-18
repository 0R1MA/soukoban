#pragma once

class Stage;
class Object;

class Player : public Anim
{
public:
	Player();
	~Player();
	void Initialize(VECTOR pos);
	void Update(std::shared_ptr<Stage> stage, std::vector<std::shared_ptr<Object>> objects);
	void ObjectCollision(std::shared_ptr<Stage> stage, std::shared_ptr<Object> object, std::vector<std::shared_ptr<Object>> objects);	// オブジェクトとの衝突判定
	void Draw();

private:
	VECTOR position;	// ポジション
	VECTOR direction;	// 方向ベクトル
	VECTOR nextPosition;	// 次のポジション
	float speed;		// 移動速度
	bool onKey;		// キー入力フラグ

	void SetNextPosition(VECTOR dir);	// 次のポジションを設定
	void Move();		// 移動処理
};
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
	void SetPosition(VECTOR pos);	// �ʒu��ݒ�
	void Update(std::shared_ptr<GameManeger> game, std::shared_ptr<Stage> stage, std::vector<std::shared_ptr<Object>> objects);
	void ObjectCollision(std::shared_ptr<Stage> stage, std::shared_ptr<Object> object, std::vector<std::shared_ptr<Object>> objects);	// �I�u�W�F�N�g�Ƃ̏Փ˔���
	void Draw();

	VECTOR GetPosition() const { return position; }	// ���݂̈ʒu���擾

private:
	VECTOR position;	// �|�W�V����
	VECTOR direction;	// �����x�N�g��
	VECTOR nextPosition;	// ���̃|�W�V����
	float speed;		// �ړ����x
	bool onKey;		// �L�[���̓t���O
	bool onMove;	// �ړ����t���O

	void SetNextPosition(VECTOR dir);	// ���̃|�W�V������ݒ�
	void Move();		// �ړ�����
};
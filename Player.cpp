#include "DxLib.h"
#include <memory>
#include <vector>
#include "Anim.h"
#include "Player.h"
#include "Stage.h"
#include "Object.h"

Player::Player() :Anim("date/IdleAnimations.png", "date/WalkAnimations.png")
{
	state = Idle;
	position = VGet(0.0f, 0.0f, 0.0f);
	nextPosition = VGet(0.0f, 0.0f, 0.0f);
	direction = VGet(0.0f, 0.0f, 0.0f);
	speed = 0.0f;
	onKey = false;
}

Player::~Player()
{
	
}

void Player::Initialize(VECTOR pos)
{
	position = pos;
	direction = VGet(0.0f, 0.0f, 0.0f);
	nextPosition = position; // �����ʒu�����̃|�W�V�����ɐݒ�
	speed = 4.0f;
}

void Player::Update(std::shared_ptr<Stage> stage, std::vector<std::shared_ptr<Object>> objects)
{
	if(position.x == nextPosition.x && position.y == nextPosition.y)
	{
		state = Idle; // �Î~��Ԃɂ���
		if (!CheckHitKeyAll())
		{
			onKey = false;
		}
	}
	else
	{
		state = Walk; // ������Ԃɂ���
		onKey = true; // �L�[���͂������Ԃɂ���
	}
	// �L�[���͈͂�x�����󂯕t����@���͂��Ȃ��Ȃ������Ɏ��̈ړ����󂯕t����
	// �}�b�v�`�b�v����i�q�_�ړ�����
	if ((CheckHitKey(KEY_INPUT_UP)||CheckHitKey(KEY_INPUT_W)) && !onKey)
	{
		direction = VGet(0.0f, -60.0f, 0.0f);
		dir = 3; // �����
		SetNextPosition(direction);
	}
	else if ((CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) && !onKey)
	{
		direction = VGet(0.0f, 60.0f, 0.0f);
		dir = 0; // ������
		SetNextPosition(direction);
	}
	else if ((CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) && !onKey)
	{
		direction = VGet(-60.0f, 0.0f, 0.0f);
		dir = 2; // ������
		SetNextPosition(direction);
	}
	else if ((CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) && !onKey)
	{
		direction = VGet(60.0f, 0.0f, 0.0f);
		dir = 1; // �E����
		SetNextPosition(direction);
	}
	else if (!CheckHitKeyAll())
	{
		onKey = false;
	}


	// �X�e�[�W�̏Փ˔���
	bool ismove = stage->isHit((int)nextPosition.x, (int)nextPosition.y); 
	if (ismove)
	{
		nextPosition = position; // �Փ˂��Ă���ꍇ�͌��̈ʒu�ɖ߂�
	}

	for (auto obj : objects)
	{
		if (nextPosition.x == obj->position.x && nextPosition.y == obj->position.y)
		{
			// �I�u�W�F�N�g�Ƃ̏Փ˔���
			ObjectCollision(stage, obj, objects);
		}
	}
	

	// �ړ�����
	Move();
	Anim::Update(); // �A�j���[�V�����̍X�V
}

void Player::ObjectCollision(std::shared_ptr<Stage> stage, std::shared_ptr<Object> object, std::vector<std::shared_ptr<Object>> objects)
{
	VECTOR nextObjctPos = VAdd(object->position, direction); // �I�u�W�F�N�g�̎��̈ʒu���v�Z
	// �I�u�W�F�N�g�̈ړ��\���ǂ����𔻒�
	bool ismove = stage->isHit((int)nextObjctPos.x, (int)nextObjctPos.y);
	for (auto obj : objects)
	{
		if (obj->position.x == nextObjctPos.x && obj->position.y == nextObjctPos.y)
		{
			ismove = true;
		}
	}
	if (!ismove)
	{
		// �I�u�W�F�N�g���ړ��\�ȏꍇ
		object->nextPosition = nextObjctPos; // �I�u�W�F�N�g�̈ʒu���X�V
	}
	else
	{
		nextPosition = position; // �I�u�W�F�N�g���ړ��ł��Ȃ��ꍇ�̓v���C���[�̈ʒu�����ɖ߂�
	}
}

void Player::Draw()
{
	Anim::Draw(position); // �A�j���[�V�����̕`��
	//DrawBoxAA(position.x - 30, position.y - 30, position.x + 30, position.y + 30, GetColor(255, 0, 0), false); // �v���C���[�̈ʒu��Ԃ��l�p�ŕ\��
}

void Player::SetNextPosition(VECTOR dir)
{
	nextPosition = VAdd(position, dir);
	onKey = true;
}

void Player::Move()
{
	// �ړ����� ���̃|�W�V�����Ɍ������Ĉړ�
	if (position.x < nextPosition.x)
	{
		position.x += speed;
		if (position.x > nextPosition.x) position.x = nextPosition.x; // �I�[�o�[�V���[�g�h�~
	}
	else if (position.x > nextPosition.x)
	{
		position.x -= speed;
		if (position.x < nextPosition.x) position.x = nextPosition.x; // �I�[�o�[�V���[�g�h�~
	}
	if (position.y < nextPosition.y)
	{
		position.y += speed;
		if (position.y > nextPosition.y) position.y = nextPosition.y; // �I�[�o�[�V���[�g�h�~
	}
	else if (position.y > nextPosition.y)
	{
		position.y -= speed;
		if (position.y < nextPosition.y) position.y = nextPosition.y; // �I�[�o�[�V���[�g�h�~
	}
}
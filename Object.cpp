#include "DxLib.h"
#include <memory>
#include "Object.h"
#include "Stage.h"

Object::Object()
{
	modelHandle = LoadGraph("date/WoodenCrate.png"); // ���f���̃n���h�������[�h
	position = VGet(0.0f, 0.0f, 0.0f); // �����ʒu��ݒ�
	nextPosition = position; // ���̈ʒu�������ʒu�ɐݒ�
	speed = 8.0f; // �ړ����x��ݒ�
	Initialize(VGet(300, 300, 0)); // �������֐����Ăяo��
}

Object::~Object()
{
	// �f�X�g���N�^�̌�n������
	if (modelHandle != -1)
	{
		DeleteGraph(modelHandle); // ���f���̃n���h�����폜
	}
}

void Object::Initialize(VECTOR pos)
{
	position = pos; // �ʒu��ݒ�
	nextPosition = position; // ���̈ʒu�������ʒu�ɐݒ�
}

void Object::Update()
{
	// �I�u�W�F�N�g�̍X�V����
	if(position.x != nextPosition.x || position.y != nextPosition.y)
	{
		//position��nextPositon�ɑ��x�ɉ����Ĉړ�������
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
}

void Object::Draw()
{
	// �I�u�W�F�N�g�̕`�揈��
	if (modelHandle != -1)
	{
		DrawRotaGraph3((int)position.x-0.1f, (int)position.y+3, 16, 44, 1.9f, 1.5f, 0, modelHandle, TRUE, FALSE);
	}
}
#pragma once

class Stage;

class Object
{
	public:
	int modelHandle;	// ���f���̃n���h��
	VECTOR position;	// �ʒu
	VECTOR nextPosition;	// ���̈ʒu
	float speed;		// �ړ����x
	bool onGoal;	// �S�[���ɓ��B�������ǂ���

	Object();
	~Object();
	void Initialize();
	void SetPosition(VECTOR pos);
	void Update();
	void Draw();
};
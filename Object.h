#pragma once

class Stage;

class Object
{
	public:
	int modelHandle;	// ���f���̃n���h��
	VECTOR position;	// �ʒu
	VECTOR nextPosition;	// ���̈ʒu
	float speed;		// �ړ����x

	Object();
	~Object();
	void Initialize(VECTOR pos);
	void Update();
	void Draw();
};
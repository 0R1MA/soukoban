#pragma once

class Anim
{
	public:

	enum
	{
		Idle,	// �Î~
		Walk,	// ����
	};

	Anim(const char* path1, const char* path2);
	~Anim();
	void Update();
	void Draw(VECTOR Pos);

protected:
	const int IdleMax = 4;			// �ő�t���[����
	const int WalkMax = 6;			// �ő�t���[����
	int IdleModelHandle[16];		// �Î~
	int WalkModelHandle[24];		// ����
	int state;						// ���݂̏��
	int dir;						// �A�j���[�V�����̕���
	int frame;						// ���݂̃t���[��
	int NowAnimation; 				// ���݂̃A�j���[�V����
	int NowPattern;					// ���݂̃p�^�[��
	float modelsize; 				// ���f���̃T�C�Y
	float time;						// ���Ԍv���p
	const float FPS = 60.0f;		// �t���[�����[�g
};
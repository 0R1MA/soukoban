#include "DxLib.h"
#include "Anim.h"

Anim::Anim(const char* path1, const char* path2)
{
	dir				= 0; // ��������
	frame			= 0; // �����t���[��
	state			= Idle;
	time			= 0.0f;
	NowAnimation	= 0;
	NowPattern		= 0;
	modelsize		= 1.3f; // ���f���̃T�C�Y
	LoadDivGraph(path1, 16, 4, 4, 80, 80, IdleModelHandle);
	LoadDivGraph(path2, 24, 5, 5, 80, 80, WalkModelHandle);
}

Anim::~Anim()
{

}

void Anim::Update()
{
	time += 1.0f / FPS; // ���Ԃ��X�V
	if(time >= 10.0f / FPS)
	{
		frame++; // �t���[����i�߂�
		time = 0.0f; // ���Ԃ����Z�b�g
		if(frame >= (state == Idle ? IdleMax : WalkMax))
		{
			frame = 0; // �t���[�������Z�b�g
		}
	}
	if(state == Idle && frame >= IdleMax)
	{
		frame = 0;
	}
	else if(state == Walk && frame >= WalkMax)
	{
		frame = 0; 
	}

	// �A�j���[�V�����̍X�V�����������Ɏ���
	if (state == Idle)
	{
		NowPattern = dir * IdleMax + frame; // ���݂̃p�^�[�����v�Z
		NowAnimation = IdleModelHandle[NowPattern];
	}
	else if (state == Walk)
	{
		NowPattern = dir * WalkMax + frame; // ���݂̃p�^�[�����v�Z
		NowAnimation = WalkModelHandle[NowPattern];
	}
}

void Anim::Draw(VECTOR Pos)
{
	// �A�j���[�V�����̕`�揈���������Ɏ���
	DrawRotaGraph3(Pos.x, Pos.y, 40, 40, modelsize, modelsize, 0, NowAnimation, TRUE, FALSE);
}
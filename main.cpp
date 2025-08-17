#include "DxLib.h"
#include <iostream>
#include <math.h>
#include <memory>
#include "Anim.h"
#include "Player.h"
#include "Stage.h"
#include "Object.h"

const int ScreenX = 660;
const int ScreenY = 660;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	SetGraphMode(ScreenX, ScreenY, 32);
	// ������
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	// ������
	std::shared_ptr<Player> player	= std::make_shared<Player>();
	std::shared_ptr<Stage> stage	= std::make_shared<Stage>();
	std::shared_ptr<Object> object	= std::make_shared<Object>();
	
	stage->Initialize(player, object); // �X�e�[�W�̏�����

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �d�r�b�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// �������n�܂�O�̎���

		// ��ʂ��N���A
		ClearDrawScreen();

		object->Update();				// �I�u�W�F�N�g�̍X�V����
		player->Update(stage, object);	// �v���C���[�̍X�V����

		stage->Draw();					// �X�e�[�W�̕`�揈��
		object->Draw();					// �I�u�W�F�N�g�̕`�揈��
		player->Draw();					// �v���C���[�̕`�揈��

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();

		// �G��fps�Œ菈��
		// �������߂āA1��̉�ʍX�V��1/60�b�ɂȂ�悤��while���[�v�񂵂đ҂�
		auto afterTime = GetNowHiPerformanceCount(); // �������I�������̎���
		while (afterTime - prevTime < 16667)
		{
			afterTime = GetNowHiPerformanceCount();
		}
	}

	// ��n��
	player	= nullptr;
	object	= nullptr;
	stage	= nullptr;
	DxLib_End();

	// �\�t�g�I��
	return 0;
}
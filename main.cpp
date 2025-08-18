#include "DxLib.h"
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>
#include "Anim.h"
#include "Player.h"
#include "Stage.h"
#include "Object.h"
#include "GameManeger.h"

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
	std::shared_ptr<Player>			player	= std::make_shared<Player>();
	std::shared_ptr<Stage>			stage	= std::make_shared<Stage>();
	std::shared_ptr<GameManeger>	game	= std::make_shared<GameManeger>();
	
	std::vector<std::shared_ptr<Object>> objects;	// �I�u�W�F�N�g�̃��X�g
	for(int i = 0; i < 10; ++i)						// ��Ƃ���10�̃I�u�W�F�N�g���쐬
	{
		auto obj = std::make_shared<Object>();
		objects.emplace_back(obj);					// �I�u�W�F�N�g�����X�g�ɒǉ�
	}
	stage->Initialize(player, objects, game);				// �X�e�[�W�̏�����

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �d�r�b�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		auto prevTime = GetNowHiPerformanceCount();	// �������n�܂�O�̎���

		// ��ʂ��N���A
		ClearDrawScreen();

		////�X�V����////
		game->Update(objects);
		for (auto obj : objects)
		{
			obj->Update();				// �I�u�W�F�N�g�̍X�V����
		}
		player->Update(stage, objects);	// �v���C���[�̍X�V����
	

		////�`��////
		stage->Draw();					// �X�e�[�W�̕`�揈��
		for (auto obj : objects)
		{
			obj->Draw();				// �I�u�W�F�N�g�̕`�揈��
		}
		player->Draw();					// �v���C���[�̕`�揈��
		game->Draw();

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
	stage	= nullptr;
	game	= nullptr;
	objects.clear();
	DxLib_End();

	// �\�t�g�I��
	return 0;
}
#include "DxLib.h"
#include <math.h>
#include <memory>
#include "Stage.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"

Stage::Stage()
{
	// �R���X�g���N�^�̏���������
	LoadDivGraph("date/Tile.png", 3, 3, 1, 32, 32, stageHandle);
}

Stage::~Stage()
{
	// �f�X�g���N�^�̌�n������
}

void Stage::Initialize(std::shared_ptr<Player> player, std::shared_ptr<Object> object)
{
	// �X�e�[�W�̏���������
	// �����ŕK�v�ȃ��\�[�X�̃��[�h�⏉���ݒ���s��
	// �󔒁����@�����ǁ@.���S�[���@$�����@@���v���C���[
	const char* Map[] =
	{
		"###########",
		"#    .    #",
		"#         #",
		"#    $    #",
		"#         #",
		"#    @    #",
		"#         #",
		"#         #",
		"#         #",
		"#         #",
		"###########",
	};
	// �}�b�v�f�[�^�̏�����
	for (int y = 0; y < stageHeight; ++y)
	{
		map[y] = new char[stageWidth + 1]; // �e�s�̃}�b�v�f�[�^���m��
		for (int x = 0; x < stageWidth; ++x)
		{
			map[y][x] = Map[y][x]; // �}�b�v�f�[�^���R�s�[
			// �v���C���[�Ɣ��̈ʒu��ݒ�
			if (map[y][x] == '@') // �v���C���[�̈ʒu
			{
				// �v���C���[�̏����ʒu��ݒ�
				player->Initialize(VGet(x * 60 + 30, y * 60 + 30, 0.0f)); // �v���C���[�̏����ʒu��ݒ�
			}
			else if (map[y][x] == '$') // ���̈ʒu
			{
				// ���̏����ʒu��ݒ�
				object->Initialize(VGet(x * 60 + 30, y * 60 + 30, 0.0f)); // �I�u�W�F�N�g�̏����ʒu��ݒ�
			}
		}
		map[y][stageWidth] = '\0'; // �s���Ƀk��������ǉ�
	}
}

void Stage::Update()
{
	// �X�e�[�W�̍X�V����
	// �����ŃQ�[���̃��W�b�N���Ԃ̍X�V���s��
}

void Stage::Draw()
{
	// �X�e�[�W�̕`�揈��
	// �����ŃX�e�[�W�̔w�i��I�u�W�F�N�g��`�悷��
	for (int y = 0; y < stageHeight; ++y)
	{
		for (int x = 0; x < stageWidth; ++x)
		{
			int tileType = map[y][x]; // �^�C���̎�ނ��擾
			int tileIndex = -1; // �^�C���̃C���f�b�N�X��������
			switch (tileType)
			{
				case '#': // ��
					tileIndex = 0;
					break;
				case ' ': // ��
					tileIndex = 1;
					break;
				case '.': // �S�[��
					tileIndex = 2;
					break;
				case '$': // ��
					tileIndex = 1; // ���͏��Ɠ����^�C�����g�p
					break;
				case '@': // �v���C���[
					tileIndex = 1; // �v���C���[�����Ɠ����^�C�����g�p
					break;
			}
			if (tileIndex != -1)
			{
				DrawRotaGraph3(x * 60 + 30, y * 60 + 30, 16, 16, 2.f, 2.f, 0, stageHandle[tileIndex], TRUE, FALSE); // �^�C����`��
			}
		}
	}
}

bool Stage::isHit(int x, int y)
{
	// �w�肳�ꂽ���W���X�e�[�W�̕ǂɏՓ˂��Ă��邩�ǂ����𔻒�
	int tileX = x / 60; // �^�C����X���W
	int tileY = y / 60; // �^�C����Y���W
	// �͈͊O�`�F�b�N
	if (tileX < 0 || tileX >= stageWidth || tileY < 0 || tileY >= stageHeight)
	{
		return false; // �͈͊O�̏ꍇ�͏Փ˂��Ȃ�
	}
	// �^�C�����ǂ̏ꍇ�͏Փ�
	if (map[tileY][tileX] == '#')
	{
		return true; // �Փ˂��Ă���
	}
	return false; // �Փ˂��Ă��Ȃ�
}
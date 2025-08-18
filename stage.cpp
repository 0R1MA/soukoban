#include "DxLib.h"
#include <memory>
#include "Stage.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"
#include "GameManeger.h"

Stage::Stage()
	: currentStage(0)
{
	// �R���X�g���N�^�̏���������
	maps = {
	   {
		   "###########",
		   "#    .    #",
		   "#         #",
		   "#    $    #",
		   "#         #",
		   "#    @    #",
		   "#       . #",
		   "#         #",
		   "#      $  #",
		   "#         #",
		   "###########",
	   },
	   {
		   "###########",
		   "# .     . #",
		   "#   $ $   #",
		   "#         #",
		   "#   @     #",
		   "#         #",
		   "#   $ $   #",
		   "# .     . #",
		   "###########",
	   }
	};
	LoadDivGraph("date/Tile.png", 3, 3, 1, 32, 32, stageHandle);
}

Stage::~Stage()
{
	// �f�X�g���N�^�̌�n������
}

void Stage::Initialize(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game)
{
	// �X�e�[�W�̏���������
	// �����ŕK�v�ȃ��\�[�X�̃��[�h�⏉���ݒ���s��
	// �󔒁����@�����ǁ@.���S�[���@$�����@@���v���C���[
	const std::vector<std::string>& Map = maps[currentStage];
	int object_count = 0, clearPos_count = 0;
	for (int y = 0; y < stageHeight; ++y)
	{
		map[y] = new char[stageWidth + 1];
		for (int x = 0; x < stageWidth; ++x)
		{
			map[y][x] = Map[y][x];
			if (map[y][x] == '@')
				player->Initialize(VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
			else if (map[y][x] == '$')
			{
				objects.at(object_count)->Initialize(VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
				++object_count;
			}
			else if (map[y][x] == '.')
			{
				game->Initialize(clearPos_count, VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
				++clearPos_count;
			}
		}
		map[y][stageWidth] = '\0';
	}
	for (auto obj : objects)
	{
		if (obj->position.x == 0 && obj->position.y == 0)
			obj->modelHandle = -1;
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
		return false;	// �͈͊O�̏ꍇ�͏Փ˂��Ȃ�
	}
	// �^�C�����ǂ̏ꍇ�͏Փ�
	if (map[tileY][tileX] == '#')
	{
		return true;	// �Փ˂��Ă���
	}
	return false;		// �Փ˂��Ă��Ȃ�
}
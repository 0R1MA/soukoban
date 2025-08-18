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
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXX###XXXX",
		   "XXXX#.#XXXX",
		   "XXXX# #XXXX",
		   "XXXX#$#XXXX",
		   "XXXX# #XXXX",
		   "XXXX# #XXXX",
		   "XXXX#@#XXXX",
		   "XXXX###XXXX",
		   "XXXXXXXXXXX",
	   }, {
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X#########X",
		   "X#@      #X",
		   "X#       #X",
		   "X# .  $  #X",
		   "X#       #X",
		   "X#    $ .#X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X########XX",
		   "X#@     ##X",
		   "X#.  $*  #X",
		   "X#    #  #X",
		   "X#       #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X########XX",
		   "X#@     ##X",
		   "X#  $$   #X",
		   "X#  #.  .#X",
		   "X#       #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXX####XX",
		   "X#####  #XX",
		   "X#@   .$##X",
		   "X#     $ #X",
		   "X# #  .  #X",
		   "X#       #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XX#######XX",
		   "X##  @  ##X",
		   "X#   #   #X",
		   "X#  $*$  #X",
		   "X#   .   #X",
		   "X##  .  ##X",
		   "XX#######XX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "X#######XXX",
		   "X#     ###X",
		   "X#    .. #X",
		   "X#  $$$@ #X",
		   "X#   # . #X",
		   "X#########X",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XXXX#####XX",
		   "XX###  @#XX",
		   "XX#. *# #XX",
		   "XX#   $ #XX",
		   "XX# $. ##XX",
		   "XX######XXX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
	   },
		{
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		   "XX######XXX",
		   "XX#@ ..#XXX",
		   "XX# #$ ##XX",
		   "XX# #   #XX",
		   "XX#  $# #XX",
		   "XX#  *  #XX",
		   "XX#######XX",
		   "XXXXXXXXXXX",
		   "XXXXXXXXXXX",
		},
		 {
		   "###########",
		   "# ***     #",
		   "#*        #",
		   "#* ***    #",
		   "#*   *    #",
		   "# *** *** #",
		   "#    *    #",
		   "#    * ***#",
		   "#    *   *#",
		   "#@   $.** #",
		   "###########",
		 }
	};
	LoadDivGraph("date/Tile.png", 3, 3, 1, 32, 32, stageHandle);
}

Stage::~Stage()
{
	// �f�X�g���N�^�̌�n������
}

void Stage::Initialize()
{
	// �X�e�[�W�̏���������
}

void Stage::SetStage(int stageIndex, std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game)
{
	// �X�e�[�W��ݒ肷�鏈��
	if (stageIndex < 0 || stageIndex >= maps.size())
	{
		return; // �����ȃX�e�[�W�C���f�b�N�X�̏ꍇ�͉������Ȃ�
	}
	currentStage = stageIndex;

	const std::vector<std::string>& Map = maps[currentStage];
	int object_count = 0, clearPos_count = 0;
	for (int y = 0; y < stageHeight; ++y)
	{
		map[y] = new char[stageWidth + 1];
		for (int x = 0; x < stageWidth; ++x)
		{
			map[y][x] = Map[y][x];
			if (map[y][x] == '@' || map[y][x] == '+')
				player->SetPosition(VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
			if (map[y][x] == '$' || map[y][x] == '*')
			{
				objects.at(object_count)->SetPosition(VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
				++object_count;
			}
			if (map[y][x] == '.' || map[y][x] == '*' || map[y][x] == '+')
			{
				game->SetGoal(clearPos_count, VGet(x * 60.f + 30.f, y * 60.f + 30.f, 0.0f));
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

void Stage::NextStage(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game)
{
	// ���̃X�e�[�W�ɐi�ޏ���
	currentStage = (currentStage + 1) % maps.size();
	for (int y = 0; y < stageHeight; ++y)
	{
		delete[] map[y];
	}
	for (auto obj : objects){
		obj->Initialize(); // �I�u�W�F�N�g�̏�����
	}
	SetStage(currentStage, player, objects, game); // �K�v�ȃC���X�^���X��n���ď�����
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
				case '+': //�@�v���C���[�ƃS�[��
					tileIndex = 2; // �v���C���[�ƃS�[�����d�Ȃ��Ă���ꍇ�̓S�[���^�C�����g�p
					break;
				case '*': // ���ƃS�[��
					tileIndex = 2; // ���ƃS�[�����d�Ȃ��Ă���ꍇ�̓S�[���^�C�����g�p
					break;
				case 'X': // �X�e�[�W�O�̃^�C��
					tileIndex = -1; // �\�����Ȃ�
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
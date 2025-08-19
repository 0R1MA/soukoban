#include "DxLib.h"
#include <memory>
#include <vector>
#include <stack>
#include "GameManeger.h"
#include "stage.h"
#include "Anim.h"
#include "Player.h"
#include "Object.h"

GameManeger::GameManeger()
{
	isClear = false;
	_next	= false;
	undo	= false;
}

GameManeger::~GameManeger()
{
	
}

void GameManeger::Initialize()
{

}

void GameManeger::SetGoal(int Index, VECTOR Pos)
{
	goalPosition.emplace_back(Pos);
}

void GameManeger::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects)
{
	
	if (CheckHitKey(KEY_INPUT_B))
	{
		if (!undo)
		{
			undo = true; // B�L�[�������ꂽ��Undo�t���O�𗧂Ă�
			Undo(player, objects); // B�L�[�������ꂽ��Undo�����s
		}
	}
	else
	{
		undo = false; // B�L�[��������Ă��Ȃ��ꍇ��Undo�t���O�����낷
	}
	ClearCheck(objects);
}

void GameManeger::ClearCheck(std::vector<std::shared_ptr<Object>> objects)
{
	//�@�S�[���n�_��ɂ���I�u�W�F�N�g�̐��𐔂���
	int count = 0;
	for (auto obj : objects)
	{
		for (auto Goal : goalPosition)
		{
			if (obj->position.x == Goal.x && obj->position.y == Goal.y)
			{
				obj->onGoal = true; // �I�u�W�F�N�g���S�[���ɓ��B�����ƃ}�[�N
				++count;
				break; // ��̃S�[���ɓ��B�����玟�̃I�u�W�F�N�g��
			}
			else
			{
				obj->onGoal = false; // �I�u�W�F�N�g���S�[���ɓ��B���Ă��Ȃ��ƃ}�[�N
			}
		}
	}

	if (count == goalPosition.size())
	{
		isClear = true;
	}
	else
	{
		isClear = false;
	}
}

void GameManeger::SaveState(VECTOR player, const std::vector<std::shared_ptr<Object>>& objects)
{
	GameState state;
	state.playerPos = player;
	for (auto& obj : objects) {
		state.objectPositions.push_back(obj->position);
	}
	history.push(state);
}

void GameManeger::Undo(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects)
{
	if (!history.empty()) {
		GameState state = history.top();
		history.pop();
		player->SetPosition(state.playerPos);
		for (size_t i = 0; i < objects.size(); ++i) {
			objects[i]->SetPosition(state.objectPositions[i]);
			if (objects[i]->position.x == 0 && objects[i]->position.y == 0)
				objects[i]->modelHandle = -1;
		}
	}
}

bool GameManeger::Reset()
{
	// �����Ƀ��Z�b�g����������
	if(CheckHitKey(KEY_INPUT_R))
	{
		goalPosition.clear();
		history = std::stack<GameState>(); // �������N���A
		return true; // ���Z�b�g�����������ꍇ
	}
	else
	{
		return false; // ���Z�b�g���s���Ȃ������ꍇ
	}
	
}

bool GameManeger::NextStage()
{

	if (CheckHitKey(KEY_INPUT_LSHIFT) && CheckHitKey(KEY_INPUT_N))
	{
		if (!_next)
		{
			_next = true;
			goalPosition.clear();
			history = std::stack<GameState>(); // �������N���A
			return true; // �X�e�[�W�N���A�Ŏ��̃X�e�[�W�֐i��
		}
	}
	else
	{
		_next = false;
	}

	// ���̃X�e�[�W�֐i�ޏ���������
	if (isClear && CheckHitKey(KEY_INPUT_RETURN))
	{
		history = std::stack<GameState>(); // �������N���A
		goalPosition.clear();
		return true; // �X�e�[�W�N���A�Ŏ��̃X�e�[�W�֐i��
	}
	else
	{
		return false; // �܂����̃X�e�[�W�ɐi�߂Ȃ�
	}
}

void GameManeger::PreviousStage()
{
	// �������͂őI�񂾃X�e�[�W�ɂ�����
}

void GameManeger::Draw()
{
	if (isClear)
	{
		SetFontSize(150);		// �t�H���g�̃T�C�Y��ݒ�
		DrawString(140, 250, "CLEAR", 0xFAFA0A);
	}
}
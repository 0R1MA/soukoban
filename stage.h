#pragma once
#include <vector>
#include <string>

class Player;
class Object;
class GameManeger;

const int stageWidth = 11;		// �X�e�[�W�̕�
const int stageHeight = 11;	// �X�e�[�W�̍���

class Stage
{
	public:
	int stageHandle[3];	// �X�e�[�W�̃n���h��
	char* map[stageWidth*stageHeight];	// �X�e�[�W�̃}�b�v�f�[�^
	int currentStage; // ���݂̃X�e�[�W�ԍ�
	std::vector<std::vector<std::string>> maps; // �S�X�e�[�W�̃}�b�v�f�[�^
	Stage();
	~Stage();
	void Initialize(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Object>> objects, std::shared_ptr<GameManeger> game);
	void Update();
	void Draw();
	bool isHit(int x, int y);
};
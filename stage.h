#pragma once

class Player;
class Object;

const int stageWidth = 11;		// �X�e�[�W�̕�
const int stageHeight = 11;	// �X�e�[�W�̍���

class Stage
{
	public:
	int stageHandle[3];	// �X�e�[�W�̃n���h��
	char* map[stageWidth*stageHeight];	// �X�e�[�W�̃}�b�v�f�[�^
	Stage();
	~Stage();
	void Initialize(std::shared_ptr<Player> player, std::shared_ptr<Object> object);
	void Update();
	void Draw();

	bool isHit(int x, int y);

};
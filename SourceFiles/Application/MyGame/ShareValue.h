#pragma once

// �ϐ����L�ׂ̈̍\����
struct ShareValue
{
private:
	ShareValue() = default;
	~ShareValue() = default;
	ShareValue(const ShareValue& obj) = delete;
	ShareValue& operator=(const ShareValue& obj) = delete;

public:
	bool isGoal = false;
	bool isGameOver = false;
	int stageNum = 7;

	static ShareValue* GetInstance() { static ShareValue obj; return &obj; }
};
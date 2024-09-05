#pragma once
#include "GameObject.h"
#include <list>

namespace WristerEngine::_3D
{
	// �X�e�[�W��ɂ���Q�[���\�����Ǘ��N���X
	class BaseStage
	{
	private:
		// �X�e�[�W��ɂ���Q�[���\����
		std::list<GameObject> stageObjects;
		// Json����ǂݍ��񂾃f�[�^
		ObjectData objData;

	protected:
		// �ŗL������
		virtual void VirtualInitialize() {};
		// �ŗL�X�V
		virtual void VirtualUpdate() {};

		// ������
		void Initialize();
		// �X�V
		void Update();
	};
}
#pragma once
class Input
{
public:
	/// <summary>
	/// �L�[���X�V����
	/// </summary>
	void KeyUpdate();
	/// <summary>
	/// �L�[�������ꂽ�u�Ԃ�
	/// </summary>
	bool IsTrigger(char key);
	/// <summary>
	/// �L�[��������Ă��邩
	/// </summary>
	bool IsPress(char key);
	/// <summary>
	/// �L�[�������ꂽ�u�Ԃ�
	/// </summary>
	bool IsRelease(char key);

public:
	char keys[256];
	char oldkeys[256];
};


#pragma once
class Input
{
	/// --�����o�ϐ�-- ///
public:

private:
	char keys[256];
	char oldkeys[256];

	// --�C���X�^���X-- //
	static Input* myInstance;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Input* GetInstance();

	// --�f�X�g���N�^-- //
	~Input();

	// --�X�V����-- //
	void Update();

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

private:
	// --�R���X�g���N�^-- //
	Input();

	/// --�����o�֐�END-- ///
};


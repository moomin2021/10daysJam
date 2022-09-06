#pragma once
class Input
{
	/// --メンバ変数-- ///
public:

private:
	char keys[256];
	char oldkeys[256];

	// --インスタンス-- //
	static Input* myInstance;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Input* GetInstance();

	// --デストラクタ-- //
	~Input();

	// --更新処理-- //
	void Update();

	/// <summary>
	/// キーが押された瞬間か
	/// </summary>
	bool IsTrigger(char key);
	/// <summary>
	/// キーが押されているか
	/// </summary>
	bool IsPress(char key);
	/// <summary>
	/// キーが離された瞬間か
	/// </summary>
	bool IsRelease(char key);

private:
	// --コンストラクタ-- //
	Input();

	/// --メンバ関数END-- ///
};


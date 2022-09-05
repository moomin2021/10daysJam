#pragma once
class Input
{
public:
	/// <summary>
	/// キー情報更新処理
	/// </summary>
	void KeyUpdate();
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

public:
	char keys[256];
	char oldkeys[256];
};


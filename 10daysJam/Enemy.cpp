#include "Enemy.h"
#include"DxLib.h"
using namespace Util;

// --コンストラクタ-- //

Enemy::Enemy() {

}

Enemy::Enemy(Vector2 pos, float radius) : obj{ pos, radius } {

}

// --デストラクタ-- //
Enemy::~Enemy() {

}

// --初期化処理-- //
void Enemy::Initialize() {

	//スポーンエフェクトのパーティクル量
	int particleNum = Random(28, 36);
	//色
	Color c;

	if (state == State::Enemy)color = RED;
	else if (state == State::Item)color = YELLOW;

	//スポーンエフェクトを出す
	for (int i = 0; i < particleNum; i++) {
		c.red = Random(128, 200);
		c.green = Random(128, 200);
		c.blue = Random(224, 255);
		//	color = c.red * pow(16, 4) + c.green * pow(16, 2) + c.blue;
		EffectInitialize(color);
	}
	spawnAddRadius = 8.0f;
	obj.radius += spawnAddRadius;
}

// --更新処理-- //
void Enemy::Update(Line hourLine_,Vector2 scorePos) {

	//スポーンエフェクトの更新
	for (int i = spawnEffect.size() - 1; i >= 0; i--) {
		//	spawnEffect[i].SetSpeed(0.5f);
		spawnEffect[i].Update();
		//if(spawnEffect[i].GetActive())DrawFormatString(0 + 40 * i, 440, 0xffffff, "active");
		//スポーンエフェクトの活動フラグが立っていなければ消す
		if (!spawnEffect[i].GetActive()) {
			spawnEffect.erase(spawnEffect.begin() + i);
		}
	}

	if (obj.radius > 8.0f) {
		obj.radius -= (spawnAddRadius / 5);
	}

	

	switch (state)
	{
	case State::Normal:
		UpdateNormal();
		break;
	case State::Reverse:
		UpdateReverse(hourLine_);
		afterPos = scorePos;
		break;
	case State::Stop:
		break;
	case State::Item:
		//色を黄色に変更
		color = YELLOW;
		afterPos = hourLine_.start;
		break;
	case State::Enemy:
		//色を赤に変更
		color = RED;
		afterPos = hourLine_.start;
		break;
	case State::Death:
		UpdateDeath(afterPos, hourLine_.length);
	default:
		break;
	}

}

void Enemy::UpdateNormal()
{
}

void Enemy::UpdateReverse(Line hourLine_)
{
	//短針に座標を追従させる
	//短針の始点と自座標から長さを取得
	Vector2 lenVec = hourLine_.start - obj.pos;
	float rad = hourLine_.radian - 90;

	float len = lenVec.length();
	//長さと短針の角度から自座標を再計算して代入
	obj.pos.x = (len * cosf((rad) / 180 * PI)) + (obj.radius * cosf((rad - 90) / 180 * PI)) + hourLine_.start.x;
	obj.pos.y = (len * sinf((rad) / 180 * PI)) + (obj.radius * sinf((rad - 90) / 180 * PI)) + hourLine_.start.y;

	//色を明るめのオレンジに
	color = 0xff7c17;
}

void Enemy::UpdateDeath(Vector2 afterPos, float randParam) {
	//始まりなら
	bezire.divisionNum = 32;
	if (effectTime == 0) {
		//ベジエ曲線の座標初期化
		//float len = obj.radius;
		for (int i = 0; i < 4; i++) {
			Vector2 pos;
			int rad = Random(0.0f, 360.0f);
			if (i == 0) {
				pos = obj.pos;
			}
			else if (i == 3) {
				pos = afterPos;
			}
			else {
				Vector2 a = obj.pos - afterPos;
				pos.x = Random(-randParam, randParam) + afterPos.x;
				pos.y = Random(-randParam, randParam) + afterPos.y;
			}
			bezire.SetControllPoint(pos, i);
		}
		//ベジエ曲線の更新
		bezire.Update();
	}



	if (effectTime < bezire.divisionNum) {
		obj.pos = bezire.pos[effectTime];
		effectTime++;
	}
	else if (effectTime >= bezire.divisionNum) {
		state = State::Delete;
	}

	//半径を小さくして色を水色に
	obj.radius = 6.0f;
	color = 0x45efff;

}


void Enemy::OnCollison()
{
	//ステートを反転に
	state = State::Reverse;
	//color = 0x7fff7f;
}

// --描画処理-- //
void Enemy::Draw(Camera camera_, int graph) {

	//スポーンエフェクト描画
	SetDrawBlendMode(DX_BLENDMODE_ADD, 256);
	for (int i = 0; i < spawnEffect.size(); i++) {

		spawnEffect[i].Draw(camera_, spawnEffect[i].GetColor(), graph);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);

	Circle pos = {
		obj.pos + camera_.GetPos(),
		obj.radius
	};

	Color newColor = HexadecimalColor(color);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(newColor.red, newColor.green, newColor.blue);
	for (int i = 0; i < 5; i++) {
		DrawRotaGraph(pos.pos.x, pos.pos.y, 0.5f, 0.0f, handle[0], true);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawRotaGraph(pos.pos.x, pos.pos.y, 0.5f, 0.0f, handle[1], true);
}

// --描画で使う画像ハンドルを設定-- //
void Enemy::SetHandle(int handle[]) {
	this->handle[0] = handle[0];
	this->handle[1] = handle[1];
}

void Enemy::SetState(State state_)
{
	state = state_;
	//状態が変わったエフェクトを出す
	for (int i = 0; i < 24; i++) {
		if (state == State::Item) {
			EffectInitialize(YELLOW);
		}
		else if (state == State::Enemy) {
			EffectInitialize(RED);
		}
		

	}

}

void Enemy::EffectInitialize(int color)
{
	Particle newParticle;
	newParticle.SetParent(obj.pos);
	newParticle.SetColor(color);
	newParticle.Initialize(true);
	spawnEffect.push_back(newParticle);

}

void Enemy::SetObj(Circle obj_)
{
	obj = obj_;
}

void Enemy::StateChange()
{
	isChange = true;
}

void Enemy::Death() {
	//ステートを死亡に
	state = State::Death;
	//エフェクトを4つ出す
	for (int i = 0; i < Random(8, 12); i++) {
		Color c;
		c.red = Random(128, 256);
		c.blue = Random(64, 96);
		c.green = Random(64, 96);
		EffectInitialize(ColorHexadecimal(c));
	}
}

//void Enemy::AllEnemyDeath()
//{
//	enemys.clear();
//}

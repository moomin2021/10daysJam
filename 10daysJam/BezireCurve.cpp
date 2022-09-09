#include"BezireCurve.h"
#include"DxLib.h"

const int controllPoint = 4;

BezireCurve::BezireCurve()
{
	for (int i = 0; i < 64; i++) {
		pos[i] = { 0,0 };
	}

	isActive = false;
	for (int i = 0; i < controllPoint; i++) {
		controll[i].x = 0;
		controll[i].y = 0;
	}
	divisionNum = 1;
}

BezireCurve::~BezireCurve()
{
}



void BezireCurve::Update()
{

	//�������������W�̎擾���s��
	for (int j = 0; j <= divisionNum; j++) {
		if (j == 0)pos[j] = { controll[0].x,controll[0].y };
		pos[j + 1] = pos[j];

		//����_-1�̐������i�ӂ̒���/���������������ڂ��j�����߂����W���i�[����ϐ�
		Vector2 middlePos[controllPoint - 1];
		for (int i = 0; i < controllPoint - 1; i++) {
			//(2�ڂ̍��W-1�ڂ̍��W)�Ő���_���m�̐����̒������v�Z���A����𕪊����̐������������A����ɉ������ڂ����|����(�����j�̒l)
			middlePos[i].x = ((controll[i + 1].x - controll[i].x) * j / divisionNum) + controll[i].x;
			middlePos[i].y = ((controll[i + 1].y - controll[i].y) * j / divisionNum) + controll[i].y;
			//DrawFormatString(0, 40 + 20 * i, 0xffffff, " middle:i=[%d]:x=[%lf]:y=[%lf]",i, middlePos[i].x,  middlePos[i].y);

		}
		//���߂�3�̓_��������Ɏg�����W���i�[����ϐ�
		Vector2 start{};
		Vector2 end{};
		start.x = ((middlePos[1].x - middlePos[0].x) * j / divisionNum) + middlePos[0].x;
		start.y = ((middlePos[1].y - middlePos[0].y) * j / divisionNum) + middlePos[0].y;
		end.x = ((middlePos[2].x - middlePos[1].x) * j / divisionNum) + middlePos[1].x;
		end.y = ((middlePos[2].y - middlePos[1].y) * j / divisionNum) + middlePos[1].y;


		pos[j].x = ((end.x - start.x) * j / divisionNum) + start.x;
		pos[j].y = ((end.y - start.y) * j / divisionNum) + start.y;
		//�`��̂��߁A�������I��
		//Draw(0xffffff);
	//	break;
	}



	/*DrawFormatString(0, 0, 0xffffff, "  start:x=[%lf]:y=[%lf]", start.x, start.y);
	DrawFormatString(0, 20, 0xffffff, "    end:x=[%lf]:y=[%lf]", end.x, end.y);*/


}

void BezireCurve::Draw(int color)
{
	for (int i = 0; i < divisionNum; i++) {
		DrawLine(pos[i].x, pos[i].y, pos[i + 1].x, pos[i + 1].y, color);
		//DrawCircle(pos.x,pos.y,2, color,true);
	}
}

void BezireCurve::SetControllPoint(Vector2 pos, int point) {
	controll[point] = pos;
}

#pragma once
#include <list>
#include "worm.h"
using namespace std;

class rabbit
{

	list<POINT> rabs; // ������ ��������� ������
	int rabSize = 20; // ������ ������
	int qRab = 10; // ��� � ������� ������ ���������� ����� ����
	int cntCyles = 0; // ������� ����




public:
	rabbit();
	~rabbit();
	void drawSelf(HDC hdc, int right, int bottom, worm*);
	void SpeedRabbit(int);

}

;


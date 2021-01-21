#include "framework.h"
#include "rabbit.h"


rabbit::rabbit()
{

	POINT rab = { 100, 200 }; // ������� ����� � ������������ � = 100, � = 200
	rabs.push_back(rab); // ����������� ����� � ������
	rab = { 200, 300 }; // �������� ����� ���������� �� � = 200, � = 300
	rabs.push_back(rab); // ����������� ������� ����� � ������
	rabs.push_back({ 300, 400 }); // �������� ������� �����

}


rabbit::~rabbit()
{
}
// ������������� ������ ������
void rabbit::drawSelf(HDC hdc, int right, int bottom, worm* snake) {

	POINT wormHead = snake->drawSelf(hdc, right, bottom);
		int rX = rand() / 32767.0 * right;
	int rY = rand() / 32767.0 * bottom;

	cntCyles++;

	if (cntCyles > qRab) {
		rabs.push_back({ rX, rY });
		cntCyles = 0;
	}



	for (auto iter = rabs.begin(); iter != rabs.end();) {

		Ellipse(hdc, iter->x - rabSize / 2, iter->y - rabSize / 2, iter->x + rabSize / 2, iter->y + rabSize / 2);

		if (abs(iter->x - wormHead.x) < 20 && abs(iter->y - wormHead.y) < 20) {

			iter = rabs.erase(iter);
			snake->prolong();
		}
		else iter++;


	}


}
void rabbit::SpeedRabbit(int sr) {
	qRab = sr;
}


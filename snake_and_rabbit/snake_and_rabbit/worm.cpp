#include "framework.h"
#include "worm.h"
#include <cmath>
// конструктор класса
worm::worm(int x, int y, bool *ptrTSDie) : posY(y), posX(x), ptrToSnakeDie(ptrTSDie) // инициализация полей
{
	segments.push_back({ posX - width / 2, posY });

}


worm::~worm()
{
}

POINT worm::drawSelf(HDC hdc, int right, int bottom) {

	// определение шага движения червяка (повороты от стен и клика мышки, работает плохо)
	if (*ptrToSnakeDie) {
		if (posX > right || posX <= 0 || posY > bottom || posY <= 0)  stepX = stepY = 0, die = 1;
	}
	else {
		if (posX > right)  stepX = -setStep;
		else if (posX <= 0)  stepX = setStep;
		if (posY > bottom) stepY = -setStep;
		else if (posY <= 0) stepY = setStep;
	}
	stepSelf();

	// заносим в 0-вые ячейки координат положение головы
	segments[0].x = posX;
	segments[0].y = posY;





	for (int i = segments.size() - 1; i > 0; i--) { // отрисовка тела червяка по координатам в массиве
		if (*ptrToSnakeDie) {
			if (segments[0].x == segments[i].x && segments[i].y == segments[0].y) stepX = stepY = 0, die = 1;
			Ellipse(hdc, segments[i].x - width / 2, segments[i].y - width / 2, segments[i].x + width / 2, segments[i].y + width / 2);
			segments[i] = segments[i - 1];
		}
		else {
			Ellipse(hdc, segments[i].x - width / 2, segments[i].y - width / 2, segments[i].x + width / 2, segments[i].y + width / 2);
			segments[i] = segments[i - 1];
		}
    }

	drawHead(hdc);
	return { posX, posY };

}

void worm::drawHead(HDC hdc) {
	POINT pt[N]; // создание массива точек для пеолигона головы


	float dangle = 2 * PI / (N - 1); //: 2 * PI / (N - 2); // определение угла между точками головы
	// (wormStartX % 10 < 5)

	float mouth = (stepX == setStep) ? 0.5 :
		(stepX == -setStep) ? N / 2 :
		(stepY == -setStep) ? N * 0.75 : N * 0.25;


	for (int i = 0; i < N - 1; i++) { // определение точек контура головы


		pt[i].x = cos(dangle * (i + mouth)) * headSize + posX;
		pt[i].y = sin(dangle * (i + mouth)) * headSize + posY;

	}

	pt[N - 1].x = posX;
	pt[N - 1].y = posY;



	Polygon(hdc, pt, N); // отрисовка головы червяка

}
// метод "шагнуть себя" - при каждом вызове позиция по Х и У меняется на значения stepX и stepY соответственно
void worm::stepSelf() {

	posX += stepX;
	posY += stepY;
}
// метод установки stepX и stepY - если аргумент vert = 1,stepY приравнивается newStep, а stepX обнуляется. Иначе наоборот
void worm::SetStep(int newStep, bool vert) {

		
	if (vert) {
			stepX = 0;
			stepY = newStep * setStep;
	}
		
	else {
			stepX = newStep * setStep;
			stepY = 0;	
	}
}
void worm::prolong() {
	segments.push_back({ posX,posY });
}
void worm::SetSpeed(int ss) {
	setStep = ss;
}
bool worm::IsWormDie() {
	return die;
	
}
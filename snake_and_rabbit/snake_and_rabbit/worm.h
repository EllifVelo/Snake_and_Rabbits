#pragma once
#include <vector>
#define N 20
#define PI 3.14
//#define SET_STEP 10
using namespace std;
class worm
{
	// свойства черв§ка или пол§ класса
	int length = 10; // длина
	const int width = 20; // ширина	
	const int headSize = 20; // размер головы
	int stepX = 10; //скорость шага по Т
	int stepY = 0; // скорость шага по Ф
	int posX; // текуща§ позици§ центра головы Т
	int posY; // Уекуща§ позици§ центра головы Ф
	vector<POINT> segments; // массив координат сегментов черв§ка(переменной длинны)
	int setStep = 10;
	bool *ptrToSnakeDie;
	bool die;


public:
	worm(int x, int y, bool *ptrTSDie); // конструктор класса по умолчанию
	~worm(); // диструктор класса (всегда один и всегда без аргументов)

	POINT drawSelf(HDC hdc, int right, int bottom);
	void stepSelf();
	void SetStep(int newStep, bool vert);
	void drawHead(HDC hdc);
	void prolong();
	void SetSpeed(int);
	bool IsWormDie();
};

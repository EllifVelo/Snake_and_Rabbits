#pragma once
#include <vector>
#define N 20
#define PI 3.14
//#define SET_STEP 10
using namespace std;
class worm
{
	// �������� ������ ��� ��� ������
	int length = 10; // �����
	const int width = 20; // ������	
	const int headSize = 20; // ������ ������
	int stepX = 10; //�������� ���� �� �
	int stepY = 0; // �������� ���� �� �
	int posX; // ������ ������ ������ ������ �
	int posY; // ������ ������ ������ ������ �
	vector<POINT> segments; // ������ ��������� ��������� ������(���������� ������)
	int setStep = 10;
	bool *ptrToSnakeDie;
	bool die;


public:
	worm(int x, int y, bool *ptrTSDie); // ����������� ������ �� ���������
	~worm(); // ���������� ������ (������ ���� � ������ ��� ����������)

	POINT drawSelf(HDC hdc, int right, int bottom);
	void stepSelf();
	void SetStep(int newStep, bool vert);
	void drawHead(HDC hdc);
	void prolong();
	void SetSpeed(int);
	bool IsWormDie();
};

#pragma once
#include <list>
#include "worm.h"
using namespace std;

class rabbit
{

	list<POINT> rabs; // список координат зайцев
	int rabSize = 20; // размер зайцев
	int qRab = 10; // раз в сколько циклов по€вл€етс€ новый за€ц
	int cntCyles = 0; // счетчик цифр




public:
	rabbit();
	~rabbit();
	void drawSelf(HDC hdc, int right, int bottom, worm*);
	void SpeedRabbit(int);

}

;


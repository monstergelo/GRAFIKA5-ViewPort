#include "skala.h"
#include <stdio.h>


int main()
{
	titik p[4];
	p[0].x = 0; p[0].y = 0;
	p[1].x = 0; p[1].y = 50;
	p[2].x = 50; p[2].y = 50;
	p[3].x = 50; p[3].y = 0;
	titik pivot = {25, 25};

	scaleBanyakDot(pivot, p, 5, 4);
	for (int i = 0; i < 4; i++) {
		printf("Titik %d: %d,%d\n", i, p[i].x, p[i].y);
	}


	return 0;
}
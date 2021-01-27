#include "headerFiles/algorithm.h"

int licznikRuchow = 0;
int zewnetrzneGraniceZnalezione = 0;

int licznikSkretowLewo = 0;
int licznikSkretowPrawo = 0;

int prevX;
int prevY;

void rozpocznijAutomatyczneOdkrywanie(char *swiat)
{
    int startX = getCurrentX() + 1;	//zapisanie poczatkowego pkt
    int startY = getCurrentY() + 1;

    printf("\n START X: %d START Y: %d \n", startX, startY);
    do {
	wykonajRuchy(startX, startY, swiat);
	if (getCurrentX() == startX && getCurrentY() == startY) {	//powrot do punktu startu
	    zewnetrzneGraniceZnalezione = 1;
	}
    } while (zewnetrzneGraniceZnalezione != 1);

    int bfStartPositionX = getCurrentX();	//pozycja startowa do pelnego przeszukania swiata
    int bfStartPositionY = getCurrentY();
    int swiatOdkryty = 0;

    if (licznikSkretowPrawo > licznikSkretowLewo) {	//znalezione granice zewnetrzne swiata
	do {
	    wykonajRuchy(bfStartPositionX, bfStartPositionY);
	    if (getCurrentX() == bfStartPositionX && getCurrentY() == bfStartPositionY) {	//powrot do punktu startu
		swiatOdkryty = 1;
	    }
	} while (swiatOdkryty != 1);
    } else {			//nie znaleziono jeszcze granic zewnetrznych, probujemy raz jeszcze
	rozpocznijAutomatyczneOdkrywanie(swiat);
    }

   // printf("Koniec odkrywania mapy! \n Ilosc ruchow: %d \n", licznikRuchow);
}

void wykonajRuchy(int startX, int startY, char *swiat)
{
    prevX = getCurrentX();
    prevY = getCurrentY();

    ruchDoPrzodu(swiat);
    licznikRuchow++;
    //printf("\n ACTUAL X: %d ACTUAL Y: %d \n", getCurrentX(),
	//   getCurrentY());

    if (prevX == getCurrentX() && prevY == getCurrentY()) {	//napotkano sciane
	obrocWPrawo(swiat);
	licznikSkretowPrawo++;
	ruchDoPrzodu(swiat);
	//printf("\n ACTUAL X: %d ACTUAL Y: %d \n", getCurrentX(),
	//       getCurrentY());

	if (getCurrentX() == startX && getCurrentY() == startY) {	//powrot do punktu startu
	    zewnetrzneGraniceZnalezione = 1;
	}

	obrocWLewo(swiat);
	licznikSkretowLewo++;
	ruchDoPrzodu(swiat);
	prevX = getCurrentX();
	prevY = getCurrentY();
	//printf("\n ACTUAL X: %d ACTUAL Y: %d \n", getCurrentX(),
	//       getCurrentY());

	if (getCurrentX() == startX && getCurrentY() == startY) {	//powrot do punktu startu
	    zewnetrzneGraniceZnalezione = 1;
	}

	if (prevX == getCurrentX() && prevY == getCurrentY()) {
	    obrocWPrawo(swiat);
	    licznikSkretowPrawo++;
	    ruchDoPrzodu(swiat);
	} else {
	    obrocWLewo(swiat);
	    licznikSkretowLewo++;
	    ruchDoPrzodu(swiat);
	}
	//printf("\n ACTUAL X: %d ACTUAL Y: %d \n", getCurrentX(),
	//       getCurrentY());
	licznikRuchow += 5;
    }
}

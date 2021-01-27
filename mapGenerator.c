#include "headerFiles/mapGenerator.h"

char infoLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
char exploreLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
char moveLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
char leftLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
char rightLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
char resetLink[150] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/";

struct Map mapa;
void zapiszMape(char* nazwaPliku)
{
    FILE *fPtr;
    fPtr = fopen(nazwaPliku, "w");

    if (fPtr == NULL) {
	printf("Nie udalo sie otworzyc pliku.\n");
	exit(EXIT_FAILURE);
    }
    int counter = 0;

    for (int j = 0; j < mapa.dimY; j++) {
	for (int i = 0; i < mapa.dimX; i++) {
	    if ((int) mapa.fields[i * mapa.dimY + j] != 0)
		fputs(&mapa.fields[i * mapa.dimY + j], fPtr);
	    else
		fputs(" ", fPtr);
	    counter += 1;
	}
	fputs("\n", fPtr);
	counter += 1;
    }
    fputs("\0", fPtr);

    fclose(fPtr);
    printf("Mapa wygenerowana. :) \n");
}

void inicjujMape(char *nazwa)
{
    mapa.dx = mapa.dy = 20;
    mapa.dimX = mapa.dimY = 50;
    mapa.name = nazwa;
    mapa.fields = (char *) malloc(mapa.dimX * mapa.dimY * sizeof(char));
    mapa.currentX = getCurrentX();
    mapa.currentY = getCurrentY();

    strcat(infoLink, nazwa);
    strcat(exploreLink, nazwa);
    strcat(moveLink, nazwa);
    strcat(resetLink, nazwa);

    strcat(leftLink, nazwa);
    strcat(leftLink, "/left");
    strcat(rightLink, nazwa);
    strcat(rightLink, "/right");
}

void updateMap(char *json)
{
    int prevX = mapa.currentX;
    int prevY = mapa.currentY;

    jsonParserPayload(json);
//aktualizacja mapy

    mapa.currentX = getCurrentX();
    mapa.currentY = getCurrentY();
    mapa.currentField = getFieldType();
    mapa.currentDirection = getDirection();

	if (mapa.dx < 0) {
	    mapa.dimX += mapa.dimX;
	    zwiekszRozmiarMapy(mapa.dimX, mapa.dimY);
	} else if (mapa.dx > mapa.dimX)	//dodanie kolumny 
	{
	    mapa.dimX += mapa.dimX;
	    zwiekszRozmiarMapy(mapa.dimX, mapa.dimY);
	}

	if (mapa.dy < 0) {
	    mapa.dimY += 1;
	    zwiekszRozmiarMapy(mapa.dimX, mapa.dimY);
	} else if (mapa.dy > mapa.dimY)	//dodanie kolumny 
	{
	    mapa.dimY += mapa.dimY;
	    zwiekszRozmiarMapy(mapa.dimX, mapa.dimY);
	}


	if (mapa.currentX > prevX)
	    mapa.dx += 1;
	else if (mapa.currentX < prevX)
	    mapa.dx -= 1;

	if (mapa.currentY > prevY)
	    mapa.dy += 1;
	else if (mapa.currentY < prevY)
	    mapa.dy -= 1;

    if (mapa.currentX == prevX && mapa.currentY == prevY) {	//napotkano sciane
	if (mapa.currentDirection == 'E')
	    mapa.fields[mapa.dimX + (mapa.dx + 1) * mapa.dimY + mapa.dy] = 'w';
	else if (mapa.currentDirection == 'W')
	    mapa.fields[mapa.dimX + (mapa.dx - 1) * mapa.dimY + mapa.dy] = 'w';
	else if (mapa.currentDirection == 'N')
	    mapa.fields[mapa.dimX + mapa.dx * mapa.dimY + (mapa.dy + 1)] = 'w';
	else if (mapa.currentDirection == 'S')
	    mapa.fields[mapa.dimX + mapa.dx * mapa.dimY + (mapa.dy - 1)] = 'w';
    } else
	mapa.fields[mapa.dimX + mapa.dx * mapa.dimY + mapa.dy] = mapa.currentField;

}

void wyczyscMape()
{
    free(mapa.fields);
}

void zwiekszRozmiarMapy(int sizeX, int sizeY)
{
    mapa.fields =
	realloc(mapa.fields,
		(sizeX + sizeX) * (sizeY + sizeY) * sizeof(char));

    mapa.dimX = sizeX + sizeX;
    mapa.dimY = sizeY + sizeY;

    mapa.dx += sizeX;
    mapa.dy += sizeY;
}

void wypiszMape()
{
    printf("DANE MAPY:\n");
    printf("name: %s\n", mapa.name);
    printf("aktualna pozycja x: %d\n", mapa.currentX);
    printf("aktualna pozycja y: %d\n", mapa.currentY);
    printf("typ pola: %c\n", mapa.currentField);
    printf("Aktualny kierunek: %c\n", mapa.currentDirection);

    for (int j = 0; j < mapa.dimY; j++) {
	for (int i = 0; i < mapa.dimX; i++) {
	    if ((int) *(mapa.fields + i * mapa.dimY + j) != 0)
		printf("%c", mapa.fields[i * mapa.dimY + j]);
	    else
		printf(" ");
	}
	printf("\n");
    }
}

char* dajInfoLink(){
    return infoLink;
}

char* dajExploreLink(){
    return exploreLink;
}

char* dajMoveLink(){
    return moveLink;
}

char* dajLeftLink(){
    return leftLink;
}

char* dajRightLink(){
    return rightLink;
}

char* dajResetLink(){
    return resetLink;
}

int dajSzerokoscMapy(){
    return mapa.dimX;
}

int dajWysokoscMapy(){
    return mapa.dimY;
}

char* dajAktualnaMape(){
    return mapa.fields;
}

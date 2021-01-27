#include "headerFiles/mainTest.h"
#include "headerFiles/apiConnectorTest.h"
#include "headerFiles/mapGeneratorTest.h"
#include "headerFiles/jsonConverterTest.h"
#include "headerFiles/algorithmTest.h"

void testingMenu()
{				//menu do testowania
    printf("###MENU TESTOWANIA### \n");
    printf("1 - test parser json \n");
    printf("2 - test zapisu mapy \n");
    printf("3 - test algorytmu \n");
    printf("4 - test polaczenia api \n");
    printf("0 - zamkniecie aplikacji \n");

    do {
	printf("opcja: \n");
	scanf("%d", &choice);
	(void) getchar();

	switch (choice) {
	case 0:
	    break;
	case 1:
	    testJSONParser();
	    break;
	case 2:
	    testZapisuMapy();
	    break;
	case 3:
	    testAlgorytmu();
	    break;
	case 4:
	    testApi();
	    break;
	default:
	    printf("Nieznana opcja! \n");
	}
    } while (choice != 0);
}

int main(int argc, char **argv)
{
    testingMenu();
    return 0;
}

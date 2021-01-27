#include "headerFiles/main.h"

void sterowanieReczne()
{				//menu sterowania recznego
    printf("###MENU STEROWANIA RECZNEGO### \n");
    printf("1 - powrot do poprzedniego menu \n");
    printf("2 - info \n");
    printf("3 - ruch \n");
    printf("4 - obrot w lewo\n");
    printf("5 - obort w prawo \n");
    printf("6 - odkryj swiat \n");
    printf("7 - resetuj swiat \n");
    printf("8 - zapisz mape \n");
    printf("9 - wyswietl mape \n");
    printf("10 - generuj PNG mapy \n");
    printf("0 - zamkniecie aplikacji \n");

    do {
	printf("opcja: \n");
	scanf("%d", &wybor);
	(void) getchar();

	switch (wybor) {
	case 1:
	    wyborTrybuPracy();
	    break;
	case 2:
	    info(swiat);
	    break;
	case 3:
	    ruchDoPrzodu(swiat);
	    break;
	case 4:
	    obrocWLewo(swiat);
	    break;
	case 5:
	    obrocWPrawo(swiat);
	    break;
	case 6:
	    odkryjSwiat(swiat);
	case 7:
	    resetujSwiat(swiat);
	    break;
	case 8:
	    zapiszMape("mapa.txt");
	    break;
	case 9:
	    wypiszMape();
	    break;
	case 10:
	    generujPngMapy("mapa.png");
	    break;
	case 0:
	    break;
	default:
	    printf("Nieznana opcja! \n");
	}
    } while (wybor != 0);
}

void sterowanieAutomatyczne()
{				//uruchomienie algorytmu

    printf("###MENU STEROWANIA AUTOMATYCZNEGO### \n");
    printf("1 - powrot do poprzedniego menu \n");
    printf("2 - uruchom  \n");
    printf("3 - wyswietl mape \n");
    printf("4 - zapisz mape \n");
    printf("5 - generuj PNG mapy \n");
    printf("0 - zamkniecie aplikacji \n");

    do {
	printf("opcja: \n");
	scanf("%d", &wybor);
	(void) getchar();

	switch (wybor) {
	case 1:
	    wyborTrybuPracy();
	    break;
	case 2:
	    rozpocznijAutomatyczneOdkrywanie(swiat);
	    break;
	case 3:
	    wypiszMape();
	    break;
	case 4:
	    zapiszMape("mapa.txt");
	    break;
	case 5:
	    generujPngMapy("mapa.png");
	    break;
	case 0:
	    break;
	default:
	    printf("Nieznana opcja! \n");
	}
    } while (wybor != 0);
}

void wyborTrybuPracy()
{
    printf("###WYBOR TRYBU PRACY### \n");
    printf("1 - reczny \n");
    printf("2 - automatyczny \n");
    printf("0 - zamknij \n");

    printf("opcja: \n");
    scanf("%d", &wybor);
    (void) getchar();

    if (wybor == 0) {
	return;
    } else if (wybor == 1) {
	sterowanieReczne();
    } else if (wybor == 2) {
	sterowanieAutomatyczne();
    } else {
	do {
	    printf("Nieznana opcja! \n");
	    printf("1 - reczny \n");
	    printf("2 - automatyczny \n");
	    printf("0 - zamknij \n");
	} while (wybor == 1 || wybor == 2 || wybor == 0);
    }
}

void generujPngMapy(char* nazwaPliku)
{
   	   int width, width_grass, width_sand, width_wall;
	   int height, height_grass, height_sand, height_wall;
	   png_byte color_type, color_type_grass, color_type_sand, color_type_wall;
	   png_byte bit_depth, bit_depth_grass,bit_depth_sand, bit_depth_wall;
	   png_bytep *row_pointers = NULL;
	   png_bytep *row_pointers_out = NULL;
	   png_bytep *row_pointers_grass = NULL;
	   png_bytep *row_pointers_out_grass = NULL;
	   png_bytep *row_pointers_sand = NULL;
	   png_bytep *row_pointers_out_sand = NULL;
	   png_bytep *row_pointers_wall = NULL;
	   png_bytep *row_pointers_out_wall = NULL;

	   read_png_file("grass.png", &width_grass, &height_grass, &color_type_grass, &bit_depth_grass, &row_pointers_grass);
	   process_png_file(width_grass, height_grass, row_pointers_grass);
	   row_pointers_out_grass = create_image(width_grass, height_grass);

	   read_png_file("sand.png", &width_sand, &height_sand, &color_type_sand, &bit_depth_sand, &row_pointers_sand);
	   process_png_file(width_sand, height_sand, row_pointers_sand);
	   row_pointers_out_sand = create_image(width_sand, height_sand);

	   read_png_file("wall.png", &width_wall, &height_wall, &color_type_wall, &bit_depth_wall, &row_pointers_wall);
	   process_png_file(width_wall, height_wall, row_pointers_wall);
	   row_pointers_out_wall = create_image(width_wall, height_wall);

	   read_png_file(nazwaPliku, &width, &height, &color_type, &bit_depth, &row_pointers);
	   process_png_file(width, height, row_pointers);
	   row_pointers_out = create_image(dajSzerokoscMapy()*32,dajWysokoscMapy()*32);
	   init_png_file(dajSzerokoscMapy()*32, dajWysokoscMapy()*32, row_pointers_out, dajAktualnaMape(), row_pointers_out_grass, row_pointers_out_sand, row_pointers_out_wall);
	   write_png_file(nazwaPliku, dajSzerokoscMapy()*32,dajWysokoscMapy()* 32, color_type, bit_depth, row_pointers_out);
}

int main(int argc, char **argv)
{
    printf("Podaj nazwe swiata: \n");
    scanf("%s", swiat);
    (void) getchar();

    inicjujMape(swiat);
    wyborTrybuPracy();
    wyczyscMape();
    return 0;
}

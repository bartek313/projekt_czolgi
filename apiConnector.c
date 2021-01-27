#include "headerFiles/apiConnector.h"
#include "headerFiles/mapGenerator.h"

typedef struct _Memory {
    char *response;
    size_t size;
} Memory;

int wykonajRequest(char *url)
{
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	    fprintf(stderr,
		    "Błąd! curl_easy_perform() niepowodzenie: %s\n",
		    curl_easy_strerror(res));
	else {
	    printf("%s", chunk.response);
	}
	//odczyt danych z json
	updateMap(chunk.response);
	free(chunk.response);
	curl_easy_cleanup(curl);
	return 1;
    } else
	return 0;
}

size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;

    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    if (mem->response != NULL)
	ptr = realloc(mem->response, mem->size + realsize + 1);
    else
	ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
	return 0;	
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;	

    return realsize;
}

char *concatenate(char *a, char *b, char *c)
{
  int size = strlen(a) + strlen(b) + strlen(c) + 1;
  char *str = malloc(size);
  strcpy (str, a);
  strcat (str, b);
  strcat (str, c); 

  return str;
}

int info(char swiat[])
{		
    //char link[strlen(swiat) + strlen(infoLink) + 1];	//info
    //char *str = concatenate(link, infoLink, swiat);
    //printf("\n %s \n", str);
    return wykonajRequest(dajInfoLink()/*str*/);
}

int odkryjSwiat(char swiat[])
{				//odkrywanie swiata
    return wykonajRequest(dajExploreLink());
}

int ruchDoPrzodu(char swiat[])
{				//ruch do przodu
    return wykonajRequest(dajMoveLink());
}

int obrocWLewo(char swiat[])
{				//obrot w lewo
    return wykonajRequest(dajLeftLink());
}

int obrocWPrawo(char swiat[])
{				//obrot w prawo
    return wykonajRequest(dajRightLink());
}

int resetujSwiat(char swiat[])
{				//reset
    return wykonajRequest(dajResetLink());
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "input.h"

int getInt(char* msg)
{
	int returnAux;
	printf("%s", msg);
	scanf("%d", &returnAux);
	return returnAux;
}

float getFloat(char* msg)
{
	float returnAux;
	printf("%s", msg);
	scanf("%f", &returnAux);
	return returnAux;
}

char getChar(char* msg)
{
	char returnAux;
	printf("%s", msg);
	scanf("%c", &returnAux);
	return returnAux;
}

int getString(char* msg, char* destino)
{
	int returnAux;
	returnAux = 0;
	printf("%s", msg);
	scanf("%s", destino);
	if(esNumerica(destino))
	{
		returnAux = -1;
	}

	return returnAux;
}

int getCuit(char* msg)
{
    int cuit;
    char stringAux[21];
    getString(msg, stringAux);
    while(esCuit(stringAux) == 0)
    {
        printf("\\ERROR\\\n");
        getString(msg, stringAux);
    }
    cuit = atoi(stringAux);
    return cuit;
}

int getPositivoEntero(char* msg)
{
    int positivoAux = -1;
    while(positivoAux < 0)
    {
        positivoAux = getInt(msg);
        if(positivoAux < 0)
        {
            printf("Ingrese un valor positivo.");
        }
    }
    return positivoAux;
}

float getPositivoFlotante(char* msg)
{
    float positivoAux = -1;
    while(positivoAux < 0)
    {
        positivoAux = getFloat(msg);
        if(positivoAux < 0)
        {
            printf("Ingrese un valor positivo.");
        }
    }
    return positivoAux;
}

int esNumerica(char* cadena)
{
	int i=0;
	int retorno = 1;
	if(strlen(cadena) > 0)
	{
		while(cadena[i] != '\0')
		{
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

int esAlfanumerica(char* cadena)
{
	int i = 0;
	int caracter;
	int returnAux = 1;
	if(strlen(cadena) > 0)
	{
		while(*(cadena+i) != '\0')
		{
			caracter = (int)cadena[i];
			if(!((caracter > 64 && caracter < 91) || (caracter > 96 && caracter < 123)))
			{
				returnAux = 0;
				break;
			}
			i++;
		}
	}
	return returnAux;
}

int esCuit(char* cadena)
{
    int retorn;
    int caracter;
    retorn = 1;
    for(int x = 0; cadena[x] != '\0'; x++)
    {
        caracter = (int)cadena[x];
        if(isdigit(cadena[x]) == 0 && cadena[x] != '-')
        {
            retorn = 0;
            break;
        }
        if(cadena[x] == '-')
        {
            for(int y = x; cadena[y] != '\0'; y++)
            {
                cadena[y] = cadena[y+1];
            }
        }
    }
    return retorn;
}

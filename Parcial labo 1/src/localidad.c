#include <stdio.h>
#include "cliente.h"

void IniciarLocalidad(eLocalidad localidades[], int tamLocalidad)
{
    for(int x = 0; x < tamLocalidad; x++)
    {
        localidades[x].isEmpty = 1;
    }
}

int AltaLocalidad(eLocalidad localidades[], int tamLocalidad)
{
    int indice;
    int idLocal;
    int existe;
    char descLocal[26];
    indice = BuscarLibreLocalidad(localidades, tamLocalidad);
    if(indice != -1)
    {
        idLocal = 50+indice;
        getString("Ingrese nombre de la localidad: ", descLocal);
        existe = BuscarLocalidadExistente(localidades, tamLocalidad, descLocal);
        if(existe == 0)
        {
            CargaLocalidad(localidades, indice, idLocal, descLocal);
        }
    }
    return idLocal;
}

int BuscarLibreLocalidad(eLocalidad localidades[], int tamLocalidad)
{
    int indiceLibre = -1;
    for(int x = 0; x < tamLocalidad; x++)
    {
        if(localidades[x].isEmpty == 1)
        {
            indiceLibre = x;
            break;
        }
    }
    return indiceLibre;
}

void CargaLocalidad(eLocalidad localidades[], int indice, int idLocalidad, char* descLocal)
{
    localidades[indice].idLocalidad = idLocalidad;
    strcpy(localidades[indice].descLocalidad, descLocal);
    localidades[indice].isEmpty = 0;
}

int BuscarLocalidadExistente(eLocalidad localidades[], int tamLocalidad, char* localidadIng)
{
    int returnAux = 0;
    for(int x = 0; x < tamLocalidad; x++)
    {
        if(strcmp(localidades[x].descLocalidad, localidadIng) == 0)
        {
            returnAux = localidades[x].idLocalidad;
            break;
        }
    }
    return returnAux;
}

int ImprimirLocalidad(eLocalidad localidades[], int tamLocalidad, int idLocalidad)
{
	int indice = 0;
	indice = BuscarIndiceLocalidad(localidades, tamLocalidad, idLocalidad);
	if(indice != -1)
	{
		printf("%s", localidades[indice].descLocalidad);
	}
	return indice;
}

int BuscarIndiceLocalidad(eLocalidad localidades[], int tamLocalidad, int idLocalidad)
{
	int indice = -1;
	for(int x = 0; x < tamLocalidad; x++)
	{
		if(localidades[x].idLocalidad == idLocalidad)
		{
			indice = x;
			break;
		}
	}
	return indice;
}

int SolicitarLocalidadIngresada(eLocalidad localidades[], int tamLocalidad)
{
    int flagError = 0;
    int idLocalidad = 0;
    char direccion[26];
    do{
        if(flagError == 1)
        {
            printf("\\ERROR\\");
        }
        getString("\nIngrese localidad: ", direccion);
        idLocalidad = BuscarLocalidadExistente(localidades, tamLocalidad, direccion);
        flagError = 1;
    }while(idLocalidad == 0);
    return idLocalidad;
}

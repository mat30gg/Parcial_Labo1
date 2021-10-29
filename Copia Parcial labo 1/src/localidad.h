#define TAMLOCALIDAD 50

typedef struct{
    int idLocalidad;
    char descLocalidad[25];
    int isEmpty;
}eLocalidad;

void IniciarLocalidad(eLocalidad localidades[], int tamLocalidad);
int AltaLocalidad(eLocalidad localidades[], int tamLocalidad);
int BuscarLibreLocalidad(eLocalidad localidades[], int tamLocalidad);
void CargaLocalidad(eLocalidad localidades[], int indice, int idLocalidad, char* descLocal);

int BuscarLocalidadExistente(eLocalidad localidades[], int tamLocalidad, char* localidadIng);
int ImprimirLocalidad(eLocalidad localidades[], int tamLocalidad, int idLocalidad);
int SolicitarLocalidadIngresada(eLocalidad localidades[], int tamLocalidad);
int BuscarIndiceLocalidad(eLocalidad localidades[], int tamLocalidad, int idLocalidad);

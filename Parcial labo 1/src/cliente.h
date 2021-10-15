#include "localidad.h"

#define TAMCLIENTE 100
#define TAMLOCALIDAD 50

typedef struct{
    int idCliente;
    char nombre[26];
    int cuit;
    char direccion[26];
    int idLocalidad;
    int isEmpty;
}eCliente;

typedef struct{
    int idLocalidad;
    char* descLocalidad;
    int isEmpty;
}eLocalidad;

void InicializarClientes(eCliente arrayCliente[], int tamCliente);
int SolicitarIdCliente(char* mensaje, eCliente arrayCliente[], int tamCliente);
int BuscarClientePorID(eCliente arrayCliente[], int tamCliente, int id);
int IngresarIdClienteExistente(eCliente arrayCliente[], int tamCliente);
void ImprimirTodosCliente(eCliente arrayCliente[], int tamCliente);
void ImprimirUnCliente(eCliente cliente);

int MainAltaCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad,int* ultimoId);
void CargaCliente(eCliente arrayCliente[], int indice, char nombre[], int cuit, char direccion[], int localidad, int idCliente);
int BuscarLibreCliente(eCliente arrayCliente[], int tamCliente);

int MainModificarCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad);
int SolicitarIdClienteModificar(eCliente arrayCliente[], int tamCliente);
int ModificarCliente(eCliente arrayCliente[], int indice, eLocalidad localidades[], int tamLocalidad);
int ModificarDireccion(eCliente* cliente);
int ModificarLocalidad(eCliente* cliente, eLocalidad localidades[], int tamLocalidad);

int MainBajaCliente(eCliente arrayCliente[], int tamCliente);
int SolicitarIdClienteBaja(eCliente arrayCliente[], int tamCliente);
int ConfirmacionBajaCliente(eCliente cliente);
int BajaCliente(eCliente arrayCliente[], int indice);

int SolicitarLocalidadIngresada(eCliente arrayCliente[], int tamCliente, char* direccion);

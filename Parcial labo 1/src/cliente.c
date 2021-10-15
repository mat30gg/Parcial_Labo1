#include <stdio.h>
#include <string.h>
#include "localidad.h"
#include "cliente.h"
#include "input.h"

void InicializarClientes(eCliente arrayCliente[], int tamCliente)
{
    for(int x = 0; x < tamCliente; x++)
    {
        arrayCliente[x].isEmpty = 1;
    }
}

int MainAltaCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad, int* ultimoId)
{
    int indice;
    char nombre[26];
    int cuit;
    char direccion[26];
    int idLocalidad;
    int retorn = 0;
    indice = BuscarLibreCliente(arrayCliente, tamCliente);
    if(indice != -1)
    {
        retorn = 1;
        printf("Cargando cliente en ID: %d\n", *ultimoId);
        getString("Ingrese nombre del cliente: ", nombre);
        cuit = getCuit("Ingrese CUIT del cliente: ");
        getString("Ingrese direccion del cliente: ", direccion);
        idLocalidad = AltaLocalidad(localidades, tamLocalidad);
        CargaCliente(arrayCliente, indice, nombre, cuit, direccion, idLocalidad, (*ultimoId)++);
    }
    return retorn;
}

void CargaCliente(eCliente arrayCliente[], int indice, char nombre[], int cuit, char direccion[], int localidad, int idCliente)
{
    arrayCliente[indice].isEmpty = 0;
    strcpy(arrayCliente[indice].nombre, nombre);
    arrayCliente[indice].cuit = cuit;
    strcpy(arrayCliente[indice].direccion, direccion);
    arrayCliente[indice].idLocalidad = localidad;
    arrayCliente[indice].idCliente = idCliente;
}

int BuscarLibreCliente(eCliente arrayCliente[], int tamCliente)
{
    int retorn = -1;
    for(int i = 0; i < tamCliente; i++)
    {
        if(arrayCliente[i].isEmpty == 1)
        {
            retorn = i;
            break;
        }
    }
    return retorn;
}

int MainModificarCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad)
{
    int retorn = 0;
    int indiceModificar;
    indiceModificar = SolicitarIdClienteModificar(arrayCliente, tamCliente);
    if(indiceModificar != -1)
    {
        ModificarCliente(arrayCliente, indiceModificar, localidades, tamLocalidad);
        retorn = 1;
    }
    return retorn;
}

int SolicitarIdClienteModificar(eCliente arrayCliente[], int tamCliente)
{
    int indiceModificar = -1;
    while(indiceModificar == -1)
    {
        indiceModificar = SolicitarIdCliente("\nIngrese ID del cliente a modificar: ", arrayCliente, tamCliente);
    }
    return indiceModificar;
}

int SolicitarIdCliente(char* mensaje, eCliente arrayCliente[], int tamCliente)
{
    int idRetorn = -1;
    int id;
    id = getInt(mensaje);
    idRetorn = BuscarClientePorID(arrayCliente, tamCliente, id);
    if(idRetorn == -1)
    {
        printf("\n\\ID no encontrado\\");
    }
    return idRetorn;
}

int BuscarClientePorID(eCliente arrayCliente[], int tamCliente, int id)
{
    int indice = -1;
    for(int x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].idCliente == id && arrayCliente[x].isEmpty == 0)
        {
            indice = x;
            break;
        }
    }
    return indice;
}

int IngresarIdClienteExistente(eCliente arrayCliente[], int tamCliente)
{
    int idCliente;
    do{
        idCliente = getInt("\nIngrese id de un cliente existente: ");
    }while(BuscarClientePorID(arrayCliente, tamCliente, idCliente) == -1);
    return idCliente;
}

int ModificarCliente(eCliente arrayCliente[], int indice, eLocalidad localidades[], int tamLocalidad)
{
    int modificado = 1;
    int eleccion;
    do{
        printf("\n1 - Direccion");
        printf("\n2 - Localidad");
        printf("\n0 - SALIR");
        eleccion = getInt("\nQue va a modificar: ");
        switch(eleccion)
        {
            case 1:
                ModificarDireccion(&arrayCliente[indice]);
            break;
            case 2:
                ModificarLocalidad(&arrayCliente[indice], localidades, tamLocalidad);
            break;
            case 0:
                modificado = 0;
            break;
            default:
                printf("\\Eleccion invalida.\\");
        }
    }while(eleccion != 0);
    return modificado;
}

int ModificarDireccion(eCliente* cliente)
{
    getString("\nIngrese nueva direccion del cliente: ", cliente->direccion);
    return 1;
}

int ModificarLocalidad(eCliente* cliente, eLocalidad localidades, int tamLocalidad)
{
    cliente->idLocalidad = AltaLocalidad(localidades, tamLocalidad);
    return 1;
}

int MainBajaCliente(eCliente arrayCliente[], int tamCliente)
{
    int retorn = 0;
    int indiceBaja;
    int eleccion;
    indiceBaja = SolicitarIdClienteBaja(arrayCliente, tamCliente);
    if(indiceBaja != -1)
    {
        eleccion = ConfirmacionBajaCliente(arrayCliente[indiceBaja]);
        if(eleccion == 1)
        {
            BajaCliente(arrayCliente, indiceBaja);
        }
        retorn = 1;
    }
    return retorn;
}

int SolicitarIdClienteBaja(eCliente arrayCliente[], int tamCliente)
{
    int indiceBaja = -1;
    while(indiceBaja == -1)
    {
        indiceBaja = SolicitarIdCliente("\nIngrese ID del cliente a dar de baja: ", arrayCliente, tamCliente);
    }
    return indiceBaja;
}


int ConfirmacionBajaCliente(eCliente cliente)
{
    int eleccion = -1;
    printf("\n");
    ImprimirUnCliente(cliente);
    printf("\n(0 No)\n(1 Si)");
    while(eleccion != 0 && eleccion != 1)
    {
        eleccion = getInt("\nConfirmar dar de baja: ");
        if(eleccion != 0 && eleccion != 1)
        {
            printf("\\Valor invalido.\\");
        }
    }
    return eleccion;
}

int BajaCliente(eCliente arrayCliente[], int indice)
{
    arrayCliente[indice].isEmpty = 1;
    return 1;
}

void ImprimirTodosCliente(eCliente arrayCliente[], int tamCliente)
{
    printf("\n|__ID__|___Nombre___|____Cuit_____|___Direccion___|___Localidad___|");
    for(int x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0)
        {
            printf("\n");
            ImprimirUnCliente(arrayCliente[x]);
        }
    }
}

void ImprimirUnCliente(eCliente cliente)
{
    printf("{ %-4d / %-11s/ %-12d/ %-14s/ %-14d}", cliente.idCliente, cliente.nombre, cliente.cuit, cliente.direccion, cliente.idLocalidad);
}



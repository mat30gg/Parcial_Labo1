#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "pedidos.h"
#include "input.h"
#include "nucleo.h"

int MainMenu()
{
    int eleccion;
    printf("\n(1)  - Alta cliente.");
    printf("\n(2)  - Modificar datos cliente.");
    printf("\n(3)  - Baja cliente.");
    printf("\n(4)  - Crear pedido de recoleccion.");
    printf("\n(5)  - Procesar residuos.");
    printf("\n(6)  - Imprimir clientes.");
    printf("\n(7)  - Imprimir pedidos pendientes.");
    printf("\n(8)  - Imprimir pedidos procesados");
    printf("\n(9)  - Cantidad de pedidos pendientes en localidad.");
    printf("\n(10) - Promedio de kilos de polipropileno reciclados por gente.");
    printf("\n(0)  - SALIR");
    eleccion = getInt("\nElija una opcion: ");
    return eleccion;
}

int MainAltaPedido(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int* ultimoId)
{
    int kilosTotales;
    int idCliente;
    int idPedido;
    int indice;
    int retorn = 0;
    indice = BuscarLibrePedidos(pedidos, tamPedidos);
    if(indice != -1)
    {
        retorn = 1;
        idPedido = (*ultimoId)++;
        ImprimirTodosCliente(arrayCliente, tamCliente);
        idCliente = IngresarIdClienteExistente(arrayCliente, tamCliente);
        kilosTotales = getPositivoFlotante("Ingrese kilos totales a recolectar: ");
        CargaPedido(pedidos, indice, idPedido, idCliente, kilosTotales, "PENDIENTE");
    }
    return retorn;
}

int MainProcesarResiduo(ePedido pedidos[], int tamPedidos)
{
    int indiceProcesar;
    ImprimirTodosPedido(pedidos, tamPedidos);
    indiceProcesar = SolicitarIdPedidoProcesar(pedidos, tamPedidos);
    IngresarPlasticos(pedidos, indiceProcesar);
    strcpy(pedidos[indiceProcesar].estadoPedido, "COMPLETADO");
    return 1;
}

int IngresarPlasticos(ePedido pedidos[], int indice)
{
    int flagError = 0;
    do{
        if(flagError == 1)
        {
            printf("\\ERROR\\");
        }
        pedidos[indice].HDPE = getPositivoFlotante("\nCantidad de HDPE recolectado: ");
        pedidos[indice].LDPE = getPositivoFlotante("\nCantidad de LDPE recolectado: ");
        pedidos[indice].PP = getPositivoFlotante("\nCantidad de PP recolectado: ");
        flagError = 1;
    }while(VerificarPlasticos(pedidos[indice]) != 1);
    return 1;
}

int VerificarPlasticos(ePedido pedido)
{
    float sumador;
    int returnValidar;
    sumador = pedido.HDPE + pedido.LDPE + pedido.PP;
    if(sumador <= pedido.kilosTotales)
    {
        returnValidar = 1;
    }
    else
    {
        returnValidar = 0;
    }
    return returnValidar;
}

int MainImprimirClientes(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos)
{
    int cantPendientes;
    printf("\n|__ID__|___Nombre___|____Cuit_____|___Direccion___|__IDLocalidad__|\n");
    for(int x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0)
        {
            ImprimirUnCliente(arrayCliente[x]);
            cantPendientes = CantidadPendientes(pedidos, tamPedidos, arrayCliente[x].idCliente);
            printf(" !Cantidad de pedidos de recoleccion pendientes: %d", cantPendientes);
        }
    }
    return cantPendientes;
}

int CantidadPendientes(ePedido pedidos[], int tamPedidos, int idCliente)
{
    int contadorPendientes = 0;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0)
        {
            if(pedidos[x].idCliente == idCliente && strcmp(pedidos[x].estadoPedido, "PENDIENTE") == 0)
            {
                contadorPendientes++;
            }
        }
    }
    return contadorPendientes;
}

int MainImprimirEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, char* estado)
{
    int auxId;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0)
        {
            auxId = BuscarClientePorID(arrayCliente, tamCliente, pedidos[x].idCliente);
            if(strcmp(estado, "PENDIENTE") == 0)
            {
                ImprimirPendiente(pedidos[x].idPedido, arrayCliente[auxId].cuit, arrayCliente[auxId].direccion, pedidos[x].kilosTotales);
            }
            if(strcmp(estado, "COMPLETADO") == 0)
            {
                ImprimirProcesado(pedidos[x].idPedido, arrayCliente[auxId].cuit, arrayCliente[auxId].direccion, pedidos[x].HDPE, pedidos[x].LDPE, pedidos[x].PP);
            }
        }
    }
    return 1;
}

void ImprimirPendiente(int idPedido, int cuit, char* direccion, float kilosTotales)
{
    printf("\n(%d) - %d - %s - %.2f", idPedido, cuit, direccion, kilosTotales);
}

void ImprimirProcesado(int idPedido, int cuit, char* direccion, float hdpe, float ldpe, float pp)
{
    printf("\n(%d) - %d - %s - %.2f - %.2f - %.2f", idPedido, cuit, direccion, hdpe, ldpe, pp);
}

int MainPendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades, int tamLocalidad)
{
    int contador;
    int idLocalidad;
    idLocalidad = SolicitarLocalidadIngresada(localidades, tamLocalidad);
    contador = PendientesEnLocalidad(arrayCliente, tamCliente, pedidos, tamPedidos, idLocalidad);
    printf("\nLa cantidad de pedidos pendientes en la localidad es de %d", contador);
    return 1;
}

int ContarPedidosDeCliente(ePedido pedidos[], int tamPedidos, int idCliente)
{
    int contador = 0;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0 && pedidos[x].idCliente == idCliente)
        {
            contador++;
        }
    }
    return contador;
}

int PendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int localidad)
{
    int aux = 0;
    int sumador;
    for(int x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0 && arrayCliente[x].idLocalidad == localidad)
        {
            sumador = CantidadPendientes(pedidos, tamPedidos, arrayCliente[x].idCliente);
            aux = aux + sumador;
        }
    }
    return aux;
}

int MainPoliPromedio(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos)
{
    float promedio;
    ClientesPP(arrayCliente, tamCliente, pedidos, tamPedidos, &promedio);
    printf("El promedio de Polopropileno por cliente es de %.2f", promedio);
    return 1;
}

int ClientesPP(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, float* promedio)
{
    int x;
    int contadorClientesPP = 0;
    int contadorPP = 0;
    int aux;
    for(x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0)
        {
            aux = PedidosPP(pedidos, tamPedidos, arrayCliente[x].idCliente);
            contadorPP = contadorPP + aux;
            contadorClientesPP++;
        }
    }
    *promedio = (float)contadorPP / (float)contadorClientesPP;
    return contadorPP;
}

int PedidosPP(ePedido pedidos[], int tamPedidos, int idCliente)
{
    int contador = 0;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0 && pedidos[x].idCliente == idCliente)
        {
            if(pedidos[x].PP > 0)
            {
                contador = contador + pedidos[x].PP;
            }
        }
    }
    return contador;
}
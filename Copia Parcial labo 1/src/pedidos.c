#include <stdio.h>
#include <string.h>
#include "input.h"
#include "pedidos.h"

void InicializarPedidos(ePedido pedidos[], int tamPedidos)
{
    for(int x = 0; x < tamPedidos; x++)
    {
        pedidos[x].isEmpty = 1;
    }
}

int BuscarLibrePedidos(ePedido pedidos[], int tamPedidos)
{
    int indice = -1;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 1)
        {
            indice = x;
            break;
        }
    }
    return indice;
}

void CargaPedido(ePedido pedidos[], int indice, int idPedido, int idCliente, float kTotales, int estadoPedido)
{
    if(pedidos[indice].isEmpty == 1)
    {
        pedidos[indice].idPedido = idPedido;
        pedidos[indice].idCliente = idCliente;
        pedidos[indice].kilosTotales = kTotales;
        pedidos[indice].estadoPedido = estadoPedido;
        pedidos[indice].isEmpty = 0;
    }
}

int ImprimirTodosPedido(ePedido pedidos[], int tamPedidos)
{
    printf("[IdPedido][IdCliente][Kilos totales][Estado pedido]");
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0)
        {
            printf("\n");
            ImprimirUnPedido(pedidos[x]);
        }
    }
    return 1;
}

void ImprimirUnPedido(ePedido pedido)
{
	char estadoP[11];
	if(pedido.estadoPedido != 0)
	{
		strcpy(estadoP, "COMPLETADO");
	}
	else
	{
		strcpy(estadoP, "PENDIENTE");
	}
    printf("(%-8d) (%-9d) (%-9.2f) (%-13s)", pedido.idPedido, pedido.idCliente, pedido.kilosTotales, estadoP);
}

int SolicitarIdPedidoProcesar(ePedido pedidos[], int tamPedidos)
{
    int indiceProcesar = -1;
    while(indiceProcesar == -1)
    {
        indiceProcesar = SolicitarIdPedido("\nIngrese ID del pedido a procesar: ", pedidos, tamPedidos);
    }
    return indiceProcesar;
}

int SolicitarIdPedido(char* mensaje, ePedido pedidos[], int tamPedidos)
{
    int idRetorn = -1;
    int id;
    id = getInt(mensaje);
    idRetorn = BuscarPedidoPorID(pedidos, tamPedidos, id);
    if(idRetorn == -1)
    {
        printf("\n\\ID no encontrado\\");
    }
    return idRetorn;
}

int BuscarPedidoPorID(ePedido pedidos[], int tamPedidos, int id)
{
    int indice = -1;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].idPedido == id && pedidos[x].isEmpty == 0)
        {
            indice = x;
            break;
        }
    }
    return indice;
}

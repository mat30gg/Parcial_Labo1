#include <stdio.h>
#include "cliente.h"
#include "pedidos.h"
#include "localidad.h"
#include "nucleo.h"

int main()
{
	setbuf(stdout, NULL);
    int eleccion;
    int ultimoClienteId = 1;
    int ultimoPedidosId = 500;
    int banderaPedidos = 0;
    int contCliente = 0;
    eCliente arrayClientes[TAMCLIENTE];
    ePedido pedidos[TAMPEDIDOS];
    eLocalidad localidades[TAMLOCALIDAD];
    InicializarClientes(arrayClientes, TAMCLIENTE);
    InicializarPedidos(pedidos, TAMPEDIDOS);
    IniciarLocalidad(localidades, TAMLOCALIDAD);
    do{
        eleccion = MainMenu();
        switch(eleccion)
        {
            case 1:
                MainAltaCliente(arrayClientes, TAMCLIENTE, localidades, TAMLOCALIDAD, &ultimoClienteId);
                contCliente++;
            break;
            case 2:
            	if(contCliente > 0)
            	{
            		MainModificarCliente(arrayClientes, TAMCLIENTE, localidades, TAMLOCALIDAD);
            	}
            break;
            case 3:
            	if(contCliente > 0)
            	{
            		MainBajaCliente(arrayClientes, TAMCLIENTE);
            		contCliente--;
            	}
            break;
            case 4:
            	if(contCliente > 0)
            	{
            		MainAltaPedido(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, &ultimoPedidosId);
            		banderaPedidos = 1;
            	}
            break;
            case 5:
                if(banderaPedidos == 1)
                {
                    MainProcesarResiduo(pedidos, TAMPEDIDOS);
                }
            break;
            case 6:
            	if(contCliente > 0)
            	{
            		MainImprimirClientes(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS);
            	}
            break;
            case 7:
                if(banderaPedidos == 1)
                {
                    MainImprimirEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, PENDIENTE);
                }
            break;
            case 8:
                if(banderaPedidos == 1)
                {
                    MainImprimirEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, COMPLETADO);
                }
            break;
            case 9:
                if(banderaPedidos == 1)
                {
                    MainPendientesEnLocalidad(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, localidades, TAMLOCALIDAD);
                }
            break;
            case 10:
                if(banderaPedidos == 1)
                {
                    MainPoliPromedio(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS);
                }
            break;
            case 11:
            	if(banderaPedidos == 1)
            	{
            		MainClienteMasEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, PENDIENTE);
            	}
            break;
            case 12:
            	if(banderaPedidos == 1)
            	{
            		MainClienteMasEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, COMPLETADO);
            	}
            break;
            case 0:
                printf("SALIENDO.");
            break;
            default:
                printf("\\ERROR\\");
        }
    }while(eleccion != 0);
    return 0;
}


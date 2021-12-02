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
                if(MainAltaCliente(arrayClientes, TAMCLIENTE, localidades, TAMLOCALIDAD, &ultimoClienteId))
                {
                	contCliente++;
                }
                else
                {
                	printf("No se pudo dar de alta el cliente.\n");
                }
            break;
            case 2:
            	if(contCliente > 0)
            	{
            		ImprimirTodosCliente(arrayClientes, TAMCLIENTE, localidades, TAMLOCALIDAD);
            		if(MainModificarCliente(arrayClientes, TAMCLIENTE, localidades, TAMLOCALIDAD) == 0)
            		{
            			printf("No se pudo modificar el cliente.\n");
            		}
            	}
            	else
            	{
            		printf("No hay clientes cargados.\n");
            	}
            break;
            case 3:
            	if(contCliente > 0)
            	{
            		ImprimirTodosCliente(arrayClientes, TAMCLIENTE, localidades, TAMLOCALIDAD);
            		if(MainBajaCliente(arrayClientes, TAMCLIENTE))
            		{
            			contCliente--;
            		}
            		else
            		{
            			printf("No se pudo dar de baja el cliente.\n");
            		}
            	}
            	else
            	{
            		printf("No hay clientes cargados.\n");
            	}
            break;
            case 4:
            	if(contCliente > 0)
            	{
            		if(MainAltaPedido(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, localidades, TAMLOCALIDAD, &ultimoPedidosId))
            		{
            			banderaPedidos = 1;
            		}
            		else
            		{
            			printf("No se pudo dar de alta el pedido de recoleccion.\n");
            		}
            	}
            	else
            	{
            		printf("No hay clientes cargados.\n");
            	}
            break;
            case 5:
                if(banderaPedidos == 1)
                {
                	if(MainImprimirEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, PENDIENTE) == 1)
                	{
                		MainProcesarResiduo(pedidos, TAMPEDIDOS);
                	}
                }
                else
				{
					printf("No hay pedidos cargados.\n");
				}
            break;
            case 6:
            	if(contCliente > 0)
            	{
            		MainImprimirClientes(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, localidades, TAMLOCALIDAD);
            	}
            	else
            	{
            		printf("No hay clientes cargados.\n");
            	}
            break;
            case 7:
                if(banderaPedidos == 1)
                {
                    if(MainImprimirEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, PENDIENTE) == 0)
                    {
                    	printf("No hay pedidos de recoleccion pendientes.\n");
                    }
                }
                else
				{
					printf("No hay pedidos cargados.\n");
				}
            break;
            case 8:
                if(banderaPedidos == 1)
                {
                    if(MainImprimirEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, COMPLETADO) == 0)
                    {
                    	printf("No hay pedidos de recoleccion completados.\n");
                    }
                }
                else
				{
					printf("No hay pedidos cargados.\n");
				}
            break;
            case 9:
                if(banderaPedidos == 1)
                {
                    MainPendientesEnLocalidad(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, localidades, TAMLOCALIDAD);
                }
                else
                {
                	printf("No hay pedidos cargados.\n");
                }
            break;
            case 10:
                if(banderaPedidos == 1)
                {
                    MainPoliPromedio(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS);
                }
                else
				{
					printf("No hay pedidos cargados.\n");
				}
            break;
            case 11:
            	if(banderaPedidos == 1)
            	{
            		if(MainClienteMasEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, PENDIENTE) == 0)
            		{
            			printf("No hay clientes con pedidos de recoleccion pendientes.\n");
            		}
            	}
            	else
				{
					printf("No hay pedidos cargados.\n");
				}
            break;
            case 12:
            	if(banderaPedidos == 1)
            	{
            		if(MainClienteMasEstado(arrayClientes, TAMCLIENTE, pedidos, TAMPEDIDOS, COMPLETADO) == 0)
            		{
            			printf("No hay clientes con pedidos de recoleccion completados.\n");
            		}
            	}
            	else
				{
					printf("No hay pedidos cargados.\n");
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


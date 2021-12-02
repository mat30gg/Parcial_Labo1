#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "pedidos.h"
#include "localidad.h"
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
    printf("\n(11) - Cliente con mas pedidos pendientes.");
    printf("\n(12) - Cliente con mas pedidos completados.");
    printf("\n(0)  - SALIR");
    eleccion = getInt("\nElija una opcion: ");
    return eleccion;
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
        getStringAll("Ingrese direccion del cliente: ", direccion);
        idLocalidad = AltaLocalidad(localidades, tamLocalidad);
        CargaCliente(arrayCliente, indice, nombre, cuit, direccion, idLocalidad, (*ultimoId)++);
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

int ModificarCliente(eCliente arrayCliente[], int indice, eLocalidad localidades[], int tamLocalidad)
{
    int modificado = 1;
    printf("\n");
    ImprimirUnCliente(arrayCliente[indice]);
    ImprimirLocalidad(localidades, tamLocalidad, arrayCliente[indice].idLocalidad);
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
    getStringAll("\nIngrese nueva direccion del cliente: ", cliente->direccion);
    return 1;
}

int ModificarLocalidad(eCliente* cliente, eLocalidad localidades[], int tamLocalidad)
{
    cliente->idLocalidad = AltaLocalidad(localidades, tamLocalidad);
    return 1;
}

int MainAltaPedido(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades[], int tamLocalidad, int* ultimoId)
{
    float kilosTotales;
    int idCliente;
    int idPedido;
    int indice;
    int retorn = 0;
    indice = BuscarLibrePedidos(pedidos, tamPedidos);
    if(indice != -1)
    {
        retorn = 1;
        idPedido = (*ultimoId)++;
        ImprimirTodosCliente(arrayCliente, tamCliente, localidades, tamLocalidad);
        idCliente = IngresarIdClienteExistente(arrayCliente, tamCliente);
        kilosTotales = getPositivoFlotante("Ingrese kilos totales a recolectar: ");
        CargaPedido(pedidos, indice, idPedido, idCliente, kilosTotales, PENDIENTE);
    }
    return retorn;
}

int MainProcesarResiduo(ePedido pedidos[], int tamPedidos)
{
    int indiceProcesar;
    indiceProcesar = SolicitarIdPedidoProcesar(pedidos, tamPedidos);
    if(pedidos[indiceProcesar].estadoPedido == PENDIENTE)
    {
    	IngresarPlasticos(pedidos, indiceProcesar);
    }
    pedidos[indiceProcesar].estadoPedido = COMPLETADO;
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

int MainImprimirClientes(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades[], int tamLocalidad)
{
    int cantPendientes;
    printf("\n|__ID__|___Nombre___|____Cuit_____|___Direccion___|__Localidad__|\n");
    for(int x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0)
        {
            ImprimirUnCliente(arrayCliente[x]);
            ImprimirLocalidad(localidades, tamLocalidad, arrayCliente[x].idLocalidad);
            cantPendientes = CantidadEstado(pedidos, tamPedidos, arrayCliente[x].idCliente, PENDIENTE);
            printf(" !Cantidad de pedidos de recoleccion pendientes: %d\n", cantPendientes);
        }
    }
    return cantPendientes;
}

int CantidadEstado(ePedido pedidos[], int tamPedidos, int idCliente, int estadoPedido)
{
    int contadorEstadoPedido = 0;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0)
        {
            if(pedidos[x].idCliente == idCliente && pedidos[x].estadoPedido == estadoPedido)
            {
                contadorEstadoPedido++;
            }
        }
    }
    return contadorEstadoPedido;
}

void ImprimirTodosCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad)
{
    printf("\n|__ID__|___Nombre___|____Cuit_____|___Direccion___|___Localidad___|");
    for(int x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0)
        {
            printf("\n");
            ImprimirUnCliente(arrayCliente[x]);
            ImprimirLocalidad(localidades, tamLocalidad, arrayCliente[x].idLocalidad);
        }
    }
}

int MainImprimirEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int estado)
{
    int auxId;
    int bandera1 = 0;
    for(int x = 0; x < tamPedidos; x++)
    {
        if(pedidos[x].isEmpty == 0 && pedidos[x].estadoPedido == estado)
        {

            auxId = BuscarClientePorID(arrayCliente, tamCliente, pedidos[x].idCliente);
            if(auxId != -1)
            {
            	if(x == 0)
				{
					printf("/ ID / CUIT Cliente /    Direccion    / ");
				}
				if(estado == PENDIENTE)
				{
					if(bandera1 == 0)
					{
						printf("Kg totales");
						bandera1 = 1;
					}
					ImprimirPendiente(pedidos[x].idPedido, arrayCliente[auxId].cuit, arrayCliente[auxId].direccion, pedidos[x].kilosTotales);
				}
				if(estado == COMPLETADO)
				{
					if(bandera1 == 0)
					{
						printf("HDPE  /  LDPE /  PP");
						bandera1 = 1;
					}
					ImprimirProcesado(pedidos[x].idPedido, arrayCliente[auxId].cuit, arrayCliente[auxId].direccion, pedidos[x].HDPE, pedidos[x].LDPE, pedidos[x].PP);
				}
            }
        }
    }
    return bandera1;
}

void ImprimirPendiente(int idPedido, int cuit, char* direccion, float kilosTotales)
{
    printf("\n(%-3d)  %-12d , %-15s / %.2f Kg", idPedido, cuit, direccion, kilosTotales);
}

void ImprimirProcesado(int idPedido, int cuit, char* direccion, float hdpe, float ldpe, float pp)
{
    printf("\n(%-3d)  %-12d , %-15s / %-6.2f/ %-6.2f/ %-6.2f", idPedido, cuit, direccion, hdpe, ldpe, pp);
}

int MainPendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades[], int tamLocalidad)
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
            sumador = CantidadEstado(pedidos, tamPedidos, arrayCliente[x].idCliente, PENDIENTE);
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
    return promedio;
}

int ClientesPP(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, float* promedio)
{
    int x;
    int contadorClientesPP = 0;
    float contadorPP = 0;
    float aux;
    for(x = 0; x < tamCliente; x++)
    {
        if(arrayCliente[x].isEmpty == 0)
        {
            aux = PedidosPP(pedidos, tamPedidos, arrayCliente[x].idCliente);
            contadorPP = contadorPP + aux;
            contadorClientesPP++;
        }
    }
    *promedio = contadorPP / contadorClientesPP;
    return contadorPP;
}

float PedidosPP(ePedido pedidos[], int tamPedidos, int idCliente)
{
    float contador = 0;
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

int MainClienteMasEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int estadoPedido)
{
	int idClienteMax;
	int indiceCliente;
	int cant;
	int exito = 0;
	idClienteMax = IdClienteMasEstado(arrayCliente, tamCliente, pedidos, tamPedidos, estadoPedido);
	cant = CantidadEstado(pedidos, tamPedidos, idClienteMax, estadoPedido);
	indiceCliente = BuscarClientePorID(arrayCliente, tamCliente, idClienteMax);
	if(cant > 0)
	{
		exito = 1;
		printf("El cliente con mas pedidos en estado de: ");
		if(estadoPedido == COMPLETADO)
		{
			printf("COMPLETADO");
		}
		if(estadoPedido == PENDIENTE)
		{
			printf("PENDIENTE");
		}
		printf(" es: \n");
		ImprimirUnCliente(arrayCliente[indiceCliente]);
		printf("\nCon un total de %d pedidos contados.", cant);
	}
	return exito;
}

int IdClienteMasEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int estadoPedido)
{
	int maximoEstado;
	int contadorEstado;
	int idClienteMax;
	int banderaMaximo = 0;
	for(int x = 0; x < tamCliente; x++)
	{
		if(arrayCliente[x].isEmpty == 0)
		{
			contadorEstado = CantidadEstado(pedidos, tamPedidos, arrayCliente[x].idCliente, estadoPedido);
			if(banderaMaximo == 0 || contadorEstado > maximoEstado)
			{
				idClienteMax = arrayCliente[x].idCliente;
				maximoEstado = contadorEstado;
				banderaMaximo = 1;
			}
		}
	}
	return idClienteMax;
}

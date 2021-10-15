int MainMenu();
int MainAltaPedido(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int* ultimoId);

int MainProcesarResiduo(ePedido pedidos[], int tamPedidos);
int IngresarPlasticos(ePedido pedidos[], int indice);
int VerificarPlasticos(ePedido pedido);

int MainImprimirClientes(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos);
int CantidadPendientes(ePedido pedidos[], int tamPedidos, int idCliente);

int MainImprimirEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, char* estado);
void ImprimirPendiente(int idPedido, int cuit, char* direccion, float kilosTotales);
void ImprimirProcesado(int idPedido, int cuit, char* direccion, float hdpe, float ldpe, float pp);

int MainPendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos);
int ContarPedidosDeCliente(ePedido pedidos[], int tamPedidos, int idCliente);
int PendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, char* localidad);

int MainPoliPromedio(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos);
int ClientesPP(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, float* promedio);
int PedidosPP(ePedido pedidos[], int tamPedidos, int idCliente);

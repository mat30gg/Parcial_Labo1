int MainMenu();
int MainAltaCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad,int* ultimoId);
int MainAltaPedido(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades[], int tamLocalidad, int* ultimoId);

int MainProcesarResiduo(ePedido pedidos[], int tamPedidos);
int IngresarPlasticos(ePedido pedidos[], int indice);
int VerificarPlasticos(ePedido pedido);

int MainImprimirClientes(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades[], int tamLocalidad);
int CantidadEstado(ePedido pedidos[], int tamPedidos, int idCliente, int estadoPedido);
void ImprimirTodosCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad);

int MainImprimirEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int estado);
void ImprimirPendiente(int idPedido, int cuit, char* direccion, float kilosTotales);
void ImprimirProcesado(int idPedido, int cuit, char* direccion, float hdpe, float ldpe, float pp);

int MainPendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, eLocalidad localidades[], int tamLocalidad);
int ContarPedidosDeCliente(ePedido pedidos[], int tamPedidos, int idCliente);
int PendientesEnLocalidad(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int localidad);

int MainPoliPromedio(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos);
int ClientesPP(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, float* promedio);
float PedidosPP(ePedido pedidos[], int tamPedidos, int idCliente);

int MainModificarCliente(eCliente arrayCliente[], int tamCliente, eLocalidad localidades[], int tamLocalidad);
int ModificarCliente(eCliente arrayCliente[], int indice, eLocalidad localidades[], int tamLocalidad);
int ModificarDireccion(eCliente* cliente);
int ModificarLocalidad(eCliente* cliente, eLocalidad localidades[], int tamLocalidad);

int MainClienteMasEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int estadoPedido);
int IdClienteMasEstado(eCliente arrayCliente[], int tamCliente, ePedido pedidos[], int tamPedidos, int estadoPedido);

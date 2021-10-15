#define TAMPEDIDOS 1000

typedef struct{
    int idPedido;
    int idCliente;
    float kilosTotales;
    float HDPE;
    float LDPE;
    float PP;
    char estadoPedido[11];
    int isEmpty;
}ePedido;

void InicializarPedidos(ePedido pedidos[], int tamPedidos);
int BuscarLibrePedidos(ePedido pedidos[], int tamPedidos);
void CargaPedido(ePedido pedidos[], int indice, int idPedido, int idCliente, float kTotales, char* estadoPedido);

int ImprimirTodosPedido(ePedido pedidos[], int tamPedidos);
void ImprimirUnPedido(ePedido pedido);

int SolicitarIdPedidoProcesar(ePedido pedidos[], int tamPedidos);
int SolicitarIdPedido(char* mensaje, ePedido pedidos[], int tamPedidos);
int BuscarPedidoPorID(ePedido pedidos[], int tamPedidos, int id);

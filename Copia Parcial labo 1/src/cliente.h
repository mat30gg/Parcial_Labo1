#define TAMCLIENTE 100

typedef struct{
    int idCliente;
    char nombre[26];
    int cuit;
    char direccion[26];
    int idLocalidad;
    int isEmpty;
}eCliente;

void InicializarClientes(eCliente arrayCliente[], int tamCliente);
int SolicitarIdCliente(char* mensaje, eCliente arrayCliente[], int tamCliente);
int BuscarClientePorID(eCliente arrayCliente[], int tamCliente, int id);
int IngresarIdClienteExistente(eCliente arrayCliente[], int tamCliente);
void ImprimirTodosCliente(eCliente arrayCliente[], int tamCliente);
void ImprimirUnCliente(eCliente cliente);

void CargaCliente(eCliente arrayCliente[], int indice, char nombre[], int cuit, char direccion[], int localidad, int idCliente);
int BuscarLibreCliente(eCliente arrayCliente[], int tamCliente);

int SolicitarIdClienteModificar(eCliente arrayCliente[], int tamCliente);

int MainBajaCliente(eCliente arrayCliente[], int tamCliente);
int SolicitarIdClienteBaja(eCliente arrayCliente[], int tamCliente);
int ConfirmacionBajaCliente(eCliente cliente);
int BajaCliente(eCliente arrayCliente[], int indice);

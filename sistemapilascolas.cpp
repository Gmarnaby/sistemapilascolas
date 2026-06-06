#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <cstdio>
#include <iomanip>


using namespace std;


//   ESTRUCTURAS


struct ingresos {
    int correlativoIng = 0;
    string proveedorIng;
    string fechaIng;
    string productoIng;
    int cantidadIng = 0;
};
struct nodoPila {
    ingresos ingreso;
    nodoPila* siguientePila;
};
struct pedidos {
    int correlativo = 0;
    string producto;
    int cantidad = 0;
    string cliente;
    string direccion;
};
struct nodoCola {
    pedidos pedido;
    nodoCola* siguienteCola;
};
struct cola {
    nodoCola* primero;
    nodoCola* ultimo;
};
struct nodoArbol {
    pedidos pedido;
    nodoArbol* izquierda;
    nodoArbol* derecha;
};
struct nodoAVL {
    pedidos  pedido;
    nodoAVL* izquierda;
    nodoAVL* derecha;
    int      altura;
};
struct inventario {
    int    id = 0;
    string producto;
    int    cantidad = 0;
    int    cantMinima = 0;
    double precio = 0.0;
};
struct nodoLista {
    inventario item;
    nodoLista* anterior;
    nodoLista* siguiente;
};
struct listaDoble {
    nodoLista* cabeza;
    nodoLista* cola;
    int        cantidad;
};


//   PROTOTIPOS

//Estetica
void   color(int c);
void   cls();
void   pausar();
void   barra(char relleno = 205, int ancho = 62);   
void   lineaSimple(int ancho = 62);                 
void   encabezado(const string& modulo, const string& sub = "");
void   mensajeOK(const string& msg);
void   mensajeERROR(const string& msg);
void   mensajeINFO(const string& msg);
void   mensajeADVERTENCIA(const string& msg);
void   separador();
int    menuNavegable(const string& titulo, const string& subtitulo,
    const vector<string>& opciones, int colorTitulo = 11);
void   tarjetaIngreso(const ingresos& ing, void* ptr);
void   tarjetaPedido(const pedidos& ped, void* ptr);
void   tarjetaInventario(const inventario& inv, void* ptrAnt, void* ptr, void* ptrSig);
void   dibujo();
void   portada();
void   cargando();
bool   iniciarSesion();

// Pila
void modulopila(nodoPila*& p);
int  push(nodoPila*& p);
int  pop(nodoPila*& p);
void mostrarpila(nodoPila*& p);
void modificarpila(nodoPila*& p, int correModificarIng);
void buscarpila(nodoPila*& p, int correBuscarIng);
void guardarIngreso(nodoPila*& p);
void actualizarIngreso(nodoPila*& p);
void cargarIngreso(nodoPila*& p);
void pantallacargaIngresos(nodoPila*& p);

// Cola
void modulocola(cola& q);
int  encolar(cola& q);
int  desencolar(cola& q);
void mostrarcola(cola q);
void buscarcola(cola q, int corre);
void modificarcola(cola q, int corre);
void guardarPedidos(const pedidos& q);
void actualizarPedidos(const cola& q);
void cargarPedidos(cola& q);
void pantallacargaPedidos(cola& q);

// Lista Doble
void       moduloLista(listaDoble& lista);
void       insertarLista(listaDoble& lista);
void       eliminarLista(listaDoble& lista, int id);
void       vaciarLista(listaDoble& lista);
void       mostrarLista(const listaDoble& lista);
void       buscarLista(const listaDoble& lista, int id);
void       modificarLista(listaDoble& lista, int id);
nodoLista* buscarNodoLista(listaDoble& lista, int id);

// Arbol ABB
void       moduloarbol(nodoArbol*& arbol);
void       insertarArbol(nodoArbol*& arbol);
void       insertarNodo(nodoArbol*& arbol, pedidos p);
void       mostrarArbolOrden(nodoArbol* arbol);
void       buscarMayor(nodoArbol* arbol);
nodoArbol* eliminarNodo(nodoArbol* arbol, int correlativo);
nodoArbol* encontrarMinimo(nodoArbol* nodo);
void       vaciarArbol(nodoArbol*& arbol);
void       dibujarArbol(nodoArbol* raiz);
void       llenarNiveles(nodoArbol* nodo, int nivel, int pos, int ancho,
    vector<vector<pair<nodoArbol*, int>>>& niveles);

// Arbol AVL
void     moduloAVL(nodoAVL*& avl);
void     insertarAVL(nodoAVL*& avl);
nodoAVL* insertarNodoAVL(nodoAVL* raiz, pedidos p, bool& insertado);
nodoAVL* eliminarNodoAVL(nodoAVL* raiz, int correlativo, bool& eliminado);
nodoAVL* vaciarAVL_aux(nodoAVL* raiz);
void     vaciarAVL(nodoAVL*& avl);
void     mostrarAVLOrden(nodoAVL* raiz);
void     buscarMayorAVL(nodoAVL* raiz);
void     dibujarAVL(nodoAVL* raiz);
int      alturaAVL(nodoAVL* n);
int      factorEquilibrio(nodoAVL* n);
void     actualizarAltura(nodoAVL* n);
nodoAVL* rotarDerecha(nodoAVL* y);
nodoAVL* rotarIzquierda(nodoAVL* x);
nodoAVL* balancear(nodoAVL* n);
nodoAVL* minimoAVL(nodoAVL* n);
void     llenarNivelesAVL(nodoAVL* nodo, int nivel, int pos, int ancho,
    vector<vector<pair<nodoAVL*, int>>>& niveles);


//   VARIABLES GLOBALES

int correlativoPedidos = 1;
int correlativoIngGlobal = 1;
int correlativoInventario = 1;

//   PALETA DE COLORES

#define C_RESET     7
#define C_BORDE     8    
#define C_TITULO    11   
#define C_SUBTIT    3     
#define C_LABEL     8     
#define C_VALOR     15    
#define C_OK        10    
#define C_ERROR     12    
#define C_WARN      14    
#define C_INFO      9     
#define C_SELEC     10    
#define C_NORMAL    7     
#define C_SALIR     12    
#define C_PUNTERO   14    
#define C_MAYOREO   14    
#define C_BAJOSTK   12    
#define C_PRECIO    10    
#define C_MEM       8     
#define C_ARBOL_OK  10    
#define C_ARBOL_L   14    
#define C_ARBOL_CR  12    


//FUNCIONES CENTRALIZADAS DE APARIENCIA


void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cls() { system("cls"); }
void pausar() { system("pause"); }


void barra(char relleno, int ancho) {
    color(C_BORDE);
    for (int i = 0; i < ancho; i++) cout << relleno;
    cout << "\n";
    color(C_RESET);
}

void lineaSimple(int ancho) {
    color(C_BORDE);
    
    for (int i = 0; i < ancho; i++) cout << char(196);
    cout << "\n";
    color(C_RESET);
}


void encabezado(const string& modulo, const string& sub) {
    const int W = 62;
    color(C_BORDE);
    cout << char(201); 
    for (int i = 0; i < W; i++) cout << char(205); 
    cout << char(187) << "\n"; 

    
    int pad = (W - (int)modulo.size()) / 2;
    color(C_BORDE); cout << char(186); 
    color(C_TITULO);
    for (int i = 0; i < pad; i++) cout << " ";
    cout << modulo;
    for (int i = 0; i < W - pad - (int)modulo.size(); i++) cout << " ";
    color(C_BORDE); cout << char(186) << "\n"; 

   
    if (!sub.empty()) {
        color(C_BORDE); cout << char(186); 
        color(C_SUBTIT);
        int pad2 = (W - (int)sub.size()) / 2;
        for (int i = 0; i < pad2; i++) cout << " ";
        cout << sub;
        for (int i = 0; i < W - pad2 - (int)sub.size(); i++) cout << " ";
        color(C_BORDE); cout << char(186) << "\n";
    }

    color(C_BORDE);
    cout << char(200); 
    for (int i = 0; i < W; i++) cout << char(205);
    cout << char(188) << "\n\n"; 
    color(C_RESET);
}

void separador() {
    color(C_BORDE);
    cout << " ";
    for (int i = 0; i < 60; i++) cout << char(196);
    cout << "\n";
    color(C_RESET);
}


void mensajeOK(const string& msg) {
    color(C_BORDE);  cout << " " << char(218);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(191) << "\n";

    color(C_BORDE);  cout << " " << char(179);
    color(C_OK);     cout << "  [  OK  ]  " << msg;
    int relleno = 46 - (int)msg.size();
    if (relleno < 0) relleno = 0;
    for (int i = 0; i < relleno; i++) cout << " ";
    color(C_BORDE);  cout << char(179) << "\n";

    color(C_BORDE);  cout << " " << char(192);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(217) << "\n\n";
    color(C_RESET);
}


void mensajeERROR(const string& msg) {
    color(C_BORDE);  cout << " " << char(218);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(191) << "\n";

    color(C_BORDE);  cout << " " << char(179);
    color(C_ERROR);  cout << "  [ ERR  ]  " << msg;
    int relleno = 46 - (int)msg.size();
    if (relleno < 0) relleno = 0;
    for (int i = 0; i < relleno; i++) cout << " ";
    color(C_BORDE);  cout << char(179) << "\n";

    color(C_BORDE);  cout << " " << char(192);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(217) << "\n\n";
    color(C_RESET);
}


void mensajeINFO(const string& msg) {
    color(C_BORDE);  cout << " " << char(218);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(191) << "\n";

    color(C_BORDE);  cout << " " << char(179);
    color(C_INFO);   cout << "  [ INFO ]  " << msg;
    int relleno = 46 - (int)msg.size();
    if (relleno < 0) relleno = 0;
    for (int i = 0; i < relleno; i++) cout << " ";
    color(C_BORDE);  cout << char(179) << "\n";

    color(C_BORDE);  cout << " " << char(192);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(217) << "\n\n";
    color(C_RESET);
}

// Mensaje advertencia
void mensajeADVERTENCIA(const string& msg) {
    color(C_BORDE);  cout << " " << char(218);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(191) << "\n";

    color(C_BORDE);  cout << " " << char(179);
    color(C_WARN);   cout << "  [ WARN ]  " << msg;
    int relleno = 46 - (int)msg.size();
    if (relleno < 0) relleno = 0;
    for (int i = 0; i < relleno; i++) cout << " ";
    color(C_BORDE);  cout << char(179) << "\n";

    color(C_BORDE);  cout << " " << char(192);
    for (int i = 0; i < 58; i++) cout << char(196);
    cout << char(217) << "\n\n";
    color(C_RESET);
}


// Menu navegable 

int menuNavegable(const string& titulo, const string& subtitulo,
    const vector<string>& opciones, int colorTitulo)
{
    int op = 0;
    int tecla = 0;
    int n = (int)opciones.size();

    do {
        cls();

        const int W = 62;
        color(C_BORDE);
        cout << char(201);
        for (int i = 0; i < W; i++) cout << char(205);
        cout << char(187) << "\n";

        auto lineaCentrada = [&](const string& txt, int c) {
            int pad = (W - (int)txt.size()) / 2;
            color(C_BORDE); cout << char(186);
            color(c);
            for (int i = 0; i < pad; i++) cout << " ";
            cout << txt;
            for (int i = 0; i < W - pad - (int)txt.size(); i++) cout << " ";
            color(C_BORDE); cout << char(186) << "\n";
            };

        lineaCentrada(titulo, colorTitulo);
        if (!subtitulo.empty()) lineaCentrada(subtitulo, C_SUBTIT);

        color(C_BORDE);
        cout << char(204);
        for (int i = 0; i < W; i++) cout << char(205);
        cout << char(185) << "\n";


        for (int i = 0; i < n; i++) {
            color(C_BORDE); cout << char(186);
            bool selec = (i == op);
            bool esUlti = (i == n - 1); 

            if (selec) {
                color(C_PUNTERO); cout << "  " << char(16) << char(16) << " "; 
                color(esUlti ? C_SALIR : C_SELEC);

                cout << "[ " << opciones[i] << " ]";

                int used = 7 + (int)opciones[i].size() + 2;
                for (int k = used; k < W; k++) cout << " ";
            }
            else {
                color(C_BORDE); cout << "      ";
                color(esUlti ? C_ERROR : C_NORMAL);
                cout << opciones[i];
                int used = 6 + (int)opciones[i].size();
                for (int k = used; k < W; k++) cout << " ";
            }
            color(C_BORDE); cout << char(186) << "\n";
        }

        color(C_BORDE);
        cout << char(204);
        for (int i = 0; i < W; i++) cout << char(196);
        cout << char(185) << "\n";

        color(C_BORDE); cout << char(186);
        color(C_LABEL);
        string hint = "  Use las FLECHAS y ENTER para seleccionar ";
        cout << hint;
        for (int i = (int)hint.size(); i < W; i++) cout << " ";
        color(C_BORDE); cout << char(186) << "\n";

        color(C_BORDE);
        cout << char(200);
        for (int i = 0; i < W; i++) cout << char(205);
        cout << char(188) << "\n";

        tecla = _getch();
        if (tecla == 72) { op--; if (op < 0) op = n - 1; }
        if (tecla == 80) { op++; if (op >= n) op = 0; }

    } while (tecla != 13);

    color(C_RESET);
    return op;
}

// Tarjeta de ingreso (Pila)

void tarjetaIngreso(const ingresos& ing, void* ptr) {
    color(C_BORDE);
    cout << "  " << char(218);
    for (int i = 0; i < 56; i++) cout << char(196);
    cout << char(191) << "\n";

    auto fila = [](const string& lbl, const string& val, int cLbl, int cVal) {
        color(C_BORDE); cout << "  " << char(179) << " ";
        color(cLbl);    cout << left << setw(18) << lbl;
        color(C_BORDE); cout << char(179) << " ";
        color(cVal);    cout << left << setw(35) << val.substr(0, 35);
        color(C_BORDE); cout << char(179) << "\n";
        };

    fila("Ingreso No.", to_string(ing.correlativoIng), C_LABEL, C_WARN);
    fila("Proveedor", ing.proveedorIng, C_LABEL, C_VALOR);
    fila("Fecha", ing.fechaIng, C_LABEL, C_INFO);
    fila("Producto", ing.productoIng, C_LABEL, C_VALOR);
    fila("Cantidad", to_string(ing.cantidadIng), C_LABEL, C_OK);


    ostringstream ss; ss << ptr;
    color(C_BORDE); cout << "  " << char(179) << " ";
    color(C_LABEL); cout << left << setw(18) << "Direccion Mem.";
    color(C_BORDE); cout << char(179) << " ";
    color(C_MEM);   cout << left << setw(35) << ss.str().substr(0, 35);
    color(C_BORDE); cout << char(179) << "\n";

    color(C_BORDE);
    cout << "  " << char(192);
    for (int i = 0; i < 56; i++) cout << char(196);
    cout << char(217) << "\n";
    color(C_RESET);
}


// Tarjeta de pedido (Cola / Arboles)

void tarjetaPedido(const pedidos& ped, void* ptr) {
    bool mayoreo = (ped.cantidad >= 50);
    color(C_BORDE);
    cout << "  " << char(218);
    for (int i = 0; i < 56; i++) cout << char(196);
    cout << char(191) << "\n";

    auto fila = [](const string& lbl, const string& val, int cLbl, int cVal) {
        color(C_BORDE); cout << "  " << char(179) << " ";
        color(cLbl);    cout << left << setw(18) << lbl;
        color(C_BORDE); cout << char(179) << " ";
        color(cVal);    cout << left << setw(35) << val.substr(0, 35);
        color(C_BORDE); cout << char(179) << "\n";
        };

    fila("Pedido No.", to_string(ped.correlativo), C_LABEL, C_WARN);
    fila("Producto", ped.producto, C_LABEL, C_VALOR);
    fila("Cantidad", to_string(ped.cantidad) + (mayoreo ? "  << MAYOREO 15%" : ""),
        C_LABEL, mayoreo ? C_MAYOREO : C_OK);
    fila("Cliente", ped.cliente, C_LABEL, C_TITULO);
    fila("Direccion", ped.direccion, C_LABEL, C_VALOR);

    if (ptr) {
        ostringstream ss; ss << ptr;
        color(C_BORDE); cout << "  " << char(179) << " ";
        color(C_LABEL); cout << left << setw(18) << "Direccion Mem.";
        color(C_BORDE); cout << char(179) << " ";
        color(C_MEM);   cout << left << setw(35) << ss.str().substr(0, 35);
        color(C_BORDE); cout << char(179) << "\n";
    }

    color(C_BORDE);
    cout << "  " << char(192);
    for (int i = 0; i < 56; i++) cout << char(196);
    cout << char(217) << "\n";
    color(C_RESET);
}


// Tarjeta de inventario (Lista Doble)

void tarjetaInventario(const inventario& inv, void* ptrAnt, void* ptr, void* ptrSig) {
    bool bajo = (inv.cantidad <= inv.cantMinima);
    int cCant = bajo ? C_BAJOSTK : C_OK;

    color(C_BORDE);
    cout << "  " << char(218);
    for (int i = 0; i < 56; i++) cout << char(196);
    cout << char(191) << "\n";

    auto fila = [](const string& lbl, const string& val, int cLbl, int cVal) {
        color(C_BORDE); cout << "  " << char(179) << " ";
        color(cLbl);    cout << left << setw(18) << lbl;
        color(C_BORDE); cout << char(179) << " ";
        color(cVal);    cout << left << setw(35) << val.substr(0, 35);
        color(C_BORDE); cout << char(179) << "\n";
        };

    char buf[32];
    snprintf(buf, sizeof(buf), "Q%.2f", inv.precio);
    char bufT[32];
    snprintf(bufT, sizeof(bufT), "Q%.2f", inv.precio * inv.cantidad);

    fila("ID", to_string(inv.id), C_LABEL, C_WARN);
    fila("Producto", inv.producto, C_LABEL, C_VALOR);
    fila("Cantidad", to_string(inv.cantidad) + (bajo ? "  << STOCK BAJO" : ""),
        C_LABEL, cCant);
    fila("Cant. Minima", to_string(inv.cantMinima), C_LABEL, C_LABEL);
    fila("Precio Unit.", string(buf), C_LABEL, C_PRECIO);
    fila("Valor Total", string(bufT), C_LABEL, C_PRECIO);

   
    auto filaPtr = [](const string& lbl, void* p) {
        ostringstream ss; ss << p;
        color(C_BORDE); cout << "  " << char(179) << " ";
        color(C_LABEL); cout << left << setw(18) << lbl;
        color(C_BORDE); cout << char(179) << " ";
        color(C_MEM);   cout << left << setw(35) << ss.str().substr(0, 35);
        color(C_BORDE); cout << char(179) << "\n";
        };
    filaPtr("Dir. Anterior", ptrAnt);
    filaPtr("Dir. Nodo", ptr);
    filaPtr("Dir. Siguiente", ptrSig);

    color(C_BORDE);
    cout << "  " << char(192);
    for (int i = 0; i < 56; i++) cout << char(196);
    cout << char(217) << "\n";
    color(C_RESET);
}


//   MAIN


int main()
{
    cola       q = { NULL, NULL };
    nodoPila* p = NULL;
    listaDoble lista = { NULL, NULL, 0 };
    nodoArbol* arbol = NULL;
    nodoAVL* avl = NULL;

    dibujo();
    portada();
    if (!iniciarSesion()) return 0;
    cargando();

    int op;
    do {
        op = menuNavegable(
            "SISTEMA DE CONTROL DE INVENTARIO",
            "KANGAROO BOXING",
            { "Modulo PILA  (Ingresos)",
              "Modulo COLA  (Pedidos)",
              "Modulo LISTA DOBLE  (Inventario)",
              "Modulo ARBOL ABB",
              "Modulo ARBOL AVL",
              "Salir del sistema" },
            C_TITULO
        );

        switch (op) {
        case 0: pantallacargaIngresos(p); modulopila(p);   break;
        case 1: pantallacargaPedidos(q);  modulocola(q);   break;
        case 2: moduloLista(lista);                         break;
        case 3: moduloarbol(arbol);                         break;
        case 4: moduloAVL(avl);                             break;
        case 5:
            cls();
            encabezado("SALIENDO DEL SISTEMA", "Hasta luego");
            color(C_WARN);  cout << "  Guardando datos";
            for (int i = 0; i < 3; i++) { Sleep(300); cout << "."; }
            cout << "\n\n";
            color(C_OK);    cout << "  Cerrando aplicacion";
            Sleep(600);
            color(C_RESET); cout << "\n\n";
            break;
        }
    } while (op != 5);

    return 0;
}


//   MODULO PILA


void modulopila(nodoPila*& p) {
    int op;
    int correPush, busqueda, modificacion;
    int x;
    char res;

    do {
        op = menuNavegable(
            "MODULO PILA",
            "INGRESOS PENDIENTES DE VALIDACION",
            { "Registrar ingreso",
              "Validar (POP)",
              "Mostrar pila",
              "Buscar ingreso",
              "Modificar ingreso",
              "Regresar al menu principal" },
            C_TITULO
        );

        cls();
        switch (op) {
        case 0:
            encabezado("REGISTRAR INGRESO DE PRODUCTO");
            correPush = push(p);
            mensajeOK("Ingreso No." + to_string(correPush) + " registrado con exito");
            separador();
            color(C_TITULO); cout << "\n  Estado actual de la pila:\n\n";
            mostrarpila(p);
            break;

        case 1:
            encabezado("VALIDAR INGRESO (POP)");
            if (p != NULL) {
                color(C_LABEL); cout << "  Se validara el ingreso No. ";
                color(C_WARN);  cout << p->ingreso.correlativoIng << "\n";
                color(C_LABEL); cout << "  Desea continuar? (Y/N): ";
                color(C_VALOR); cin >> res; cin.ignore();
                if (res == 'Y' || res == 'y') {
                    x = pop(p);
                    mensajeOK("Ingreso No." + to_string(x) + " validado correctamente");
                    separador();
                    color(C_TITULO); cout << "\n  Estado actual de la pila:\n\n";
                    if (p != NULL) mostrarpila(p);
                    else mensajeINFO("La pila esta vacia");
                }
            }
            else {
                mensajeADVERTENCIA("No existen ingresos pendientes de validacion");
            }
            break;

        case 2:
            encabezado("MOSTRAR PILA DE INGRESOS");
            if (p != NULL) mostrarpila(p);
            else mensajeADVERTENCIA("No hay ingresos registrados");
            break;

        case 3:
            encabezado("BUSCAR INGRESO");
            color(C_LABEL); cout << "  Ingrese el No. de ingreso a buscar: ";
            color(C_VALOR); cin >> busqueda; cin.ignore();
            buscarpila(p, busqueda);
            break;

        case 4:
            encabezado("MODIFICAR INGRESO");
            color(C_LABEL); cout << "  Ingrese el No. de ingreso a modificar: ";
            color(C_VALOR); cin >> modificacion; cin.ignore();
            modificarpila(p, modificacion);
            break;
        }

        if (op != 5) { cout << "\n"; pausar(); }

    } while (op != 5);
}

int push(nodoPila*& p) {
    nodoPila* aux = new nodoPila();
    aux->ingreso.correlativoIng = correlativoIngGlobal++;

    color(C_LABEL); cout << "  Proveedor del producto : "; color(C_VALOR); getline(cin, aux->ingreso.proveedorIng);
    color(C_LABEL); cout << "  Fecha de ingreso (dd/mm/yy): "; color(C_VALOR); getline(cin, aux->ingreso.fechaIng);
    color(C_LABEL); cout << "  Nombre del producto    : "; color(C_VALOR); getline(cin, aux->ingreso.productoIng);
    color(C_LABEL); cout << "  Cantidad de producto   : "; color(C_VALOR); cin >> aux->ingreso.cantidadIng; cin.ignore();

    aux->siguientePila = p;
    p = aux;
    guardarIngreso(p);
    return aux->ingreso.correlativoIng;
}

int pop(nodoPila*& p) {
    nodoPila* aux = p;
    int corre = aux->ingreso.correlativoIng;
    p = aux->siguientePila;
    delete aux;
    actualizarIngreso(p);
    return corre;
}

void mostrarpila(nodoPila*& p) {
    nodoPila* aux = p;
    int contador = 0;
    while (aux != NULL) {
        tarjetaIngreso(aux->ingreso, aux);
        cout << "\n";
        aux = aux->siguientePila;
        contador++;
    }
    color(C_LABEL); cout << "  Total de ingresos en pila: ";
    color(C_WARN);  cout << contador << "\n";
    color(C_RESET);
}

void modificarpila(nodoPila*& p, int correModificarIng) {
    nodoPila* aux = p;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->ingreso.correlativoIng == correModificarIng) {
            color(C_TITULO); cout << "\n  Modificando ingreso No. [" << aux->ingreso.correlativoIng << "]\n\n";
            color(C_LABEL);  cout << "  Proveedor      : "; color(C_VALOR); getline(cin, aux->ingreso.proveedorIng);
            color(C_LABEL);  cout << "  Fecha          : "; color(C_VALOR); getline(cin, aux->ingreso.fechaIng);
            color(C_LABEL);  cout << "  Nombre producto: "; color(C_VALOR); getline(cin, aux->ingreso.productoIng);
            color(C_LABEL);  cout << "  Cantidad       : "; color(C_VALOR); cin >> aux->ingreso.cantidadIng; cin.ignore();
            mensajeOK("Ingreso modificado correctamente");
            encontrado = true;
        }
        aux = aux->siguientePila;
    }
    if (!encontrado) mensajeERROR("No se encontro el ingreso No." + to_string(correModificarIng));
}

void buscarpila(nodoPila*& p, int correBuscarIng) {
    nodoPila* aux = p;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->ingreso.correlativoIng == correBuscarIng) {
            tarjetaIngreso(aux->ingreso, aux);
            encontrado = true;
        }
        aux = aux->siguientePila;
    }
    if (!encontrado) mensajeERROR("No se encontro el ingreso No." + to_string(correBuscarIng));
}

void guardarIngreso(nodoPila*& p) {
    ofstream archivo("ingresos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << p->ingreso.correlativoIng << "|" << p->ingreso.proveedorIng << "|"
            << p->ingreso.fechaIng << "|" << p->ingreso.productoIng << "|"
            << p->ingreso.cantidadIng << endl;
        archivo.close();
    }
}

void actualizarIngreso(nodoPila*& p) {
    ofstream archivo("ingresos.txt", ios::out);
    nodoPila* aux = p;
    if (archivo.is_open()) {
        while (aux != NULL) {
            archivo << aux->ingreso.correlativoIng << "|" << aux->ingreso.proveedorIng << "|"
                << aux->ingreso.fechaIng << "|" << aux->ingreso.productoIng << "|"
                << aux->ingreso.cantidadIng << endl;
            aux = aux->siguientePila;
        }
        archivo.close();
    }
}

void cargarIngreso(nodoPila*& p) {
    ifstream archivo("ingresos.txt");
    string linea;
    if (archivo.fail()) {
        mensajeERROR("Fallo al cargar ingresos - contacte servicio tecnico");
        exit(1);
    }
    int maxCorr = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        nodoPila* nuevo = new nodoPila;
        getline(ss, dato, '|');
        nuevo->ingreso.correlativoIng = stoi(dato);
        if (nuevo->ingreso.correlativoIng > maxCorr) maxCorr = nuevo->ingreso.correlativoIng;
        getline(ss, nuevo->ingreso.proveedorIng, '|');
        getline(ss, nuevo->ingreso.fechaIng, '|');
        getline(ss, nuevo->ingreso.productoIng, '|');
        getline(ss, dato, '|');
        nuevo->ingreso.cantidadIng = stoi(dato);
        nuevo->siguientePila = p;
        p = nuevo;
    }
    archivo.close();
    correlativoIngGlobal = maxCorr + 1;
}

void pantallacargaIngresos(nodoPila*& p) {
    cls();
    encabezado("CARGANDO MODULO PILA", "Ingresos Pendientes de Validacion");
    color(C_LABEL); cout << "  Accediendo a datos";
    for (int i = 0; i < 3; i++) { Sleep(300); cout << "."; }
    cout << "\n\n  [";
    color(C_OK);
    for (int i = 0; i < 20; i++) {
        if (i == 5) cargarIngreso(p);
        cout << char(219);
        Sleep(60);
    }
    color(C_RESET); cout << "] ";
    color(C_OK); cout << "100%\n\n";
    color(C_RESET);
}

//   MODULO COLA


void modulocola(cola& q) {
    int op;
    char res;
    int correEncolar, correBuscar, correModificar;
    int x;

    do {
        op = menuNavegable(
            "MODULO COLA",
            "PEDIDOS DE CLIENTES",
            { "Ingresar pedido",
              "Despachar pedido (DESENCOLAR)",
              "Mostrar cola",
              "Buscar pedido",
              "Modificar pedido",
              "Regresar al menu principal" },
            C_TITULO
        );

        cls();
        switch (op) {
        case 0:
            encabezado("INGRESAR PEDIDO DE CLIENTE");
            correEncolar = encolar(q);
            mensajeOK("Pedido No." + to_string(correEncolar) + " ingresado correctamente");
            separador();
            color(C_TITULO); cout << "\n  Estado actual de la cola:\n\n";
            mostrarcola(q);
            break;

        case 1:
            encabezado("DESPACHAR PEDIDO");
            if (q.primero != NULL) {
                color(C_LABEL); cout << "  Se despachara el pedido No. ";
                color(C_WARN);  cout << q.primero->pedido.correlativo << "\n";
                color(C_LABEL); cout << "  Desea continuar? (Y/N): ";
                color(C_VALOR); cin >> res; cin.ignore();
                if (res == 'Y' || res == 'y') {
                    x = desencolar(q);
                    mensajeOK("Pedido No." + to_string(x) + " despachado correctamente");
                    separador();
                    color(C_TITULO); cout << "\n  Estado actual de la cola:\n\n";
                    if (q.primero != NULL) mostrarcola(q);
                    else mensajeINFO("La cola esta vacia");
                }
            }
            else {
                mensajeADVERTENCIA("No hay pedidos pendientes de despacho");
            }
            break;

        case 2:
            encabezado("MOSTRAR COLA DE PEDIDOS");
            if (q.primero != NULL) mostrarcola(q);
            else mensajeADVERTENCIA("No hay pedidos registrados");
            break;

        case 3:
            encabezado("BUSCAR PEDIDO");
            if (q.primero != NULL) {
                color(C_LABEL); cout << "  Numero de pedido a buscar: ";
                color(C_VALOR); cin >> correBuscar; cin.ignore();
                buscarcola(q, correBuscar);
            }
            else {
                mensajeADVERTENCIA("No hay pedidos registrados");
            }
            break;

        case 4:
            encabezado("MODIFICAR PEDIDO");
            if (q.primero != NULL) {
                color(C_LABEL); cout << "  Numero de pedido a modificar: ";
                color(C_VALOR); cin >> correModificar; cin.ignore();
                modificarcola(q, correModificar);
            }
            else {
                mensajeADVERTENCIA("No hay pedidos registrados");
            }
            break;
        }

        if (op != 5) { cout << "\n"; pausar(); }

    } while (op != 5);
}

int encolar(cola& q) {
    nodoCola* aux = new nodoCola;
    aux->pedido.correlativo = correlativoPedidos++;

    color(C_LABEL); cout << "  Producto           : "; color(C_VALOR); getline(cin, aux->pedido.producto);
    color(C_LABEL); cout << "  Cantidad           : "; color(C_VALOR); cin >> aux->pedido.cantidad; cin.ignore();
    color(C_LABEL); cout << "  Nombre del cliente : "; color(C_VALOR); getline(cin, aux->pedido.cliente);
    color(C_LABEL); cout << "  Direccion          : "; color(C_VALOR); getline(cin, aux->pedido.direccion);

    aux->siguienteCola = NULL;
    if (q.primero == NULL) q.primero = aux;
    else q.ultimo->siguienteCola = aux;
    q.ultimo = aux;
    guardarPedidos(aux->pedido);
    return aux->pedido.correlativo;
}

int desencolar(cola& q) {
    nodoCola* aux = q.primero;
    int corre = aux->pedido.correlativo;
    q.primero = q.primero->siguienteCola;
    delete aux;
    actualizarPedidos(q);
    return corre;
}

void mostrarcola(cola q) {
    nodoCola* aux = q.primero;
    int contador = 0;
    while (aux != NULL) {
        tarjetaPedido(aux->pedido, aux);
        cout << "\n";
        aux = aux->siguienteCola;
        contador++;
    }
    color(C_LABEL); cout << "  Total de pedidos en cola: ";
    color(C_WARN);  cout << contador << "\n";
    color(C_RESET);
}

void buscarcola(cola q, int corre) {
    nodoCola* aux = q.primero;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->pedido.correlativo == corre) {
            tarjetaPedido(aux->pedido, aux);
            encontrado = true;
        }
        aux = aux->siguienteCola;
    }
    if (!encontrado) mensajeERROR("No se encontro el pedido No." + to_string(corre));
}

void modificarcola(cola q, int corre) {
    nodoCola* aux = q.primero;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->pedido.correlativo == corre) {
            color(C_TITULO); cout << "\n  Modificando pedido No. [" << aux->pedido.correlativo << "]\n\n";
            color(C_LABEL);  cout << "  Nuevo producto    : "; color(C_VALOR); getline(cin, aux->pedido.producto);
            color(C_LABEL);  cout << "  Nueva cantidad    : "; color(C_VALOR); cin >> aux->pedido.cantidad; cin.ignore();
            color(C_LABEL);  cout << "  Nuevo cliente     : "; color(C_VALOR); getline(cin, aux->pedido.cliente);
            color(C_LABEL);  cout << "  Nueva direccion   : "; color(C_VALOR); getline(cin, aux->pedido.direccion);
            mensajeOK("Pedido modificado correctamente");
            encontrado = true;
        }
        aux = aux->siguienteCola;
    }
    if (!encontrado) mensajeERROR("No se encontro el pedido No." + to_string(corre));
    actualizarPedidos(q);
}

void guardarPedidos(const pedidos& q) {
    ofstream archivo("pedidos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << q.correlativo << "|" << q.producto << "|"
            << q.cantidad << "|" << q.cliente << "|" << q.direccion << endl;
        archivo.close();
    }
}

void actualizarPedidos(const cola& q) {
    ofstream archivo("pedidos.txt", ios::out);
    nodoCola* aux = q.primero;
    if (archivo.is_open()) {
        while (aux != NULL) {
            archivo << aux->pedido.correlativo << "|" << aux->pedido.producto << "|"
                << aux->pedido.cantidad << "|" << aux->pedido.cliente << "|"
                << aux->pedido.direccion << endl;
            aux = aux->siguienteCola;
        }
        archivo.close();
    }
}

void cargarPedidos(cola& q) {
    ifstream archivo("pedidos.txt");
    string linea;
    if (archivo.fail()) {
        mensajeERROR("Fallo al cargar pedidos - contacte servicio tecnico");
        exit(1);
    }
    int maxCorr = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        nodoCola* nuevo = new nodoCola;
        getline(ss, dato, '|');
        nuevo->pedido.correlativo = stoi(dato);
        if (nuevo->pedido.correlativo > maxCorr) maxCorr = nuevo->pedido.correlativo;
        getline(ss, nuevo->pedido.producto, '|');
        getline(ss, dato, '|');
        nuevo->pedido.cantidad = stoi(dato);
        getline(ss, nuevo->pedido.cliente, '|');
        getline(ss, nuevo->pedido.direccion, '|');
        nuevo->siguienteCola = NULL;
        if (q.primero == NULL) q.primero = nuevo;
        else q.ultimo->siguienteCola = nuevo;
        q.ultimo = nuevo;
    }
    archivo.close();
    correlativoPedidos = maxCorr + 1;
}

void pantallacargaPedidos(cola& q) {
    cls();
    encabezado("CARGANDO MODULO COLA", "Pedidos de Clientes");
    color(C_LABEL); cout << "  Accediendo a datos";
    for (int i = 0; i < 3; i++) { Sleep(300); cout << "."; }
    cout << "\n\n  [";
    color(C_OK);
    for (int i = 0; i < 20; i++) {
        if (i == 5) cargarPedidos(q);
        cout << char(219);
        Sleep(60);
    }
    color(C_RESET); cout << "] ";
    color(C_OK); cout << "100%\n\n";
    color(C_RESET);
}


//   MODULO LISTA DOBLE (INVENTARIO)


void insertarLista(listaDoble& lista) {
    nodoLista* nuevo = new nodoLista();
    nuevo->item.id = correlativoInventario++;

    color(C_LABEL); cout << "  Nombre del producto  : "; color(C_VALOR); getline(cin, nuevo->item.producto);
    color(C_LABEL); cout << "  Cantidad en bodega   : "; color(C_VALOR); cin >> nuevo->item.cantidad; cin.ignore();
    color(C_LABEL); cout << "  Cantidad minima      : "; color(C_VALOR); cin >> nuevo->item.cantMinima; cin.ignore();
    color(C_LABEL); cout << "  Precio unitario   Q  : "; color(C_VALOR); cin >> nuevo->item.precio; cin.ignore();

    nuevo->siguiente = NULL;
    nuevo->anterior = lista.cola;

    if (lista.cabeza == NULL) lista.cabeza = nuevo;
    else lista.cola->siguiente = nuevo;
    lista.cola = nuevo;
    lista.cantidad++;
}

nodoLista* buscarNodoLista(listaDoble& lista, int id) {
    nodoLista* aux = lista.cabeza;
    while (aux != NULL) {
        if (aux->item.id == id) return aux;
        aux = aux->siguiente;
    }
    return NULL;
}

void buscarLista(const listaDoble& lista, int id) {
    nodoLista* aux = lista.cabeza;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->item.id == id) {
            tarjetaInventario(aux->item, aux->anterior, aux, aux->siguiente);
            encontrado = true;
        }
        aux = aux->siguiente;
    }
    if (!encontrado) mensajeERROR("No se encontro el producto con ID " + to_string(id));
}

void eliminarLista(listaDoble& lista, int id) {
    nodoLista* aux = buscarNodoLista(lista, id);
    if (aux == NULL) {
        mensajeERROR("No se encontro el ID " + to_string(id));
        return;
    }
    if (aux->anterior != NULL) aux->anterior->siguiente = aux->siguiente;
    else lista.cabeza = aux->siguiente;
    if (aux->siguiente != NULL) aux->siguiente->anterior = aux->anterior;
    else lista.cola = aux->anterior;
    delete aux;
    lista.cantidad--;
    mensajeOK("Producto eliminado del inventario");
}

void modificarLista(listaDoble& lista, int id) {
    nodoLista* aux = buscarNodoLista(lista, id);
    if (aux == NULL) {
        mensajeERROR("No se encontro el ID " + to_string(id));
        return;
    }
    color(C_TITULO); cout << "\n  Modificando producto ID [" << aux->item.id << "] - " << aux->item.producto << "\n\n";
    color(C_LABEL);  cout << "  Nuevo nombre       : "; color(C_VALOR); getline(cin, aux->item.producto);
    color(C_LABEL);  cout << "  Nueva cantidad     : "; color(C_VALOR); cin >> aux->item.cantidad; cin.ignore();
    color(C_LABEL);  cout << "  Nueva cant. minima : "; color(C_VALOR); cin >> aux->item.cantMinima; cin.ignore();
    color(C_LABEL);  cout << "  Nuevo precio     Q : "; color(C_VALOR); cin >> aux->item.precio; cin.ignore();
    mensajeOK("Producto modificado correctamente");
}

void vaciarLista(listaDoble& lista) {
    nodoLista* aux = lista.cabeza;
    while (aux != NULL) {
        nodoLista* temp = aux->siguiente;
        delete aux;
        aux = temp;
    }
    lista.cabeza = lista.cola = NULL;
    lista.cantidad = 0;
}

void mostrarLista(const listaDoble& lista) {
    if (lista.cabeza == NULL) {
        mensajeADVERTENCIA("El inventario esta vacio");
        return;
    }

    
    color(C_TITULO); cout << "  INVENTARIO  -  ARTICULOS DEPORTIVOS PARA CANGUROS";
    color(C_LABEL);  cout << "  (" << lista.cantidad << " productos)\n\n";

    color(C_BORDE);
    cout << "  " << char(218)
        << string(6, char(196)) << char(194)
        << string(22, char(196)) << char(194)
        << string(14, char(196)) << char(194)
        << string(12, char(196)) << char(191) << "\n";

    color(C_BORDE); cout << "  " << char(179);
    color(C_WARN);
    cout << left << setw(6) << " ID"
        << char(179)
        << setw(22) << " Producto"
        << char(179)
        << setw(14) << " Stock/Min"
        << char(179)
        << setw(12) << " Precio";
    color(C_BORDE); cout << char(179) << "\n";

    color(C_BORDE);
    cout << "  " << char(195)
        << string(6, char(196)) << char(197)
        << string(22, char(196)) << char(197)
        << string(14, char(196)) << char(197)
        << string(12, char(196)) << char(180) << "\n";

    nodoLista* aux = lista.cabeza;
    while (aux != NULL) {
        bool bajo = (aux->item.cantidad <= aux->item.cantMinima);
        int  cFila = bajo ? C_BAJOSTK : C_VALOR;

        string sId = to_string(aux->item.id);
        string sProd = aux->item.producto.size() > 20 ? aux->item.producto.substr(0, 19) + "." : aux->item.producto;
        string sStk = to_string(aux->item.cantidad) + "/" + to_string(aux->item.cantMinima);
        char buf[16]; snprintf(buf, sizeof(buf), "Q%.2f", aux->item.precio);

        color(C_BORDE); cout << "  " << char(179);
        color(cFila);
        cout << left << setw(6) << (" " + sId)
            << char(179)
            << setw(22) << (" " + sProd)
            << char(179)
            << setw(14) << (" " + sStk)
            << char(179)
            << setw(12) << (" " + string(buf));
        color(C_BORDE); cout << char(179) << "\n";

        if (bajo) {
            color(C_BORDE); cout << "  " << char(179);
            color(C_BAJOSTK); cout << left << setw(54) << "   !! STOCK BAJO - REABASTECER !!";
            color(C_BORDE); cout << char(179) << "\n";
        }

        color(C_BORDE);
        cout << "  " << char(195)
            << string(6, char(196)) << char(197)
            << string(22, char(196)) << char(197)
            << string(14, char(196)) << char(197)
            << string(12, char(196)) << char(180) << "\n";

        aux = aux->siguiente;
    }

    double valorTotal = 0.0; int totalUnids = 0;
    aux = lista.cabeza;
    while (aux != NULL) { valorTotal += aux->item.precio * aux->item.cantidad; totalUnids += aux->item.cantidad; aux = aux->siguiente; }

    char bufT[32]; snprintf(bufT, sizeof(bufT), "Q%.2f", valorTotal);
    color(C_LABEL); cout << "\n  Unidades totales : "; color(C_TITULO); cout << totalUnids;
    color(C_LABEL); cout << "     Valor total inventario : "; color(C_PRECIO); cout << bufT << "\n\n";
    color(C_RESET);
}

void moduloLista(listaDoble& lista) {
    int op;
    do {
        op = menuNavegable(
            "MODULO LISTA DOBLE",
            "CONTROL DE INVENTARIO",
            { "Agregar producto",
              "Eliminar producto",
              "Vaciar inventario",
              "Mostrar inventario",
              "Buscar producto",
              "Modificar producto",
              "Regresar al menu principal" },
            C_TITULO
        );

        cls();
        int idOp;
        char conf;
        switch (op) {
        case 0:
            encabezado("AGREGAR PRODUCTO AL INVENTARIO");
            insertarLista(lista);
            mensajeOK("Producto agregado correctamente");
            mostrarLista(lista);
            break;
        case 1:
            encabezado("ELIMINAR PRODUCTO");
            if (lista.cabeza == NULL) { mensajeADVERTENCIA("El inventario esta vacio"); break; }
            color(C_LABEL); cout << "  ID a eliminar: "; color(C_VALOR); cin >> idOp; cin.ignore();
            eliminarLista(lista, idOp);
            mostrarLista(lista);
            break;
        case 2:
            encabezado("VACIAR INVENTARIO");
            if (lista.cabeza == NULL) { mensajeADVERTENCIA("El inventario ya esta vacio"); break; }
            color(C_WARN); cout << "  Seguro que deseas vaciar el inventario? (Y/N): ";
            color(C_VALOR); cin >> conf; cin.ignore();
            if (conf == 'Y' || conf == 'y') { vaciarLista(lista); mensajeOK("Inventario vaciado"); }
            break;
        case 3:
            encabezado("MOSTRAR INVENTARIO");
            mostrarLista(lista);
            break;
        case 4:
            encabezado("BUSCAR PRODUCTO");
            if (lista.cabeza == NULL) { mensajeADVERTENCIA("El inventario esta vacio"); break; }
            color(C_LABEL); cout << "  ID a buscar: "; color(C_VALOR); cin >> idOp; cin.ignore();
            buscarLista(lista, idOp);
            break;
        case 5:
            encabezado("MODIFICAR PRODUCTO");
            if (lista.cabeza == NULL) { mensajeADVERTENCIA("El inventario esta vacio"); break; }
            color(C_LABEL); cout << "  ID a modificar: "; color(C_VALOR); cin >> idOp; cin.ignore();
            modificarLista(lista, idOp);
            break;
        }
        if (op != 6) { cout << "\n"; pausar(); }
    } while (op != 6);
}


//   MODULO ARBOL ABB

void llenarNiveles(nodoArbol* nodo, int nivel, int pos, int ancho,
    vector<vector<pair<nodoArbol*, int>>>& niveles)
{
    if (nodo == NULL) return;
    if ((int)niveles.size() <= nivel) niveles.push_back({});
    niveles[nivel].push_back({ nodo, pos });
    int mitad = max(ancho / 2, 2);
    llenarNiveles(nodo->izquierda, nivel + 1, pos - mitad / 2, mitad, niveles);
    llenarNiveles(nodo->derecha, nivel + 1, pos + mitad / 2, mitad, niveles);
}

void dibujarArbol(nodoArbol* raiz) {
    if (raiz == NULL) { mensajeADVERTENCIA("El arbol esta vacio"); return; }

    function<int(nodoArbol*)> altura = [&](nodoArbol* n) -> int {
        if (!n) return 0; return 1 + max(altura(n->izquierda), altura(n->derecha)); };
    function<int(nodoArbol*)> contar = [&](nodoArbol* n) -> int {
        if (!n) return 0; return 1 + contar(n->izquierda) + contar(n->derecha); };

    const int ANCHO = 78;
    vector<vector<pair<nodoArbol*, int>>> niveles;
    llenarNiveles(raiz, 0, ANCHO / 2, ANCHO, niveles);

    color(C_TITULO); cout << "\n  --- ARBOL ABB VISUAL (ordenado por cantidad) ---\n\n";

    for (int i = 0; i < (int)niveles.size(); i++) {
        if (i > 0) {
            string lc(ANCHO, ' ');
            for (auto& par : niveles[i]) {
                nodoArbol* nodo = par.first; int col = par.second;
                for (auto& pp : niveles[i - 1]) {
                    nodoArbol* padre = pp.first; int cp = pp.second;
                    bool izq = (padre->izquierda == nodo), der = (padre->derecha == nodo);
                    if (izq || der) {
                        int pasos = abs(cp - col);
                        if (pasos < 1) pasos = 1;
                        char ch = izq ? '/' : '\\';
                        for (int k = 1; k < pasos; k++) {
                            int xk = izq ? (cp - k) : (cp + k);
                            if (xk >= 0 && xk < ANCHO) lc[xk] = ch;
                        }
                        break;
                    }
                }
            }
            color(C_BORDE); cout << lc << "\n";
        }
        string ln(ANCHO, ' ');
        for (auto& par : niveles[i]) {
            nodoArbol* nodo = par.first; int col = par.second;
            ostringstream tmp; tmp << (void*)nodo;
            string d = tmp.str(); if (d.size() > 4) d = d.substr(d.size() - 4);
            string et = "[" + to_string(nodo->pedido.correlativo) + ":" + to_string(nodo->pedido.cantidad) + "@" + d + "]";
            int ini = max(0, col - (int)et.size() / 2);
            for (int k = 0; k < (int)et.size() && ini + k < ANCHO; k++) ln[ini + k] = et[k];
        }
        color(C_OK); cout << ln << "\n";
    }
    color(C_LABEL);
    cout << "\n  Leyenda: [correlativo:cantidad@mem]";
    cout << "   Nodos: "; color(C_TITULO); cout << contar(raiz);
    color(C_LABEL); cout << "   Altura: "; color(C_TITULO); cout << altura(raiz) << "\n";
    color(C_RESET);
}

void insertarArbol(nodoArbol*& arbol) {
    pedidos p;
    color(C_LABEL); cout << "  Correlativo : "; color(C_VALOR); cin >> p.correlativo; cin.ignore();
    color(C_LABEL); cout << "  Producto    : "; color(C_VALOR); getline(cin, p.producto);
    color(C_LABEL); cout << "  Cantidad    : "; color(C_VALOR); cin >> p.cantidad; cin.ignore();
    color(C_LABEL); cout << "  Cliente     : "; color(C_VALOR); getline(cin, p.cliente);
    color(C_LABEL); cout << "  Direccion   : "; color(C_VALOR); getline(cin, p.direccion);
    insertarNodo(arbol, p);
}

void insertarNodo(nodoArbol*& arbol, pedidos p) {
    if (arbol == NULL) {
        nodoArbol* nuevo = new nodoArbol();
        nuevo->pedido = p; nuevo->izquierda = nuevo->derecha = NULL;
        arbol = nuevo; return;
    }
    if (p.cantidad < arbol->pedido.cantidad) insertarNodo(arbol->izquierda, p);
    else insertarNodo(arbol->derecha, p);
}

nodoArbol* encontrarMinimo(nodoArbol* nodo) {
    if (!nodo) return NULL;
    while (nodo->izquierda) nodo = nodo->izquierda;
    return nodo;
}

nodoArbol* eliminarNodo(nodoArbol* arbol, int correlativo) {
    if (!arbol) { mensajeERROR("No se encontro el correlativo " + to_string(correlativo)); return NULL; }
    arbol->izquierda = eliminarNodo(arbol->izquierda, correlativo);
    arbol->derecha = eliminarNodo(arbol->derecha, correlativo);
    if (arbol->pedido.correlativo == correlativo) {
        if (!arbol->izquierda && !arbol->derecha) { delete arbol; return NULL; }
        if (!arbol->izquierda) { nodoArbol* t = arbol->derecha;   delete arbol; return t; }
        if (!arbol->derecha) { nodoArbol* t = arbol->izquierda; delete arbol; return t; }
        nodoArbol* suc = encontrarMinimo(arbol->derecha);
        arbol->pedido = suc->pedido;
        arbol->derecha = eliminarNodo(arbol->derecha, suc->pedido.correlativo);
    }
    return arbol;
}

void vaciarArbol(nodoArbol*& arbol) {
    if (!arbol) return;
    vaciarArbol(arbol->izquierda);
    vaciarArbol(arbol->derecha);
    delete arbol; arbol = NULL;
}

void mostrarArbolOrden(nodoArbol* arbol) {
    if (!arbol) return;
    mostrarArbolOrden(arbol->izquierda);
    tarjetaPedido(arbol->pedido, arbol);
    cout << "\n";
    mostrarArbolOrden(arbol->derecha);
}

void buscarMayor(nodoArbol* arbol) {
    if (!arbol) return;
    buscarMayor(arbol->izquierda);
    if (arbol->pedido.cantidad >= 50) {
        tarjetaPedido(arbol->pedido, arbol);
        cout << "\n";
    }
    buscarMayor(arbol->derecha);
}

void moduloarbol(nodoArbol*& arbol) {
    int op; char conf; int corrElim;
    do {
        op = menuNavegable(
            "MODULO ARBOL ABB",
            "Ordenado por cantidad de pedido",
            { "Insertar pedido",
              "Eliminar pedido",
              "Vaciar arbol",
              "Mostrar arbol visual",
              "Mostrar lista ordenada",
              "Buscar pedidos mayoreo (>=50)",
              "Regresar al menu principal" },
            C_TITULO
        );
        cls();
        switch (op) {
        case 0:
            encabezado("INSERTAR PEDIDO EN ABB");
            insertarArbol(arbol);
            mensajeOK("Pedido insertado correctamente");
            dibujarArbol(arbol);
            break;
        case 1:
            encabezado("ELIMINAR PEDIDO DEL ABB");
            if (!arbol) { mensajeADVERTENCIA("El arbol esta vacio"); break; }
            color(C_LABEL); cout << "  Correlativo a eliminar: "; color(C_VALOR); cin >> corrElim; cin.ignore();
            arbol = eliminarNodo(arbol, corrElim);
            mensajeOK("Operacion completada");
            dibujarArbol(arbol);
            break;
        case 2:
            encabezado("VACIAR ARBOL ABB");
            if (!arbol) { mensajeADVERTENCIA("El arbol ya esta vacio"); break; }
            color(C_WARN); cout << "  Seguro? (Y/N): "; color(C_VALOR); cin >> conf; cin.ignore();
            if (conf == 'Y' || conf == 'y') { vaciarArbol(arbol); mensajeOK("Arbol vaciado"); }
            break;
        case 3:
            encabezado("VISUALIZACION DEL ARBOL ABB");
            dibujarArbol(arbol);
            break;
        case 4:
            encabezado("LISTA ORDENADA ABB (menor a mayor cantidad)");
            if (!arbol) { mensajeADVERTENCIA("El arbol esta vacio"); break; }
            mostrarArbolOrden(arbol);
            break;
        case 5:
            encabezado("PEDIDOS CON DESCUENTO MAYOREO (>= 50 unidades)");
            if (!arbol) { mensajeADVERTENCIA("El arbol esta vacio"); break; }
            buscarMayor(arbol);
            break;
        }
        if (op != 6) { cout << "\n"; pausar(); }
    } while (op != 6);
}


//   MODULO ARBOL AVL


int alturaAVL(nodoAVL* n) { return n ? n->altura : 0; }
int factorEquilibrio(nodoAVL* n) { return n ? alturaAVL(n->izquierda) - alturaAVL(n->derecha) : 0; }
void actualizarAltura(nodoAVL* n) { if (n) n->altura = 1 + max(alturaAVL(n->izquierda), alturaAVL(n->derecha)); }

nodoAVL* rotarDerecha(nodoAVL* y) {
    nodoAVL* x = y->izquierda, * T2 = x->derecha;
    x->derecha = y; y->izquierda = T2;
    actualizarAltura(y); actualizarAltura(x);
    return x;
}
nodoAVL* rotarIzquierda(nodoAVL* x) {
    nodoAVL* y = x->derecha, * T2 = y->izquierda;
    y->izquierda = x; x->derecha = T2;
    actualizarAltura(x); actualizarAltura(y);
    return y;
}
nodoAVL* balancear(nodoAVL* n) {
    if (!n) return NULL;
    actualizarAltura(n);
    int fe = factorEquilibrio(n);
    if (fe > 1 && factorEquilibrio(n->izquierda) >= 0) return rotarDerecha(n);
    if (fe > 1 && factorEquilibrio(n->izquierda) < 0) { n->izquierda = rotarIzquierda(n->izquierda); return rotarDerecha(n); }
    if (fe < -1 && factorEquilibrio(n->derecha) <= 0) return rotarIzquierda(n);
    if (fe < -1 && factorEquilibrio(n->derecha)    > 0) { n->derecha = rotarDerecha(n->derecha); return rotarIzquierda(n); }
    return n;
}
nodoAVL* minimoAVL(nodoAVL* n) { while (n && n->izquierda) n = n->izquierda; return n; }

nodoAVL* insertarNodoAVL(nodoAVL* raiz, pedidos p, bool& insertado) {
    if (!raiz) {
        nodoAVL* nuevo = new nodoAVL();
        nuevo->pedido = p; nuevo->izquierda = nuevo->derecha = NULL; nuevo->altura = 1;
        insertado = true; return nuevo;
    }
    if (p.cantidad < raiz->pedido.cantidad) raiz->izquierda = insertarNodoAVL(raiz->izquierda, p, insertado);
    else                                    raiz->derecha = insertarNodoAVL(raiz->derecha, p, insertado);
    return balancear(raiz);
}

void insertarAVL(nodoAVL*& avl) {
    pedidos p;
    color(C_LABEL); cout << "  Correlativo : "; color(C_VALOR); cin >> p.correlativo; cin.ignore();
    color(C_LABEL); cout << "  Producto    : "; color(C_VALOR); getline(cin, p.producto);
    color(C_LABEL); cout << "  Cantidad    : "; color(C_VALOR); cin >> p.cantidad; cin.ignore();
    color(C_LABEL); cout << "  Cliente     : "; color(C_VALOR); getline(cin, p.cliente);
    color(C_LABEL); cout << "  Direccion   : "; color(C_VALOR); getline(cin, p.direccion);
    bool insertado = false;
    avl = insertarNodoAVL(avl, p, insertado);
}

nodoAVL* eliminarNodoAVL(nodoAVL* raiz, int correlativo, bool& eliminado) {
    if (!raiz) return NULL;
    raiz->izquierda = eliminarNodoAVL(raiz->izquierda, correlativo, eliminado);
    raiz->derecha = eliminarNodoAVL(raiz->derecha, correlativo, eliminado);
    if (raiz->pedido.correlativo == correlativo) {
        eliminado = true;
        if (!raiz->izquierda && !raiz->derecha) { delete raiz; return NULL; }
        if (!raiz->izquierda) { nodoAVL* t = raiz->derecha;   delete raiz; return balancear(t); }
        if (!raiz->derecha) { nodoAVL* t = raiz->izquierda; delete raiz; return balancear(t); }
        nodoAVL* suc = minimoAVL(raiz->derecha);
        raiz->pedido = suc->pedido;
        bool dummy = false;
        raiz->derecha = eliminarNodoAVL(raiz->derecha, suc->pedido.correlativo, dummy);
    }
    return balancear(raiz);
}

nodoAVL* vaciarAVL_aux(nodoAVL* raiz) {
    if (!raiz) return NULL;
    vaciarAVL_aux(raiz->izquierda);
    vaciarAVL_aux(raiz->derecha);
    delete raiz; return NULL;
}
void vaciarAVL(nodoAVL*& avl) { avl = vaciarAVL_aux(avl); }

void mostrarAVLOrden(nodoAVL* raiz) {
    if (!raiz) return;
    mostrarAVLOrden(raiz->izquierda);

    tarjetaPedido(raiz->pedido, raiz);
    int fe = factorEquilibrio(raiz);
    string feStr = (fe >= 0 ? "+" : "") + to_string(fe);
    int cFE = (fe == 0) ? C_ARBOL_OK : (abs(fe) == 1 ? C_ARBOL_L : C_ARBOL_CR);
    color(C_LABEL); cout << "     Altura: "; color(C_INFO); cout << raiz->altura;
    color(C_LABEL); cout << "   Factor Equilibrio: "; color(cFE); cout << feStr << "\n\n";
    color(C_RESET);
    mostrarAVLOrden(raiz->derecha);
}

void buscarMayorAVL(nodoAVL* raiz) {
    if (!raiz) return;
    buscarMayorAVL(raiz->izquierda);
    if (raiz->pedido.cantidad >= 50) {
        tarjetaPedido(raiz->pedido, raiz);
        cout << "\n";
    }
    buscarMayorAVL(raiz->derecha);
}

void llenarNivelesAVL(nodoAVL* nodo, int nivel, int pos, int ancho,
    vector<vector<pair<nodoAVL*, int>>>& niveles)
{
    if (!nodo) return;
    if ((int)niveles.size() <= nivel) niveles.push_back({});
    niveles[nivel].push_back({ nodo, pos });
    int mitad = max(ancho / 2, 2);
    llenarNivelesAVL(nodo->izquierda, nivel + 1, pos - mitad / 2, mitad, niveles);
    llenarNivelesAVL(nodo->derecha, nivel + 1, pos + mitad / 2, mitad, niveles);
}

void dibujarAVL(nodoAVL* raiz) {
    if (!raiz) { mensajeADVERTENCIA("El arbol AVL esta vacio"); return; }

    function<int(nodoAVL*)> calcH = [&](nodoAVL* n) -> int {
        if (!n) return 0; return 1 + max(calcH(n->izquierda), calcH(n->derecha)); };
    function<int(nodoAVL*)> contar = [&](nodoAVL* n) -> int {
        if (!n) return 0; return 1 + contar(n->izquierda) + contar(n->derecha); };

    const int ANCHO = 78;
    vector<vector<pair<nodoAVL*, int>>> niveles;
    llenarNivelesAVL(raiz, 0, ANCHO / 2, ANCHO, niveles);

    color(C_TITULO); cout << "\n  --- ARBOL AVL VISUAL (auto-balanceado) ---\n";
    color(C_LABEL);  cout << "  Colores: ";
    color(C_ARBOL_OK); cout << "verde=balanceado  ";
    color(C_ARBOL_L);  cout << "amarillo=leve  ";
    color(C_ARBOL_CR); cout << "rojo=critico\n\n";

    for (int i = 0; i < (int)niveles.size(); i++) {
        if (i > 0) {
            string lc(ANCHO, ' ');
            for (auto& par : niveles[i]) {
                nodoAVL* nodo = par.first; int col = par.second;
                for (auto& pp : niveles[i - 1]) {
                    nodoAVL* padre = pp.first; int cp = pp.second;
                    bool izq = (padre->izquierda == nodo), der = (padre->derecha == nodo);
                    if (izq || der) {
                        int pasos = abs(cp - col); if (pasos < 1) pasos = 1;
                        char ch = izq ? '/' : '\\';
                        for (int k = 1; k < pasos; k++) {
                            int xk = izq ? (cp - k) : (cp + k);
                            if (xk >= 0 && xk < ANCHO) lc[xk] = ch;
                        }
                        break;
                    }
                }
            }
            color(C_BORDE); cout << lc << "\n";
        }

        struct Info { int ini; string et; int c; };
        vector<Info> infos;
        for (auto& par : niveles[i]) {
            nodoAVL* nodo = par.first; int col = par.second;
            int fe = factorEquilibrio(nodo);
            string feStr = (fe >= 0 ? "+" : "") + to_string(fe);
            ostringstream tmp; tmp << (void*)nodo;
            string d = tmp.str(); if (d.size() > 4) d = d.substr(d.size() - 4);
            string et = "[" + to_string(nodo->pedido.correlativo) + ":" + to_string(nodo->pedido.cantidad)
                + "|" + feStr + "@" + d + "]";
            int ini = max(0, col - (int)et.size() / 2);
            int cN = (fe == 0) ? C_ARBOL_OK : (abs(fe) == 1 ? C_ARBOL_L : C_ARBOL_CR);
            infos.push_back({ ini, et, cN });
        }
        int cur = 0;
        for (auto& info : infos) {
            if (info.ini > cur) { color(C_RESET); cout << string(info.ini - cur, ' '); cur = info.ini; }
            color(info.c); cout << info.et; cur += (int)info.et.size();
        }
        cout << "\n";
    }

    color(C_LABEL);
    cout << "\n  Leyenda: [corr:cant|FE@mem]";
    cout << "   Nodos: "; color(C_TITULO); cout << contar(raiz);
    color(C_LABEL); cout << "   Altura: "; color(C_TITULO); cout << calcH(raiz);
    color(C_LABEL); cout << "   Raiz cantidad: "; color(C_TITULO); cout << raiz->pedido.cantidad;
    int feR = factorEquilibrio(raiz);
    color(C_LABEL); cout << "   FE raiz: ";
    color(feR == 0 ? C_ARBOL_OK : (abs(feR) == 1 ? C_ARBOL_L : C_ARBOL_CR));
    cout << (feR >= 0 ? "+" : "") << feR << "\n";
    color(C_RESET);
}

void moduloAVL(nodoAVL*& avl) {
    int op; char conf; int corrElim;
    do {
        op = menuNavegable(
            "MODULO ARBOL AVL",
            "Auto-balanceado por cantidad de pedido",
            { "Insertar pedido",
              "Eliminar pedido",
              "Vaciar arbol",
              "Mostrar arbol visual",
              "Mostrar lista ordenada",
              "Buscar pedidos mayoreo (>=50)",
              "Regresar al menu principal" },
            C_TITULO
        );
        cls();
        switch (op) {
        case 0: {
            encabezado("INSERTAR PEDIDO EN AVL");
            int ha = alturaAVL(avl);
            insertarAVL(avl);
            int hd = alturaAVL(avl);
            mensajeOK("Pedido insertado y arbol rebalanceado");
            if (ha != hd) mensajeINFO("Altura cambio de " + to_string(ha) + " a " + to_string(hd));
            dibujarAVL(avl);
            break;
        }
        case 1:
            encabezado("ELIMINAR PEDIDO DEL AVL");
            if (!avl) { mensajeADVERTENCIA("El arbol esta vacio"); break; }
            color(C_LABEL); cout << "  Correlativo a eliminar: "; color(C_VALOR); cin >> corrElim; cin.ignore();
            {
                bool elim = false; int ha = alturaAVL(avl);
                avl = eliminarNodoAVL(avl, corrElim, elim);
                if (elim) {
                    int hd = alturaAVL(avl);
                    mensajeOK("Nodo eliminado y arbol rebalanceado");
                    if (ha != hd) mensajeINFO("Altura cambio de " + to_string(ha) + " a " + to_string(hd));
                    dibujarAVL(avl);
                }
                else {
                    mensajeERROR("No se encontro el correlativo " + to_string(corrElim));
                }
            }
            break;
        case 2:
            encabezado("VACIAR ARBOL AVL");
            if (!avl) { mensajeADVERTENCIA("El arbol ya esta vacio"); break; }
            color(C_WARN); cout << "  Seguro? (Y/N): "; color(C_VALOR); cin >> conf; cin.ignore();
            if (conf == 'Y' || conf == 'y') { vaciarAVL(avl); mensajeOK("Arbol AVL vaciado"); }
            break;
        case 3:
            encabezado("VISUALIZACION DEL ARBOL AVL");
            dibujarAVL(avl);
            break;
        case 4:
            encabezado("LISTA ORDENADA AVL (menor a mayor cantidad)");
            if (!avl) { mensajeADVERTENCIA("El arbol esta vacio"); break; }
            mostrarAVLOrden(avl);
            break;
        case 5:
            encabezado("PEDIDOS CON DESCUENTO MAYOREO (>= 50 unidades)");
            if (!avl) { mensajeADVERTENCIA("El arbol esta vacio"); break; }
            buscarMayorAVL(avl);
            break;
        }
        if (op != 6) { cout << "\n"; pausar(); }
    } while (op != 6);
}


//   ESTETICA - PORTADA, DIBUJO, CARGA, LOGIN


void portada() {
    cls();
    const int W = 62;
    color(C_BORDE);
    cout << char(201); for (int i = 0;i < W;i++) cout << char(205); cout << char(187) << "\n";

    auto lc = [&](const string& txt, int c, bool doble = false) {
        int pad = (W - (int)txt.size()) / 2;
        color(C_BORDE); cout << char(doble ? 186 : 186);
        color(c);
        for (int i = 0;i < pad;i++) cout << " "; cout << txt;
        for (int i = 0;i < W - pad - (int)txt.size();i++) cout << " ";
        color(C_BORDE); cout << char(186) << "\n";
        };

    lc("SISTEMA DE CONTROL DE INVENTARIO", C_TITULO);
    lc("KANGAROO BOXING", C_OK);

    color(C_BORDE);
    cout << char(204); for (int i = 0;i < W;i++) cout << char(205); cout << char(185) << "\n";
    lc("INFORMACION DEL PROYECTO", C_WARN);
    color(C_BORDE);
    cout << char(204); for (int i = 0;i < W;i++) cout << char(196); cout << char(185) << "\n";

    lc("Curso    :  Programacion III", C_VALOR);
    lc("Lenguaje :  C++ (Estructurado)", C_VALOR);
    lc("Entrega  :  Junio 2026", C_VALOR);

    color(C_BORDE);
    cout << char(204); for (int i = 0;i < W;i++) cout << char(196); cout << char(185) << "\n";
    lc("INTEGRANTES DEL GRUPO", C_WARN);
    color(C_BORDE);
    cout << char(204); for (int i = 0;i < W;i++) cout << char(196); cout << char(185) << "\n";

    lc("Marnaby Gilbertson Cux Mazat  2290-23-3596", C_VALOR);
    lc("Jose Andres Santizo Procopio  2290-24-12667", C_VALOR);
    lc("Miguel Angel Santos Garcia    2290-24-8950", C_VALOR);

    color(C_BORDE);
    cout << char(204); for (int i = 0;i < W;i++) cout << char(205); cout << char(185) << "\n";
    lc("Presione cualquier tecla para continuar...", C_INFO);
    color(C_BORDE);
    cout << char(200); for (int i = 0;i < W;i++) cout << char(205); cout << char(188) << "\n";
    color(C_RESET);

    system("pause");
}

void cargando() {
    cls();
    encabezado("INICIANDO SISTEMA", "Por favor espere...");

    color(C_LABEL); cout << "  [";
    color(C_OK);
    for (int i = 0; i < 20; i++) { cout << char(219); Sleep(80); }
    color(C_RESET); cout << "] ";
    color(C_OK); cout << "100%\n\n";

    struct { const char* msg; int c; } pasos[] = {
        { "Inicializando modulo PILA...",     C_INFO  },
        { "Inicializando modulo COLA...",     C_INFO  },
        { "Cargando base de datos...",        C_INFO  },
        { "2 + 2 = 6...",                     C_INFO  },
        { "Configurando entorno...",          C_INFO  },
        { "Sistema listo!",                   C_OK    },
    };
    for (auto& p : pasos) {
        color(C_LABEL); cout << "  > "; color(p.c); cout << p.msg << "\n"; Sleep(450);
    }

    cout << "\n";
    mensajeOK("Bienvenido al sistema");
    Sleep(500);
    color(C_LABEL); cout << "  Presione una tecla para continuar...";
    (void)_getch();
    color(C_RESET);
}

void dibujo() {
    cls();
    color(C_WARN);
    cout << "\n";
    cout << "                                                  _  _\n";
    cout << "                                                 (\\\\( \\.\n";
    cout << "                                                  `.-.\n";
    cout << "                              _...._            _,-'   `-.\n";
    cout << "\\                          ,'      `-._.---.,-'       .   \\.\n";
    cout << " \\`.                      ,'                               `.\n";
    cout << "  \\ `-...__              /                           .   .:  y\n";
    cout << "   `._     ``--..__     /                           ,'`---._/\n";
    cout << "      `-._         ``--'                      |    /_\n";
    cout << "          `.._                   _            ;   <_ \\\n";
    cout << "              `--.___             `.           `-._ \\ \\\n";
    cout << "                     `--<           `.     (\\ _/)/ `.\\/`\n";
    cout << "                         \\            \\     `<a \\  /_/\n";
    cout << "                          `.           ;      `._y\n";
    cout << "                            `--.      /    _.../\n";
    cout << "                                \\    /__..'\n";
    cout << "                                 ;  //\n";
    cout << "                                <   \\\\\n";
    cout << "                                 `.  \\\\\n";
    cout << "                                   `. \\\\_ __\n";
    cout << "                                     `.'  \\\\\n";
    cout << "                                       `----''\n\n";
    color(C_TITULO);
    cout << "              ARTICULOS DEPORTIVOS PARA CANGUROS - KANGAROO BOXING\n\n";
    color(C_RESET);
    system("pause");
}

bool iniciarSesion() {
    const string USUARIO = "admin";
    const string CONTRASENA = "admin";
    string usuario, contrasena;
    int intentos = 3;

    while (intentos > 0) {
        cls();
        encabezado("INICIO DE SESION", "ARTICULOS DEPORTIVOS PARA CANGUROS - KANGAROO BOXING");

        color(C_LABEL); cout << "  Usuario    : "; color(C_VALOR); getline(cin, usuario);
        color(C_LABEL); cout << "  Contrasena : "; color(C_VALOR); getline(cin, contrasena);

        if (usuario == USUARIO && contrasena == CONTRASENA) {
            mensajeOK("Acceso concedido  -  Bienvenido!");
            Sleep(900);
            return true;
        }
        else {
            intentos--;
            mensajeERROR("Usuario o contrasena incorrectos");
            if (intentos > 0) {
                color(C_WARN);
                cout << "  Intentos restantes: " << intentos << "\n";
            }
            Sleep(900);
        }
    }

    mensajeERROR("Demasiados intentos fallidos - Cerrando sistema");
    Sleep(1500);
    return false;
}
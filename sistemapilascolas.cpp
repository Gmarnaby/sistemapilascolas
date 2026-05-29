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

// Estetica
int  menuprincipal();
int  submenu(string titulo);
void dibujo();
void portada();
void color(int c);
void cargando();

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

// Lista Doble (Inventario)
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

//   MAIN

int main()
{
    cola q;
    q.primero = NULL;
    q.ultimo = NULL;

    nodoPila* p = NULL;
    listaDoble lista = { NULL, NULL, 0 };
    nodoArbol* arbol = NULL;
    nodoAVL* avl = NULL;

    int op;
    dibujo();
    portada();
    cargando();

    do {
        op = menuprincipal();
        switch (op) {
        case 0:
            pantallacargaIngresos(p);
            modulopila(p);
            break;
        case 1:
            pantallacargaPedidos(q);
            modulocola(q);
            break;
        case 2:
            moduloLista(lista);
            break;
        case 3:
            moduloarbol(arbol);
            break;
        case 4:
            moduloAVL(avl);
            break;
        case 5:
            system("cls");
            color(12);
            cout << "========================================\n";
            cout << "         SALIENDO DEL SISTEMA\n";
            cout << "========================================\n\n";
            color(11);
            cout << "Guardando datos";
            for (int i = 0; i < 3; i++) { cout << "."; Sleep(300); }
            cout << "\n\n";
            color(10);
            cout << "Cerrando aplicacion";
            Sleep(600);
            color(7);
            break;
        }
    } while (op != 5);

    return 0;
}

//   MENU PRINCIPAL

int menuprincipal() {
    int opcion = 0;
    int tecla;

    do {
        system("cls");
        color(11);
        cout << "==================================================\n";
        cout << "          SISTEMA DE CONTROL DE INVENTARIO\n";
        cout << "         ARTICULOS DEPORTIVOS PARA CANGUROS \n";
        cout << "==================================================\n\n";
        color(7);
        cout << "Seleccione una opcion:\n\n";

        if (opcion == 0) { color(10); cout << "   >> [ MODULO PILA ]\n"; }
        else { color(7);  cout << "      Modulo PILA\n"; }
        if (opcion == 1) { color(10); cout << "   >> [ MODULO COLA ]\n"; }
        else { color(7);  cout << "      Modulo COLA\n"; }
        if (opcion == 2) { color(10); cout << "   >> [ MODULO LISTA DOBLE ]\n"; }
        else { color(7);  cout << "      Modulo LISTA DOBLE\n"; }
        if (opcion == 3) { color(10); cout << "   >> [ MODULO ARBOL ABB ]\n"; }
        else { color(7);  cout << "      Modulo ARBOL ABB\n"; }
        if (opcion == 4) { color(10); cout << "   >> [ MODULO ARBOL AVL ]\n"; }
        else { color(7);  cout << "      Modulo ARBOL AVL\n"; }
        if (opcion == 5) { color(12); cout << "   >> [ SALIR ]\n"; }
        else { color(7);  cout << "      Salir\n"; }

        color(8);
        cout << "\nUse las flechas y ENTER para seleccionar";
        tecla = _getch();

        if (tecla == 72) opcion--;
        if (tecla == 80) opcion++;
        if (opcion < 0) opcion = 5;
        if (opcion > 5) opcion = 0;

    } while (tecla != 13);

    return opcion;
}

//   SUB MENU

int submenu(string titulo) {
    int opcion = 0;
    int tecla;

    do {
        system("cls");
        color(11);
        cout << "========================================\n";
        cout << "        " << titulo << "\n";
        cout << "========================================\n\n";

        if (opcion == 0) { color(10); cout << "   >>   [ INGRESAR DATOS ]\n"; }
        else { color(8);  cout << "        Ingresar datos\n"; }
        if (opcion == 1) { color(10); cout << "   >>   [ ELIMINAR ]\n"; }
        else { color(8);  cout << "        Eliminar\n"; }
        if (opcion == 2) { color(10); cout << "   >>   [ MOSTRAR DATOS ]\n"; }
        else { color(8);  cout << "        Mostrar datos\n"; }
        if (opcion == 3) { color(10); cout << "   >>   [ BUSCAR ]\n"; }
        else { color(8);  cout << "        Buscar\n"; }
        if (opcion == 4) { color(10); cout << "   >>   [ MODIFICAR ]\n"; }
        else { color(8);  cout << "        Modificar\n"; }
        if (opcion == 5) { color(12); cout << "   >>   [ REGRESAR ]\n"; }
        else { color(8);  cout << "        Regresar\n"; }

        tecla = _getch();
        if (tecla == 72) opcion--;
        if (tecla == 80) opcion++;
        if (opcion < 0) opcion = 5;
        if (opcion > 5) opcion = 0;

    } while (tecla != 13);

    color(7);
    return opcion;
}

//   MODULO PILA

void modulopila(nodoPila*& p) {
    int op;
    int correPush, busqueda, modificacion;
    int x;
    char res;

    do {
        op = submenu("INGRESOS PENDIENTES DE VALIDACION");

        switch (op) {
        case 0:
            cout << "\n\n~] REGISTRAR INGRESO DE PRODUCTO [~" << endl;
            correPush = push(p);
            cout << "\n\nEL INGRESO NO. " << correPush << " FUE REGISTRADO CON EXITO :D";
            break;
        case 1:
            if (p != NULL) {
                do {
                    cout << "\n\nVALIDARAS EL INGRESO " << p->ingreso.correlativoIng
                        << "\nQUIERES CONTINUAR?  (Y/N) "; cin >> res; cin.ignore();
                    if (res == 'Y' || res == 'y') {
                        x = pop(p);
                        cout << "\n\nEL REGISTRO NO. " << x << " FUE VALIDADO";
                        break;
                    }
                    else if (res == 'N' || res == 'n') break;
                } while (res != 'y' && res != 'Y' && res != 'n' && res != 'N');
            }
            else cout << "\n\nNO EXISTEN INGRESOS A VALIDAR VUELVE MAS TARDE :D";
            break;
        case 2:
            if (p != NULL) mostrarpila(p);
            else cout << "NO EXISTEN INGRESOS PARA MOSTRAR REGRESA MAS TARDE :(" << endl;
            break;
        case 3:
            cout << "\n\nINGRESE EL NO. DE INGRESO PARA BUSCAR: "; cin >> busqueda; cin.ignore();
            buscarpila(p, busqueda);
            break;
        case 4:
            cout << "\n\nINGRESE EL NO. DE INGRESO PARA MODIFICAR: "; cin >> modificacion; cin.ignore();
            modificarpila(p, modificacion);
            break;
        }
        cout << endl;
        system("pause");
        system("cls");
    } while (op != 5);
}

int push(nodoPila*& p) {
    nodoPila* aux = new nodoPila();
    aux->ingreso.correlativoIng = correlativoIngGlobal++;
    cout << "Ingrese el proveedor del producto: "; getline(cin, aux->ingreso.proveedorIng);
    cout << "Ingrese la fecha de ingreso (dd/mm/yy): "; getline(cin, aux->ingreso.fechaIng);
    cout << "Ingrese el nombre del producto: "; getline(cin, aux->ingreso.productoIng);
    cout << "Ingrese la cantidad de producto: "; cin >> aux->ingreso.cantidadIng; cin.ignore();
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
    while (aux != NULL) {
        cout << "\n\n+--------------------------------+" << endl;
        cout << "  Ingreso no: " << aux->ingreso.correlativoIng << endl;
        cout << "  Proveedor del producto: " << aux->ingreso.proveedorIng << endl;
        cout << "  Nombre del producto: " << aux->ingreso.productoIng << endl;
        cout << "+--------------------------------+" << endl;
        aux = aux->siguientePila;
    }
}

void modificarpila(nodoPila*& p, int correModificarIng) {
    nodoPila* aux = p;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->ingreso.correlativoIng == correModificarIng) {
            cout << "\nIngreso No. [" << aux->ingreso.correlativoIng << "]" << endl;
            cout << "\nIngrese el Proveedor: "; getline(cin, aux->ingreso.proveedorIng);
            cout << "Ingrese la fecha (dd/mm/yy): "; getline(cin, aux->ingreso.fechaIng);
            cout << "Ingrese el nombre del producto: "; getline(cin, aux->ingreso.productoIng);
            cout << "Ingrese la cantidad de producto: "; cin >> aux->ingreso.cantidadIng; cin.ignore();
            encontrado = true;
        }
        aux = aux->siguientePila;
    }
    if (!encontrado) cout << "\nNO SE ENCONTRO EL INGRESO >:C" << endl;
}

void buscarpila(nodoPila*& p, int correBuscarIng) {
    nodoPila* aux = p;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->ingreso.correlativoIng == correBuscarIng) {
            cout << "\n\nIngreso No. [" << aux->ingreso.correlativoIng << "]" << endl;
            cout << "\nProveedor: " << aux->ingreso.proveedorIng << endl;
            cout << "Fecha: " << aux->ingreso.fechaIng << endl;
            cout << "Nombre del Producto: " << aux->ingreso.productoIng << endl;
            cout << "Cantidad de Producto: " << aux->ingreso.cantidadIng << endl;
            encontrado = true;
        }
        aux = aux->siguientePila;
    }
    if (!encontrado) cout << "\nNO SE ENCONTRO EL REGISTRO INTENTE MAS TARDE >:C" << endl;
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
        cout << "Fallo al cargar los ingresos contacte con servicio tecnico" << endl;
        exit(1);
    }
    int maxCorrelativoIng = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        nodoPila* nuevo = new nodoPila;
        getline(ss, dato, '|');
        nuevo->ingreso.correlativoIng = stoi(dato);
        if (nuevo->ingreso.correlativoIng > maxCorrelativoIng)
            maxCorrelativoIng = nuevo->ingreso.correlativoIng;
        getline(ss, nuevo->ingreso.proveedorIng, '|');
        getline(ss, nuevo->ingreso.fechaIng, '|');
        getline(ss, nuevo->ingreso.productoIng, '|');
        getline(ss, dato, '|');
        nuevo->ingreso.cantidadIng = stoi(dato);
        nuevo->siguientePila = p;
        p = nuevo;
    }
    archivo.close();
    correlativoIngGlobal = maxCorrelativoIng + 1;
}

void pantallacargaIngresos(nodoPila*& p) {
    system("cls");
    color(14);
    cout << "========================================\n";
    cout << "   ACCEDIENDO A INGRESOS DE PRODUCTOS \n";
    cout << "========================================\n\n";
    color(11);
    cout << "Cargando";
    for (int i = 0; i < 3; i++) { cout << "."; Sleep(300); }
    cout << "\n\n";
    color(10);
    cout << "[";
    for (int i = 0; i < 20; i++) {
        if (i == 5) cargarIngreso(p);
        cout << char(219);
        Sleep(70);
    }
    cout << "]";
    Sleep(400);
    color(7);
}

//   MODULO COLA

void modulocola(cola& q) {
    int op;
    char res;
    int correEncolar, correBuscar, correModificar;
    int x;

    do {
        op = submenu("PEDIDOS DE CLIENTES");
        switch (op) {
        case 0:
            cout << "\n\n~] INGRESAR UN PEDIDO DE PRODUCTOS [~" << endl;
            correEncolar = encolar(q);
            cout << "\n\n EL PEDIDO " << correEncolar << " FUE INGRESADO CORRECTAMENTE";
            break;
        case 1:
            if (q.primero != NULL) {
                do {
                    cout << "\n\nDESPACHARAS EL PEDIDO " << q.primero->pedido.correlativo
                        << "\nQUIERES CONTINUAR?  (Y/N) "; cin >> res; cin.ignore();
                    if (res == 'Y' || res == 'y') {
                        x = desencolar(q);
                        cout << "\n\nEL PEDIDO " << x << " FUE DESPACHADO";
                        break;
                    }
                    else if (res == 'N' || res == 'n') break;
                } while (res != 'y' && res != 'Y' && res != 'n' && res != 'N');
            }
            else cout << "\n\nNO EXISTEN PEDIDOS A DESPACHAR VUELVE MAS TARDE :D";
            break;
        case 2:
            if (q.primero != NULL) mostrarcola(q);
            else cout << "\n\nNO EXISTEN PEDIDOS PARA MOSTRAR VUELVE MAS TARDE :D";
            break;
        case 3:
            if (q.primero != NULL) {
                cout << "\n\nINGRESE EL NUMERO DE PEDIDO QUE QUIERA BUSCAR: "; cin >> correBuscar; cin.ignore();
                buscarcola(q, correBuscar);
            }
            else cout << "\n\nNO EXISTEN PEDIDOS A BUSCAR VUELVE MAS TARDE :D";
            break;
        case 4:
            if (q.primero != NULL) {
                cout << "\n\nINGRESE EL NUMERO DE PEDIDO QUE QUIERA MODIFICAR: "; cin >> correModificar; cin.ignore();
                modificarcola(q, correModificar);
            }
            else cout << "\n\nNO EXISTEN PEDIDOS PARA MODIFICAR REALIZA TU CHAMBA PORFA";
            break;
        }
        cout << endl;
        system("pause");
        system("cls");
    } while (op != 5);
}

int encolar(cola& q) {
    nodoCola* aux = new nodoCola;
    aux->pedido.correlativo = correlativoPedidos++;
    cout << "Ingrese el producto del cliente: ";  getline(cin, aux->pedido.producto);
    cout << "Ingrese la cantidad de productos: "; cin >> aux->pedido.cantidad; cin.ignore();
    cout << "Ingrese el nombre del cliente: ";    getline(cin, aux->pedido.cliente);
    cout << "Ingrese la direccion del cliente: "; getline(cin, aux->pedido.direccion);
    aux->siguienteCola = NULL;
    if (q.primero == NULL) q.primero = aux;
    else q.ultimo->siguienteCola = aux;
    q.ultimo = aux;
    guardarPedidos(aux->pedido);
    return aux->pedido.correlativo;
}

int desencolar(cola& q) {
    int corre;
    nodoCola* aux = q.primero;
    corre = aux->pedido.correlativo;
    q.primero = q.primero->siguienteCola;
    delete aux;
    actualizarPedidos(q);
    return corre;
}

void mostrarcola(cola q) {
    nodoCola* aux = q.primero;
    while (aux != NULL) {
        cout << "   [" << aux->pedido.correlativo << " - " << aux->pedido.cliente << "]";
        aux = aux->siguienteCola;
    }
}

void buscarcola(cola q, int corre) {
    nodoCola* aux = q.primero;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->pedido.correlativo == corre) {
            cout << "PEDIDO NO. [" << aux->pedido.correlativo << "]" << endl;
            cout << "\nProducto: " << aux->pedido.producto << endl;
            cout << "Cantidad: " << aux->pedido.cantidad << endl;
            cout << "Cliente: " << aux->pedido.cliente << endl;
            cout << "Direccion: " << aux->pedido.direccion << endl;
            encontrado = true;
        }
        aux = aux->siguienteCola;
    }
    if (!encontrado) cout << "\nNo se encontro el pedido :(";
}

void modificarcola(cola q, int corre) {
    nodoCola* aux = q.primero;
    bool encontrado = false;
    while (aux != NULL) {
        if (aux->pedido.correlativo == corre) {
            cout << "\nPEDIDO NO. [" << aux->pedido.correlativo << "]" << endl;
            cout << "\nIngrese el nuevo producto: "; getline(cin, aux->pedido.producto);
            cout << "Ingrese la nueva cantidad de producto: "; cin >> aux->pedido.cantidad; cin.ignore();
            cout << "Ingrese el nuevo del cliente: "; getline(cin, aux->pedido.cliente);
            cout << "Ingrese la nueva direccion: "; getline(cin, aux->pedido.direccion);
            encontrado = true;
        }
        aux = aux->siguienteCola;
    }
    if (!encontrado) cout << "No se encontro el pedido :(";
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
        cout << "Fallo al cargar los pedidos contacte con servicio tecnico" << endl;
        exit(1);
    }
    int maxCorrelativo = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        nodoCola* nuevo = new nodoCola;
        getline(ss, dato, '|');
        nuevo->pedido.correlativo = stoi(dato);
        if (nuevo->pedido.correlativo > maxCorrelativo)
            maxCorrelativo = nuevo->pedido.correlativo;
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
    correlativoPedidos = maxCorrelativo + 1;
}

void pantallacargaPedidos(cola& q) {
    system("cls");
    color(14);
    cout << "========================================\n";
    cout << "      ACCEDIENDO A LOS PEDIDOS\n";
    cout << "========================================\n\n";
    color(11);
    cout << "Cargando";
    for (int i = 0; i < 3; i++) { cout << "."; Sleep(300); }
    cout << "\n\n";
    color(10);
    cout << "[";
    for (int i = 0; i < 20; i++) {
        if (i == 5) cargarPedidos(q);
        cout << char(219);
        Sleep(70);
    }
    cout << "]";
    Sleep(400);
    color(7);
}

//   MODULO LISTA DOBLEMENTE ENLAZADA - INVENTARIO

void insertarLista(listaDoble& lista) {
    nodoLista* nuevo = new nodoLista();

    nuevo->item.id = correlativoInventario++;
    cout << "  Nombre producto  : "; getline(cin, nuevo->item.producto);
    cout << "  Cantidad en bodega: "; cin >> nuevo->item.cantidad; cin.ignore();
    cout << "  Cantidad minima  : "; cin >> nuevo->item.cantMinima; cin.ignore();
    cout << "  Precio unitario  : Q"; cin >> nuevo->item.precio; cin.ignore();

    nuevo->siguiente = NULL;
    nuevo->anterior = lista.cola;

    if (lista.cabeza == NULL) {
        lista.cabeza = nuevo;
    }
    else {
        lista.cola->siguiente = nuevo;
    }
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
            bool bajoStock = (aux->item.cantidad <= aux->item.cantMinima);

            color(11);
            cout << "\n  +------------------------------------+";
            color(7);
            cout << "\n  ID          : "; color(10); cout << aux->item.id; color(7);
            cout << "\n  Producto    : " << aux->item.producto;
            cout << "\n  Cantidad    : ";
            if (bajoStock) { color(12); }
            else { color(10); }
            cout << aux->item.cantidad; color(7);
            cout << "\n  Cant. minima: " << aux->item.cantMinima;
            if (bajoStock) { color(12); cout << "  << STOCK BAJO"; color(7); }
            cout << "\n  Precio      : Q" << fixed << aux->item.precio;
            cout << "\n  Valor total : Q" << fixed << (aux->item.precio * aux->item.cantidad);
            color(11);
            cout << "\n  +------------------------------------+\n";
            color(7);
            encontrado = true;
        }
        aux = aux->siguiente;
    }
    if (!encontrado) {
        color(12);
        cout << "\n  No se encontro el producto con ID " << id << "\n";
        color(7);
    }
}

void eliminarLista(listaDoble& lista, int id) {
    nodoLista* aux = buscarNodoLista(lista, id);

    if (aux == NULL) {
        color(12);
        cout << "\n  No se encontro el ID " << id << "\n";
        color(7);
        return;
    }

    if (aux->anterior != NULL)
        aux->anterior->siguiente = aux->siguiente;
    else
        lista.cabeza = aux->siguiente;

    if (aux->siguiente != NULL)
        aux->siguiente->anterior = aux->anterior;
    else
        lista.cola = aux->anterior;

    delete aux;
    lista.cantidad--;

    color(10);
    cout << "\n  Producto eliminado del inventario.\n";
    color(7);
}

void modificarLista(listaDoble& lista, int id) {
    nodoLista* aux = buscarNodoLista(lista, id);

    if (aux == NULL) {
        color(12);
        cout << "\n  No se encontro el ID " << id << "\n";
        color(7);
        return;
    }

    color(11);
    cout << "\n  Modificando producto ID [" << aux->item.id << "] - " << aux->item.producto << "\n";
    color(7);
    cout << "  Nuevo nombre     : "; getline(cin, aux->item.producto);
    cout << "  Nueva cantidad   : "; cin >> aux->item.cantidad; cin.ignore();
    cout << "  Nueva cant. min  : "; cin >> aux->item.cantMinima; cin.ignore();
    cout << "  Nuevo precio   Q : "; cin >> aux->item.precio; cin.ignore();

    color(10);
    cout << "\n  Producto modificado correctamente.\n";
    color(7);
}

void vaciarLista(listaDoble& lista) {
    nodoLista* aux = lista.cabeza;
    while (aux != NULL) {
        nodoLista* temp = aux->siguiente;
        delete aux;
        aux = temp;
    }
    lista.cabeza = NULL;
    lista.cola = NULL;
    lista.cantidad = 0;
}

void mostrarLista(const listaDoble& lista) {
    if (lista.cabeza == NULL) {
        color(12);
        cout << "\n  El inventario esta vacio.\n";
        color(7);
        return;
    }

    const int ANCHOS[4] = { 8, 22, 20, 16 };
    const int COLS = 4;

    auto lineaH = [&]() {
        color(8);
        cout << "  +";
        for (int c = 0; c < COLS; c++) {
            for (int k = 0; k < ANCHOS[c]; k++) cout << "-";
            cout << "+";
        }
        cout << "\n";
        };

    auto celda = [&](const string& txt, int ancho, int col) {
        string t = " " + txt;
        if ((int)t.size() >= ancho) t = t.substr(0, ancho - 2) + ".";
        cout << t;
        color(8);
        for (int k = (int)t.size(); k < ancho; k++) cout << " ";
        cout << "|";
        };

    // Titulo
    color(11);
    cout << "\n  INVENTARIO - ARTICULOS DEPORTIVOS PARA CANGUROS";
    cout << "  (" << lista.cantidad << " productos)\n\n";

    lineaH();
    color(14);
    cout << "  |";
    const string hdrs[4] = { " ID", " Producto", " Stock / Min.", " Precio" };
    for (int c = 0; c < COLS; c++) {
        string h = hdrs[c];
        if ((int)h.size() >= ANCHOS[c]) h = h.substr(0, ANCHOS[c] - 1);
        cout << h;
        for (int k = (int)h.size(); k < ANCHOS[c]; k++) cout << " ";
        color(8); cout << "|";
    }
    cout << "\n";
    lineaH();

    nodoLista* aux = lista.cabeza;
    while (aux != NULL) {
        bool bajoStock = (aux->item.cantidad <= aux->item.cantMinima);

        string sId = to_string(aux->item.id);
        string sProd = aux->item.producto;
        string sStk = to_string(aux->item.cantidad) + " / " + to_string(aux->item.cantMinima);

        char buf[32];
        snprintf(buf, sizeof(buf), "Q%.2f", aux->item.precio);
        string sPrecio = buf;

        int cId = bajoStock ? 12 : 10;
        int cProd = bajoStock ? 12 : 7;
        int cStk = bajoStock ? 12 : 14;
        int cPrice = bajoStock ? 12 : 11;

        color(8); cout << "  |";
        color(cId);    celda(sId, ANCHOS[0], 0);
        color(cProd);  celda(sProd, ANCHOS[1], 1);
        color(cStk);   celda(sStk, ANCHOS[2], 2);
        color(cPrice); celda(sPrecio, ANCHOS[3], 3);
        cout << "\n";

        if (bajoStock) {
            color(8); cout << "  |";
            color(12);
            string alerta = " !! STOCK BAJO !!";
            cout << alerta;
            int relleno = ANCHOS[0] + ANCHOS[1] + ANCHOS[2] + ANCHOS[3] + COLS - 1
                - (int)alerta.size();
            for (int k = 0; k < relleno; k++) cout << " ";
            color(8); cout << "|\n";
        }

        lineaH();
        aux = aux->siguiente;
    }

    double valorTotal = 0.0;
    int    totalUnids = 0;
    aux = lista.cabeza;
    while (aux != NULL) {
        valorTotal += aux->item.precio * aux->item.cantidad;
        totalUnids += aux->item.cantidad;
        aux = aux->siguiente;
    }

    char bufTotal[64];
    snprintf(bufTotal, sizeof(bufTotal), "Q%.2f", valorTotal);

    color(8);
    cout << "  Unidades totales en bodega : "; color(11); cout << totalUnids; color(7);
    cout << "\n";
    color(8);
    cout << "  Valor total del inventario : "; color(10); cout << bufTotal; color(7);
    cout << "\n\n";
}

// Menu del modulo inventario (lista doble)
void moduloLista(listaDoble& lista) {
    int  op;
    int  idBuscar, idEliminar, idModificar;
    char conf;

    do {
        system("cls");
        color(11);
        cout << "========================================\n";
        cout << "   MODULO INVENTARIO (LISTA DOBLE)\n";
        cout << "========================================\n";
        color(8);
        cout << "  Navegacion bidireccional entre nodos\n";
        cout << "  Productos registrados: "; color(11); cout << lista.cantidad; color(8);
        cout << "\n";
        color(11);
        cout << "========================================\n\n";

        color(7);
        cout << "  1. Agregar producto\n";
        cout << "  2. Eliminar producto\n";
        cout << "  3. Vaciar inventario\n";
        cout << "  4. Mostrar inventario (tabla)\n";
        cout << "  5. Buscar producto\n";
        cout << "  6. Modificar producto\n";
        cout << "  7. Regresar\n\n";

        color(8);
        cout << "  Seleccione: ";
        color(7);
        cin >> op; cin.ignore();

        switch (op) {
        case 1:
            insertarLista(lista);
            color(10);
            cout << "\n  Producto agregado al inventario.\n";
            color(7);
            break;

        case 2:
            if (lista.cabeza == NULL) {
                color(12); cout << "\n  El inventario esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Ingrese el ID a eliminar: ";
                cin >> idEliminar; cin.ignore();
                eliminarLista(lista, idEliminar);
            }
            break;

        case 3:
            if (lista.cabeza == NULL) {
                color(12); cout << "\n  El inventario ya esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Seguro que deseas vaciar el inventario? (Y/N): ";
                cin >> conf; cin.ignore();
                if (conf == 'Y' || conf == 'y') {
                    vaciarLista(lista);
                    color(10); cout << "\n  Inventario vaciado exitosamente.\n"; color(7);
                }
            }
            break;

        case 4:
            mostrarLista(lista);
            break;

        case 5:
            if (lista.cabeza == NULL) {
                color(12); cout << "\n  El inventario esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Ingrese el ID a buscar: ";
                cin >> idBuscar; cin.ignore();
                buscarLista(lista, idBuscar);
            }
            break;

        case 6:
            if (lista.cabeza == NULL) {
                color(12); cout << "\n  El inventario esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Ingrese el ID a modificar: ";
                cin >> idModificar; cin.ignore();
                modificarLista(lista, idModificar);
            }
            break;
        }

        if (op != 7) { cout << "\n"; system("pause"); }

    } while (op != 7);
}

//   MODULO ARBOL BINARIO (ABB)

void llenarNiveles(nodoArbol* nodo, int nivel, int pos, int ancho,
    vector<vector<pair<nodoArbol*, int>>>& niveles)
{
    if (nodo == NULL) return;
    if ((int)niveles.size() <= nivel)
        niveles.push_back({});
    niveles[nivel].push_back({ nodo, pos });
    int mitad = ancho / 2;
    if (mitad < 2) mitad = 2;
    llenarNiveles(nodo->izquierda, nivel + 1, pos - mitad / 2, mitad, niveles);
    llenarNiveles(nodo->derecha, nivel + 1, pos + mitad / 2, mitad, niveles);
}

void dibujarArbol(nodoArbol* raiz)
{
    if (raiz == NULL) {
        color(12);
        cout << "\n  El arbol esta vacio.\n";
        color(7);
        return;
    }

    function<int(nodoArbol*)> altura = [&](nodoArbol* n) -> int {
        if (n == NULL) return 0;
        return 1 + max(altura(n->izquierda), altura(n->derecha));
        };
    int h = altura(raiz);

    const int ANCHO = 78;
    vector<vector<pair<nodoArbol*, int>>> niveles;
    llenarNiveles(raiz, 0, ANCHO / 2, ANCHO, niveles);

    cout << "\n";

    for (int i = 0; i < (int)niveles.size(); i++) {

        if (i > 0) {
            string lineaConex(ANCHO, ' ');
            for (auto& par : niveles[i]) {
                nodoArbol* nodo = par.first;
                int col = par.second;
                for (auto& parPadre : niveles[i - 1]) {
                    nodoArbol* padre = parPadre.first;
                    int colPadre = parPadre.second;
                    bool esHijoIzq = (padre->izquierda == nodo);
                    bool esHijoDer = (padre->derecha == nodo);
                    if (esHijoIzq || esHijoDer) {
                        int desde = min(colPadre, col);
                        int hasta = max(colPadre, col);
                        char cChar = esHijoIzq ? '/' : '\\';
                        int pasos = hasta - desde;
                        if (pasos <= 0) pasos = 1;
                        for (int k = 1; k < pasos; k++) {
                            int xk = esHijoIzq ? (colPadre - k) : (colPadre + k);
                            if (xk >= 0 && xk < ANCHO)
                                lineaConex[xk] = cChar;
                        }
                        break;
                    }
                }
            }
            color(8);
            cout << lineaConex << "\n";
        }

        string lineaNodos(ANCHO, ' ');
        for (auto& par : niveles[i]) {
            nodoArbol* nodo = par.first;
            int col = par.second;
            string etiqueta = "[" + to_string(nodo->pedido.correlativo)
                + ":" + to_string(nodo->pedido.cantidad) + "]";
            int inicio = col - (int)etiqueta.size() / 2;
            if (inicio < 0) inicio = 0;
            for (int k = 0; k < (int)etiqueta.size(); k++) {
                int xk = inicio + k;
                if (xk < ANCHO) lineaNodos[xk] = etiqueta[k];
            }
        }
        color(10);
        cout << lineaNodos << "\n";
    }

    color(7);
    color(8);
    cout << "\n  Descripcion: [correlativo:cantidad]";

    function<int(nodoArbol*)> contarNodos = [&](nodoArbol* n) -> int {
        if (n == NULL) return 0;
        return 1 + contarNodos(n->izquierda) + contarNodos(n->derecha);
        };

    cout << "   Nodos: ";
    color(11); cout << contarNodos(raiz);
    color(8);  cout << "   Altura: ";
    color(11); cout << h;
    color(7);  cout << "\n";
}

void insertarArbol(nodoArbol*& arbol) {
    pedidos p;
    cout << "Correlativo: "; cin >> p.correlativo; cin.ignore();
    cout << "Producto: ";    getline(cin, p.producto);
    cout << "Cantidad: ";    cin >> p.cantidad; cin.ignore();
    cout << "Cliente: ";     getline(cin, p.cliente);
    cout << "Direccion: ";   getline(cin, p.direccion);
    insertarNodo(arbol, p);
}

void insertarNodo(nodoArbol*& arbol, pedidos p) {
    if (arbol == NULL) {
        nodoArbol* nuevo = new nodoArbol();
        nuevo->pedido = p;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        arbol = nuevo;
    }
    else {
        if (p.cantidad < arbol->pedido.cantidad)
            insertarNodo(arbol->izquierda, p);
        else
            insertarNodo(arbol->derecha, p);
    }
}

nodoArbol* encontrarMinimo(nodoArbol* nodo) {
    if (nodo == NULL) return NULL;
    while (nodo->izquierda != NULL)
        nodo = nodo->izquierda;
    return nodo;
}

nodoArbol* eliminarNodo(nodoArbol* arbol, int correlativo) {
    if (arbol == NULL) {
        color(12);
        cout << "\n  No se encontro el correlativo " << correlativo << "\n";
        color(7);
        return NULL;
    }
    arbol->izquierda = eliminarNodo(arbol->izquierda, correlativo);
    arbol->derecha = eliminarNodo(arbol->derecha, correlativo);

    if (arbol->pedido.correlativo == correlativo) {
        if (arbol->izquierda == NULL && arbol->derecha == NULL) {
            delete arbol; return NULL;
        }
        if (arbol->izquierda == NULL) {
            nodoArbol* temp = arbol->derecha; delete arbol; return temp;
        }
        if (arbol->derecha == NULL) {
            nodoArbol* temp = arbol->izquierda; delete arbol; return temp;
        }
        nodoArbol* sucesor = encontrarMinimo(arbol->derecha);
        arbol->pedido = sucesor->pedido;
        arbol->derecha = eliminarNodo(arbol->derecha, sucesor->pedido.correlativo);
    }
    return arbol;
}

void vaciarArbol(nodoArbol*& arbol) {
    if (arbol == NULL) return;
    vaciarArbol(arbol->izquierda);
    vaciarArbol(arbol->derecha);
    delete arbol;
    arbol = NULL;
}

void mostrarArbolOrden(nodoArbol* arbol) {
    if (arbol == NULL) return;
    mostrarArbolOrden(arbol->izquierda);
    color(11);
    cout << "\n  +---------------------------------+";
    color(7);
    cout << "\n  Pedido No.: "; color(10); cout << arbol->pedido.correlativo; color(7);
    cout << "\n  Cliente   : " << arbol->pedido.cliente;
    cout << "\n  Producto  : " << arbol->pedido.producto;
    cout << "\n  Cantidad  : " << arbol->pedido.cantidad;
    if (arbol->pedido.cantidad >= 50) {
        color(14); cout << "  << MAYOREO - DESCUENTO 15%"; color(7);
    }
    color(11);
    cout << "\n  +---------------------------------+";
    color(7);
    mostrarArbolOrden(arbol->derecha);
}

void buscarMayor(nodoArbol* arbol) {
    if (arbol == NULL) return;
    buscarMayor(arbol->izquierda);
    if (arbol->pedido.cantidad >= 50) {
        color(14);
        cout << "\n  +================================+";
        cout << "\n  PEDIDO CON DESCUENTO";
        cout << "\n  +================================+";
        color(7);
        cout << "\n  Cliente : " << arbol->pedido.cliente;
        cout << "\n  Producto: " << arbol->pedido.producto;
        cout << "\n  Cantidad: " << arbol->pedido.cantidad;
        color(14);
        cout << "\n  DESCUENTO: 15%";
        cout << "\n  +================================+";
        color(7);
    }
    buscarMayor(arbol->derecha);
}

void moduloarbol(nodoArbol*& arbol) {
    int  op;
    int  corrEliminar;
    char conf;

    do {
        system("cls");
        color(11);
        cout << "========================================\n";
        cout << "        MODULO ARBOL BINARIO (ABB)\n";
        cout << "        (Ordenado por cantidad)\n";
        cout << "========================================\n\n";
        color(7);
        cout << "  1. Insertar pedido\n";
        cout << "  2. Eliminar pedido\n";
        cout << "  3. Vaciar arbol\n";
        cout << "  4. Mostrar arbol visual\n";
        cout << "  5. Mostrar lista ordenada\n";
        cout << "  6. Buscar pedidos de mayoreo\n";
        cout << "  7. Regresar\n\n";
        color(8);
        cout << "  Seleccione: ";
        color(7);
        cin >> op; cin.ignore();

        switch (op) {
        case 1:
            cout << "\n";
            insertarArbol(arbol);
            color(10); cout << "\n  Pedido insertado correctamente.\n"; color(7);
            break;
        case 2:
            if (arbol == NULL) {
                color(12); cout << "\n  El arbol esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Ingrese el correlativo a eliminar: ";
                cin >> corrEliminar; cin.ignore();
                arbol = eliminarNodo(arbol, corrEliminar);
                color(10); cout << "\n  Operacion completada.\n"; color(7);
            }
            break;
        case 3:
            if (arbol == NULL) {
                color(12); cout << "\n  El arbol ya esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Seguro que deseas vaciar el arbol? (Y/N): ";
                cin >> conf; cin.ignore();
                if (conf == 'Y' || conf == 'y') {
                    vaciarArbol(arbol);
                    color(10); cout << "\n  Arbol vaciado exitosamente.\n"; color(7);
                }
            }
            break;
        case 4:
            cout << "\n";
            dibujarArbol(arbol);
            break;
        case 5:
            if (arbol == NULL) {
                color(12); cout << "\n  El arbol esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  --- Pedidos en orden (menor a mayor cantidad) ---\n";
                mostrarArbolOrden(arbol);
                cout << "\n";
            }
            break;
        case 6:
            if (arbol == NULL) {
                color(12); cout << "\n  El arbol esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  --- Pedidos con descuento (cantidad >= 50) ---\n";
                buscarMayor(arbol);
                cout << "\n";
            }
            break;
        }

        if (op != 7) { cout << "\n"; system("pause"); }

    } while (op != 7);
}

//   MODULO ARBOL AVL

int alturaAVL(nodoAVL* n) {
    if (n == NULL) return 0;
    return n->altura;
}

int factorEquilibrio(nodoAVL* n) {
    if (n == NULL) return 0;
    return alturaAVL(n->izquierda) - alturaAVL(n->derecha);
}

void actualizarAltura(nodoAVL* n) {
    if (n == NULL) return;
    n->altura = 1 + max(alturaAVL(n->izquierda), alturaAVL(n->derecha));
}

nodoAVL* rotarDerecha(nodoAVL* y) {
    nodoAVL* x = y->izquierda;
    nodoAVL* T2 = x->derecha;
    x->derecha = y;
    y->izquierda = T2;
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}

nodoAVL* rotarIzquierda(nodoAVL* x) {
    nodoAVL* y = x->derecha;
    nodoAVL* T2 = y->izquierda;
    y->izquierda = x;
    x->derecha = T2;
    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

nodoAVL* balancear(nodoAVL* n) {
    if (n == NULL) return NULL;
    actualizarAltura(n);
    int fe = factorEquilibrio(n);

    if (fe > 1 && factorEquilibrio(n->izquierda) >= 0)
        return rotarDerecha(n);
    if (fe > 1 && factorEquilibrio(n->izquierda) < 0) {
        n->izquierda = rotarIzquierda(n->izquierda);
        return rotarDerecha(n);
    }
    if (fe < -1 && factorEquilibrio(n->derecha) <= 0)
        return rotarIzquierda(n);
    if (fe < -1 && factorEquilibrio(n->derecha) > 0) {
        n->derecha = rotarDerecha(n->derecha);
        return rotarIzquierda(n);
    }
    return n;
}

nodoAVL* minimoAVL(nodoAVL* n) {
    if (n == NULL) return NULL;
    while (n->izquierda != NULL)
        n = n->izquierda;
    return n;
}

nodoAVL* insertarNodoAVL(nodoAVL* raiz, pedidos p, bool& insertado) {
    if (raiz == NULL) {
        nodoAVL* nuevo = new nodoAVL();
        nuevo->pedido = p;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        nuevo->altura = 1;
        insertado = true;
        return nuevo;
    }
    if (p.cantidad < raiz->pedido.cantidad)
        raiz->izquierda = insertarNodoAVL(raiz->izquierda, p, insertado);
    else
        raiz->derecha = insertarNodoAVL(raiz->derecha, p, insertado);

    return balancear(raiz);
}

void insertarAVL(nodoAVL*& avl) {
    pedidos p;
    cout << "\n  Correlativo: "; cin >> p.correlativo; cin.ignore();
    cout << "  Producto   : "; getline(cin, p.producto);
    cout << "  Cantidad   : "; cin >> p.cantidad; cin.ignore();
    cout << "  Cliente    : "; getline(cin, p.cliente);
    cout << "  Direccion  : "; getline(cin, p.direccion);
    bool insertado = false;
    avl = insertarNodoAVL(avl, p, insertado);
}

nodoAVL* eliminarNodoAVL(nodoAVL* raiz, int correlativo, bool& eliminado) {
    if (raiz == NULL) return NULL;

    raiz->izquierda = eliminarNodoAVL(raiz->izquierda, correlativo, eliminado);
    raiz->derecha = eliminarNodoAVL(raiz->derecha, correlativo, eliminado);

    if (raiz->pedido.correlativo == correlativo) {
        eliminado = true;
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz; return NULL;
        }
        if (raiz->izquierda == NULL) {
            nodoAVL* temp = raiz->derecha; delete raiz; return balancear(temp);
        }
        if (raiz->derecha == NULL) {
            nodoAVL* temp = raiz->izquierda; delete raiz; return balancear(temp);
        }
        nodoAVL* sucesor = minimoAVL(raiz->derecha);
        raiz->pedido = sucesor->pedido;
        bool dummy = false;
        raiz->derecha = eliminarNodoAVL(raiz->derecha, sucesor->pedido.correlativo, dummy);
    }
    return balancear(raiz);
}

nodoAVL* vaciarAVL_aux(nodoAVL* raiz) {
    if (raiz == NULL) return NULL;
    vaciarAVL_aux(raiz->izquierda);
    vaciarAVL_aux(raiz->derecha);
    delete raiz;
    return NULL;
}

void vaciarAVL(nodoAVL*& avl) {
    avl = vaciarAVL_aux(avl);
}

void mostrarAVLOrden(nodoAVL* raiz) {
    if (raiz == NULL) return;
    mostrarAVLOrden(raiz->izquierda);

    int fe = factorEquilibrio(raiz);
    string feStr = (fe >= 0 ? "+" : "") + to_string(fe);

    color(11);
    cout << "\n  +---------------------------------+";
    color(7);
    cout << "\n  Pedido No. : "; color(10); cout << raiz->pedido.correlativo; color(7);
    cout << "\n  Cliente    : " << raiz->pedido.cliente;
    cout << "\n  Producto   : " << raiz->pedido.producto;
    cout << "\n  Cantidad   : " << raiz->pedido.cantidad;
    cout << "\n  Altura nodo: " << raiz->altura;
    cout << "\n  F.Equilib. : ";
    if (fe == 0) { color(10); }
    else if (fe == 1 || fe == -1) { color(14); }
    else { color(12); }
    cout << feStr;
    color(7);
    if (raiz->pedido.cantidad >= 50) {
        color(14); cout << "\n  >> MAYOREO - DESCUENTO 15%"; color(7);
    }
    color(11);
    cout << "\n  +---------------------------------+";
    color(7);
    mostrarAVLOrden(raiz->derecha);
}

void buscarMayorAVL(nodoAVL* raiz) {
    if (raiz == NULL) return;
    buscarMayorAVL(raiz->izquierda);
    if (raiz->pedido.cantidad >= 50) {
        color(14);
        cout << "\n  +================================+";
        cout << "\n  PEDIDO CON DESCUENTO";
        cout << "\n  +================================+";
        color(7);
        cout << "\n  Cliente : " << raiz->pedido.cliente;
        cout << "\n  Producto: " << raiz->pedido.producto;
        cout << "\n  Cantidad: " << raiz->pedido.cantidad;
        color(14);
        cout << "\n  DESCUENTO: 15%";
        cout << "\n  +================================+";
        color(7);
    }
    buscarMayorAVL(raiz->derecha);
}

void llenarNivelesAVL(nodoAVL* nodo, int nivel, int pos, int ancho,
    vector<vector<pair<nodoAVL*, int>>>& niveles)
{
    if (nodo == NULL) return;
    if ((int)niveles.size() <= nivel)
        niveles.push_back({});
    niveles[nivel].push_back({ nodo, pos });
    int mitad = ancho / 2;
    if (mitad < 2) mitad = 2;
    llenarNivelesAVL(nodo->izquierda, nivel + 1, pos - mitad / 2, mitad, niveles);
    llenarNivelesAVL(nodo->derecha, nivel + 1, pos + mitad / 2, mitad, niveles);
}

void dibujarAVL(nodoAVL* raiz)
{
    if (raiz == NULL) {
        color(12);
        cout << "\n  El arbol AVL esta vacio.\n";
        color(7);
        return;
    }

    function<int(nodoAVL*)> calcAltura = [&](nodoAVL* n) -> int {
        if (n == NULL) return 0;
        return 1 + max(calcAltura(n->izquierda), calcAltura(n->derecha));
        };
    int h = calcAltura(raiz);

    function<int(nodoAVL*)> contarNodos = [&](nodoAVL* n) -> int {
        if (n == NULL) return 0;
        return 1 + contarNodos(n->izquierda) + contarNodos(n->derecha);
        };

    const int ANCHO = 78;
    vector<vector<pair<nodoAVL*, int>>> niveles;
    llenarNivelesAVL(raiz, 0, ANCHO / 2, ANCHO, niveles);

    cout << "\n";
    color(11);
    cout << "  --- ARBOL AVL VISUAL ---\n";
    color(8);
    cout << "  Colores: ";
    color(10); cout << "verde=bal. ";
    color(14); cout << "amarillo=leve ";
    color(12); cout << "rojo=critico";
    color(7);  cout << "\n\n";

    for (int i = 0; i < (int)niveles.size(); i++) {

        if (i > 0) {
            string lineaConex(ANCHO, ' ');
            for (auto& par : niveles[i]) {
                nodoAVL* nodo = par.first;
                int col = par.second;
                for (auto& parPadre : niveles[i - 1]) {
                    nodoAVL* padre = parPadre.first;
                    int colPadre = parPadre.second;
                    bool esIzq = (padre->izquierda == nodo);
                    bool esDer = (padre->derecha == nodo);
                    if (esIzq || esDer) {
                        int desde = min(colPadre, col);
                        int hasta = max(colPadre, col);
                        char cChar = esIzq ? '/' : '\\';
                        int pasos = hasta - desde;
                        if (pasos <= 0) pasos = 1;
                        for (int k = 1; k < pasos; k++) {
                            int xk = esIzq ? (colPadre - k) : (colPadre + k);
                            if (xk >= 0 && xk < ANCHO)
                                lineaConex[xk] = cChar;
                        }
                        break;
                    }
                }
            }
            color(8);
            cout << lineaConex << "\n";
        }

        struct InfoNodo { int inicio; string etiqueta; int colorNodo; };
        vector<InfoNodo> infos;

        for (auto& par : niveles[i]) {
            nodoAVL* nodo = par.first;
            int col = par.second;
            int fe = factorEquilibrio(nodo);
            string feStr = (fe >= 0 ? "+" : "") + to_string(fe);
            string etiqueta = "[" + to_string(nodo->pedido.correlativo)
                + ":" + to_string(nodo->pedido.cantidad)
                + "|" + feStr + "]";
            int inicio = col - (int)etiqueta.size() / 2;
            if (inicio < 0) inicio = 0;
            int colorNodo;
            if (fe == 0)             colorNodo = 10;
            else if (fe == 1 || fe == -1) colorNodo = 14;
            else                          colorNodo = 12;
            infos.push_back({ inicio, etiqueta, colorNodo });
        }

        int cursorX = 0;
        for (auto& info : infos) {
            if (info.inicio > cursorX) {
                color(7);
                cout << string(info.inicio - cursorX, ' ');
                cursorX = info.inicio;
            }
            color(info.colorNodo);
            cout << info.etiqueta;
            cursorX += (int)info.etiqueta.size();
        }
        cout << "\n";
    }

    color(7);
    cout << "\n";
    color(8);
    cout << "  Leyenda: [correlativo:cantidad|FE]   FE = factor de equilibrio\n";
    cout << "  Nodos : "; color(11); cout << contarNodos(raiz);
    color(8); cout << "   Altura: "; color(11); cout << h;
    color(8); cout << "   Raiz cant.: "; color(11); cout << raiz->pedido.cantidad;
    color(8); cout << "   FE raiz: ";
    int feRaiz = factorEquilibrio(raiz);
    if (feRaiz == 0) { color(10); }
    else if (abs(feRaiz) == 1) { color(14); }
    else { color(12); }
    cout << (feRaiz >= 0 ? "+" : "") << feRaiz;
    color(7); cout << "\n";
}

void moduloAVL(nodoAVL*& avl)
{
    int  op;
    int  corrEliminar;
    char conf;

    do {
        system("cls");
        color(11);
        cout << "========================================\n";
        cout << "       MODULO ARBOL AVL\n";
        cout << "       (Auto-balanceado por cantidad)\n";
        cout << "========================================\n";
        color(8);
        cout << "  El AVL se rebalancea automaticamente\n";
        cout << "  despues de cada insercion/eliminacion\n";
        color(11);
        cout << "========================================\n\n";
        color(7);
        cout << "  1. Insertar pedido\n";
        cout << "  2. Eliminar pedido\n";
        cout << "  3. Vaciar arbol\n";
        cout << "  4. Mostrar arbol visual\n";
        cout << "  5. Mostrar lista ordenada\n";
        cout << "  6. Buscar pedidos de mayoreo\n";
        cout << "  7. Regresar\n\n";
        color(8);
        cout << "  Seleccione: ";
        color(7);
        cin >> op; cin.ignore();

        switch (op) {
        case 1: {
            cout << "\n";
            int altAntes = alturaAVL(avl);
            insertarAVL(avl);
            int altDespues = alturaAVL(avl);
            color(10);
            cout << "\n  Pedido insertado y arbol rebalanceado.";
            color(8);
            if (altAntes != altDespues)
                cout << "\n  (Altura cambio de " << altAntes << " a " << altDespues << ")";
            cout << "\n";
            color(7);
            break;
        }
        case 2:
            if (avl == NULL) {
                color(12); cout << "\n  El arbol esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Ingrese el correlativo a eliminar: ";
                cin >> corrEliminar; cin.ignore();
                bool eliminado = false;
                int altAntes = alturaAVL(avl);
                avl = eliminarNodoAVL(avl, corrEliminar, eliminado);
                if (eliminado) {
                    color(10);
                    cout << "\n  Nodo eliminado y arbol rebalanceado.";
                    color(8);
                    int altDespues = alturaAVL(avl);
                    if (altAntes != altDespues)
                        cout << "\n  (Altura cambio de " << altAntes << " a " << altDespues << ")";
                    cout << "\n";
                    color(7);
                }
                else {
                    color(12);
                    cout << "\n  No se encontro el correlativo " << corrEliminar << ".\n";
                    color(7);
                }
            }
            break;
        case 3:
            if (avl == NULL) {
                color(12); cout << "\n  El arbol ya esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  Seguro que deseas vaciar el arbol AVL? (Y/N): ";
                cin >> conf; cin.ignore();
                if (conf == 'Y' || conf == 'y') {
                    vaciarAVL(avl);
                    color(10); cout << "\n  Arbol vaciado exitosamente.\n"; color(7);
                }
            }
            break;
        case 4:
            cout << "\n";
            dibujarAVL(avl);
            break;
        case 5:
            if (avl == NULL) {
                color(12); cout << "\n  El arbol esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  --- Lista en orden (menor a mayor cantidad) ---\n";
                mostrarAVLOrden(avl);
                cout << "\n";
            }
            break;
        case 6:
            if (avl == NULL) {
                color(12); cout << "\n  El arbol esta vacio.\n"; color(7);
            }
            else {
                cout << "\n  --- Pedidos de mayoreo (cantidad >= 50) ---\n";
                buscarMayorAVL(avl);
                cout << "\n";
            }
            break;
        }

        if (op != 7) { cout << "\n"; system("pause"); }

    } while (op != 7);
}

//   ESTETICA

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void portada() {
    system("cls");
    color(11);
    cout << "============================================================\n";
    cout << "            SISTEMA DE CONTROL DE INVENTARIO\n";
    cout << "============================================================\n";
    color(10);
    cout << "            ARTICULOS DEPORTIVOS PARA CANGUROS \n";
    color(11);
    cout << "============================================================\n\n";
    color(7);
    cout << "------------------------------------------------------------\n";
    cout << "                  INFORMACION DEL PROYECTO\n";
    cout << "------------------------------------------------------------\n\n";
    cout << "  Curso      : Programacion III\n";
    cout << "  Lenguaje   : C++ (Estructurado)\n";
    cout << "  Entrega    : Abril 2026\n\n";
    color(11);
    cout << "------------------------------------------------------------\n";
    cout << "                  INTEGRANTES DEL GRUPO\n";
    cout << "------------------------------------------------------------\n";
    color(7);
    cout << "  > Marnaby Gilbertson Geroham Cux Mazat\n";
    cout << "       Carnet: 2290-23-3596\n";
    cout << "  > Jose Andres Santizo Procopio\n";
    cout << "       Carnet: 2290-24-12667\n";
    cout << "  > Miguel Angel Santos Garcia Velasquez\n";
    cout << "       Carnet: 2290-24-8950\n\n";
    color(10);
    cout << "------------------------------------------------------------\n";
    cout << "   Presione cualquier tecla para iniciar el sistema...\n";
    cout << "------------------------------------------------------------\n";
    system("pause");
}

void cargando() {
    system("cls");
    color(11);
    cout << "CARGANDO SISTEMA...\n\n";
    color(10);
    cout << "[";
    for (int i = 0; i < 20; i++) { cout << char(219); Sleep(100); }
    cout << "] 100%\n\n";
    color(14);
    cout << "Inicializando modulo PILA...\n";  Sleep(500);
    cout << "Inicializando modulo COLA...\n";  Sleep(500);
    cout << "Cargando base de datos...\n"; Sleep(500);
    cout << "2 + 2 = 6...\n"; Sleep(500);
    cout << "Configurando entorno...\n";       Sleep(500);
    color(10);
    cout << "\nSistema listo!\n";
    Sleep(800);
    color(7);
    cout << "\nSistema listo. Presione una tecla...";
    (void)_getch();
}

void dibujo() {
    system("cls");
    color(10);
    cout << "                                                  _  _" << endl;
    cout << "                                                 (\\\\( \\." << endl;
    cout << "                                                  `.-." << endl;
    cout << "                              _...._            _,-'   `-." << endl;
    cout << "\\                          ,'      `-._.---.,-'       .   \\." << endl;
    cout << " \\`.                      ,'                               `." << endl;
    cout << "  \\ `-...__              /                           .   .:  y" << endl;
    cout << "   `._     ``--..__     /                           ,'`---._/" << endl;
    cout << "      `-._         ``--'                      |    /_" << endl;
    cout << "          `.._                   _            ;   <_ \\" << endl;
    cout << "              `--.___             `.           `-._ \\ \\" << endl;
    cout << "                     `--<           `.     (\\ _/)/ `.\\/`" << endl;
    cout << "                         \\            \\     `<a \\  /_/" << endl;
    cout << "                          `.           ;      `._y" << endl;
    cout << "                            `--.      /    _../" << endl;
    cout << "                                \\    /__..'" << endl;
    cout << "                                 ;  //" << endl;
    cout << "                                <   \\\\" << endl;
    cout << "                                 `.  \\\\" << endl;
    cout << "                                   `. \\\\_ __" << endl;
    cout << "                                     `.'  \\\\" << endl;
    cout << "                                       `----''" << endl;
    system("pause");
}
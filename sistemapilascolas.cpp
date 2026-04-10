#include <iostream>
#include<conio.h>
#include<cstdlib>
#include<string>
#include<fstream>
#include<sstream>
#include <windows.h>

using namespace std;

struct ingresos {
    int correlativoIng = 0;
    string proveedorIng;
    string fechaIng;
    string productoIng;
    int cantidadIng;
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

int menuprincipal();
int submenu(string titulo);
void modulopila(nodoPila*& p);
void modulocola(cola& q);
int push(nodoPila*& p);
int pop(nodoPila*& p);
int encolar(cola& q);
int desencolar(cola& q);
void portada();
void color(int c);
void cargando();
void guardarPedidos(const pedidos& q);
void actualizarPedidos(const cola& q);
void cargarPedidos(cola& q);
void guardarIngreso(nodoPila*& p);
void actualizarIngreso(nodoPila*& p);
void cargarIngreso(nodoPila*& p);
void mostrarpila(nodoPila*& p);
void modificarpila(nodoPila*& p, int correModificarIng);
void buscarpila(nodoPila*& p, int correBuscarIng);
void buscarcola(cola q, int corre);
void modificarcola(cola q, int corre);
void mostrarcola(cola q);
void pantallacargaPedidos(cola& q);
void pantallacargaIngresos(nodoPila*& p);

int correlativoPedidos = 1;
int correlativoIngGlobal = 1;

int main()
{
    cola q;
    q.primero = NULL;
    q.ultimo = NULL;

    nodoPila* p = NULL;

    int op;
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
            system("cls");

            color(12);
            cout << "========================================\n";
            cout << "         SALIENDO DEL SISTEMA\n";
            cout << "========================================\n\n";

            color(11);
            cout << "Guardando datos";

            for (int i = 0; i < 3; i++) {
                cout << ".";
                Sleep(300);
            }

            cout << "\n\n";

            color(10);
            cout << "Cerrando aplicacion";
            Sleep(600);

            color(7);
            break;
        }

    } while (op != 2);

    return 0;
}

//---MENU PRINCIPAL---
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

        if (opcion == 0) {
            color(10);
            cout << "   >> [ MODULO PILA ]\n";
        }
        else {
            color(7);
            cout << "      Modulo PILA\n";
        }

        if (opcion == 1) {
            color(10);
            cout << "   >> [ MODULO COLA ]\n";
        }
        else {
            color(7);
            cout << "      Modulo COLA\n";
        }

        if (opcion == 2) {
            color(12);
            cout << "   >> [ SALIR ]\n";
        }
        else {
            color(7);
            cout << "      Salir\n";
        }

        color(8);
        cout << "\nUse las flechas y ENTER para seleccionar";

        tecla = _getch();

        if (tecla == 72) opcion--;
        if (tecla == 80) opcion++;

        if (opcion < 0) opcion = 2;
        if (opcion > 2) opcion = 0;

    } while (tecla != 13);

    return opcion;
}

//------SUB MENU----
int submenu(string titulo) {
    int opcion = 0;
    int tecla;

    do {
        system("cls");

        color(11);
        cout << "========================================\n";
        cout << "        " << titulo << "\n";
        cout << "========================================\n\n";

        color(7);

        if (opcion == 0) {
            color(10);
            cout << "   >>   [ INGRESAR DATOS ]\n";
        }
        else {
            color(8);
            cout << "        Ingresar datos\n";
        }

        if (opcion == 1) {
            color(10);
            cout << "   >>   [ ELIMINAR ]\n";
        }
        else {
            color(8);
            cout << "        Eliminar\n";
        }

        if (opcion == 2) {
            color(10);
            cout << "   >>   [ MOSTRAR DATOS ]\n";
        }
        else {
            color(8);
            cout << "        Mostrar datos\n";
        }

        if (opcion == 3) {
            color(10);
            cout << "   >>   [ BUSCAR ]\n";
        }
        else {
            color(8);
            cout << "        Buscar\n";
        }

        if (opcion == 4) {
            color(10);
            cout << "   >>   [ MODIFICAR ]\n";
        }
        else {
            color(8);
            cout << "        Modificar\n";
        }

        if (opcion == 5) {
            color(12);
            cout << "   >>   [ REGRESAR ]\n";
        }
        else {
            color(8);
            cout << "        Regresar\n";
        }

        tecla = _getch();

        if (tecla == 72) opcion--;
        if (tecla == 80) opcion++;

        if (opcion < 0) opcion = 5;
        if (opcion > 5) opcion = 0;

    } while (tecla != 13);

    color(7);
    return opcion;
}

//-----------MODULOS-----------------

//----PILAS----
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
                    cout << "\n\nVALIDARAS EL INGRESO " << p->ingreso.correlativoIng << "\nQUIERES CONTINUAR?  (Y/N) "; cin >> res; cin.ignore();
                    if (res == 'Y' || res == 'y') {
                        x = pop(p);
                        cout << "\n\nEL REGISTRO NO. " << x << " FUE VALIDADO";
                        break;
                    }
                    else if (res == 'N' || res == 'n') {
                        break;
                    }
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

//----colas----
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
                    cout << "\n\nDESPACHARAS EL PEDIDO " << q.primero->pedido.correlativo << "\nQUIERES CONTINUAR?  (Y/N) "; cin >> res; cin.ignore();
                    if (res == 'Y' || res == 'y') {
                        x = desencolar(q);
                        cout << "\n\nEL PEDIDO " << x << " FUE DESPACHADO";
                        break;
                    }
                    else if (res == 'N' || res == 'n') {
                        break;
                    }
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

//----FUNCIONES----

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
    int corre;

    corre = aux->ingreso.correlativoIng;
    p = aux->siguientePila;
    delete aux;

    actualizarIngreso(p);

    return corre;
}

void mostrarpila(nodoPila*& p) {
    nodoPila* aux = p;

    while (aux != NULL) {
        cout << "\n\n┌--------------------------------┐" << endl;
        cout << "  Ingreso no: " << aux->ingreso.correlativoIng << endl;
        cout << "  Proveedor del producto: " << aux->ingreso.proveedorIng << endl;
        cout << "  Nombre del producto: " << aux->ingreso.productoIng << endl;
        cout << "└--------------------------------┘" << endl;

        aux = aux->siguientePila;
    }
}

void modificarpila(nodoPila*& p, int correModificarIng) {
    nodoPila* aux = p;
    bool encontradoModificarIng = false;

    while (aux != NULL) {
        if (aux->ingreso.correlativoIng == correModificarIng) {
            cout << "\nIngreso No. [" << aux->ingreso.correlativoIng << "]" << endl;
            cout << "\nIngrese el Proveedor: "; getline(cin, aux->ingreso.proveedorIng);
            cout << "Ingrese la fecha (dd/mm/yy): "; getline(cin, aux->ingreso.fechaIng);
            cout << "Ingrese el nombre del producto: "; getline(cin, aux->ingreso.productoIng);
            cout << "Ingrese la cantidad de producto: "; cin >> aux->ingreso.cantidadIng; cin.ignore();

            encontradoModificarIng = true;
        }
        aux = aux->siguientePila;
    }
    if (!encontradoModificarIng) cout << "\nNO SE ENCONTRO EL INGRESO >:C" << endl;
}

void buscarpila(nodoPila*& p, int correBuscarIng) {
    nodoPila* aux = p;
    bool encontradoBuscarIng = false;

    while (aux != NULL) {
        if (aux->ingreso.correlativoIng == correBuscarIng) {
            cout << "\n\nIngreso No. [" << aux->ingreso.correlativoIng << "]" << endl;
            cout << "\nProveedor: " << aux->ingreso.proveedorIng << endl;
            cout << "Fecha: " << aux->ingreso.fechaIng << endl;
            cout << "Nombre del Producto: " << aux->ingreso.productoIng << endl;
            cout << "Cantidad de Producto: " << aux->ingreso.cantidadIng << endl;

            encontradoBuscarIng = true;
        }
        aux = aux->siguientePila;
    }
    if (!encontradoBuscarIng) cout << "\nNO SE ENCONTRO EL REGISTRO INTENTE MAS TARDE >:C" << endl;
}

void guardarIngreso(nodoPila*& p) {
    ofstream archivo("ingresos.txt", ios::app);

    if (archivo.is_open()) {
        archivo << p->ingreso.correlativoIng << "|" << p->ingreso.proveedorIng << "|"
            << p->ingreso.fechaIng << "|" << p->ingreso.productoIng << "|" << p->ingreso.cantidadIng << endl;

        archivo.close();
    }
}

void actualizarIngreso(nodoPila*& p) {
    ofstream archivo("ingresos.txt", ios::out);

    nodoPila* aux = p;

    if (archivo.is_open()) {
        while (aux != NULL) {
            archivo << aux->ingreso.correlativoIng << "|" << aux->ingreso.proveedorIng << "|"
                << aux->ingreso.fechaIng << "|" << aux->ingreso.productoIng << "|" << aux->ingreso.cantidadIng << endl;
            
            aux = aux->siguientePila;
        }
        archivo.close();
    }
}

void cargarIngreso(nodoPila*& p) {
    ifstream archivo("ingresos.txt");
    string linea;

    if (archivo.fail()) {
        cout << "Fallo al cargar los pedidos contacte con servicio tecnico" << endl;
        exit(1);
    }

    int maxCorrelativoIng = 0;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;

        nodoPila* nuevo = new nodoPila;

        getline(ss, dato, '|');
        nuevo->ingreso.correlativoIng = stoi(dato);

        if (nuevo->ingreso.correlativoIng > maxCorrelativoIng) {
            maxCorrelativoIng = nuevo->ingreso.correlativoIng;
        }

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

int encolar(cola& q) {
    nodoCola* aux = new nodoCola;
    
    aux->pedido.correlativo = correlativoPedidos++;
    cout << "Ingrese el producto del cliente: "; 
    getline(cin, aux->pedido.producto);
    cout << "Ingrese la cantidad de productos: "; 
    cin >> aux->pedido.cantidad;
    cin.ignore();
    cout << "Ingrese el nombre del cliente: "; 
    getline(cin, aux->pedido.cliente);
    cout << "Ingrese la direccion del cliente: "; 
    getline(cin, aux->pedido.direccion);
    
    aux->siguienteCola = NULL;

    if (q.primero == NULL) {
        q.primero = aux;
    }
    else {
        q.ultimo->siguienteCola = aux;
    }
    q.ultimo = aux;

    guardarPedidos(aux->pedido);

    return aux->pedido.correlativo;
}

int desencolar(cola& q) {
    int corre;
    nodoCola* aux;

    aux = q.primero;
    corre = aux->pedido.correlativo;
    q.primero = q.primero->siguienteCola;
    delete aux;

    actualizarPedidos(q);

    return corre;
}

void mostrarcola(cola q) {
    nodoCola* aux;

    aux = q.primero;

    while (aux != NULL) {
        cout << "   [" << aux->pedido.correlativo << " - " << aux->pedido.cliente << "]";
        aux = aux->siguienteCola;
    }
}

void buscarcola(cola q, int corre) {
    nodoCola* aux;
    aux = q.primero;
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
    nodoCola* aux;
    aux = q.primero;
    bool encontrado = false;
    string producto;

    while (aux != NULL) {
        if (aux->pedido.correlativo == corre) {
            cout << "\nPEDIDO NO. [" << aux->pedido.correlativo << "]" << endl;
            cout << "\nIngrese el nuevo producto: "; getline(cin, producto);
            aux->pedido.producto = producto;
            cout << "Ingrese la nueva cantidad de producto: ";
            cin >> aux->pedido.cantidad;
            cin.ignore();
            cout << "Ingrese el nuevo del cliente: ";
            getline(cin, aux->pedido.cliente);
            cout << "Ingrese la nueva direccion: ";
            getline(cin, aux->pedido.direccion);
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

        if (nuevo->pedido.correlativo > maxCorrelativo) {
            maxCorrelativo = nuevo->pedido.correlativo;
        }

        getline(ss, nuevo->pedido.producto, '|');

        getline(ss, dato, '|');
        nuevo->pedido.cantidad = stoi(dato);

        getline(ss, nuevo->pedido.cliente, '|');
        getline(ss, nuevo->pedido.direccion, '|');

        nuevo->siguienteCola = NULL;

        if (q.primero == NULL) {
            q.primero = nuevo;
        }
        else {
            q.ultimo->siguienteCola = nuevo;
        }
        q.ultimo = nuevo;
    }

    archivo.close();

    correlativoPedidos = maxCorrelativo + 1;
}

//----ESTETICA----
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

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cargando() {
    system("cls");

    color(11);
    cout << "CARGANDO SISTEMA...\n\n";

    color(10);
    cout << "[";

    for (int i = 0; i < 20; i++) {
        cout << char(219);
        Sleep(100);
    }

    cout << "] 100%\n";

    cout << "\n";

    color(14);
    cout << "Inicializando modulo PILA...\n";
    Sleep(500);

    cout << "Inicializando modulo COLA...\n";
    Sleep(500);

    cout << "Configurando entorno...\n";
    Sleep(500);

    color(10);
    cout << "\nSistema listo!\n";
    Sleep(800);

    color(7);
    cout << "\nSistema listo. Presione una tecla...";
    (void)_getch();
}

void pantallacargaPedidos(cola& q) {
    system("cls");

    color(14);
    cout << "========================================\n";
    cout << "      ACCEDIENDO A LOS PEDIDOS" << "\n";
    cout << "========================================\n\n";

    color(11);
    cout << "Cargando";

    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(300);
    }

    cout << "\n\n";

    color(10);
    cout << "[";

    for (int i = 0; i < 20; i++) {
                
        if (i == 5) {
            cargarPedidos(q);
        }

        cout << char(219);
        Sleep(70);
    }

    cout << "]";

    Sleep(400);
    color(7);
}

void pantallacargaIngresos(nodoPila*& p) {
    system("cls");

    color(14);
    cout << "========================================\n";
    cout << "   ACCEDIENDO A INGRESOS DE PRODUCTOS " << "\n";
    cout << "========================================\n\n";

    color(11);
    cout << "Cargando";

    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(300);
    }

    cout << "\n\n";

    color(10);
    cout << "[";
    for (int i = 0; i < 20; i++) {
        if (i == 5) {
            cargarIngreso(p);
        }
        
        cout << char(219);
        Sleep(70);
    }
    cout << "]";

    Sleep(400);
    color(7);
}
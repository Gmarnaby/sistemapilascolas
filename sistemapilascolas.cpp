#include <iostream>
#include<conio.h>
#include<cstdlib>
#include<string>
#include <windows.h>

using namespace std;

struct nodoPila {
    int dato;
    nodoPila* siguientePila;
};

struct pedidos {
    int correlativo;
    string producto;
    int cantidad;
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
void modulopila();
void modulocola();
void push();
void pop();
int encolar(cola& q);
int desencolar(cola& q);
void portada();
void color(int c);
void cargando();
void mostrarpila();
void modificarpila();
void buscarpila();
void buscarcola(cola q, int corre);
void modificarcola();
void mostrarcola(cola q);
void pantallacarga(string modulo);

int correlativoPedidos = 1;

int main()
{
    int op;
    portada();
    cargando();

    do {
        op = menuprincipal();
        switch (op) {
        case 0:
            pantallacarga("MODULO PILA");
            modulopila();
            break;

        case 1:
            pantallacarga("MODULO COLA");
            modulocola();
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
void modulopila() {
    int op;

    do {
        op = submenu("MODULO PILA");

        switch (op) {
        case 0: push(); break;
        case 1: mostrarpila(); break;
        case 2: modificarpila(); break;
        case 3: buscarpila(); break;
        case 4: pop(); break;
        }

    } while (op != 5);

}

//----colas----
void modulocola() {
    cola q;
    q.primero = NULL;
    q.ultimo = NULL;
    
    int op;
    char res;
    int correEncolar, correBuscar;
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
                    cout << "\n\nDESPACHARAS EL PEDIDO " << q.primero->pedido.correlativo << "\nQUIERES CONTINUAR?  (Y/N) "; cin >> res;
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
                cout << "\n\nINGRESE EL NUMERO DE PEDIDO QUE QUIERA BUSCAR: "; cin >> correBuscar;
                buscarcola(q, correBuscar);
            }
            else cout << "\n\nNO EXISTEN PEDIDOS A BUSCAR VUELVE MAS TARDE :D";
            break;

        case 4:
            modificarcola();
            break;

        }
        cout << endl;
        system("pause");
        system("cls");

    } while (op != 5);
}

//----FUNCIONES----

void push() {



}

void pop() {



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

    return aux->pedido.correlativo;
}

int desencolar(cola& q) {
    int corre;
    nodoCola* aux;

    aux = q.primero;
    corre = aux->pedido.correlativo;
    q.primero = q.primero->siguienteCola;
    delete aux;

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

void mostrarpila() {
    
}

void modificarpila() {


}

void buscarpila() {


}

void modificarcola() {


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

void pantallacarga(string modulo) {
    system("cls");

    color(14);
    cout << "========================================\n";
    cout << "      ACCEDIENDO A " << modulo << "\n";
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
        cout << char(219);
        Sleep(70);
    }
    cout << "]";

    Sleep(400);
    color(7);
}
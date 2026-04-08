#include <iostream>
#include<conio.h>
#include <windows.h>

using namespace std;

int menuprincipal();
int submenu();
void modulopila();
void modulocola();
void push();
void pop();
void encolar();
void desencolar();
void portada();
void color(int c);
void cargando();
void mostrarpila();
void modificarpila();
void buscarpila();
void buscarcola();
void modificarcola();
void mostrarcola();
void pantallacarga(string modulo);


int main()
{
    portada();
    cargando();
    menuprincipal();

    int op;

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
            cout << "   >>   [ MOSTRAR DATOS ]\n";
        }
        else {
            color(8);
            cout << "        Mostrar datos\n";
        }

        if (opcion == 2) {
            color(10);
            cout << "   >>   [ MODIFICAR ]\n";
        }
        else {
            color(8);
            cout << "        Modificar\n";
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
            cout << "   >>   [ ELIMINAR ]\n";
        }
        else {
            color(8);
            cout << "        Eliminar\n";
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
    int op;

    do {
        op = submenu("MODULO COLA");
        switch (op) {
        case 0:
            encolar();
            break;
        case 1:
            mostrarcola();
            break;
        case 2:
            modificarcola();
            break;
        case 3:
            buscarcola();
            break;
        case 4:
            desencolar();
        }


    } while (op != 5);

}

//----FUNCIONES----

void push() {



}

void pop() {



}

void encolar() {



}

void desencolar() {



}

void mostrarpila() {



}

void modificarpila() {


}

void buscarpila() {


}

void mostrarcola() {


}

void modificarcola() {


}
void buscarcola() {


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
    cout << "  > Miguel Angel Santos García Velásquez\n";
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
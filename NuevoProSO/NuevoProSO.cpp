// NuevoProSO.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "BitacoraP.h";
#include "AlmacenDatos.h";
#include "PrioridadProceso.h";
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define limite 5

#include <chrono>
#include <thread>
using namespace std::chrono_literals;
using namespace std;
AlmacenDatos procesos = AlmacenDatos();

int main() {
    int op;
    bool exit;
    do {
        op = 0;
        exit = false;
        cout << "*****BIENVENIDO AL SIMULADOR PCB***** " << endl;
        cout << "1--> LEER ARCHIVO " << endl;
        cout << "2--> ATENDER PROCESOS " << endl;
        cout << "3--> IMPRIMIR BITACORA " << endl;
        cout << "4--> SALIR " << endl;
        cout << "INGRESE LA OPCIÓN QUE DESEE " << endl;
        cin >> op;

        switch (op) {

        case 1:
            procesos.LeerFichero();
            break;
        case 2:
            system("cls");
            procesos.EjecutarProcesos();
            break;
        case 3:
          
            procesos.mostrarProcesos();
            break;
        case 4:
            exit = true;
         
        default:
            cout << endl << "Ingreso una opcion incorrecta" << endl<<endl;
         
        }
    } while (!exit);
    return 0;

}


    

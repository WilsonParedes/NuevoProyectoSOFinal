#pragma once..
#include "BitacoraP.h";
#include<vector>;
#include<fstream>;
#include<iostream>;
#include<iomanip>;
#include<stdlib.h>;
#include<cstring>;
#include<istream>;
#include<string>;
#include <iostream>
#include<windows.h>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

class AlmacenDatos
{
public:
	ifstream l, car1;
	ofstream in, car;
	vector<BitacoraP> almacen;
	vector<BitacoraP> ContenedorTXT;
	
public:
	AlmacenDatos() {

	};

	void agregarProceso(BitacoraP bitacora) {
		almacen.push_back(bitacora);
	}

	void agregarProcesoaContenedorTXT(BitacoraP bitacora) {
		ContenedorTXT.push_back(bitacora);
	}

	void mostrarProcesos() {
		cout << "No. Proceso\t | Tema\t\t\t | Prioridad\t | Paternidad | Tiempo de Ejecución\t | Estado del Proceso ";
		cout << endl;
		for (int i = 0; i < almacen.size(); i++) {
			cout << almacen[i].toString();
			cout << endl;
		}
	}

	void mostrarProcesosContenedroTXT() {
		system("cls");
		cout << "No. Proceso\t | Tema\t\t\t | Prioridad\t | Paternidad\t | Tiempo de Ejecución\t | Estado del Proceso ";
		cout << endl;
		for (int i = 0; i < ContenedorTXT.size(); i++) {
			cout << ContenedorTXT[i].toString();
			cout << endl;
			
		}
		cout << endl;
	}


	void LeerFichero() {// Procedimiento para imprimir el inventario en pantalla.
			string temp;
			string temNoProceso, tempTema, tempEstado,tempPaternidad,tempTiempo;
			string pp;
			string leer; // se declaran 2 variables una para abrir el fichero y otra para almacenar la información que se encuentra en el fichero
			int cont = 0;
			l.open("Inventario.txt", ios::in);//se abre el fichero
			if (l.fail()) {// muestra error en caso el fichero este dañado o no exista
				cout << "El archivo no se pudo abrir, puede que este dañado";
				exit(1);
			}// fin de error
			system("cls");
			
			while (!l.eof()) {//lectura del fichero
				cont = 0;
				
				getline(l, leer);// almacena la información del fichero en la variable leer 
				//cout << leer << "\n";// se imprime en pantalla, guarda el formato exacto de como se encuentra en el fichero.


				stringstream input_stringstream(leer);

				while (getline(input_stringstream,temp,'|')) {
				
					if (cont == 0) {
						temNoProceso = temp;
					}if (cont == 1) {
						tempTema = temp;
					}if (cont == 2) {
						pp = temp;
					}if (cont == 3) {
						tempPaternidad = temp;
					}if (cont == 4) {
						tempTiempo = temp;
					}

					cont++;
				}
				agregarProcesoaContenedorTXT(BitacoraP::BitacoraP(temNoProceso, tempTema, pp, tempPaternidad, tempTiempo,"NUEVO"));
			}l.close();	// fin de la lectura del fichero	


			mostrarProcesosContenedroTXT(); 
			int casteo,casteo2, k = 0;
			bool salida = false;
			string temporal;
			do {
				for (int i = 0; i < ContenedorTXT.size(); i++) {
					salida = false;
					for (int j = 0; j < 5; j++) {
						if (j == 4) {
							temporal = ContenedorTXT[i].getTiempoEjecucion();
							casteo = atoi(temporal.c_str());
							if (casteo <= 0) {

							}
							else {
								if (ContenedorTXT[i].getEstadoProceso()._Equal("NUEVO")) {
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(),"NUEVO"));
									
								}
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(),"LISTO"));
								k = 0;
								if (casteo > 20) {
									salida = true;
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(),"EJECUCION"));
									casteo2 = atoi(temporal.c_str()) - 20;
									ContenedorTXT[i].setTiempoEjecucion(to_string(casteo2));
									ContenedorTXT[i].setEstadoProceso("EJECUCION");
									cout << endl << "se esta ejecucantdo el proceso : " << ContenedorTXT[i].getNoProceso() << " ";
									for (k = 0; k < 20; k++) {
										cout << (k + 1) << " ";
										Sleep(1000);
									}
									cout << endl << "Proceso Bloqueado, Tiempo restante : " << ContenedorTXT[i].getTiempoEjecucion() << endl;
									cout << endl;
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(),"BLOQUEADO"));
								}

								if (casteo <= 0) {
									/*ContenedorTXT[i].setTiempoEjecucion("0");
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), PrioridadProceso::EJECUCION, ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion()));*/
								}
								if (casteo <= 20) {
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(),"EJECUCION"));
									casteo2 = atoi(temporal.c_str() - atoi(temporal.c_str()));
									ContenedorTXT[i].setTiempoEjecucion(to_string(casteo2));

									cout << endl << "se esta ejecucantdo el proceso : " << ContenedorTXT[i].getNoProceso() << " ";
									for (k = 0; k < casteo; k++) {
										cout << (k + 1) << " ";
										Sleep(1000);
									}
									cout << endl << "Proceso Terminado : " << ContenedorTXT[i].getTiempoEjecucion() << endl;
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(),"TERMINADO"));
									ContenedorTXT[i].setEstadoProceso("TERMINADO");
								}
							
							}
							
						}
					}

				}
			} while (salida);
			mostrarProcesos();
		}
};


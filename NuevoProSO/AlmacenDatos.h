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
#include <vector>


using namespace std;

class AlmacenDatos
{
public:
	ifstream l, car1;
	ofstream in, car;
	vector<BitacoraP> almacen;
	vector<BitacoraP> ContenedorTXT;
	vector<BitacoraP> ContenedorTXTAuxiliar;
	
public:
	AlmacenDatos() {

	};

	void agregarProceso(BitacoraP bitacora) {
		almacen.push_back(bitacora);
		
	}

	void agregarProcesoAuxiliar(BitacoraP bitacora) {
		
		ContenedorTXTAuxiliar.push_back(bitacora);
	}

	void agregarProcesoaContenedorTXT(BitacoraP bitacora) {
		ContenedorTXT.push_back(bitacora);
	}


	void elminarProcesosContenedorTXTAuxiliar() {
		ContenedorTXTAuxiliar.erase(ContenedorTXTAuxiliar.begin() +0);
	}

	void mostrarProcesos() {
		system("cls");
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
	void mostrarProcesosContenedroTXTauxiliar() {
		
		cout << "No. Proceso\t | Tema\t\t\t | Prioridad\t | Paternidad\t | Tiempo de Ejecución\t | Estado del Proceso ";
		cout << endl;
		try {
			for (int i = 0; i < ContenedorTXTAuxiliar.size(); i++) {
				cout << ContenedorTXTAuxiliar[i].toString();
				cout << endl;

			}
			cout << endl;
		}
		catch (exception e) {
			cout << "CPU sin Procesos " << endl;
		}
	}


	void OrdenarArrayIngenieroPorPrioridad() {
		string temp, temp1;
		int contenedor = 0;
		int contendor1 = 0;

		/*Metodo burbuja*/
		for (int j = 0; j < ContenedorTXT.size() - 1; j++) {

			for (int i = 0; i < ContenedorTXT.size() - 1; i++) {
				contenedor = atoi(ContenedorTXT[i].getPrioridadProceso().c_str());
				contendor1 = atoi(ContenedorTXT[i + 1].getPrioridadProceso().c_str());
				if (contenedor > contendor1) {
					string tempProceso = ContenedorTXT[i].getNoProceso();
					string tempTema = ContenedorTXT[i].getTemaEjecucion();
					string tempPP = ContenedorTXT[i].getPrioridadProceso();
					string tempPaternidad = ContenedorTXT[i].getPaternidad();
					string tempTiempo = ContenedorTXT[i].getTiempoEjecucion();
					string tempEstado = ContenedorTXT[i].getEstadoProceso();
					ContenedorTXT[i] = ContenedorTXT[i + 1];
					ContenedorTXT[i + 1] = BitacoraP::BitacoraP(tempProceso, tempTema, tempPP, tempPaternidad, tempTiempo, tempEstado);
				}
			}
		}
		
		mostrarProcesosContenedroTXT();
	}

	void crearHijosalosProcesos() {
		int contenedor = 0;
		int tiempo=0;
		int tiempohijos = 0;
		int contador = 0;
		for (int i = 0; i < ContenedorTXT.size();i++) {
			contador = 0;
			contenedor = (i+1)+1;
			tiempo = atoi(ContenedorTXT[i].getTiempoEjecucion().c_str());
			agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(),ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getEstadoProceso()));
			for (int j = 0; j < contenedor; j++) {
				tiempohijos = tiempo / contenedor;
				contador += 1;
				agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), " -> HIJO " +to_string(contador), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), to_string(tiempohijos), "NUEVO"));
				agregarProcesoAuxiliar(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), " -> HIJO " + to_string(contador), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), to_string(tiempohijos), "NUEVO"));
			}
		}

		mostrarProcesos();
		mostrarProcesosContenedroTXTauxiliar();
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

			cout << "Lectura del TXT cargada con éxito" << endl;
			/*mostrarProcesosContenedroTXT();*/
			OrdenarArrayIngenieroPorPrioridad();
			crearHijosalosProcesos();
		}

		void EjecutarProcesos() {
			mostrarProcesosContenedroTXT();
			int casteo, casteo2, k = 0;
			bool salida = false;
			int prioridad = 0;
			
			string temporal;
			do {
				salida = false;
				for (int i = 0; i < ContenedorTXT.size(); i++) {
					
					for (int j = 0; j < 5; j++) {
						if (j == 4) {
							temporal = ContenedorTXT[i].getTiempoEjecucion(); /*Almacena el tiempo del proceso*/
							casteo = atoi(temporal.c_str());
							if (casteo <= 0) {

							}
							else {
								/*if (ContenedorTXT[i].getEstadoProceso()._Equal("NUEVO")) {
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "NUEVO"));

								}*/
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "LISTO"));
								k = 0;
								if (casteo > 20) {
									salida = true;
									int contador =0;
									int tiempohijos = 0;
									int tiemporestantehijo = 0;
									casteo2 = atoi(temporal.c_str() - 20);//tiempo restante
									ContenedorTXT[i].setTiempoEjecucion(to_string(casteo2));//se pasa el tiempo por parametro
									prioridad = (atoi(ContenedorTXT[i].getPrioridadProceso().c_str()) + 1) + 1;
									cout << endl << "El proceso principal es : " << ContenedorTXT[i].getNoProceso() << endl;
									/*PrioriodadProcesoLargo(casteo2, temporal, prioridad);/*Realiza el proceso corto
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "EJECUCION"));
									ProcesoParaEliminarHijos(prioridad);
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "TERMINADO"));*/

									for (int l = 0; l < prioridad; l++) {
										if (tiemporestantehijo >=20) {
											casteo2 = atoi(temporal.c_str()) - tiemporestantehijo;
											ContenedorTXT[i].setTiempoEjecucion(to_string(casteo2));
											ContenedorTXT[i].setEstadoProceso("EJECUCION");
											cout << endl << "Proceso Bloqueado, Tiempo restante : " << to_string(casteo2) << endl;
											cout << endl;
											agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "BLOQUEADO"));
											agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "BLOQUEADO"));
											ProcesoParaEliminarHijos(contador);
											for (int k = 0; k < (prioridad - contador); k++) {
												agregarProcesoAuxiliar(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[0].getNoProceso(), ContenedorTXTAuxiliar[0].getTemaEjecucion(), ContenedorTXTAuxiliar[0].getPrioridadProceso(), ContenedorTXTAuxiliar[0].getPaternidad(), ContenedorTXTAuxiliar[0].getTiempoEjecucion(), "BLOQUEADO"));
												ProcesoParaEliminarHijos(1);
											}
											
										}
										else {
											contador++;
											agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "LISTO"));
											cout << endl << "se esta ejecucantdo el proceso hijo " + to_string(contador) + " : --> ";

											tiempohijos = atoi(ContenedorTXTAuxiliar[l].getTiempoEjecucion().c_str());
											agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "EJECUCION"));

											for (int k = 0; k < tiempohijos; k++) {
												cout << (k + 1) << " ";
												Sleep(1000);
											}
											cout << endl << "Proceso hijo " + to_string(contador) + " Terminado : " << ContenedorTXTAuxiliar[l].getTiempoEjecucion() << endl;
											agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "TERMINADO"));
											ContenedorTXTAuxiliar[l].setEstadoProceso("TERMINADO");

											tiemporestantehijo += tiempohijos;
											
										}
									}
									
									/*casteo2 = atoi(temporal.c_str()) - 20;
									ContenedorTXT[i].setTiempoEjecucion(to_string(casteo2));
									ContenedorTXT[i].setEstadoProceso("EJECUCION");
									cout << endl << "se esta ejecucantdo el proceso : " << ContenedorTXT[i].getNoProceso() << " ";
									for (k = 0; k < 20; k++) {
										cout << (k + 1) << " ";
										Sleep(1000);
									}
									cout << endl << "Proceso Bloqueado, Tiempo restante : " << ContenedorTXT[i].getTiempoEjecucion() << endl;
									cout << endl;
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "BLOQUEADO"));
									*/								
								}else{
									if (casteo <= 20)
									casteo2 = atoi(temporal.c_str() - atoi(temporal.c_str()));//tiempo restante
									ContenedorTXT[i].setTiempoEjecucion(to_string(casteo2));//se pasa el tiempo por parametro
									prioridad = (atoi(ContenedorTXT[i].getPrioridadProceso().c_str()) + 1) + 1;
									cout << endl << "El proceso principal es : " << ContenedorTXT[i].getNoProceso() << endl;
									PrioriodadProcesoCorto(casteo2, temporal, prioridad);/*Realiza el proceso corto*/
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "EJECUCION"));
									agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), "TERMINADO"));
									ProcesoParaEliminarHijos(prioridad);
								}
								
							}

						}
					}

				}
			} while (salida);
		}

		void PrioriodadProcesoCorto(int casteo2,string temporal, int prioridad) {
			int tiempohijos = 0;
			int contador = 0;
			try {
				for (int l = 0; l < prioridad; l++) {
					contador++;
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "LISTO"));
					cout << endl << "se esta ejecucantdo el proceso hijo " + to_string(contador) + " : --> ";
					tiempohijos = atoi(ContenedorTXTAuxiliar[l].getTiempoEjecucion().c_str());
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "EJECUCION"));
					for (int k = 0; k < tiempohijos; k++) {
						cout << (k + 1) << " ";
						Sleep(1000);
					}
					cout << endl << "Proceso hijo " + to_string(contador) + " Terminado : " << ContenedorTXTAuxiliar[l].getTiempoEjecucion() << endl;
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "TERMINADO"));
					ContenedorTXTAuxiliar[l].setEstadoProceso("TERMINADO");

				}
			}
			catch (exception e) {

			}
			
			
		}


		void PrioriodadProcesoLargo(int casteo2, string temporal, int prioridad) {
			int tiempohijos = 0;
			int contador = 0;
			try {
				for (int l = 0; l < prioridad; l++) {
					contador++;
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "LISTO"));
					cout << endl << "se esta ejecucantdo el proceso hijo " + to_string(contador) + " : --> ";
					tiempohijos = atoi(ContenedorTXTAuxiliar[l].getTiempoEjecucion().c_str());
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "EJECUCION"));
					for (int k = 0; k < tiempohijos; k++) {
						cout << (k + 1) << " ";
						Sleep(1000);
					}
					cout << endl << "Proceso hijo " + to_string(contador) + " Terminado : " << ContenedorTXTAuxiliar[l].getTiempoEjecucion() << endl;
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), "TERMINADO"));
					ContenedorTXTAuxiliar[l].setEstadoProceso("TERMINADO");

				}
				
			}
			catch (exception e) {
				cout << endl;
			}

		}

		void ProcesoParaEliminarHijos(int prioridad) {
			
			try {
				/*For que elimina jhijos*/
				for (int l = 0; l < prioridad; l++) {
					elminarProcesosContenedorTXTAuxiliar();
				}
				cout << endl;
			}
			catch (exception e) {
				cout << endl << "YA NO EXISTEN MAS PROCESOS DENTRO DEL CPU" << endl;
			}
		}

};


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
		cout << "No. Proceso\t | Tema\t\t\t | Prioridad\t | Paternidad\t | T. de Ejecución\t | T. Pendiente\t | Estado del Proceso ";
		cout << endl;
		for (int i = 0; i < almacen.size(); i++) {
			cout << almacen[i].toString();
			cout << endl;
		}
		cout << endl;
	}

	void mostrarProcesosContenedroTXT() {
		system("cls");
		cout <<"No. Proceso\t | Tema\t\t\t | Prioridad\t  | Paternidad\t | T. de Ejecución\t | T. Pendiente\t | Estado del Proceso ";
		cout << endl;
		for (int i = 0; i < ContenedorTXT.size(); i++) {
			cout << ContenedorTXT[i].toString();
			cout << endl;
			
		}
		cout << endl;

		
	}
	void mostrarProcesosContenedroTXTauxiliar() {
		
		cout << "No. Proceso\t | Tema\t\t\t | Prioridad\t   | Paternidad\t | Tiempo de Ejecución\t | Estado del Proceso ";
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
					ContenedorTXT[i + 1] = BitacoraP::BitacoraP(tempProceso, tempTema, tempPP, tempPaternidad, tempTiempo,tempTiempo,tempEstado,0);
				}
			}
		}
		
	}

	void crearHijosalosProcesos() {
		int contenedor = 0;
		int tiempo=0;
		int tiempohijos = 0;
		int contador = 0;
		for (int i = 0; i < ContenedorTXT.size();i++) {
			contador = 0;
			contenedor = (i+1)+1;
			ContenedorTXT[i].setHijoPendiente(contenedor);
			tiempo = atoi(ContenedorTXT[i].getTiempoEjecucion().c_str());
			agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(),ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getEstadoProceso(),contenedor));
			for (int j = 0; j < contenedor; j++) {
				tiempohijos = tiempo / contenedor;
				contador += 1;
				agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), " -> HIJO " +to_string(contador), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), to_string(tiempohijos), to_string(tiempohijos), "NUEVO", contenedor));
				agregarProcesoAuxiliar(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), " -> HIJO " + to_string(contador), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), to_string(tiempohijos), to_string(tiempohijos), "NUEVO", contenedor));
			}
		}

		mostrarProcesos();
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
				cout << endl << "El archivo no se pudo abrir, puede que este danado o no exista, compruebe que en la carpeta se encuentre el archivo PCB.txt"<< endl;
				
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
				agregarProcesoaContenedorTXT(BitacoraP::BitacoraP(temNoProceso, tempTema, pp, tempPaternidad, tempTiempo, tempTiempo,"NUEVO",0));
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
		int tiempoacumulado = 0;
		int tiemporestante = 0;
		int hijopendiente = 0;
		string temporal;
		do {
			salida = false;
			for (int i = 0; i < ContenedorTXT.size(); i++) {
				temporal = ContenedorTXT[i].getTiempoEjecucion(); /*Almacena el tiempo del proceso*/
				casteo = atoi(temporal.c_str());
				if (casteo <= 0) {
				}
				else {
					if ((atoi(ContenedorTXT[i].getTiempoPendiente().c_str())) != 0) {
						agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getTiempoEjecucion(), "LISTO", ContenedorTXT[i].getHijoPendiente()));
						ContenedorTXT[i].setEstadoProceso("LISTO");
					}

					k = 0;
					if (casteo > 20) {
						int contador = 0;
						int tiempohijos = 0;
						int tiemporestantehijo = 0;
						mostrarProcesosContenedroTXT();
						cout << "Cargando Proceso al CPU" << endl;
						Sleep(1500);
						ContenedorTXT[i].setEstadoProceso("EJECUCION");
						mostrarProcesosContenedroTXT();
						Sleep(1500);
						casteo2 = atoi(temporal.c_str() - 20);//tiempo restante
						ContenedorTXT[i].setTiempoPendiente(to_string(casteo2));//se pasa el tiempo por parametro
						//prioridad = (atoi(ContenedorTXT[i].getPrioridadProceso().c_str()) + 1) + 1;
						prioridad = ContenedorTXT[i].getHijoPendiente();
						cout << endl << "El proceso principal es : " << ContenedorTXT[i].getNoProceso() << " tiempo requerido en CPU: " << ContenedorTXT[i].getTiempoEjecucion() << endl;
						for (int l = 0; l < prioridad; l++) {
							if (tiemporestantehijo >= 20) {
								casteo2 = atoi(temporal.c_str()) - tiemporestantehijo;
								ContenedorTXT[i].setTiempoPendiente(to_string(casteo2));
								ContenedorTXT[i].setEstadoProceso("EJECUCION");
								cout << endl << "Proceso Bloqueado, Tiempo restante : " << to_string(casteo2) << endl;
								cout << endl;
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "BLOQUEADO", hijopendiente));
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getTiempoPendiente(), "BLOQUEADO", hijopendiente));
								ProcesoParaEliminarHijos(contador);
								for (int k = 0; k < (prioridad - contador); k++) {
									agregarProcesoAuxiliar(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[0].getNoProceso(), ContenedorTXTAuxiliar[0].getTemaEjecucion(), ContenedorTXTAuxiliar[0].getPrioridadProceso(), ContenedorTXTAuxiliar[0].getPaternidad(), ContenedorTXTAuxiliar[0].getTiempoEjecucion(), ContenedorTXTAuxiliar[0].getTiempoPendiente(), "BLOQUEADO", ContenedorTXTAuxiliar[0].getHijoPendiente()));
									ProcesoParaEliminarHijos(1);
								}
								ContenedorTXT[i].setEstadoProceso("BLOQUEADO");

								if ((ContenedorTXTAuxiliar.size()) == 0) {
								}
								else {
									salida = true;
								}
							}
							else {
								contador++;
								hijopendiente = prioridad - contador;
								ContenedorTXT[i].setHijoPendiente(hijopendiente);
								ContenedorTXTAuxiliar[l].setHijoPendiente(hijopendiente);
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "LISTO", ContenedorTXTAuxiliar[l].getHijoPendiente()));
								cout << endl << "se esta ejecucantdo el proceso hijo " + to_string(contador) + " : --> ";
								tiempohijos = atoi(ContenedorTXTAuxiliar[l].getTiempoEjecucion().c_str());
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "EJECUCION", ContenedorTXTAuxiliar[l].getHijoPendiente()));
								for (int k = 0; k < tiempohijos; k++) {
									cout << (k + 1) << " ";
									Sleep(1000);
								}
								cout << endl << "Proceso hijo " + to_string(contador) + " Terminado : " << ContenedorTXTAuxiliar[l].getTiempoEjecucion() << endl;
								cout << endl;
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "TERMINADO", ContenedorTXTAuxiliar[l].getHijoPendiente()));
								ContenedorTXTAuxiliar[l].setEstadoProceso("TERMINADO");
								ContenedorTXT[i].setEstadoProceso("TERMINADO");
								tiemporestantehijo += tiempohijos;
							}
						}
					}
					else {
						if (casteo <= 20) {
							if ((atoi(ContenedorTXT[i].getTiempoPendiente().c_str()) == 0)) {
							}
							else {
								mostrarProcesosContenedroTXT();
								cout << "Cargando Proceso al CPU" << endl;
								Sleep(1500);
								ContenedorTXT[i].setEstadoProceso("EJECUCION");
								mostrarProcesosContenedroTXT();
								Sleep(1500);
								casteo2 = atoi(temporal.c_str() - atoi(temporal.c_str()));//tiempo restante
								ContenedorTXT[i].setTiempoPendiente(to_string(casteo2));//se pasa el tiempo por parametro

								//prioridad = (atoi(ContenedorTXT[i].getPrioridadProceso().c_str()) + 1) + 1;
								prioridad = ContenedorTXT[i].getHijoPendiente();
								cout << endl << "El proceso principal es : " << ContenedorTXT[i].getNoProceso() << " tiempo requerido en CPU: " << ContenedorTXT[i].getTiempoEjecucion() << endl;
								PrioriodadProcesoCorto(casteo2, temporal, prioridad);/*Realiza el proceso corto*/
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getTiempoPendiente(), "EJECUCION", 0));
								agregarProceso(BitacoraP::BitacoraP(ContenedorTXT[i].getNoProceso(), ContenedorTXT[i].getTemaEjecucion(), ContenedorTXT[i].getPrioridadProceso(), ContenedorTXT[i].getPaternidad(), ContenedorTXT[i].getTiempoEjecucion(), ContenedorTXT[i].getTiempoPendiente(), "TERMINADO", 0));
								ContenedorTXT[i].setHijoPendiente(0);
								ContenedorTXT[i].setEstadoProceso("TERMINADO");
								ProcesoParaEliminarHijos(prioridad);
							}
						}
					}
				}
			}
		} while (salida);

		/*Actualizar tabla con todos los procesos terminados*/
		for (int i = 0; i < ContenedorTXT.size(); i++) {
			ContenedorTXT[i].setEstadoProceso("TERMINADO");
		}
		mostrarProcesosContenedroTXT();
			
		}

		void PrioriodadProcesoCorto(int casteo2,string temporal, int prioridad) {
			int tiempohijos = 0;
			int contador = 0;
			int hijospendientes = 0;
			try {
				
				for (int l = 0; l < prioridad; l++) {
					contador++;
					hijospendientes = prioridad - contador;
					ContenedorTXTAuxiliar[l].setTiempoPendiente(to_string(casteo2));
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "LISTO", hijospendientes));
					cout << endl << "se esta ejecucantdo el proceso hijo " + to_string(contador) + " : --> ";
					tiempohijos = atoi(ContenedorTXTAuxiliar[l].getTiempoEjecucion().c_str());
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "EJECUCION", hijospendientes));
					for (int k = 0; k < tiempohijos; k++) {
						cout << (k + 1) << " ";
						Sleep(1000);
					}
					cout << endl << "Proceso hijo " + to_string(contador) + " Terminado : " << ContenedorTXTAuxiliar[l].getTiempoPendiente() << endl;
					agregarProceso(BitacoraP::BitacoraP(ContenedorTXTAuxiliar[l].getNoProceso(), ContenedorTXTAuxiliar[l].getTemaEjecucion(), ContenedorTXTAuxiliar[l].getPrioridadProceso(), ContenedorTXTAuxiliar[l].getPaternidad(), ContenedorTXTAuxiliar[l].getTiempoEjecucion(), ContenedorTXTAuxiliar[l].getTiempoPendiente(), "TERMINADO", hijospendientes));
					ContenedorTXTAuxiliar[l].setEstadoProceso("TERMINADO");

				}
			}
			catch (exception e) {

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

		void Deley(int tiempo) {

		}
};


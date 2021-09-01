#pragma once

#include <iostream>
#include "PrioridadProceso.h"


#define limite 5
using namespace std;

class BitacoraP {
private:
    string NoProceso;
    string TemaEjecucion;
    PrioridadProceso pp;
    string paternidad;
    string tiempoejecución;

public:

    BitacoraP(string NoProceso, string TemaEjecucion, PrioridadProceso pp, string paternidad, string tiempoejecucion) {
        this->NoProceso = NoProceso;
        this->TemaEjecucion = TemaEjecucion;
        this->pp = pp;
        this->paternidad = paternidad;
        this->tiempoejecución = tiempoejecucion;
    }

    void setNoProceso(string NoProceso) {
        this->NoProceso = NoProceso;
    }
    void setTemaEjecucion(string TemaEjecucion) {
        this->TemaEjecucion = TemaEjecucion;
    }
    void setPrioridadProceso(PrioridadProceso pp) {

        this->pp = pp;
    }
    void setPaternidad(string paternidad) {
        this->paternidad = paternidad;
    }
    void setTiempoEjecucion(string tiempoejecución) {
        this->tiempoejecución = tiempoejecución;
    }

    string getNoProceso() {
        return NoProceso;
    }
    string getTemaEjecucion() {
        return TemaEjecucion;
    }
    PrioridadProceso getPrioridadProceso() {
        return pp;
    }
    string getPaternidad() {
        return paternidad;
    }
    string getTiempoEjecucion() {
        return tiempoejecución;
    }

    string toString() {
        return NoProceso + "\t\t" + " | " + TemaEjecucion + "\t\t" + " | " + paternidad + "\t\t" + " | " + tiempoejecución;
    }



};
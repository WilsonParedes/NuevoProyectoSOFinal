#pragma once

#include <iostream>
#include "PrioridadProceso.h"


#define limite 5
using namespace std;

class BitacoraP {
private:
    string NoProceso;
    string TemaEjecucion;
    string pp;
    string paternidad;
    string tiempoejecuci�n;
    string estadoproceso;

public:

    BitacoraP(string NoProceso, string TemaEjecucion, string pp, string paternidad, string tiempoejecucion, string estadoproceso) {
        this->NoProceso = NoProceso;
        this->TemaEjecucion = TemaEjecucion;
        this->pp = pp;
        this->paternidad = paternidad;
        this->tiempoejecuci�n = tiempoejecucion;
        this->estadoproceso = estadoproceso;
    }

    void setNoProceso(string NoProceso) {
        this->NoProceso = NoProceso;
    }
    void setTemaEjecucion(string TemaEjecucion) {
        this->TemaEjecucion = TemaEjecucion;
    }
    void setPrioridadProceso(string pp) {

        this->pp = pp;
    }
    void setPaternidad(string paternidad) {
        this->paternidad = paternidad;
    }
    void setTiempoEjecucion(string tiempoejecuci�n) {
        this->tiempoejecuci�n = tiempoejecuci�n;
    }

    void setEstadoProceso(string estadoproceso) {
        this->estadoproceso = estadoproceso;
    }

    string getNoProceso() {
        return NoProceso;
    }
    string getTemaEjecucion() {
        return TemaEjecucion;
    }
    string getPrioridadProceso() {
        return pp;
    }
    string getPaternidad() {
        return paternidad;
    }
    string getTiempoEjecucion() {
        return tiempoejecuci�n;
    }
    string getEstadoProceso() {
        return estadoproceso;
    }
    string toString() {
        return NoProceso + "\t\t" + " | " + TemaEjecucion + "\t\t" + " | " + pp + "\t\t" + " | " + paternidad +"\t\t" + " | " + tiempoejecuci�n + "\t\t\t" + " | "+ estadoproceso;
    }



};
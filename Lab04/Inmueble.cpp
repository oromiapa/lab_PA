#include <iostream>

#include "Inmueble.h"
#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Administracion.h"

Inmueble::Inmueble(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid) 
    : direccion(direccion), superficie(superficie), anioConstruccion(anioConstruccion), numeroID(numid) {}

Inmueble::~Inmueble() {}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




DtDireccion Inmueble::getDireccion() {
    return this->direccion;
}

float Inmueble::getSuperficie() {
    return this->superficie;
}

DtFecha Inmueble::getAnioConstruccion() {
    return this->anioConstruccion;
}

int Inmueble::getNumeroID() {
    return this->numeroID;
}

Propietario* Inmueble::getDuenio() const {
    return this->duenio;
}

DtFecha Inmueble::getFechaAdministracion() const {
    if (this->administracionAsociada != nullptr) {
        return this->administracionAsociada->getFechaInicio(); 
    }
    return DtFecha(0, 0, 2026); 
}

Administracion* Inmueble::getAdministracion() const {
    return this->administracionAsociada;
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




void Inmueble::setDireccion(const DtDireccion& direccion) {
    this->direccion = direccion;
}

void Inmueble::setSuperficie(float superficie) {
    this->superficie = superficie;
}

void Inmueble::setAnioConstruccion(const DtFecha& anioConstruccion) {
    this->anioConstruccion = anioConstruccion;
}

void Inmueble::setNumeroID(int numeroID) {
    this->numeroID = numeroID;
}

void Inmueble::setDuenio(Propietario* p) {
    this->duenio = p;
}

void Inmueble::setAdministracion(Administracion* admin) {
    this->administracionAsociada = admin;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Inmueble::altaPublicacion(const int numid, const char* text, float price, bool tipopub) {
    if (this->administracionAsociada == nullptr) {
        throw std::runtime_error("Error: El inmueble no posee una administración activa para ser publicado.");
    }

    this->administracionAsociada->altaPublicacion(numid, text, price, tipopub);
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Inmueble::borrarAdministracion() {
    std::cout << "[DEBUG] borrarAdministracion inicio\n"; std::cout.flush();
    if (this->administracionAsociada != nullptr) {
        std::cout << "[DEBUG] desvincularInmueble\n"; std::cout.flush();
        this->administracionAsociada->desvincularInmueble(this->numeroID);
        std::cout << "[DEBUG] borrarPublicacion\n"; std::cout.flush();
        this->administracionAsociada->borrarPublicacion();
        std::cout << "[DEBUG] delete admin\n"; std::cout.flush();
        delete this->administracionAsociada;
        this->administracionAsociada = nullptr;
        std::cout << "[DEBUG] borrarAdministracion fin\n"; std::cout.flush();
    }
}


void Inmueble::removerPropietario(int numid) {
    Propietario* prop = this->getDuenio();

    if (prop != nullptr) {
        prop->removerPropietario(numid); 
    }
}

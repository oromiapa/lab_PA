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
        return this->administracionAsociada->getFechaInicio(); // Mensaje 2.2.1 del DC
    }
    return DtFecha(0, 0, 2026); // Fecha por defecto si no tuviera (por seguridad)
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
    if (this->administracionAsociada != nullptr) {
        

        this->administracionAsociada->borrarPublicacion();

        this->administracionAsociada->desvincularInmueble(this->numeroID);

        delete this->administracionAsociada;

        this->administracionAsociada = nullptr;
    }
}


void Inmueble::removerPropietario(int numid) {
    Propietario* prop = this->getDuenio();

    if (prop != nullptr) {
        prop->removerPropietario(numid); 
    }
}

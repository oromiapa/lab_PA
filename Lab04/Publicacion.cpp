#include "Publicacion.h"

// ICollection/interfaces
#include "./ICollection/interfaces/IIterator.h"

// ICollection/collections
#include "./ICollection/collections/List.h"



Publicacion::Publicacion(int id, const char* texto, float precio, const DtFecha& fecha, bool tipoPub, bool activa) {
    this->id = id;
    this->texto = texto;
    this->precio = precio;
    this->fechaPublicacion = fecha;
    this->tipoPublicacion = tipoPub;
    this->activa = activa;
}


Publicacion::~Publicacion() {
    
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


int Publicacion::getID() const {
    return this->id;
}

std::string Publicacion::getTexto() const {
    return this->texto;
}

float Publicacion::getPrecio() const {
    return this->precio;
}

DtFecha Publicacion::getFechaPublicacion() const {
    return this->fechaPublicacion;
}

bool Publicacion::getTipoPublicacion() const {
    return this->tipoPublicacion;
}

bool Publicacion::getActiva() const {
    return this->activa;
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Publicacion::setTexto(const char* texto) {
    this->texto = texto;
}

void Publicacion::setPrecio(float precio) {
    this->precio = precio;
}

void Publicacion::setFechaPublicacion(const DtFecha& fecha) {
    this->fechaPublicacion = fecha;
}

void Publicacion::setTipoPublicacion(bool tipoPub) {
    this->tipoPublicacion = tipoPub;
}

void Publicacion::setActiva(bool activa) {
    this->activa = activa;
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool Publicacion::comprobarTipo(bool tipoPub) const {
    return this->tipoPublicacion == tipoPub;
}

bool Publicacion::mismaFecha(const DtFecha& fecha) const {
    return (this->fechaPublicacion.getDia() == fecha.getDia() &&
            this->fechaPublicacion.getMes() == fecha.getMes() &&
            this->fechaPublicacion.getAnio() == fecha.getAnio());
}
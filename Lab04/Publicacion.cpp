#include "Publicacion.h"
#include "Visita.h"

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
    this->visitas = nullptr;  // sin esto, ~Publicacion() hace delete sobre basura → segfault
}


Publicacion::~Publicacion() {
    // Cuando la publicación muere, se lleva consigo el contenedor de la lista de visitas
    if (this->visitas != nullptr) {
        delete this->visitas;
    }
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




//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Publicacion::borrarVisita() {

    if (this->visitas != nullptr) {
        
        IIterator* itVis = this->visitas->getIterator();

        while (itVis->hasCurrent()) {
            ICollectible* item = itVis->getCurrent();
            
            Visita* currentVis = dynamic_cast<Visita*>(item);

            if (currentVis != nullptr) {
                delete currentVis;
            }
            
            itVis->next();
        }
        
        delete itVis;
    }
}



//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



bool Publicacion::comprobarDatos(bool tipopub, float preciomin, float preciomax) const {
    if (this->tipoPublicacion != tipopub)
        return false;
    if (this->precio < preciomin || this->precio > preciomax)
        return false;
    return true;
}

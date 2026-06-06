#include "Administracion.h"
#include "Inmueble.h"
#include "Publicacion.h"


//ICollection/interfaces
#include "./ICollection/interfaces/IIterator.h"

//ICollection/collections
#include "./ICollection/collections/List.h"


Administracion::Administracion() : fechainicio(), inmuebleAdministrado(nullptr) {}

Administracion::Administracion(const DtFecha& fechainicio, Inmueble* inmueble) {
    this->fechainicio = fechainicio;
    this->inmuebleAdministrado = inmueble;
    this->publicaciones = new List(); 
}

Administracion::~Administracion() {
    // 1. Recorremos y borramos cada objeto Publicacion que se creó adentro
    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        if (p != nullptr) {
            delete p; 
        }
        it->next();
    }
    delete it;

    // 2. Borramos la estructura contenedora de la lista
    delete this->publicaciones;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


DtFecha Administracion::getFechaInicio() const {
    return this->fechainicio;
}

Inmueble* Administracion::getInmueble() const {
    return this->inmuebleAdministrado;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Administracion::setFechaInicio(const DtFecha& fechainicio) {
    this->fechainicio = fechainicio;
}


void Administracion::setInmueble(Inmueble* inmueble) {
    this->inmuebleAdministrado = inmueble;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Administracion::altaPublicacion(const int numid, const char* text, float price, bool tipopub) {
    int maxId = 0;
    DtFecha fechaHoy(6, 6, 2026); // Fecha actual simulada

    // 1. Recorremos todas las publicaciones de esta administración
    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        
        if (p != nullptr) {
            // Aprovechamos la pasada para calcular el ID autoincremental
            if (p->getID() > maxId) {
                maxId = p->getID();
            }

            // 2. Buscamos la publicación activa
            if (p->getActiva()) { 
                // 3. Comprobamos si es del mismo tipo (Venta/Alquiler)
                if (p->comprobarTipo(tipopub)) {
                    // 4. Verificamos la restricción de fecha
                    if (p->mismaFecha(fechaHoy)) {
                        delete it; // Limpieza obligatoria antes del throw
                        throw std::invalid_argument("Regla de negocio: No es posible crear una nueva publicación del mismo tipo en la misma fecha.");
                    } else {
                        // Activa = true, Tipo = true, MismaFecha = false -> Desactivamos la vieja
                        p->setActiva(false);
                    }
                }
            }
        }
        it->next();
    }
    delete it; 

    int nuevoId = maxId + 1;
    Publicacion* nuevaPub = new Publicacion(nuevoId, text, price, fechaHoy, tipopub, true);

    this->publicaciones->add(nuevaPub);
}

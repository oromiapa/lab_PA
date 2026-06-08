#include "Administracion.h"
#include "Inmueble.h"
#include "Inmobiliaria.h"
#include "Publicacion.h"
#include "Casa.h"
#include "Apartamento.h"



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
    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        if (p != nullptr) {
            delete p; 
        }
        it->next();
    }
    delete it;

    delete this->publicaciones;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


DtFecha Administracion::getFechaInicio() const {
    return this->fechainicio;
}

Inmueble* Administracion::getInmueble() const {
    return this->inmuebleAdministrado;
}


Inmobiliaria* Administracion::getInmobiliaria() const {
    return this->InmobiliariaAsociada;
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
    DtFecha fechaHoy(6, 6, 2026); 

    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        
        if (p != nullptr) {
            if (p->getID() > maxId) {
                maxId = p->getID();
            }

            if (p->getActiva()) { 
                if (p->comprobarTipo(tipopub)) {
                    if (p->mismaFecha(fechaHoy)) {
                        delete it;
                        throw std::invalid_argument("Regla de negocio: No es posible crear una nueva publicación del mismo tipo en la misma fecha.");
                    } else {
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


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Administracion::borrarPublicacion() {

    if (this->publicaciones != nullptr) {
        IIterator* itPub = this->publicaciones->getIterator();

        while (itPub->hasCurrent()) {
            Publicacion* currentPub = dynamic_cast<Publicacion*>(itPub->getCurrent());

            if (currentPub != nullptr) {
                currentPub->borrarVisita();

                delete currentPub; 
            }
            itPub->next();
        }
        delete itPub;
    }
}




void Administracion::desvincularInmueble(int numid) {
    if (this->InmobiliariaAsociada != nullptr) {
        this->InmobiliariaAsociada->desvincularInmueble(numid, this); 
    }
}




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




ICollection* Administracion::filtrarPublicaciones(bool tipopub, float preciomin, float preciomax, TipoInmueble tipo) {
 
    ICollection* resultado = new List();
 
    if (this->inmuebleAdministrado == nullptr)
        return resultado;
 
    bool esCasa        = dynamic_cast<Casa*>(this->inmuebleAdministrado) != nullptr;
    bool esApartamento = dynamic_cast<Apartamento*>(this->inmuebleAdministrado) != nullptr;
 
    bool cumpleTipo = (tipo == TipoInmueble::AMBOS) ||
                      (tipo == TipoInmueble::CASA        && esCasa) ||
                      (tipo == TipoInmueble::APARTAMENTO && esApartamento);
 
    if (!cumpleTipo)
        return resultado;
 
    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        if (p != nullptr && p->getActiva() && p->comprobarDatos(tipopub, preciomin, preciomax)) {
 
            TipoInmueble tipoConcreto = esCasa ? TipoInmueble::CASA : TipoInmueble::APARTAMENTO;
 
            DtPublicacion* dt = new DtPublicacion(
                p->getID(),
                p->getFechaPublicacion(),
                p->getTexto().c_str(),
                tipoConcreto
            );
            resultado->add(dt);
        }
        it->next();
    }
    delete it;
 
    return resultado;
}






DtInmueble* Administracion::seleccionarPublicacion(int id) {
 
    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = static_cast<Publicacion*>(it->getCurrent());
        if (p->getID() == id) {
            delete it;
            return new DtInmueble(
                this->inmuebleAdministrado->getNumeroID(),
                this->inmuebleAdministrado->getDireccion(),
                this->inmuebleAdministrado->getSuperficie(),
                this->inmuebleAdministrado->getAnioConstruccion()
            );
        }
        it->next();
    }
    delete it;
    return nullptr;
}
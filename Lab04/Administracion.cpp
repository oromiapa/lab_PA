#include <ctime>
#include <iostream>

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


Administracion::Administracion() 
    : fechainicio(), inmuebleAdministrado(nullptr), 
      publicaciones(nullptr), InmobiliariaAsociada(nullptr) {}


Administracion::Administracion(const DtFecha& fechainicio, Inmueble* inmueble) {
    this->fechainicio = fechainicio;
    this->inmuebleAdministrado = inmueble;
    this->publicaciones = new List(); 
    this->InmobiliariaAsociada = nullptr;
}

Administracion::~Administracion() {
    if (this->publicaciones != nullptr)
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

void Administracion::setInmobiliaria(Inmobiliaria* inm) {
    this->InmobiliariaAsociada = inm;
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


DtFecha Administracion::obtenerFecha() const {
    time_t ahora = time(nullptr);       
    tm* local = localtime(&ahora);      

    int dia  = local->tm_mday;
    int mes  = local->tm_mon + 1;       
    int anio = local->tm_year + 1900;   

    return DtFecha(dia, mes, anio);

}



void Administracion::altaPublicacion(const int numid, const char* text, float price, bool tipopub) {

    int maxId = 0;
    DtFecha fechaActual = obtenerFecha() ;


    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        
        if (p != nullptr) {
            if (p->getID() > maxId) {
                maxId = p->getID();
            }

            if (p->getActiva()) { 
                if (p->comprobarTipo(tipopub)) {
                    if (p->mismaFecha(fechaActual)) {
                        delete it; 
                        throw std::invalid_argument("Regla de negocio: No es posible crear una nueva publicación del mismo tipo en la misma fecha.");
                    } 
                    else {
                        p->setActiva(false);
                    }
                }
            }
        }
        it->next();
    }
    delete it; 

    int nuevoId = maxId + 1;
    Publicacion* nuevaPub = new Publicacion(nuevoId, text, price, fechaActual, tipopub, true);

    this->publicaciones->add(nuevaPub);
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Administracion::borrarPublicacion() {
    std::cout << "[DEBUG] borrarPublicacion inicio\n"; std::cout.flush();
    if (this->publicaciones != nullptr) {
        IIterator* it = this->publicaciones->getIterator();
        while (it->hasCurrent()) {
            Publicacion* pub = static_cast<Publicacion*>(it->getCurrent());
            std::cout << "[DEBUG] borrando pub id=" << pub->getID() << "\n"; std::cout.flush();
            pub->borrarVisita();
            std::cout << "[DEBUG] borrarVisita OK\n"; std::cout.flush();
            delete pub;
            std::cout << "[DEBUG] delete pub OK\n"; std::cout.flush();
            it->next();
        }
        delete it;
    }
    std::cout << "[DEBUG] borrarPublicacion fin\n"; std::cout.flush();
}




void Administracion::desvincularInmueble(int numid) {
    std::cout << "[DEBUG] Administracion::desvincularInmueble, InmobiliariaAsociada=" << this->InmobiliariaAsociada << "\n"; std::cout.flush();
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




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




Publicacion* Administracion::getPublicacion(int id) {

    if (this->publicaciones != nullptr) {

        IIterator* itPub = this->publicaciones->getIterator();

        while (itPub->hasCurrent()) {

            Publicacion* pub = dynamic_cast<Publicacion*>(itPub->getCurrent());
            
            if (pub != nullptr && pub->getID() == id) {
                delete itPub;
                return pub;
            }
            itPub->next();
 
        }
        delete itPub;
    }

    return nullptr;

}
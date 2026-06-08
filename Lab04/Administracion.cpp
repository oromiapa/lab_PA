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


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Administracion::borrarPublicacion() {

    if (this->publicaciones != nullptr) {
        IIterator* itPub = this->publicaciones->getIterator();

        while (itPub->hasCurrent()) {
            Publicacion* currentPub = dynamic_cast<Publicacion*>(itPub->getCurrent());

            if (currentPub != nullptr) {
                // 💡 ¡NUEVO PASO!: Antes de borrar la publicación, limpiamos sus visitas
                currentPub->borrarVisita();

                // DESTROY de la publicación real
                delete currentPub; 
            }
            itPub->next();
        }
        delete itPub;
    }
}




void Administracion::desvincularInmueble(int numid) {
    if (this->InmobiliariaAsociada != nullptr) {
        // Le pasamos el ID y nos pasamos a nosotros mismos (this)
        this->InmobiliariaAsociada->desvincularInmueble(numid, this); 
    }
}




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




ICollection* Administracion::filtrarPublicaciones(bool tipopub, float preciomin, float preciomax, TipoInmueble tipo) {
 
    ICollection* resultado = new List();
 
    // 1. Verificar si el inmueble asociado cumple el tipo pedido
    if (this->inmuebleAdministrado == nullptr)
        return resultado;
 
    bool esCasa        = dynamic_cast<Casa*>(this->inmuebleAdministrado) != nullptr;
    bool esApartamento = dynamic_cast<Apartamento*>(this->inmuebleAdministrado) != nullptr;
 
    bool cumpleTipo = (tipo == TipoInmueble::AMBOS) ||
                      (tipo == TipoInmueble::CASA        && esCasa) ||
                      (tipo == TipoInmueble::APARTAMENTO && esApartamento);
 
    if (!cumpleTipo)
        return resultado;
 
    // 2. Recorrer publicaciones y filtrar
    IIterator* it = this->publicaciones->getIterator();
    while (it->hasCurrent()) {
        Publicacion* p = dynamic_cast<Publicacion*>(it->getCurrent());
        if (p != nullptr && p->getActiva() && p->comprobarDatos(tipopub, preciomin, preciomax)) {
 
            // Determinar TipoInmueble concreto para el DtPublicacion
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
            // Construir y retornar el DtInmueble del inmueble administrado
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
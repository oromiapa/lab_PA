#include "Inmobiliaria.h"
#include "Inmueble.h"
#include "Administracion.h"
#include "Propietario.h"

//DataTypes
#include "./DataTypes/DtInmXProp.h"
#include "./DataTypes/DtInmuebleAdministrado.h"
#include "./DataTypes/DtInmueble.h"

//ICollection
#include "./ICollection/String.h"
#include "./ICollection/Integer.h"

//ICollection/interfaces
#include "./ICollection/interfaces/IIterator.h"

//ICollection/collections
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/collections/List.h"

Inmobiliaria::Inmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL) 
    : Usuario(nickname, nombre, email, contrasenia), telefono(telefono), URL(URL), direccionInmobiliaria(direccionInmobiliaria) {
        this->inmuebles = new OrderedDictionary();
        this->propietariosAsociados = new OrderedDictionary();
        this->administraciones = new List();
}

Inmobiliaria::~Inmobiliaria() {
    delete this->inmuebles;
    delete this->propietariosAsociados;
    delete this->administraciones;
}

DtDireccion Inmobiliaria::getDireccionInmobiliaria() const {
    return this->direccionInmobiliaria;
}

std::string Inmobiliaria::getTelefono() const {
    return this->telefono;
}

std::string Inmobiliaria::getURL() const {
    return this->URL;
}

DtInmobiliaria Inmobiliaria::getDatos() {
    DtInmobiliaria dt(this->getNickname().c_str(), this->getNombre().c_str());
    return dt;
}

void Inmobiliaria::setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria) {
    this->direccionInmobiliaria = direccionInmobiliaria;
}

void Inmobiliaria::setTelefono(const char* telefono) {
    this->telefono = telefono;
}

void Inmobiliaria::setURL(const char* URL) {
    this->URL = URL;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Inmobiliaria::vincularPropietario(Propietario* p) {
    if (p == nullptr) return;

    IDictionary* dictInmuebles = p->obtenerInmueblesPropios(); 
    
    IIterator* it = dictInmuebles->getIterator();
    while (it->hasCurrent()) {
        Inmueble* inm = dynamic_cast<Inmueble*>(it->getCurrent());
        if (inm != nullptr) {
            this->vincularInmueble(inm); 
        }
        it->next();
    }
    
    delete it; 
    
}

void Inmobiliaria::vincularInmueble(Inmueble* i) {
    if (i == nullptr) return;

    int id = i->getNumeroID(); 
    Integer* key = new Integer(id);

    this->inmuebles->add(key, i); 
}


IDictionary* Inmobiliaria::getInmuebles() const {
    return this->inmuebles;
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




ICollection* Inmobiliaria::seleccionarInmobiliaria() {
    ICollection* listaRetorno = new List();

    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {
        Inmueble* currentInm = dynamic_cast<Inmueble*>(it->getCurrent());
        
        if (currentInm != nullptr) {
            int id = currentInm->getNumeroID();
            DtDireccion dir = currentInm->getDireccion();

            Propietario* elDuenio = currentInm->getDuenio();
            DtPropietario dtProp = elDuenio->getDatosPropietario(); 

            DtInmXProp* dtCompuesto = new DtInmXProp(id, dir, dtProp);
            listaRetorno->add(dtCompuesto);
        }
        it->next();
    }
    delete it;

    return listaRetorno; 
}


DtFecha Inmobiliaria::obtenerFecha() {
    DtFecha fechaActual(5, 6, 2026); 
    return fechaActual;
}


void Inmobiliaria::altaAdministracion(int numid) {
    Integer* keyBuscar = new Integer(numid);
    ICollectible* item = this->inmuebles->find(keyBuscar);
    delete keyBuscar; 

    if (item == nullptr) {
        throw std::invalid_argument("El inmueble seleccionado no pertenece a esta inmobiliaria.");
    }
    Inmueble* inm = dynamic_cast<Inmueble*>(item);

    DtFecha fechaHoy = this->obtenerFecha();

    Administracion* nuevaAdmin = new Administracion(fechaHoy, inm);

    this->administraciones->add(nuevaAdmin);

    inm->setAdministracion(nuevaAdmin);
    
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



ICollection* Inmobiliaria::seleccionarInmobiliariaAdministrada() {
    ICollection* listaRetorno = new List();

    IIterator* itAdmin = this->administraciones->getIterator();

    while (itAdmin->hasCurrent()) {
        Administracion* currentAdmin = dynamic_cast<Administracion*>(itAdmin->getCurrent());
        
        if (currentAdmin != nullptr) {
            DtFecha fechaAdmin = currentAdmin->getFechaInicio();

            Inmueble* currentInm = currentAdmin->getInmueble();
            
            if (currentInm != nullptr) {
                int id = currentInm->getNumeroID(); 
                DtDireccion dir = currentInm->getDireccion();

                DtAdministracion dtAdminAux(fechaAdmin); 
                DtInmuebleAdministrado* dtCompuesto = new DtInmuebleAdministrado(id, dir, dtAdminAux);

                listaRetorno->add(dtCompuesto);
            }
        }
        itAdmin->next();
    }
    delete itAdmin; 

    return listaRetorno; 
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Inmobiliaria::desvincularInmueble(int numid, Administracion* admin) {
    if (this->inmuebles != nullptr) {
        Integer* keyInm = new Integer(numid);
        
        this->inmuebles->remove(keyInm); 
        
        delete keyInm; 
    }

    if (this->administraciones != nullptr && admin != nullptr) {
        this->administraciones->remove(admin);
    }
}




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




ICollection* Inmobiliaria::filtrarPublicaciones(bool tipopub, float preciomin, float preciomax, TipoInmueble tipo) {
 
    ICollection* resultado = new List();
 
    DtInmobiliaria dtInmo(this->getNickname().c_str(), this->getNombre().c_str());
 
    IIterator* itAdmin = this->administraciones->getIterator();
    while (itAdmin->hasCurrent()) {
        Administracion* admin = static_cast<Administracion*>(itAdmin->getCurrent());
 
        ICollection* pubsFiltradas = admin->filtrarPublicaciones(tipopub, preciomin, preciomax, tipo);
 
        IIterator* itPub = pubsFiltradas->getIterator();
        while (itPub->hasCurrent()) {
            DtPublicacion* dtPub = static_cast<DtPublicacion*>(itPub->getCurrent());
            DataFiltro* df = new DataFiltro(dtInmo, *dtPub);
            resultado->add(df);
            itPub->next();
        }
        delete itPub;
        delete pubsFiltradas; 
 
        itAdmin->next();
    }
    delete itAdmin;
 
    return resultado;
}






DtInmueble* Inmobiliaria::seleccionarPublicacion(int id) {
 
    IIterator* it = this->administraciones->getIterator();
    while (it->hasCurrent()) {
        Administracion* admin = static_cast<Administracion*>(it->getCurrent());
 
        DtInmueble* resultado = admin->seleccionarPublicacion(id);
        if (resultado != nullptr) {
            delete it;
            return resultado;
        }
        it->next();
    }
    delete it;
    return nullptr;
}
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

    // 1. Obtenemos el diccionario original de inmuebles del propietario
    // (Ya no se crea una lista temporal con 'new List()')
    IDictionary* dictInmuebles = p->obtenerInmueblesPropios(); 
    
    // 2. Iteramos el diccionario directamente
    IIterator* it = dictInmuebles->getIterator();
    while (it->hasCurrent()) {
        Inmueble* inm = dynamic_cast<Inmueble*>(it->getCurrent());
        if (inm != nullptr) {
            // Tu función miembro que agrega el inmueble a la inmobiliaria
            this->vincularInmueble(inm); 
        }
        it->next();
    }
    
    // 3. Limpieza de memoria
    delete it; // Solo borramos el iterador temporal.
    
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
    // Creamos la lista de retorno de DtInmXProp (Mensaje 2 del DC)
    ICollection* listaRetorno = new List();

    // Mensaje 2.1* [foreach]: i := next
    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {
        Inmueble* currentInm = dynamic_cast<Inmueble*>(it->getCurrent());
        
        if (currentInm != nullptr) {
            // Mensaje 2.2* d := getDatos() : DtInmueble
            int id = currentInm->getNumeroID();
            DtDireccion dir = currentInm->getDireccion();

            // Mensaje 2.2.1* nom := getNombre() : string (Le pide los datos al Propietario)
            Propietario* elDuenio = currentInm->getDuenio();
            DtPropietario dtProp = elDuenio->getDatosPropietario(); 

            // Se empaqueta en el DataType compuesto
            DtInmXProp* dtCompuesto = new DtInmXProp(id, dir, dtProp);
            listaRetorno->add(dtCompuesto);
        }
        it->next();
    }
    delete it;

    return listaRetorno; // Retorna el set de DtInmXProp al Sistema
}


DtFecha Inmobiliaria::obtenerFecha() {
    // Instanciamos (configuramos) el DataType con la fecha de hoy
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

    // 1. Iteramos la lista de ADMINISTRACIONES (las relaciones asociativas reales)
    IIterator* itAdmin = this->administraciones->getIterator();

    while (itAdmin->hasCurrent()) {
        Administracion* currentAdmin = dynamic_cast<Administracion*>(itAdmin->getCurrent());
        
        if (currentAdmin != nullptr) {
            // 2. Le pedimos la fecha directamente a la administración
            DtFecha fechaAdmin = currentAdmin->getFechaInicio();

            // 3. Le pedimos el Inmueble asociado a esa administración
            Inmueble* currentInm = currentAdmin->getInmueble();
            
            if (currentInm != nullptr) {
                // 4. Extraemos los datos del inmueble 
                // 💡 Nota: Asegúrate de usar getNumId() o getNumeroID() según tu Inmueble.h
                int id = currentInm->getNumeroID(); 
                DtDireccion dir = currentInm->getDireccion();

                // 5. Empaquetamos todo en el DataType correspondiente
                DtAdministracion dtAdminAux(fechaAdmin); 
                DtInmuebleAdministrado* dtCompuesto = new DtInmuebleAdministrado(id, dir, dtAdminAux);

                // 6. ¡EL PASO FALTANTE! Metemos el DataType en la lista que va a viajar al main
                listaRetorno->add(dtCompuesto);
            }
        }
        itAdmin->next();
    }
    delete itAdmin; // Limpieza del iterador para evitar leaks

    return listaRetorno; 
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Inmobiliaria::desvincularInmueble(int numid, Administracion* admin) {
    // 1. Removemos el Inmueble de la colección por su clave (ID)
    if (this->inmuebles != nullptr) {
        Integer* keyInm = new Integer(numid);
        
        // El remove saca el objeto de la lista asociativa pero NO lo borra de la memoria
        this->inmuebles->remove(keyInm); 
        
        delete keyInm; // Limpiamos la llave temporal que creamos para buscar
    }

    // 2. Removemos la Administración de la colección
    if (this->administraciones != nullptr && admin != nullptr) {
        // Al pasarle directamente el puntero 'admin', la colección sabe cuál quitar
        this->administraciones->remove(admin);
    }
}




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




ICollection* Inmobiliaria::filtrarPublicaciones(bool tipopub, float preciomin, float preciomax, TipoInmueble tipo) {
 
    ICollection* resultado = new List();
 
    DtInmobiliaria dtInmo(this->getNickname().c_str(), this->getNombre().c_str());
 
    // static_cast: administraciones solo contiene Administracion*, no hay subclases
    IIterator* itAdmin = this->administraciones->getIterator();
    while (itAdmin->hasCurrent()) {
        Administracion* admin = static_cast<Administracion*>(itAdmin->getCurrent());
 
        ICollection* pubsFiltradas = admin->filtrarPublicaciones(tipopub, preciomin, preciomax, tipo);
 
        // static_cast: pubsFiltradas solo contiene DtPublicacion*
        IIterator* itPub = pubsFiltradas->getIterator();
        while (itPub->hasCurrent()) {
            DtPublicacion* dtPub = static_cast<DtPublicacion*>(itPub->getCurrent());
            DataFiltro* df = new DataFiltro(dtInmo, *dtPub);
            resultado->add(df);
            itPub->next();
        }
        delete itPub;
        delete pubsFiltradas; // DtPublicacion copiados en DataFiltro, se puede liberar
 
        itAdmin->next();
    }
    delete itAdmin;
 
    return resultado;
}






DtInmueble* Inmobiliaria::seleccionarPublicacion(int id) {
 
    // static_cast: administraciones solo contiene Administracion*
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
#include "Sistema.h"
#include "Usuario.h"
#include "Cliente.h"
#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Inmueble.h"
#include "Casa.h"
#include "Apartamento.h"
#include "Administracion.h"
#include "Publicacion.h"

//DataTypes
#include "./DataTypes/DtPropietario.h"
#include "./DataTypes/DtInmobiliaria.h"
#include "./DataTypes/DtInmueble.h"
#include "./DataTypes/DtInmXProp.h"
#include "./DataTypes/DtInmuebleAdministrado.h"

//ICollection
#include "./ICollection/String.h"
#include "./ICollection/Integer.h"

//ICollection/interfaces
#include "./ICollection/interfaces/IIterator.h"

//ICollection/collections
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/collections/List.h"



Sistema::Sistema() {
    this->usuarios = new OrderedDictionary();
    this->inmuebles = new OrderedDictionary();
    this->inmobiliarias = new OrderedDictionary();
    this->inmobiliariaActual = nullptr;
    this->propietarioActual = nullptr;
    this->contadorInmuebles = 0;
}

Sistema::~Sistema() {
    IIterator* itU = this->usuarios->getIterator();
    while (itU->hasCurrent()) {
        delete itU->getCurrent();
        itU->next();
    }
    delete itU;
    delete this->usuarios; 

    IIterator* itI = this->inmuebles->getIterator();
    while (itI->hasCurrent()) {
        delete itI->getCurrent();
        itI->next();
    }
    delete itI;
    delete this->inmuebles;

    delete this->inmobiliarias; 
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




bool Sistema::existeUsuario(const char* nickname) {

    String* key = new String(nickname);
    bool existe = this->usuarios->member(key);
    delete key;
    return existe;

}


void Sistema::altaCliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento) {

    if (this->existeUsuario(nickname)) 
        throw std::invalid_argument("El usuario ya existe");

    Cliente* cliente = new Cliente(nickname, nombre, email, contrasenia, apellido, documento);
    String* key = new String(nickname);
    this->usuarios->add(key, cliente);

}


void Sistema::altaPropietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria) {

    if (this->existeUsuario(nickname)) 
        throw std::invalid_argument("El usuario ya existe");
    

    Propietario* propietario = new Propietario(nickname, nombre, email, contrasenia, telefono, cuentaBancaria);
    String* key = new String(nickname);
    this->usuarios->add(key, propietario);

    this->propietarioActual = propietario;

}


int Sistema::autoincremental() {
    return ++this->contadorInmuebles;
}


void Sistema::crearCasa(const DtDireccion & direccion, const DtFecha & anioConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho) {

    int numid = this->autoincremental();
    Integer* key = new Integer(numid);
    Casa* casa = new Casa(direccion, superficie, anioConstruccion, numid, propiedadHorizontal, tipoTecho);
    this->inmuebles->add(key, casa);
    this->propietarioActual->vincularInmueble(casa);

}


void Sistema::crearApartamento(const DtDireccion & direccion, const DtFecha & anioConstruccion, float superficie, int numeroPiso, bool TieneAscensor, const float & gastosComunes) {

    int numid = this->autoincremental();
    Integer* key = new Integer(numid);
    Apartamento* apartamento = new Apartamento(direccion, superficie, anioConstruccion, numid, numeroPiso, TieneAscensor, gastosComunes);
    this->inmuebles->add(key, apartamento);
    this->propietarioActual->vincularInmueble(apartamento);

}


void Sistema::altaInmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL) {

    if (this->existeUsuario(nickname)) 
        throw std::invalid_argument("El usuario ya existe");

    
    Inmobiliaria* inmobiliaria = new Inmobiliaria(nickname, nombre, email, contrasenia, direccionInmobiliaria, telefono, URL);
    String* key = new String(nickname);
    
    this->usuarios->add(key, inmobiliaria);
    
    this->inmobiliariaActual = inmobiliaria; 

}


ICollection* Sistema::listarPropietarios() {

    ICollection* propietarios = new List();
    IIterator* it = this->usuarios->getIterator();

    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        Propietario* p = dynamic_cast<Propietario*>(item);

        if (p != nullptr) {
            DtPropietario datos = p->getDatosPropietario();
            DtPropietario* dtParaLista = new DtPropietario(datos.getNickname(), datos.getNombre());
            propietarios->add(dtParaLista);
        }

        it->next();

    }

    delete it;
    return propietarios;

}


void Sistema::vincularPropietario(const char* nicknamePropietario) {

    String* keyBuscar = new String(nicknamePropietario);
    ICollectible* item = this->usuarios->find(keyBuscar);
    delete keyBuscar; 
    if (item == nullptr) {
        throw std::invalid_argument("El propietario no existe.");
    }
    
    Propietario* prop = dynamic_cast<Propietario*>(item);
    if (prop == nullptr) {
        throw std::invalid_argument("El nickname ingresado no pertenece a un propietario.");
    }

    if (this->inmobiliariaActual != nullptr) {
        

        this->inmobiliariaActual->vincularPropietario(prop); 
        
    } else {
        throw std::runtime_error("No hay una inmobiliaria activa en el sistema para vincular.");
    }
}


void Sistema::finalizarAltaInmobiliaria() {
    this->inmobiliariaActual = nullptr; 
}

void Sistema::finalizarAltaPropietario() {
    this->propietarioActual = nullptr;
}




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




ICollection* Sistema::listarInmobiliarias() {

    ICollection* inmobiliarias = new List();
    IIterator* it = this->usuarios->getIterator();

    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        Inmobiliaria* i = dynamic_cast<Inmobiliaria*>(item);

        if (i != nullptr) {
            DtInmobiliaria datos = i->getDatos();
            DtInmobiliaria* dtParaLista = new DtInmobiliaria(datos.getNickname(), datos.getNombre());
            inmobiliarias->add(dtParaLista);
        }

        it->next();
    
    }
    
    delete it;
    return inmobiliarias;

}




ICollection* Sistema::seleccionarInmobiliaria(const char* nombreInmobiliaria) {
    if (nombreInmobiliaria == nullptr) {
        throw std::invalid_argument("El nombre de la inmobiliaria no puede ser nulo.");
    }

    String* keyBuscar = new String(nombreInmobiliaria);
    ICollectible* item = this->usuarios->find(keyBuscar);
    delete keyBuscar;

    if (item == nullptr) {
        throw std::invalid_argument("La inmobiliaria seleccionada no existe.");
    }

    Inmobiliaria* inm = dynamic_cast<Inmobiliaria*>(item);
    if (inm == nullptr) {
        throw std::invalid_argument("El usuario encontrado no es una inmobiliaria.");
    }

    this->inmobiliariaActual = inm;


    ICollection* resultado = inm->seleccionarInmobiliaria();

    return resultado;
}




void Sistema::altaAdministracion(int numid) {
    if (this->inmobiliariaActual == nullptr) {
        throw std::runtime_error("Error: No hay ninguna inmobiliaria seleccionada en memoria.");
    }

    this->inmobiliariaActual->altaAdministracion(numid);

    this->inmobiliariaActual = nullptr;
    
}





//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||






ICollection* Sistema::seleccionarInmobiliariaAdministrada(const char* nombreInmobiliaria) {
    ICollection* listaRetorno = new List();

    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {
        Inmueble* currentInm = dynamic_cast<Inmueble*>(it->getCurrent());
        
        if (currentInm != nullptr) {
            int id = currentInm->getNumeroID();
            DtDireccion dir = currentInm->getDireccion();

            DtFecha fechaAdmin = currentInm->getFechaAdministracion(); 

            DtInmuebleAdministrado* dtCompuesto = new DtInmuebleAdministrado(id, dir, fechaAdmin);
            listaRetorno->add(dtCompuesto);
        }
        it->next();
    }
    delete it;

    return listaRetorno; 
}



void Sistema::altaPublicacion(const int numid, const char* text, float price, bool tipopub) {
    Integer* key = new Integer(numid);
    ICollectible* item = this->inmuebles->find(key);
    delete key;

    if (item == nullptr) {
        throw std::invalid_argument("Error: No existe un inmueble con el ID especificado.");
    }

    Inmueble* inm = dynamic_cast<Inmueble*>(item);

    inm->altaPublicacion(numid, text, price, tipopub);
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



ICollection* Sistema::listarinmueblesxpropietario() {
    ICollection* listaRetorno = new List();
    
    IIterator* itInm = this->inmuebles->getIterator();

    while (itInm->hasCurrent()) {
        Inmueble* currentInm = dynamic_cast<Inmueble*>(itInm->getCurrent());

        if (currentInm != nullptr) {
            int id = currentInm->getNumeroID(); 
            DtDireccion dir = currentInm->getDireccion();

            Propietario* prop = currentInm->getDuenio(); 

            if (prop != nullptr) {
                DtPropietario dtPropAux(prop->getNickname().c_str(), prop->getNombre().c_str());

                DtInmXProp* dtCompuesto = new DtInmXProp(id, dir, dtPropAux);

                listaRetorno->add(dtCompuesto);
            }
        }
        itInm->next();
    }
    delete itInm; 

    return listaRetorno;
}



DtInmueble Sistema::seleccionarInmueble(int numid) {
    
    Integer* keyBuscar = new Integer(numid);
    ICollectible* item = this->inmuebles->find(keyBuscar);
    delete keyBuscar;

    if (item == nullptr) {
        throw std::invalid_argument("El inmueble seleccionado no existe.");
    }

    Inmueble* i = dynamic_cast<Inmueble*>(item);

    this->inmuebleActual = i;

    int id = this->inmuebleActual->getNumeroID();
    DtDireccion dir = this->inmuebleActual->getDireccion();
    float superficie = this->inmuebleActual->getSuperficie();
    DtFecha fecha = this->inmuebleActual->getAnioConstruccion();


    return DtInmueble(id, dir, superficie, fecha); 

}




void Sistema::eliminarInmueble(int numid) {
    if (this->inmuebleActual == nullptr || this->inmuebleActual->getNumeroID() != numid) {
        throw std::runtime_error("Error: Inmueble no seleccionado o ID inválido.");
    }

    this->inmuebleActual->borrarAdministracion();
    this->inmuebleActual->removerPropietario(numid);

    Integer* keyInm = new Integer(numid);
    this->inmuebles->remove(keyInm);
    delete keyInm;

    delete this->inmuebleActual;
    
    this->inmuebleActual = nullptr;
}




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



ICollection* Sistema::filtrarPublicaciones(bool tipopub , float preciomin , float preciomax , TipoInmueble tipo) {

    ICollection* listaRetorno = new List();

    IIterator* itInm = this->inmobiliarias->getIterator();

    while (itInm->hasCurrent()) {
        Inmobiliaria* currentInm = dynamic_cast<Inmobiliaria*>(itInm->getCurrent());

        if (currentInm != nullptr) {


             

            if (prop != nullptr) {
                DtPropietario dtPropAux(prop->getNickname().c_str(), prop->getNombre().c_str());

                DtInmXProp* dtCompuesto = new DtInmXProp(id, dir, dtPropAux);

                listaRetorno->add(dtCompuesto);
            }
        }
        itInm->next();
    }
    delete itInm; 

    return listaRetorno;


}



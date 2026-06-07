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


//Constructor y destructor

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





// Métodos

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
    // 1. Buscamos el usuario en el diccionario global de usuarios del sistema
    String* keyBuscar = new String(nicknamePropietario);
    ICollectible* item = this->usuarios->find(keyBuscar);
    delete keyBuscar; // Borramos la clave de búsqueda para evitar fugas de memoria

    if (item == nullptr) {
        throw std::invalid_argument("El propietario no existe.");
    }
    
    // 2. Súper importante: Validamos que realmente sea un Propietario
    Propietario* prop = dynamic_cast<Propietario*>(item);
    if (prop == nullptr) {
        throw std::invalid_argument("El nickname ingresado no pertenece a un propietario.");
    }

    // 3. Le pasamos el propietario a la inmobiliaria que el sistema está "recordando"
    if (this->inmobiliariaActual != nullptr) {
        
        // AQUÍ PASA TODO: El sistema le da el Propietario, 
        // y la Inmobiliaria absorbe sus inmuebles automáticamente
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

    // 1. Inmobiliaria := find(nickname)
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

    // Post-condición: Recordamos la inmobiliaria para el paso 3 (altaAdministracion)
    this->inmobiliariaActual = inm;

    // 2. DELEGACIÓN (Mensaje 2 del diagrama de comunicación)
    // El sistema le dice a la inmobiliaria: "Trabaja tú y dame los resultados"
    ICollection* resultado = inm->seleccionarInmobiliaria();

    return resultado;
}




void Sistema::altaAdministracion(int numid) {
    if (this->inmobiliariaActual == nullptr) {
        throw std::runtime_error("Error: No hay ninguna inmobiliaria seleccionada en memoria.");
    }

    // El sistema solo le pasa el ID, la inmobiliaria maneja su propia fecha interna
    this->inmobiliariaActual->altaAdministracion(numid);

    // Post-condición: limpieza del recuerdo
    this->inmobiliariaActual = nullptr;
    
}





//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||






ICollection* Sistema::seleccionarInmobiliariaAdministrada(const char* nombreInmobiliaria) {
    ICollection* listaRetorno = new List();

    // Mensaje 2.1* [foreach]: i := next (Itera la colección de inmuebles)
    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {
        Inmueble* currentInm = dynamic_cast<Inmueble*>(it->getCurrent());
        
        if (currentInm != nullptr) {
            int id = currentInm->getNumeroID();
            DtDireccion dir = currentInm->getDireccion();

            // 💡 Mensaje 2.2.1: El Inmueble va a buscar la fecha de su administración
            DtFecha fechaAdmin = currentInm->getFechaAdministracion(); 

            // Se empaqueta en el DataType compuesto
            DtInmuebleAdministrado* dtCompuesto = new DtInmuebleAdministrado(id, dir, fechaAdmin);
            listaRetorno->add(dtCompuesto);
        }
        it->next();
    }
    delete it;

    return listaRetorno; 
}



void Sistema::altaPublicacion(const int numid, const char* text, float price, bool tipopub) {
    // 1. Buscamos el inmueble por su ID en el diccionario del Sistema
    Integer* key = new Integer(numid);
    ICollectible* item = this->inmuebles->find(key);
    delete key;

    if (item == nullptr) {
        throw std::invalid_argument("Error: No existe un inmueble con el ID especificado.");
    }

    Inmueble* inm = dynamic_cast<Inmueble*>(item);

    // 2. Transmitimos el mensaje al Inmueble (Mensaje 2 del DC)
    inm->altaPublicacion(numid, text, price, tipopub);
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



ICollection* Sistema::listarinmueblesxpropietario() {
    ICollection* listaRetorno = new List();
    
    // 1. Iteramos la colección de inmuebles del sistema
    IIterator* itInm = this->inmuebles->getIterator();

    while (itInm->hasCurrent()) {
        Inmueble* currentInm = dynamic_cast<Inmueble*>(itInm->getCurrent());

        if (currentInm != nullptr) {
            // 2. Extraemos el ID y la Dirección DIRECTO desde la clase de negocio Inmueble
            int id = currentInm->getNumeroID(); 
            DtDireccion dir = currentInm->getDireccion();

            // 3. Obtenemos su propietario asociado
            Propietario* prop = currentInm->getDuenio(); 

            if (prop != nullptr) {
                // 4. Fabricamos el DataType plano del propietario
                DtPropietario dtPropAux(prop->getNickname().c_str(), prop->getNombre().c_str());

                // 5. ¡Directo al constructor del DataType Compuesto!
                DtInmXProp* dtCompuesto = new DtInmXProp(id, dir, dtPropAux);

                // 6. Lo agregamos al set/lista de retorno
                listaRetorno->add(dtCompuesto);
            }
        }
        itInm->next();
    }
    delete itInm; // Evitamos memory leaks

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





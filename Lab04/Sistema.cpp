#include "Sistema.h"
#include "Inmobiliaria.h"
#include "Propietario.h"
#include "Cliente.h"
#include "Inmueble.h"
#include "Casa.h"
#include "Apartamento.h"
// Constructor
Sistema::Sistema() : autoincrementalID(0) {
    // Inicialización de colecciones si fuera necesario
}

// Destructor
Sistema::~Sistema() {
    // Limpieza de recursos si fuera necesario
}

// listarInmobiliarias
std::set<DataInmobiliaria> Sistema::listarInmobiliarias() {
    std::set<DataInmobiliaria> resultado;

    for (const auto& inm : inmobiliarias) {
        DataInmobiliaria dto;
        dto.nickname = inm->getNickname();
        dto.nombre   = inm->getNombre();
        resultado.insert(dto);
    }

    return resultado;
}

// listarPropietarios
std::set<DataPropietario> Sistema::listarPropietarios() {
    std::set<DataPropietario> resultado;

    for (const auto& prop : propietarios) {
        DataPropietario dto;
        dto.nickname = prop->getNickname();
        dto.nombre   = prop->getNombre();
        resultado.insert(dto);
    }

    return resultado;
}

// altaCliente
void Sistema::altaCliente(const std::string& contrasenia, const std::string& email, const std::string& nombre, const std::string& apellido, const std::string& documento) {
    std::shared_ptr<Cliente> nuevo = std::make_shared<Cliente>(
        contrasenia, email, nombre, apellido, documento
    );
    clientes.insert(nuevo);
}

// altaPropietario
void Sistema::altaPropietario(const std::string& contrasenia, const std::string& email, const std::string& nombre, int cuentaBancaria, const std::string& telefono) { 
    std::shared_ptr<Propietario> nuevo = std::make_shared<Propietario>(
        contrasenia, email, nombre, cuentaBancaria, telefono
    );
    propietarios.insert(nuevo);

}

// altaInmobiliaria
void Sistema::altaInmobiliaria(const std::string& contrasenia, const std::string& email, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& url) {
    std::shared_ptr<Inmobiliaria> nuevo = std::make_shared<Inmobiliaria>(
        contrasenia, email, nombre, direccion, telefono, url
    );
    inmobiliarias.insert(nuevo);

}

// existeUsuario
bool Sistema::existeUsuario(const std::string& nickname) {
    for (const auto& prop : propietarios) {
        if (prop->getNickname() == nickname) {
            return true;
        }
    }
    for (const auto& cli : clientes) {
        if (cli->getNickname() == nickname) {
            return true;
        }
    }
    for (const auto& inm : inmobiliarias) {
        if (inm->getNickname() == nickname) {
            return true;
        }
    }
    return false;

}

// autoincremental
int Sistema::autoincremental() {    
    return ++autoincrementalID;
}

// crearCasa
void Sistema::crearCasa(const std::string& direccion, const std::string& anioConstruccion,float superficie, bool propiedadHorizontal, const std::string& tipoTecho) {
    std::shared_ptr<Casa> nueva = std::make_shared<Casa>(
        direccion, anioConstruccion, superficie, autoincremental(), propiedadHorizontal, tipoTecho
    );
    inmuebles.insert(nueva);
}

// crearApartamento
void Sistema::crearApartamento(const std::string& direccion, const std::string& anioConstruccion, float superficie, int piso, bool tieneAscensor, float gastosComunes) {
    std::shared_ptr<Apartamento> nuevo = std::make_shared<Apartamento>(
        direccion, anioConstruccion, superficie, autoincremental(), piso, tieneAscensor, gastosComunes
    );
    inmuebles.insert(nuevo);
}

// seleccionarInmobiliaria
std::shared_ptr<Inmobiliaria> Sistema::seleccionarInmobiliaria(const std::string& nickname) {
    for (const auto& inm : inmobiliarias) {
        if (inm->getNickname() == nickname) {
            return inm;
        }
    }
    return nullptr; // No encontrada
}

// seleccionarInmueble
std::shared_ptr<Inmueble> Sistema::seleccionarInmueble(int numeroID) {
    for (const auto& inm : inmuebles) {
        if (inm->getNumeroID() == numeroID) {
            return inm;
        }
    }
    return nullptr; // No encontrado
}

// eliminarInmueble
void Sistema::eliminarInmueble(int numeroID) {
    auto it = inmuebles.begin();
    while (it != inmuebles.end()) {
        if ((*it)->getNumeroID() == numeroID) {
            it = inmuebles.erase(it); // Elimina y avanza el iterador
        } else {
            ++it; // Avanza el iterador
        }
    }
}

// listarInmuebles
std::set<DataInmueble> Sistema::listarInmuebles() {
    std::set<DataInmueble> resultado;

    for (const auto& inm : inmuebles) {
        DataInmueble dto;
        dto.numeroID = inm->getNumeroID();
        dto.direccion = inm->getDireccion().getCalle() + " " + std::to_string(inm->getDireccion().getNumero());
        dto.propietario = ""; // Aquí podrías agregar lógica para obtener el propietario si es necesario
        resultado.insert(dto);
    }

    return resultado;
}

// listarInmueblesxPropietario
std::set<DataPropietario> Sistema::listarInmueblesxPropietario() {
    std::set<DataPropietario> resultado;

    for (const auto& prop : propietarios) {
        DataPropietario dto;
        dto.nickname = prop->getNickname();
        dto.nombre   = prop->getNombre();
        resultado.insert(dto);
    }

    return resultado;
}

// altaPublicacion
void Sistema::altaPublicacion(const std::string& nickname, const std::string& texto, int precio, bool tipoPublicacion) {
    // Aquí deberías implementar la lógica para crear una publicación
    // y asociarla al propietario o inmobiliaria correspondiente
}

// filtrarPublicaciones
std::set<DataFiltro> Sistema::filtrarPublicaciones(bool tipoPublicacion, float precioMinimo, float precioMaximo, int tipoInmueble) {
    std::set<DataFiltro> resultado;
    // Aquí deberías implementar la lógica para filtrar las publicaciones
    // según los criterios proporcionados
    return resultado;
}

// seleccionarPublicacion
std::shared_ptr<Publicacion> Sistema::seleccionarPublicacion(int id) {
    // Aquí deberías implementar la lógica para seleccionar una publicación por su ID
    return nullptr; // Placeholder
}

// vincularPropietario
void Sistema::vincularPropietario(const std::string& nickname) {
    // Aquí deberías implementar la lógica para vincular un propietario a un inmueble
}




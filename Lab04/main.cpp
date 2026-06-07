#include <iostream>
#include <stdexcept>

#include "Sistema.h"
#include "DataTypes/DtDireccion.h"
#include "DataTypes/DtFecha.h"
#include "DataTypes/DtInmueble.h"
#include "DataTypes/DtPropietario.h"
#include "DataTypes/DtInmobiliaria.h"
#include "DataTypes/DtInmXProp.h"
#include "DataTypes/DtInmuebleAdministrado.h"
#include "DataTypes/TipoTecho.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/interfaces/IIterator.h"

// =========================================================
// HELPERS DE IMPRESIÓN
// =========================================================

void seccion(const std::string& titulo) {
    std::cout << "\n========================================\n";
    std::cout << "  " << titulo << "\n";
    std::cout << "========================================\n";
}

void imprimirDireccion(const DtDireccion& dir) {
    std::cout << dir.getCalle() << " " << dir.getNumero() << ", " << dir.getCiudad();
}

void imprimirPropietarios(ICollection* lista) {
    std::cout << "  Propietarios registrados (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtPropietario* dt = dynamic_cast<DtPropietario*>(it->getCurrent());
        if (dt)
            std::cout << "    - [" << dt->getNickname() << "] " << dt->getNombre() << "\n";
        it->next();
    }
    delete it;
}

void imprimirInmobiliarias(ICollection* lista) {
    std::cout << "  Inmobiliarias registradas (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtInmobiliaria* dt = dynamic_cast<DtInmobiliaria*>(it->getCurrent());
        if (dt)
            std::cout << "    - [" << dt->getNickname() << "] " << dt->getNombre() << "\n";
        it->next();
    }
    delete it;
}

void imprimirInmueblesXPropietario(ICollection* lista) {
    std::cout << "  Inmuebles por propietario (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtInmXProp* dt = dynamic_cast<DtInmXProp*>(it->getCurrent());
        if (dt) {
            std::cout << "    - id=" << dt->getNumId() << " | Dir: ";
            imprimirDireccion(dt->getDireccion());
            std::cout << " | Propietario: " << dt->getPropietariovinculado().getNickname() << "\n";
        }
        it->next();
    }
    delete it;
}

void imprimirInmueblesAdministrados(ICollection* lista) {
    std::cout << "  Inmuebles administrados (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtInmuebleAdministrado* dt = dynamic_cast<DtInmuebleAdministrado*>(it->getCurrent());
        if (dt) {
            std::cout << "    - id=" << dt->getNumId() << " | Dir: ";
            imprimirDireccion(dt->getDireccion());
            std::cout << "\n";
        }
        it->next();
    }
    delete it;
}


// =========================================================
// MAIN
// =========================================================

int main() {

    Sistema sistema;

    // =========================================================
    // CASO 1: ALTA DE USUARIOS
    // =========================================================
    seccion("CASO 1: ALTA DE USUARIOS");

    // --- Clientes ---
    try {
        if (!sistema.existeUsuario("jperez")) {
            sistema.altaCliente("jperez", "Juan", "jperez@mail.com", "pass123", "Perez", "12345678");
            std::cout << "[OK] Cliente 'jperez' dado de alta.\n";
        }
        if (!sistema.existeUsuario("mgarcia")) {
            sistema.altaCliente("mgarcia", "Maria", "mgarcia@mail.com", "pass456", "Garcia", "87654321");
            std::cout << "[OK] Cliente 'mgarcia' dado de alta.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta de cliente: " << e.what() << "\n";
    }

    // --- Propietario 1: prop_lopez con una Casa ---
    try {
        if (!sistema.existeUsuario("prop_lopez")) {
            sistema.altaPropietario("prop_lopez", "Carlos", "clopez@mail.com", "propPass1", "099123456", 100200300);
            std::cout << "[OK] Propietario 'prop_lopez' dado de alta.\n";

            DtDireccion dirCasa("Rivera", 1234, "Montevideo");
            DtFecha fechaCasa(1, 1, 2005);
            sistema.crearCasa(dirCasa, fechaCasa, 120.5f, false, TipoTecho::TECHO_PLANO);
            std::cout << "[OK] Casa creada y vinculada a 'prop_lopez' (id=1).\n";

            sistema.finalizarAltaPropietario();
            std::cout << "[OK] Alta de 'prop_lopez' finalizada.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta propietario 1: " << e.what() << "\n";
    }

    // --- Propietario 2: prop_torres con un Apartamento ---
    try {
        if (!sistema.existeUsuario("prop_torres")) {
            sistema.altaPropietario("prop_torres", "Ana", "atorres@mail.com", "propPass2", "091987654", 200300400);
            std::cout << "[OK] Propietario 'prop_torres' dado de alta.\n";

            DtDireccion dirApto("18 de Julio", 900, "Montevideo");
            DtFecha fechaApto(15, 6, 2010);
            sistema.crearApartamento(dirApto, fechaApto, 75.0f, 3, true, 2500.0f);
            std::cout << "[OK] Apartamento creado y vinculado a 'prop_torres' (id=2).\n";

            sistema.finalizarAltaPropietario();
            std::cout << "[OK] Alta de 'prop_torres' finalizada.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta propietario 2: " << e.what() << "\n";
    }

    // --- Inmobiliaria ---
    try {
        if (!sistema.existeUsuario("inmo_sol")) {
            DtDireccion dirInmo("Av. Italia", 5678, "Montevideo");
            sistema.altaInmobiliaria(
                "inmo_sol", "Inmobiliaria Sol", "sol@inmosol.com", "inmoPass1",
                dirInmo, "29001234", "https://www.inmosol.com"
            );
            std::cout << "[OK] Inmobiliaria 'inmo_sol' creada.\n";

            ICollection* propietarios = sistema.listarPropietarios();
            imprimirPropietarios(propietarios);
            delete propietarios;

            sistema.vincularPropietario("prop_lopez");
            std::cout << "[OK] 'prop_lopez' vinculado a 'inmo_sol'.\n";
            sistema.vincularPropietario("prop_torres");
            std::cout << "[OK] 'prop_torres' vinculado a 'inmo_sol'.\n";

            sistema.finalizarAltaInmobiliaria();
            std::cout << "[OK] Alta de inmobiliaria finalizada.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta inmobiliaria: " << e.what() << "\n";
    }


    // =========================================================
    // CASO 2: ALTA DE ADMINISTRACIÓN
    // =========================================================
    seccion("CASO 2: ALTA DE ADMINISTRACIÓN");

    try {
        ICollection* inmobiliarias = sistema.listarInmobiliarias();
        imprimirInmobiliarias(inmobiliarias);
        delete inmobiliarias;

        ICollection* inmueblesDisponibles = sistema.seleccionarInmobiliaria("inmo_sol");
        imprimirInmueblesXPropietario(inmueblesDisponibles);
        delete inmueblesDisponibles;

        sistema.altaAdministracion(1);
        std::cout << "[OK] Administración del inmueble id=1 dada de alta.\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta de administración: " << e.what() << "\n";
    }


    // =========================================================
    // CASO 3: ALTA DE PUBLICACIÓN
    // =========================================================
    seccion("CASO 3: ALTA DE PUBLICACIÓN");

    try {
        ICollection* inmobiliarias = sistema.listarInmobiliarias();
        imprimirInmobiliarias(inmobiliarias);
        delete inmobiliarias;

        ICollection* inmueblesAdm = sistema.seleccionarInmobiliariaAdministrada("inmo_sol");
        imprimirInmueblesAdministrados(inmueblesAdm);
        delete inmueblesAdm;

        sistema.altaPublicacion(1, "Casa amplia con jardín en Montevideo.", 15000.0f, false);
        std::cout << "[OK] Publicación de alquiler creada para inmueble id=1.\n";

        // El id=2 no tiene administración, se espera error
        try {
            sistema.altaPublicacion(2, "Apartamento moderno con ascensor.", 120000.0f, true);
            std::cout << "[OK] Publicación de venta creada para inmueble id=2.\n";
        } catch (const std::exception& e) {
            std::cerr << "[ESPERADO] id=2 sin administración: " << e.what() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta de publicación: " << e.what() << "\n";
    }


    // =========================================================
    // CASO 4: ELIMINAR INMUEBLE
    // =========================================================
    seccion("CASO 4: ELIMINAR INMUEBLE");

    try {
        std::cout << "  --- Antes de eliminar ---\n";
        ICollection* antes = sistema.listarinmueblesxpropietario();
        imprimirInmueblesXPropietario(antes);
        delete antes;

        DtInmueble dtInm = sistema.seleccionarInmueble(2);
        std::cout << "[OK] Inmueble id=" << dtInm.getNumId()
                  << " seleccionado | Superficie: " << dtInm.getSuperficie() << " m2 | Dir: ";
        imprimirDireccion(dtInm.getDireccion());
        std::cout << "\n";

        sistema.eliminarInmueble(2);
        std::cout << "[OK] Inmueble id=2 eliminado.\n";

        std::cout << "  --- Después de eliminar ---\n";
        ICollection* despues = sistema.listarinmueblesxpropietario();
        imprimirInmueblesXPropietario(despues);
        delete despues;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Eliminar inmueble: " << e.what() << "\n";
    }


    seccion("FIN DE LA EJECUCIÓN");
    std::cout << "Todos los casos ejecutados.\n\n";

    return 0;
}

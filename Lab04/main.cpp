#include <iostream>
#include <stdexcept>

#include "Sistema.h"
#include "DataTypes/DtDireccion.h"
#include "DataTypes/DtFecha.h"
#include "DataTypes/DtVisita.h"
#include "DataTypes/DtInmueble.h"
#include "DataTypes/DtPropietario.h"
#include "DataTypes/DtInmobiliaria.h"
#include "DataTypes/DtInmXProp.h"
#include "DataTypes/DtInmuebleAdministrado.h"
#include "DataTypes/DataFiltro.h"
#include "DataTypes/DtPublicacion.h"
#include "DataTypes/TipoTecho.h"
#include "DataTypes/TipoInmueble.h"
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
        DtPropietario* dt = static_cast<DtPropietario*>(it->getCurrent());
        std::cout << "    - [" << dt->getNickname() << "] " << dt->getNombre() << "\n";
        it->next();
    }
    delete it;
}

void imprimirInmobiliarias(ICollection* lista) {
    std::cout << "  Inmobiliarias registradas (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtInmobiliaria* dt = static_cast<DtInmobiliaria*>(it->getCurrent());
        std::cout << "    - [" << dt->getNickname() << "] " << dt->getNombre() << "\n";
        it->next();
    }
    delete it;
}

void imprimirInmueblesXPropietario(ICollection* lista) {
    std::cout << "  Inmuebles por propietario (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtInmXProp* dt = static_cast<DtInmXProp*>(it->getCurrent());
        std::cout << "    - id=" << dt->getNumId() << " | Dir: ";
        imprimirDireccion(dt->getDireccion());
        std::cout << " | Propietario: " << dt->getPropietariovinculado().getNickname() << "\n";
        it->next();
    }
    delete it;
}

void imprimirInmueblesAdministrados(ICollection* lista) {
    std::cout << "  Inmuebles administrados (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DtInmuebleAdministrado* dt = static_cast<DtInmuebleAdministrado*>(it->getCurrent());
        std::cout << "    - id=" << dt->getNumId() << " | Dir: ";
        imprimirDireccion(dt->getDireccion());
        std::cout << "\n";
        it->next();
    }
    delete it;
}

void imprimirFiltro(ICollection* lista) {
    std::cout << "  Resultados (" << lista->getSize() << "):\n";
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        DataFiltro* df = static_cast<DataFiltro*>(it->getCurrent());
        DtInmobiliaria inmo = df->getDatosInmobiliaria();
        DtPublicacion  pub  = df->getDatosPublicacion();
        std::string tipo = (pub.getTipo() == TipoInmueble::CASA) ? "Casa" : "Apartamento";
        std::cout << "    - [" << inmo.getNickname() << "]"
                  << " id_pub=" << pub.getID()
                  << " | " << tipo
                  << " | " << pub.getTexto() << "\n";
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

        sistema.altaPublicacion(1, "Casa amplia con jardin en Montevideo.", 15000.0f, false);
        std::cout << "[OK] Publicacion de alquiler creada para inmueble id=1.\n";

        try {
            sistema.altaPublicacion(2, "Apartamento moderno con ascensor.", 120000.0f, true);
            std::cout << "[OK] Publicacion de venta creada para inmueble id=2.\n";
        } catch (const std::exception& e) {
            std::cerr << "[ESPERADO] id=2 sin administracion: " << e.what() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta de publicacion: " << e.what() << "\n";
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

        std::cout << "  --- Despues de eliminar ---\n";
        ICollection* despues = sistema.listarinmueblesxpropietario();
        imprimirInmueblesXPropietario(despues);
        delete despues;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Eliminar inmueble: " << e.what() << "\n";
    }


    // =========================================================
    // CASO 5: FILTRAR PUBLICACIONES
    // =========================================================
    seccion("CASO 5: FILTRAR PUBLICACIONES");

    try {
        // Alquileres de Casa entre $0 y $20000 — debería encontrar la publicacion del id=1
        std::cout << "  Filtro: Alquiler | $0-$20000 | Casa\n";
        ICollection* filtro1 = sistema.filtrarPublicaciones(false, 0.0f, 20000.0f, TipoInmueble::CASA);
        imprimirFiltro(filtro1);
        delete filtro1;

        // Alquileres de Apartamento — no debería encontrar nada (id=2 fue eliminado)
        std::cout << "  Filtro: Alquiler | $0-$20000 | Apartamento\n";
        ICollection* filtro2 = sistema.filtrarPublicaciones(false, 0.0f, 20000.0f, TipoInmueble::APARTAMENTO);
        imprimirFiltro(filtro2);
        delete filtro2;

        // Alquileres de cualquier tipo — debería encontrar la publicacion del id=1
        std::cout << "  Filtro: Alquiler | $0-$20000 | Ambos\n";
        ICollection* filtro3 = sistema.filtrarPublicaciones(false, 0.0f, 20000.0f, TipoInmueble::AMBOS);
        imprimirFiltro(filtro3);
        delete filtro3;

        // Ventas de cualquier tipo — no debería encontrar nada
        std::cout << "  Filtro: Venta | $0-$999999 | Ambos\n";
        ICollection* filtro4 = sistema.filtrarPublicaciones(true, 0.0f, 999999.0f, TipoInmueble::AMBOS);
        imprimirFiltro(filtro4);
        delete filtro4;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Filtrar publicaciones: " << e.what() << "\n";
    }


    // =========================================================
    // CASO 6: SELECCIONAR PUBLICACION
    // =========================================================
    seccion("CASO 6: SELECCIONAR PUBLICACION");

    try {
        // Buscar la publicacion id=1 — debería devolver los datos de la Casa
        DtInmueble dt = sistema.seleccionarPublicacion(1);
        std::cout << "[OK] Publicacion id=1 encontrada:\n";
        std::cout << "    id_inmueble=" << dt.getNumId()
                  << " | Superficie: " << dt.getSuperficie() << " m2"
                  << " | Dir: ";
        imprimirDireccion(dt.getDireccion());
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] seleccionarPublicacion id=1: " << e.what() << "\n";
    }

    try {
        // Buscar una publicacion inexistente — debería lanzar excepcion
        DtInmueble dt = sistema.seleccionarPublicacion(99);
        std::cout << "[OK] Publicacion id=99 encontrada (inesperado).\n";
    } catch (const std::exception& e) {
        std::cerr << "[ESPERADO] Publicacion id=99 no existe: " << e.what() << "\n";
    }

    seccion("FIN DE LA EJECUCION");
    std::cout << "Todos los casos ejecutados.\n\n";


    // =========================================================
    // CASO 7: VISITAS
    // =========================================================
    seccion("CASO 7: VISITAS");

    try {
        // Alta de visita de cliente "jperez" a la publicación id=1
        DtFecha fechaVisita(8, 6, 2026);
        sistema.altaVisita("jperez", 1, fechaVisita);
        std::cout << "[OK] Visita registrada para cliente 'jperez' en publicación id=1.\n";

        // Listar visitas de la publicación id=1
        ICollection* visitas = sistema.listarVisitas(1);
        std::cout << "  Visitas registradas (" << visitas->getSize() << "):\n";
        IIterator* itVis = visitas->getIterator();
        while (itVis->hasCurrent()) {
            DtVisita* dv = static_cast<DtVisita*>(itVis->getCurrent());
            if (dv != nullptr) {
                std::cout << "    - Cliente=" << dv->getNicknameCliente()
                        << " | Fecha=" << dv->getFecha().getDia() << "/"
                        << dv->getFecha().getMes() << "/"
                        << dv->getFecha().getAnio()
                        << " | PublicacionID=" << dv->getIdPublicacion()
                        << "\n";
            }
            itVis->next();
        }
        delete itVis;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Alta/Listar visitas: " << e.what() << "\n";
    }

        return 0;

        
}



#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

//Clases
#include "Sistema.h"

//Data Types
#include "DataTypes/DtDireccion.h"
#include "DataTypes/DtFecha.h"
#include "DataTypes/DtInmueble.h"
#include "DataTypes/DtPropietario.h"
#include "DataTypes/DtInmobiliaria.h"
#include "DataTypes/DtInmXProp.h"
#include "DataTypes/DtInmuebleAdministrado.h"
#include "DataTypes/DataFiltro.h"
#include "DataTypes/DtPublicacion.h"
#include "DataTypes/DtVisita.h"
#include "DataTypes/TipoTecho.h"
#include "DataTypes/TipoInmueble.h"
#include "DataTypes/DtCasa.h"
#include "DataTypes/DtApartamento.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/interfaces/IIterator.h"
#include "Factory.h"

ISistema* sistemaPtr = nullptr;
#define sistema (*static_cast<Sistema*>(sistemaPtr))

// =========================================================
// UTILIDADES
// =========================================================

void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string leerLinea(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);
    return valor;
}

int leerEntero(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limpiarBuffer();
            return valor;
        }
        std::cin.clear();
        limpiarBuffer();
        std::cout << "  [!] Ingrese un número válido.\n";
    }
}

float leerFloat(const std::string& prompt) {
    float valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limpiarBuffer();
            return valor;
        }
        std::cin.clear();
        limpiarBuffer();
        std::cout << "  [!] Ingrese un número válido.\n";
    }
}

DtFecha leerFecha(const std::string& prompt) {
    std::cout << prompt << "\n";
    int dia = leerEntero("    Dia: ");
    int mes = leerEntero("    Mes: ");
    int anio = leerEntero("    Anio: ");
    return DtFecha(dia, mes, anio);
}

DtDireccion leerDireccion(const std::string& prompt) {
    std::cout << prompt << "\n";
    std::string calle  = leerLinea("    Calle: ");
    int numero         = leerEntero("    Numero: ");
    std::string ciudad = leerLinea("    Ciudad: ");
    return DtDireccion(calle.c_str(), numero, ciudad.c_str());
}

void separador() {
    std::cout << "\n----------------------------------------\n";
}

// =========================================================
// HELPERS DE IMPRESIÓN
// =========================================================

void imprimirDireccion(const DtDireccion& dir) {
    std::cout << dir.getCalle() << " " << dir.getNumero() << ", " << dir.getCiudad();
}

void imprimirPropietarios(ICollection* lista) {
    if (lista->isEmpty()) {
        std::cout << "  (No hay propietarios registrados)\n";
    } else {
        std::cout << "  Propietarios (" << lista->getSize() << "):\n";
        IIterator* it = lista->getIterator();
        while (it->hasCurrent()) {
            DtPropietario* dt = static_cast<DtPropietario*>(it->getCurrent());
            std::cout << "    - [" << dt->getNickname() << "] " << dt->getNombre() << "\n";
            it->next();
        }
        delete it;
    }
}

void imprimirInmobiliarias(ICollection* lista) {
    if (lista->isEmpty()) {
        std::cout << "  (No hay inmobiliarias registradas)\n";
    } else {
        std::cout << "  Inmobiliarias (" << lista->getSize() << "):\n";
        IIterator* it = lista->getIterator();
        while (it->hasCurrent()) {
            DtInmobiliaria* dt = static_cast<DtInmobiliaria*>(it->getCurrent());
            std::cout << "    - [" << dt->getNickname() << "] " << dt->getNombre() << "\n";
            it->next();
        }
        delete it;
    }
}

void imprimirInmueblesXPropietario(ICollection* lista) {
    if (lista->isEmpty()) {
        std::cout << "  (No hay inmuebles registrados)\n";
    } else {
        std::cout << "  Inmuebles (" << lista->getSize() << "):\n";
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
}

void imprimirInmueblesAdministrados(ICollection* lista) {
    if (lista->isEmpty()) {
        std::cout << "  (No hay inmuebles administrados)\n";
    } else {
        std::cout << "  Inmuebles administrados (" << lista->getSize() << "):\n";
        IIterator* it = lista->getIterator();
        while (it->hasCurrent()) {
            DtInmuebleAdministrado* dt = static_cast<DtInmuebleAdministrado*>(it->getCurrent());
            DtFecha fecha = dt->getFechaAdministracion().getFechaInicio();
            std::cout << "    - id=" << dt->getNumId() << " | Dir: ";
            imprimirDireccion(dt->getDireccion());
            std::cout << " | Desde: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << "\n";
            it->next();
        }
        delete it;
    }
}

void imprimirFiltro(ICollection* lista) {
    if (lista->isEmpty()) {
        std::cout << "  (No se encontraron publicaciones)\n";
    } else {
        std::cout << "  Resultados (" << lista->getSize() << "):\n";
        IIterator* it = lista->getIterator();
        while (it->hasCurrent()) {
            DataFiltro* df = static_cast<DataFiltro*>(it->getCurrent());
            DtInmobiliaria inmo = df->getDatosInmobiliaria();
            DtPublicacion  pub  = df->getDatosPublicacion();
            std::string tipo = (pub.getTipo() == TipoInmueble::CASA) ? "Casa" : "Apartamento";
            std::cout << "    - id_pub=" << pub.getID()
                      << " | " << tipo
                      << " | [" << inmo.getNickname() << "]"
                      << " | " << pub.getTexto() << "\n";
            it->next();
        }
        delete it;
    }
}

// =========================================================
// CASOS
// =========================================================

void altaCliente() {
    separador();
    std::cout << "  ALTA CLIENTE\n";
    separador();
    std::string nick  = leerLinea("  Nickname: ");
    std::string nom   = leerLinea("  Nombre: ");
    std::string email = leerLinea("  Email: ");
    std::string pass  = leerLinea("  Contrasenia: ");
    std::string apell = leerLinea("  Apellido: ");
    std::string doc   = leerLinea("  Documento: ");

    sistema.altaCliente(nick.c_str(), nom.c_str(), email.c_str(), pass.c_str(), apell.c_str(), doc.c_str());
    std::cout << "  [OK] Cliente '" << nick << "' dado de alta.\n";
}

void altaPropietario() {
    separador();
    std::cout << "  ALTA PROPIETARIO\n";
    separador();
    std::string nick  = leerLinea("  Nickname: ");
    std::string nom   = leerLinea("  Nombre: ");
    std::string email = leerLinea("  Email: ");
    std::string pass  = leerLinea("  Contrasenia: ");
    std::string tel   = leerLinea("  Telefono: ");
    int cuenta        = leerEntero("  Cuenta bancaria: ");

    sistema.altaPropietario(nick.c_str(), nom.c_str(), email.c_str(), pass.c_str(), tel.c_str(), cuenta);
    std::cout << "  [OK] Propietario '" << nick << "' dado de alta.\n";

    // Loop de inmuebles
    while (true) {
        separador();
        std::cout << "  Agregar inmueble:\n";
        std::cout << "    1- Casa\n";
        std::cout << "    2- Apartamento\n";
        std::cout << "    0- Finalizar\n";
        int opInm = leerEntero("  Opcion: ");

        if (opInm == 0) break;

        DtDireccion dir      = leerDireccion("  Direccion:");
        DtFecha fechaConst   = leerFecha("  Anio de construccion:");
        float superficie     = leerFloat("  Superficie (m2): ");

        if (opInm == 1) {
            std::cout << "  Tipo de techo:\n";
            std::cout << "    1- Techo plano\n";
            std::cout << "    2- Techo a dos aguas\n";
            std::cout << "    3- Techo liviano\n";
            int opTecho = leerEntero("  Opcion: ");
            TipoTecho techo = (opTecho == 1) ? TipoTecho::TECHO_PLANO :
                              (opTecho == 2) ? TipoTecho::TECHO_A_DOS_AGUAS :
                                               TipoTecho::TECHO_LIVIANO;
            std::string propH = leerLinea("  Propiedad horizontal (s/n): ");
            bool propHoriz = (propH == "s" || propH == "S");

            sistema.crearCasa(dir, fechaConst, superficie, propHoriz, techo);
            std::cout << "  [OK] Casa creada.\n";

        } else if (opInm == 2) {
            int piso          = leerEntero("  Piso: ");
            std::string ascStr = leerLinea("  Tiene ascensor (s/n): ");
            bool ascensor     = (ascStr == "s" || ascStr == "S");
            float gastos      = leerFloat("  Gastos comunes: ");

            sistema.crearApartamento(dir, fechaConst, superficie, piso, ascensor, gastos);
            std::cout << "  [OK] Apartamento creado.\n";
        } else {
            std::cout << "  [!] Opcion invalida.\n";
        }
    }

    sistema.finalizarAltaPropietario();
    std::cout << "  [OK] Alta de propietario finalizada.\n";
}

void altaInmobiliaria() {
    separador();
    std::cout << "  ALTA INMOBILIARIA\n";
    separador();
    std::string nick  = leerLinea("  Nickname: ");
    std::string nom   = leerLinea("  Nombre: ");
    std::string email = leerLinea("  Email: ");
    std::string pass  = leerLinea("  Contrasenia: ");
    DtDireccion dir   = leerDireccion("  Direccion:");
    std::string tel   = leerLinea("  Telefono: ");
    std::string url   = leerLinea("  URL: ");

    sistema.altaInmobiliaria(nick.c_str(), nom.c_str(), email.c_str(), pass.c_str(), dir, tel.c_str(), url.c_str());
    std::cout << "  [OK] Inmobiliaria '" << nick << "' creada.\n";

    // Listar propietarios y vincular en loop
    ICollection* props = sistema.listarPropietarios();
    imprimirPropietarios(props);
    delete props;

    while (true) {
        separador();
        std::string nickProp = leerLinea("  Nickname del propietario a vincular (Enter para finalizar): ");
        if (nickProp.empty()) break;
        try {
            sistema.vincularPropietario(nickProp.c_str());
            std::cout << "  [OK] '" << nickProp << "' vinculado.\n";
        } catch (const std::exception& e) {
            std::cout << "  [!] " << e.what() << "\n";
        }
    }

    sistema.finalizarAltaInmobiliaria();
    std::cout << "  [OK] Alta de inmobiliaria finalizada.\n";
}

void casoAltaUsuario() {
    separador();
    std::cout << "  ALTA USUARIO\n";
    std::cout << "  Tipo de usuario:\n";
    std::cout << "    1- Cliente\n";
    std::cout << "    2- Propietario\n";
    std::cout << "    3- Inmobiliaria\n";
    int op = leerEntero("  Opcion: ");
    try {
        if      (op == 1) altaCliente();
        else if (op == 2) altaPropietario();
        else if (op == 3) altaInmobiliaria();
        else std::cout << "  [!] Opcion invalida.\n";
    } catch (const std::exception& e) {
        std::cout << "  [!] Error: " << e.what() << "\n";
    }
}

void casoAltaAdministracion() {
    separador();
    std::cout << "  ALTA ADMINISTRACION\n";
    separador();
    try {
        ICollection* inmos = sistema.listarInmobiliarias();
        imprimirInmobiliarias(inmos);
        bool sinInmos = inmos->isEmpty();
        delete inmos;
        if (sinInmos) return;

        std::string nickInmo = leerLinea("  Nickname de la inmobiliaria: ");
        ICollection* inmuebles = sistema.seleccionarInmobiliaria(nickInmo.c_str());
        imprimirInmueblesXPropietario(inmuebles);
        delete inmuebles;

        int idInm = leerEntero("  ID del inmueble a administrar: ");
        sistema.altaAdministracion(idInm);
        std::cout << "  [OK] Administracion dada de alta.\n";
    } catch (const std::exception& e) {
        std::cout << "  [!] Error: " << e.what() << "\n";
    }
}

void casoAltaPublicacion() {
    separador();
    std::cout << "  ALTA PUBLICACION\n";
    separador();
    try {
        ICollection* inmos = sistema.listarInmobiliarias();
        imprimirInmobiliarias(inmos);
        bool sinInmos2 = inmos->isEmpty();
        delete inmos;
        if (sinInmos2) return;

        std::string nickInmo = leerLinea("  Nickname de la inmobiliaria: ");
        ICollection* inmuebles = sistema.seleccionarInmobiliariaAdministrada(nickInmo.c_str());
        imprimirInmueblesAdministrados(inmuebles);
        delete inmuebles;

        int idInm       = leerEntero("  ID del inmueble: ");
        std::string txt = leerLinea("  Descripcion: ");
        float precio    = leerFloat("  Precio: ");
        std::cout << "  Tipo de publicacion:\n";
        std::cout << "    1- Venta\n";
        std::cout << "    2- Alquiler\n";
        int opTipo  = leerEntero("  Opcion: ");
        bool tipoPub = (opTipo == 1);

        sistema.altaPublicacion(idInm, txt.c_str(), precio, tipoPub);
        std::cout << "  [OK] Publicacion creada.\n";
    } catch (const std::exception& e) {
        std::cout << "  [!] Error: " << e.what() << "\n";
    }
}

void casoAgendarVisita() {
    separador();
    std::cout << "  AGENDAR VISITA\n";
    separador();
    try {
        std::string nickCliente = leerLinea("  Nickname del cliente: ");
        int idPub               = leerEntero("  ID de la publicacion: ");
        DtFecha fecha           = leerFecha("  Fecha de la visita:");
        std::string contacto    = leerLinea("  Forma de contacto: ");

        sistema.altaVisita(nickCliente.c_str(), idPub, fecha, contacto.c_str());
        std::cout << "  [OK] Visita agendada.\n";
    } catch (const std::exception& e) {
        std::cout << "  [!] Error: " << e.what() << "\n";
    }
}

void casoConsultarPublicaciones() {
    separador();
    std::cout << "  CONSULTAR PUBLICACIONES\n";
    separador();
    try {
        // Filtros
        std::cout << "  Tipo de publicacion:\n";
        std::cout << "    1- Venta\n";
        std::cout << "    2- Alquiler\n";
        int opTipo   = leerEntero("  Opcion: ");
        bool tipoPub = (opTipo == 1);

        float precioMin = leerFloat("  Precio minimo: ");
        float precioMax = leerFloat("  Precio maximo: ");

        std::cout << "  Tipo de inmueble:\n";
        std::cout << "    1- Casa\n";
        std::cout << "    2- Apartamento\n";
        std::cout << "    3- Ambos\n";
        int opInm = leerEntero("  Opcion: ");
        TipoInmueble tipoInm = (opInm == 1) ? TipoInmueble::CASA :
                               (opInm == 2) ? TipoInmueble::APARTAMENTO :
                                              TipoInmueble::AMBOS;

        ICollection* filtro = sistema.filtrarPublicaciones(tipoPub, precioMin, precioMax, tipoInm);
        imprimirFiltro(filtro);

        if (!filtro->isEmpty()) {
            int idPub = leerEntero("  Seleccionar publicacion por ID (0 para omitir): ");
            if (idPub != 0) {
                DtInmueble* dt = sistema.seleccionarPublicacion(idPub);
                std::cout << "  Inmueble asociado:\n";
                std::cout << "    id=" << dt->getNumId()
                        << " | Superficie: " << dt->getSuperficie() << " m2"
                        << " | Dir: ";
                imprimirDireccion(dt->getDireccion());
                std::cout << "\n";
                if (DtCasa* c = dynamic_cast<DtCasa*>(dt)) {
                    std::cout << "    Tipo: Casa\n";
                    std::cout << "    Propiedad horizontal: " << (c->getPropiedadHorizontal() ? "Si" : "No") << "\n";
                    std::string tipoTechoStr;
                    switch (c->getTecho()) {
                        case TipoTecho::TECHO_PLANO:        tipoTechoStr = "Techo plano"; break;
                        case TipoTecho::TECHO_A_DOS_AGUAS:  tipoTechoStr = "Techo a dos aguas"; break;
                        case TipoTecho::TECHO_LIVIANO:      tipoTechoStr = "Techo liviano"; break;
                    }
                    std::cout << "    Techo: " << tipoTechoStr << "\n";
                } else if (DtApartamento* a = dynamic_cast<DtApartamento*>(dt)) {
                    std::cout << "    Tipo: Apartamento\n";
                    std::cout << "    Piso: " << a->getNumeroPiso() << "\n";
                    std::cout << "    Ascensor: " << (a->hayAscensor() ? "Si" : "No") << "\n";
                    std::cout << "    Gastos comunes: $" << a->getGastosComunes() << "\n";
                }
                delete dt;
                            }
                        }
                        delete filtro;
                    } catch (const std::exception& e) {
                        std::cout << "  [!] Error: " << e.what() << "\n";
                    }
                }


void casoEliminarInmueble() {
    separador();
    std::cout << "  ELIMINAR INMUEBLE\n";
    separador();
    try {
        ICollection* lista = sistema.listarinmueblesxpropietario();
        imprimirInmueblesXPropietario(lista);
        delete lista;

        int idInm = leerEntero("  ID del inmueble a eliminar: ");
        DtInmueble dt = sistema.seleccionarInmueble(idInm);
        std::cout << "  Inmueble seleccionado: id=" << dt.getNumId()
                  << " | Superficie: " << dt.getSuperficie() << " m2"
                  << " | Dir: ";
        imprimirDireccion(dt.getDireccion());
        std::cout << "\n";

        std::string confirm = leerLinea("  Confirmar eliminacion (s/n): ");
        if (confirm == "s" || confirm == "S") {
            sistema.eliminarInmueble(idInm);
            std::cout << "  [OK] Inmueble eliminado.\n";
        } else {
            std::cout << "  [!] Eliminacion cancelada.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "  [!] Error: " << e.what() << "\n";
    }
}

// =========================================================
// PRECARGA
// =========================================================

void precargar() {
    std::cout << "\n  [Precargando datos...]\n";

    // Clientes
    sistema.altaCliente("jperez", "Juan", "jperez@mail.com", "pass123", "Perez", "12345678");
    sistema.altaCliente("mgarcia", "Maria", "mgarcia@mail.com", "pass456", "Garcia", "87654321");

    // Propietario 1: prop_lopez con una Casa (id=1)
    sistema.altaPropietario("prop_lopez", "Carlos", "clopez@mail.com", "propPass1", "099123456", 100200300);
    sistema.crearCasa(
        DtDireccion("Rivera", 1234, "Montevideo"),
        DtFecha(1, 1, 2005),
        120.5f, false, TipoTecho::TECHO_PLANO
    );
    sistema.finalizarAltaPropietario();

    // Propietario 2: prop_torres con un Apartamento (id=2)
    sistema.altaPropietario("prop_torres", "Ana", "atorres@mail.com", "propPass2", "091987654", 200300400);
    sistema.crearApartamento(
        DtDireccion("18 de Julio", 900, "Montevideo"),
        DtFecha(15, 6, 2010),
        75.0f, 3, true, 2500.0f
    );
    sistema.finalizarAltaPropietario();

    // Inmobiliaria
    sistema.altaInmobiliaria(
        "inmo_sol", "Inmobiliaria Sol", "sol@inmosol.com", "inmoPass1",
        DtDireccion("Av. Italia", 5678, "Montevideo"),
        "29001234", "https://www.inmosol.com"
    );
    sistema.vincularPropietario("prop_lopez");
    sistema.vincularPropietario("prop_torres");
    sistema.finalizarAltaInmobiliaria();

    // Administracion del inmueble id=1
    sistema.seleccionarInmobiliaria("inmo_sol");
    sistema.altaAdministracion(1);

    // Publicacion de alquiler para inmueble id=1
    sistema.altaPublicacion(1, "Casa amplia con jardin en Montevideo.", 15000.0f, false);

    std::cout << "  [OK] Datos precargados:\n";
    std::cout << "       Clientes:       jperez, mgarcia\n";
    std::cout << "       Propietarios:   prop_lopez (Casa id=1), prop_torres (Apto id=2)\n";
    std::cout << "       Inmobiliaria:   inmo_sol\n";
    std::cout << "       Administracion: inmueble id=1\n";
    std::cout << "       Publicacion:    id=1 | Alquiler | $15000\n";
}

// =========================================================
// MAIN
// =========================================================

int main() {
    // Obtener el Sistema via Factory (singleton)
    sistemaPtr = Factory::getInstancia()->getSistema();

    std::cout << "\n  ================================\n";
    std::cout << "    Sistema de Gestion Inmobiliaria\n";
    std::cout << "  ================================\n";

    std::cout << "\n  Desea precargar datos de prueba? (s/n): ";
    std::string resp;
    std::getline(std::cin, resp);
    if (resp == "s" || resp == "S") {
        try {
            precargar();
        } catch (const std::exception& e) {
            std::cout << "  [!] Error en precarga: " << e.what() << "\n";
        }
    }

    while (true) {
        separador();
        std::cout << "  MENU PRINCIPAL\n";
        std::cout << "    1- Alta Usuario\n";
        std::cout << "    2- Alta Administracion\n";
        std::cout << "    3- Alta Publicacion\n";
        std::cout << "    4- Agendar Visita\n";
        std::cout << "    5- Consultar Publicaciones\n";
        std::cout << "    6- Eliminar Inmueble\n";
        std::cout << "    0- Salir\n";
        separador();

        int op = leerEntero("  Opcion: ");

        switch (op) {
            case 1: casoAltaUsuario();          break;
            case 2: casoAltaAdministracion();   break;
            case 3: casoAltaPublicacion();      break;
            case 4: casoAgendarVisita();        break;
            case 5: casoConsultarPublicaciones(); break;
            case 6: casoEliminarInmueble();     break;
            case 0:
                return 0;
            default:
                std::cout << "  [!] Opcion invalida.\n";
        }
    }
}

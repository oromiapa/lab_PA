#include <iostream>
#include <stdexcept>

// Se incluyen los DataTypes necesarios para los parámetros
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/TipoTecho.h"
#include "./DataTypes/DtPropietario.h"
#include "./DataTypes/DtInmobiliaria.h" // <-- NUEVO: Para poder listar las inmobiliarias
#include "./DataTypes/DtInmXProp.h" 

// Se incluyen las interfaces de las colecciones para poder iterar
#include "./ICollection/interfaces/ICollection.h"
#include "./ICollection/interfaces/IIterator.h"

// Se incluye la Factory para acceder al sistema de forma correcta
#include "Factory.h"
#include "ISistema.h"

int main() {
    std::cout << "========== INICIANDO PRUEBAS DEL SISTEMA ==========" << std::endl;

    // 1. Obtener la interfaz del sistema a través de la Fábrica
    ISistema* sys = Factory::getInstancia()->getSistema();
    std::cout << "[OK] Sistema instanciado correctamente a traves de la Factory." << std::endl;

    // 2. Definir datos de prueba globales
    DtDireccion dirCasa("Av. Siempreviva", 742, "Springfield");
    DtDireccion dirApto("18 de Julio", 1234, "Montevideo");
    DtDireccion dirInmo("Sarandi", 555, "San Jose");
    DtFecha fechaConstruccion(15, 5, 2010);

    // 3. CASO DE USO: Alta de Propietario con sus Inmuebles asociados
    std::cout << "\n--- [Caso de Uso] Alta de Propietario e Inmuebles ---" << std::endl;
    try {
        sys->altaPropietario("maria_prop", "Maria Lopez", "maria@mail.com", "secret456", "099123456", 12345678);
        sys->crearCasa(dirCasa, fechaConstruccion, 120.5f, false, TipoTecho::TECHO_A_DOS_AGUAS); 
        sys->crearApartamento(dirApto, fechaConstruccion, 65.0f, 4, true, 4500.0f);
        sys->finalizarAltaPropietario();
        std::cout << "[OK] Propietario 'maria_prop' e inmuebles creados con exito." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Fallo el alta del propietario: " << e.what() << std::endl;
    }

    // 4. CASO DE USO: Alta Inmobiliaria
    std::cout << "\n--- [Caso de Uso] Alta Inmobiliaria y Vinculacion ---" << std::endl;
    try {
        sys->altaInmobiliaria("inmo_central", "Inmo Central", "contacto@inmo.com", "admin789", dirInmo, "29001234", "www.inmocentral.com");
        sys->vincularPropietario("maria_prop");
        sys->finalizarAltaInmobiliaria();
        std::cout << "[OK] Inmobiliaria 'InmoCentral' vinculada con los inmuebles de Maria." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Ocurrio un problema con la inmobiliaria: " << e.what() << std::endl;
    }

    // 5. Prueba de control de Clientes independientes
    try {
        sys->altaCliente("juan99", "Juan Perez", "juan@mail.com", "pass123", "Perez", "1.234.567-8");
    } catch (...) {}

    // ====================================================================================
    // 6. CASO DE USO COMPLETO: ALTA DE ADMINISTRACIÓN (Visualización de listas)
    // ====================================================================================
    std::cout << "\n--- [Caso de Uso] Alta de Administracion ---" << std::endl;
    
    // PASO 1: El sistema muestra las Inmobiliarias para que el usuario elija
    std::cout << "[UI] Listando Inmobiliarias registradas en el sistema:" << std::endl;
    try {
        ICollection* listaInmobiliarias = sys->listarInmobiliarias();
        if (listaInmobiliarias != nullptr) {
            std::cout << "--------------------------------------------------" << std::endl;
            IIterator* itInmo = listaInmobiliarias->getIterator();
            while (itInmo->hasCurrent()) {
                DtInmobiliaria* dtInmo = dynamic_cast<DtInmobiliaria*>(itInmo->getCurrent());
                if (dtInmo != nullptr) {
                    std::cout << " -> Nickname: " << dtInmo->getNickname() << std::endl;
                    std::cout << "    Nombre:   " << dtInmo->getNombre() << std::endl;
                    std::cout << "--------------------------------------------------" << std::endl;
                }
                delete dtInmo;
                itInmo->next();
            }
            delete itInmo;
            delete listaInmobiliarias;
        }
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] No se pudieron listar las inmobiliarias: " << e.what() << std::endl;
    }

    // PASO 2: El usuario selecciona una Inmobiliaria y el sistema muestra SUS Inmuebles
    int idCapturadoParaPrueba = -1; 
    std::cout << "\n[UI] Seleccionando la inmobiliaria 'inmo_central'..." << std::endl;
    
    try {
        ICollection* listaInmueblesCompuestos = sys->seleccionarInmobiliaria("inmo_central");

        if (listaInmueblesCompuestos != nullptr) {
            std::cout << "[OK] Inmuebles que CONTIENE la inmobiliaria seleccionada:" << std::endl;
            std::cout << "--------------------------------------------------" << std::endl;

            IIterator* itCompuesto = listaInmueblesCompuestos->getIterator();
            while (itCompuesto->hasCurrent()) {
                DtInmXProp* dtComp = dynamic_cast<DtInmXProp*>(itCompuesto->getCurrent());

                if (dtComp != nullptr) {
                    // Usamos getNumId() que es el que busca tu Linker
                    std::cout << " -> Inmueble ID:        " << dtComp->getNumId() << std::endl;
                    std::cout << "    Propietario Legal:  " << dtComp->getPropietariovinculado().getNombre() << std::endl;
                    std::cout << "    Direccion:          " << dtComp->getDireccion().getCiudad() << std::endl;
                    std::cout << "--------------------------------------------------" << std::endl;

                    if (idCapturadoParaPrueba == -1) {
                        idCapturadoParaPrueba = dtComp->getNumId();
                    }
                }
                delete dtComp; 
                itCompuesto->next();
            }
            delete itCompuesto;           
            delete listaInmueblesCompuestos; 
        }
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Error al seleccionar la inmobiliaria: " << e.what() << std::endl;
    }

    // PASO 3: Confirmación de Alta de Administración usando uno de los inmuebles mostrados
    std::cout << "\n[UI] Confirmando Alta de Administracion para el ID: " << idCapturadoParaPrueba << "..." << std::endl;
    try {
        if (idCapturadoParaPrueba != -1) {
            sys->altaAdministracion(idCapturadoParaPrueba);
            std::cout << "[OK] Administracion creada exitosamente en la Inmobiliaria." << std::endl;
        }
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Error al dar de alta la administracion: " << e.what() << std::endl;
    }

    // 7. Prueba de Control: Post-condición
    std::cout << "\n[Prueba de Control] Validando que el sistema limpio la inmobiliaria de la memoria..." << std::endl;
    try {
        sys->altaAdministracion(idCapturadoParaPrueba); 
    } 
    catch (const std::runtime_error& e) {
        std::cout << "[CONTROLADO] Excepcion correcta: " << e.what() << std::endl;
    }

    // 8. Verificación previa existente: Listar Propietarios
    std::cout << "\n--- Verificacion Final: Listar Propietarios ---" << std::endl;
    try {
        ICollection* lista = sys->listarPropietarios();
        if (lista != nullptr) {
            IIterator* it = lista->getIterator();
            while (it->hasCurrent()) {
                DtPropietario* dtProp = (DtPropietario*)it->getCurrent();
                std::cout << " -> Propietario: " << dtProp->getNombre() << " (" << dtProp->getNickname() << ")" << std::endl;
                delete dtProp; 
                it->next(); 
            }
            delete it;    
            delete lista; 
        }
    } catch (...) {}

    std::cout << "\n========== FIN DE LAS PRUEBAS DEL SISTEMA ==========" << std::endl;
    return 0;
}
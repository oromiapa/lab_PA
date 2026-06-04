#include <iostream>
#include <exception>
#include "Sistema.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/DtPropietario.h"


void probarAltaUsuarios(Sistema* sistema) {
    std::cout << "--- Creando Usuarios (Clientes, Propietarios e Inmobiliarias) ---" << std::endl;
    
    try {
        // 1. Altas exitosas de Clientes y Propietarios
        sistema->altaCliente("juan99", "Juan", "juan@mail.com", "pass123", "Pérez", "1.234.567-8");
        sistema->altaPropietario("maria_prop", "Maria", "maria@mail.com", "prop456", "099123456", 123456);
        
        // 2. Instanciamos DtDireccion usando tu constructor: DtDireccion(const char*, int, const char*)
        DtDireccion dirInmo("Av. 18 de Julio", 1420, "Montevideo");
        
        // Alta de Inmobiliaria pasando la dirección por referencia constante
        sistema->altaInmobiliaria("inmo_centro", "Inmo Centro", "contacto@inmo.com", "inmo789", dirInmo, "29001122", "www.inmocentro.com");
        
        std::cout << "[OK] Usuarios e Inmobiliaria creados correctamente." << std::endl;

        // 3. Caso de prueba de falla: Intentar repetir un Nickname
        std::cout << "\nIntentando registrar un nickname duplicado (debería lanzar excepción)..." << std::endl;
        sistema->altaCliente("juan99", "Juan Segundo", "juan2@mail.com", "otra", "Gomez", "4.555.666-2");
        
    } catch (const std::invalid_argument& e) {
        std::cout << "[ÉXITO DEL TEST] Excepción capturada correctamente: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Ocurrió un error inesperado: " << e.what() << std::endl;
    }
}

void probarAltaInmuebles(Sistema* sistema) {
    std::cout << "\n--- Creando Inmuebles (Casas y Apartamentos) ---" << std::endl;
    
    try {
        // Creamos las direcciones usando tu estructura
        DtDireccion dirCasa("Calle Falsa", 123, "Canelones");
        
        // Asumo un constructor similar para DtFecha (ej: día, mes, año)
        // Si tu DtFecha usa otra estructura, adáptalo de forma similar a DtDireccion
        DtFecha fechaCasa(15, 5, 2010); 
        
        // Crear una Casa
        sistema->crearCasa(dirCasa, fechaCasa, 120.5f, false, TipoTecho::TECHO_PLANO);
        std::cout << "[OK] Casa creada exitosamente (ID autoincremental)." << std::endl;

        // Dirección para el apartamento
        DtDireccion dirApto("Bulevar Artigas", 3210, "Montevideo");
        DtFecha fechaApto(1, 1, 2020);
        
        // Crear un Apartamento
        sistema->crearApartamento(dirApto, fechaApto, 65.0f, 4, true, 4500.0f);
        std::cout << "[OK] Apartamento creado exitosamente (ID autoincremental)." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Error al crear inmuebles: " << e.what() << std::endl;
    }
}

void probarListarPropietarios(Sistema* sistema) {
    std::cout << "\n--- Listando Propietarios del Sistema ---" << std::endl;
    
    ICollection* listaPropietarios = sistema->listarPropietarios();
    
    if (listaPropietarios == nullptr) {
        std::cout << "[ERROR] La colección devuelta es null." << std::endl;
        return;
    }

    IIterator* it = listaPropietarios->getIterator();
    int cont = 0;
    
    while (it->hasCurrent()) {
        cont++;
        DtPropietario* dtP = dynamic_cast<DtPropietario*>(it->getCurrent());
        if (dtP != nullptr) {
            std::cout << "Propietario " << cont << " -> " 
                      << "Nickname: " << dtP->getNickname() 
                      << " | Nombre: " << dtP->getNombre() << std::endl;
        }
        it->next();
    }
    
    std::cout << "Total de propietarios listados: " << cont << std::endl;

    // Limpieza estricta de memoria de la lista temporal
    delete it;
    
    IIterator* itClean = listaPropietarios->getIterator();
    while (itClean->hasCurrent()) {
        delete itClean->getCurrent(); // Borra cada DtPropietario creado con new en Sistema
        itClean->next();
    }
    delete itClean;
    delete listaPropietarios; // Borra el contenedor List
}

int main() {
    std::cout << "=== INICIANDO PRUEBAS DEL SISTEMA (MOCK DATA) ===" << std::endl;

    // Instanciamos el controlador principal (Sistema)
    Sistema* sistema = new Sistema();

    // Ejecución de los casos de prueba
    probarAltaUsuarios(sistema);
    probarAltaInmuebles(sistema);
    probarListarPropietarios(sistema);

    // Destrucción del sistema y liberación de memoria interna
    std::cout << "\n--- Destruyendo el Sistema ---" << std::endl;
    delete sistema;
    std::cout << "[OK] Memoria del sistema liberada con éxito." << std::endl;

    std::cout << "=== PRUEBAS FINALIZADAS ===" << std::endl;
    return 0;
}
#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <stdexcept>
#include "ISistema.h"
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/interfaces/IDictionary.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/TipoTecho.h"

class Usuario;
class Cliente;
class Propietario;
class Inmobiliaria;
class Inmueble;
class Casa;
class Apartamento;

class Sistema : public ISistema {

private:
    IDictionary* usuarios;
    IDictionary* inmuebles;
    IDictionary* inmobiliarias;
    Inmobiliaria* inmobiliariaActual;
    Propietario* propietarioActual;
    int contadorInmuebles;

public:
    Sistema();
    ~Sistema();

// Primer Caso: ALTA DE USUARIOS
    bool existeUsuario(const char* nickname);
    void altaCliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento);
    void altaPropietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria);
    int autoincremental();
    void crearCasa(const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho);
    void crearApartamento(const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, int piso, bool TieneAscensor, const float & gastosComunes);
    void altaInmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL);
    ICollection* listarPropietarios(); 
    void vincularPropietario(const char* nicknamePropietario);
    void finalizarAltaInmobiliaria();
    void finalizarAltaPropietario();


//Segundo Caso: ALTA DE ADMINISTRACION
    ICollection* listarInmobiliarias();
    ICollection* seleccionarInmobiliaria(const char* nombreInmobiliaria);
    void altaAdministracion(int numid);

};

#endif 
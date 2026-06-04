#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <string>
#include <stdexcept>
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/interfaces/IDictionary.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/TipoTecho.h"


class ISistema {

public:
    ~ISistema() ;
    virtual bool existeUsuario(const char* nickname) = 0;
    virtual void altaCliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento) = 0;
    virtual void altaPropietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria) = 0;
    virtual int autoincremental() = 0;
    virtual void crearCasa( const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho) = 0;
    virtual void crearApartamento( const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, int piso, bool TieneAscensor, const float & gastosComunes) = 0;
    virtual void altaInmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL) = 0;
    virtual ICollection* listarPropietarios() = 0;


};

#endif
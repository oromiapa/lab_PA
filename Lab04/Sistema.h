#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <stdexcept>

//Clases
#include "ISistema.h"

//DataTypes
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/TipoTecho.h"
#include "./DataTypes/TipoInmueble.h"

//ICollection/interfaces
#include "./ICollection/interfaces/IDictionary.h"
#include "./ICollection/interfaces/ICollection.h"


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

    IDictionary* clientes;
    IDictionary* propietarios;
    IDictionary* inmobiliarias;

    IDictionary* inmuebles;       
    IDictionary* casas;
    IDictionary* apartamentos;

    Inmobiliaria* inmobiliariaActual;
    Propietario* propietarioActual;
    Inmueble* inmuebleActual;
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

// Segundo Caso: ALTA DE ADMINISTRACION
    ICollection* listarInmobiliarias();
    ICollection* seleccionarInmobiliaria(const char* nombreInmobiliaria);
    void altaAdministracion(int numid);

// Tercer Caso: ALTA DE PUBLICACION
//  ICollection* listarInmobiliarias(); [Es el mismo que en el segundo caso]
    ICollection* seleccionarInmobiliariaAdministrada(const char* nombreInmobiliaria);
    void altaPublicacion(const int numid, const char* text, float price, bool tipopub);

//Caso Especial: ALTA DE VISITA
    void altaVisita(const char* nicknameCliente, int idPublicacion, const DtFecha& fechaVisita, const char* contacto);
    ICollection* listarVisitas(int idPublicacion);

// Cuarto Caso: ELIMINAR INMUEBLE
    ICollection* listarinmueblesxpropietario();
    DtInmueble seleccionarInmueble(int numid);
    void eliminarInmueble(int numid);

// Quinto Caso: CONSULTAR PUBLICACION
    ICollection* filtrarPublicaciones(bool tipopub, float preciomin, float preciomax, TipoInmueble tipo);
    DtInmueble* seleccionarPublicacion(int id);

};

#endif
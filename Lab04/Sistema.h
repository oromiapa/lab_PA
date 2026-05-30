#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <set>
#include <memory>

// Forward declarations
class Inmobiliaria;
class Administracion;
class Inmueble;
class Publicacion;
class Propietario;
class Cliente;

// DTOs
struct DataInmobiliaria {
    std::string nickname;
    std::string nombre;
};

struct DataInmueble {
    int numeroID;
    std::string direccion;
    std::string propietario;
};

struct DataPropietario {
    std::string nickname;
    std::string nombre;
};

struct DataFiltro {
};

class Sistema {
private:
    // Colecciones globales 
    std::set<std::shared_ptr<Inmobiliaria>> inmobiliarias;
    std::set<std::shared_ptr<Administracion>> administraciones;
    std::set<std::shared_ptr<Propietario>> propietarios;
    std::set<std::shared_ptr<Publicacion>> publicaciones;
    std::set<std::shared_ptr<Cliente>> clientes;
    std::set<std::shared_ptr<Inmueble>> inmuebles;

    int autoincrementalID; // contador interno para numID

public:
    // Constructores / destructor
    Sistema();
    ~Sistema();

    // Métodos principales 
    bool existeUsuario(const std::string& nickname);

    void altaCliente(const std::string& contrasenia, const std::string& email,
                     const std::string& nombre, const std::string& apellido,
                     const std::string& documento);

    void altaPropietario(const std::string& contrasenia, const std::string& email,
                         const std::string& nombre, int cuentaBancaria,
                         const std::string& telefono);

    void crearCasa(const std::string& direccion, const std::string& anioConstruccion,
                   float superficie, bool propiedadHorizontal, const std::string& tipoTecho);

    void crearApartamento(const std::string& direccion, const std::string& anioConstruccion,
                          float superficie, int piso, bool tieneAscensor,
                          float gastosComunes);

    void altaInmobiliaria(const std::string& contrasenia, const std::string& email,
                          const std::string& nombre, const std::string& direccion,
                          const std::string& telefono, const std::string& url);

    std::set<DataPropietario> listarPropietarios();
    void vincularPropietario(const std::string& nickname);

    std::set<DataInmobiliaria> listarInmobiliarias();
    std::shared_ptr<Inmobiliaria> seleccionarInmobiliaria(const std::string& nickname);

    std::set<DataInmueble> listarInmuebles();
    std::shared_ptr<Inmueble> seleccionarInmueble(int numeroID);

    void altaPublicacion(const std::string& nickname, const std::string& texto,
                         int precio, bool tipoPublicacion);

    std::set<DataFiltro> filtrarPublicaciones(bool tipoPublicacion,
                                              float precioMinimo,
                                              float precioMaximo,
                                              int tipoInmueble);

    std::shared_ptr<Publicacion> seleccionarPublicacion(int id);

    std::set<DataPropietario> listarInmueblesxPropietario();

    void eliminarInmueble(int numeroID);

    int autoincremental(); // genera numID único
};

#endif // SISTEMA_H

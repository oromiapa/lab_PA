#ifndef CLIENTE_H
#define CLIENTE_H


#include "Usuario.h"
#include "Visita.h"

#include "./ICollection/interfaces/ICollection.h"
#include "./ICollection/collections/List.h"

class Visita;

class Cliente : public Usuario {
    
private:
    std::string apellido;
    std::string documento;
    ICollection* visitas;

public:
//Constructor y Destructor
    Cliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento);
    virtual ~Cliente();

//Gets
    std::string getApellido() const;
    std::string getDocumento() const;
    
//Sets
    void setApellido(const char* apellido);
    void setDocumento(const char* documento);

//Caso especial
    void agregarVisita(Visita* v);
    ICollection* getVisitas() const;    
    
};

#endif
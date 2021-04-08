#include "Usuario.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Usuario::MAX = 500;

Usuario::Usuario()
{
	this->guardadoS = 0;
	this->guardadoC = 0;
}
Usuario::~Usuario()
{
	delete [] nickname;
	delete [] contrasenya;
	delete [] puntuaciones;
	delete[] objectsS;
	delete[] objectsC;
	
}
void Usuario::setNickname (char* n) 
{
	this->nickname = new char[strlen(n)+1];
	strcpy(this->nickname, n);
}
void Usuario::setContrasenya (char* n) 
{
	this->contrasenya = new char[strlen(n)+1];
	strcpy(this->contrasenya, n);
}
void Usuario::setPuntuaciones (float* n) 
{
	this->puntuaciones = new float [2];
	this->puntuaciones[0] = n[0];
	this->puntuaciones[1] = n[1];
}

void Usuario::setPuntuacionClasico (float f)
{
	this->puntuaciones[0] = f;
}

void Usuario::setPuntuacionSupervivencia (float f)
{
	this->puntuaciones[1] = f;
}

void Usuario::setGuardadoS(int n)
{
	this->guardadoS = n;
}

int Usuario::getGuardadoS() const
{
	return this->guardadoS;
}

void Usuario::setGuardadoC(int n)
{
	this->guardadoC = n;
}

int Usuario::getGuardadoC() const
{
	return this->guardadoC;
}

int* Usuario::getObjectsS() const
{
	return this->objectsS;
}

void Usuario::setObjectsS()
{
	this->objectsS = new int[70];
}

int* Usuario::getObjectsC() const
{
	return this->objectsC;
}
void Usuario::setObjectsC()
{
	this->objectsC = new int[170];
}

Usuario& Usuario::operator=(const Usuario &a)
{
	this->nickname = new char[strlen(a.nickname)+1];
	strcpy(this->nickname, a.nickname);

    this->contrasenya = new char[strlen(a.contrasenya)+1];
	strcpy(this->contrasenya, a.contrasenya);

    this->puntuaciones = new float [2];
    this->puntuaciones[0] = a.puntuaciones[0];
    this->puntuaciones[1] = a.puntuaciones[1];

    this->guardadoS = a.guardadoS;
    this->guardadoC = a.guardadoC;

    this->setObjectsC();
    if (this->guardadoC == 1)
    {
	    
	    int i=0;
	    while (a.objectsC[i] != -1)
	    {
	    	this->objectsC[i] = a.objectsC[i];
	    	i++;
	    }
	    this->objectsC[i] = -1;
	}

	this->setObjectsS();
	if (this->guardadoS == 1)
	{
	    
	    int j=0;
	    while (a.objectsS[j] != -1)
	    {
	    	this->objectsS[j] = a.objectsS[j];
	    	j++;
	    }
	    this->objectsS[j] = -1;
	}

    return *this;
}
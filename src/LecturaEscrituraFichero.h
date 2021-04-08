#ifndef LECTURAESCRITURAFICHERO_H_
#define LECTURAESCRITURAFICHERO_H_

#include <stdio.h>
#include <string.h>
#include "Usuario.h"



class LecturaEscrituraFichero
{	
	private:
		static int MAX;
	public:
		Usuario* leerUsuarios(FILE *file, int *size);
		void escribirUsuarios(Usuario *usuarios, int size);
};

#endif
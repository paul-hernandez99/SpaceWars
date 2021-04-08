#include "LecturaEscrituraFichero.h"

#include <iostream>
using namespace std;

int LecturaEscrituraFichero::MAX = 500;

Usuario* LecturaEscrituraFichero::leerUsuarios(FILE *file, int* size)
{
	char* linea = new char[MAX];
	char** items = new char*[240];

	fgets(linea, MAX, file);
	sscanf(linea, "%d", size);

	Usuario* usuarios = new Usuario [*size];

	int contador = 0;
	while(fgets(linea, MAX, file))
	{
		char* token = strtok(linea, ";");
		int i=0;
		while(token != NULL)
		{
			items[i] = token;
			token = strtok(NULL, ";");
			i++;
		}

		char* auxNick = new char [strlen(items[0])+1];
		strcpy(auxNick, items[0]);
		usuarios[contador].setNickname(auxNick);
		delete [] auxNick;

		char* auxContra = new char [strlen(items[1])+1];
		strcpy(auxContra, items[1]);
		usuarios[contador].setContrasenya(auxContra);
		delete [] auxContra;

		float* punt = new float [2];
		punt[0] = strtof(items[2], NULL);
		punt[1] = strtof(items[3], NULL);
		usuarios[contador].setPuntuaciones(punt);
		delete [] punt;

		int j = 4;

		usuarios[contador].setGuardadoC(atoi(items[j]));
		j++;

		if(usuarios[contador].getGuardadoC() == 1)
		{
			usuarios[contador].setObjectsC();
			int* auxObjects = usuarios[contador].getObjectsC();
			while(atoi(items[j]) != -1)
			{
				auxObjects[j-5] = atoi(items[j]);
				j++;
			}
			auxObjects[j-5] = atoi(items[j]);
			j++;
		}

		usuarios[contador].setGuardadoS(atoi(items[j]));
		j++;


		if(usuarios[contador].getGuardadoS()==1)
		{
			usuarios[contador].setObjectsS();
			int* auxObjectsS = usuarios[contador].getObjectsS();
			int k = 0;
			while(atoi(items[j]) != -1)
			{
				auxObjectsS[k] = atoi(items[j]);
				j++;
				k++;
			}
			auxObjectsS[k] = atoi(items[j]);
		}

		contador++;
	}
	delete [] linea;
	delete [] items;

	return usuarios;
}



void LecturaEscrituraFichero::escribirUsuarios(Usuario *usuarios, int size)
{
	FILE *file = fopen("Usuarios.txt", "w");
	if (file == NULL)
	{
		cout <<"Error al abrir el fichero Usuarios.txt\n";
		exit(-1);
	}

	fprintf(file, "%d\n", size);

	for (int i=0; i<size; i++)
	{
		fprintf(file, "%s;%s;%0.2f;%0.2f", usuarios[i].getNickname(), usuarios[i].getContrasenya(), usuarios[i].getPuntuaciones()[0], usuarios[i].getPuntuaciones()[1]);

		if(usuarios[i].getGuardadoC()==1)
		{
			int* objects = usuarios[i].getObjectsC();
			fprintf(file, ";1");
			int i=0;
			while(objects[i] != -1)
			{
				fprintf(file, ";%d", objects[i]);
				i++;
			}
			fprintf(file, ";-1");
		}
		else
			fprintf(file, ";0");

		if(usuarios[i].getGuardadoS()==1)
		{
			int* objects = usuarios[i].getObjectsS();
			fprintf(file, ";1");
			int i=0;
			while(objects[i] != -1)
			{
				fprintf(file, ";%d", objects[i]);
				i++;
			}
			fprintf(file, ";-1\n");
		}
		else
			fprintf(file, ";0\n");

	}

	fclose(file);
	//delete file;
}

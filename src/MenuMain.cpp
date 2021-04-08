#include "MenuMain.h"
#include "Usuario.h"
#include "Menu.h"


#include <stdio.h>
#include <curses.h>
#include <iostream>
using namespace std;


#ifdef _WIN32
    #include <windows.h>

    void ssleepp(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void ssleepp(unsigned int milliseconds)
    {
        usleep(milliseconds * 1000);
    }
#endif


MenuMain::MenuMain()
{
	tamanyoTerminal();
}

void MenuMain::menuPrincipal()
{
    FILE *file = fopen("Usuarios.txt", "r");
    if (file == NULL)
    {
        cout <<"Error al abrir el fichero Usuarios.txt\n" << endl;
        exit(-1);
    }

    int* size = new int();

    LecturaEscrituraFichero lef;
    Usuario* usuarios = lef.leerUsuarios(file, size);

    int player;
    int opcion;
    int selected;
    while(1)
    {
        MenuInicio menIn;
        opcion = menIn.menuInicio();
        switch(opcion)
        {
            case 0:
            {
                MenuIniciarSesion menInSes;
                player = (int) menInSes.menuIniciarSesion(usuarios, *size);

                while(1)
                {

                    MenuPlayer menPlay;
                    selected = menPlay.menuPlayer();
                    switch(selected)
                    {
                        case 0:
                        {
                            Clasico classic;
                            classic.jugar(usuarios, player);
                            lef.escribirUsuarios(usuarios, *size);
                            break;
                        }
                        case 1:
                        {
                            Supervivencia supervi;
                            supervi.jugar(usuarios, player);
                            lef.escribirUsuarios(usuarios, *size);
                            break;
                        }
                        case 2:
                        {
                            RankingClasico rc;
                            rc.mostrarRanking(usuarios, *size);
                            break;
                        }
                        case 3:
                        {
                            RankingSupervivencia rs;
                            rs.mostrarRanking(usuarios, *size);
                            break;
                        }
                        default:
                            break;
                    }
                    if(selected == 4) break;
                }
                break;
            }

            case 1:
            {
                MenuRegistrarse menReg;
                menReg.menuRegistrarse(usuarios, *size);
                break;
            }

            default:
                break;
        }
        if(opcion == 2)
            break;
    }
    liberarMemoriaMenuMain (size, usuarios);
    exit(0);
}
void MenuMain::liberarMemoriaMenuMain (int *size, Usuario* arrayUsers)
{
    delete [] arrayUsers;
    delete size;
    clear();
    refresh();
}

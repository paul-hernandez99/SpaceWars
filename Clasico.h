#ifndef CLASICO_H_
#define CLASICO_H_
#include <curses.h>
#include "Juego.h"
#include "NaveClasico.h"
#include "Asteroide.h"
#include "Bala.h"
#include "Usuario.h"

class Clasico: public Juego
{
	static const int MAX_AST;
	static const int MAX_BALAS;
	static const int MAX_LENGHT;

	virtual void pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast);
	virtual void subirNivel(Asteroide* asteroides, int* num_ast);
	virtual void mostrarGameOver();
	virtual int menuSalida();
	virtual WINDOW* mostrarInfo();
	virtual WINDOW* mostrarJuego();
	virtual void nuevoAsteroideVertical(Asteroide* asteroide);
	virtual void nuevoAsteroideHorizontal(Asteroide* asteroide);
	virtual void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide);
	virtual void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide);
	virtual int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide);
	
	void reanudarPartida(int* objects, NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosConsumidos, float* segundos, float* tiempo, int* disparosAcertados);
	void guardarPartida(Usuario* usuarios, int player, NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int segundos, int tiempo, int* disparosAcertados, int* disparosConsumidos);
	void crearBalas (Bala* balas, NaveClasico* nave, int* num_balas);
	void mostrarPuntuacion (Usuario* usuarios, int player, float tiempo, int* disparosAcertados);
	void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala, int* disparosConsumidos);
	int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide, int* disparosAcertados, int* disparosConsumidos);
	void quitarBala(Bala* balas, int i, int* num_balas);
	void pintarBala(WINDOW* ventana, Bala* bala, int* disparosConsumidos);
	void actualizarDisparosAcertados (int* disparosAcertados, int* disparosConsumidos);
	void actualizarC(WINDOW* ventana, NaveClasico* nave, int* disparosAcertados, int* disparosConsumidos);
	void crearAsteroidesHorizontales(Asteroide* asteroides, int* num_ast);
	void crearAsteroidesVerticales(Asteroide* asteroides, int* num_ast);
	void inicializarParametrosC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados, int* disparosConsumidos);
	void liberarMemoriaC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos, WINDOW* ventana, float* segundos, float* tiempo, int* nuevaPartida);
	void reestablecerValoresC(Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos, int* nuevaPartida);
	void movimientosJugadorC(int tecla, NaveClasico* nave, Bala* balas, int* num_balas);
public:
	Clasico();
	virtual ~Clasico(){}

	virtual void jugar(Usuario* usuarios, int player);
};

#endif
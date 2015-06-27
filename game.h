#ifndef GAME_H
#define GAME_H

#include "alien.h"
#include "player.h"
#include "projetil.h"
#include "menu.h"

#define N_KEYS 4
#define FPS 60

enum MYKEYS { KEY_LEFT, KEY_RIGHT, KEY_Z, KEY_ESCAPE };

struct Jogo {
	int largura, altura;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	bool key[N_KEYS];

	ALLEGRO_BITMAP* fundo;

	Player player;
	Alien alien[COLUNAS_TROPA][LINHAS_TROPA];

	Menu menu;

	Projetil projetil_stack[50];
	int numero_de_projeteis;
};

void inicializa_jogo (Jogo* jogo, int largura, int altura);

void finaliza_jogo (Jogo* jogo);

void desenha_jogo (Jogo* jogo);

void loop_de_jogo (Jogo* jogo);

void desenha_fundo_jogo (Jogo* jogo);

void inicializa_teclado (Jogo* jogo);

void inicializa_event_queue_jogo (Jogo* jogo);

void inicializa_timer_jogo (Jogo* jogo);

void inic_allegro (void);

void inic_allegro_primitive (void);

void inic_allegro_image (void);

#endif

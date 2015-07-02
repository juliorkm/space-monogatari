#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "alien.h"
#include "player.h"
#include "projetil.h"
#include "menu.h"
#include "mothership.h"
#include "hud.h"
#include "shield.h"

struct Jogo {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	
	int largura, altura;
	ALLEGRO_BITMAP* fundo;

	Player player;
	Mothership mothership;
	Alien alien[COLUNAS_TROPA * LINHAS_TROPA];
	int aliens_vivos;
	Menu menu;
	Hud hud;

	int numero_shields;
	Shield* shields;

	int fase;

	Projetil conjunto_projeteis[MAX_PROJETEIS];
	int numero_de_projeteis;

	int loop_count_projetil;
	int loop_count_menu_pause;
	int loop_alien_movement;
	int loop_alien_shots;
	
	bool key[N_KEYS];
};

void inicializa_display (Jogo* jogo);

void finaliza_display (Jogo* jogo);

void inicializa_jogo (Jogo* jogo, int fase);

void finaliza_jogo (Jogo* jogo);

void desenha_jogo (Jogo* jogo);

bool loop_de_jogo (Jogo* jogo);

void desenha_fundo_jogo (Jogo* jogo);

void incremento_loop_elementos_jogo (Jogo* jogo);

void inicializa_teclado_jogo (Jogo* jogo);

void inicializa_event_queue_jogo (Jogo* jogo);

void inicializa_timer_jogo (Jogo* jogo);

void tela_boot_jogo (Jogo* jogo);

void inic_allegro (void);

void inic_biblioteca_allegro (void);

void inic_biblioteca_allegro_primitive (void);

void inic_biblioteca_allegro_image (void);

void inic_biblioteca_allegro_font (void);

void inic_biblioteca_allegro_ttf (void);

#endif

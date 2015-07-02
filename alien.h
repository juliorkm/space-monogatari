#ifndef ALIEN_H
#define ALIEN_H

#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "projetil.h"
#include "config.h"

struct Jogo;

struct Alien {
	int posicao_x, posicao_y;
	int delta_x, delta_y;
	DIRECAO direcao_atual;

	int velocidade;
	
	bool vivo;

	int sprite_atual;
	ALLEGRO_BITMAP* sprites[10];
};

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y);

void inicializa_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], int posicao_x, int posicao_y);

void finaliza_alien (Alien* alien);

void desenha_alien (Alien* alien);

void desenha_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA]);

void inicializa_sprites_alien (Alien* alien);

void finaliza_sprites_alien (Alien* alien);

void muda_direcao_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], DIRECAO direcao);

void move_alien (Alien* alien, DIRECAO direcao);

void move_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], DIRECAO direcao);

void rota_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], Jogo* jogo);

void atira_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], Projetil* projetil);

void colisao_alien_vs_projetil (Jogo *jogo);

int get_posicao_x_min_alien (Alien* alien);

int get_posicao_x_max_alien (Alien* alien);

int get_posicao_y_min_alien (Alien* alien);

int get_posicao_y_max_alien (Alien* alien);

#endif

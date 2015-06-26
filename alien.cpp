#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "alien.h"

#define altura_sprites 64
#define largura_sprites 64

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y) {
	alien->posicao_x = posicao_x;
	alien->posicao_y = posicao_y;

	alien->vivo = true;

	inicializa_sprites_alien (alien);

	alien->delta_x = al_get_bitmap_width(alien->sprites[0])/2;
}

void inicializa_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			inicializa_alien (&alien[i][j], posicao_x + i * (largura_sprites + largura_sprites/4),
									posicao_y + j * (altura_sprites + altura_sprites/4) ); 

}

void finaliza_alien (Alien* alien) {
	finaliza_sprites_alien(alien);
}

void desenha_alien (Alien* alien) {
	int flags = 0;
  
	if (alien->direcao_atual == alienDIREITA)
		flags = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_bitmap (alien->sprites[0], 
					alien->posicao_x - alien->delta_x, 
					alien->posicao_y,
					flags);
}

void desenha_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA]) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			if (alien[i][j].vivo)
				desenha_alien (&alien[i][j]);
}

void inicializa_sprites_alien (Alien* alien) {
	alien->sprites[0] = al_load_bitmap("resources/alien.png");

	if (alien->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo resources/alien.png");
		exit(0);
	}
}

void finaliza_sprites_alien (Alien* alien) {
	al_destroy_bitmap(alien->sprites[0]);
}

void move_alien (Alien* alien, DIRECAO_ALIEN direcao) {
	if (direcao == alienESQUERDA) {
		alien->posicao_x -= DISTANCIA_PASSO;
		alien->direcao_atual = alienESQUERDA;
	}
	if (direcao == alienDIREITA) {
		alien->posicao_x += DISTANCIA_PASSO;
		alien->direcao_atual = alienDIREITA;
	}
}

int get_posicao_x_max_alien (Alien* alien){
	return alien->posicao_x + alien->delta_x;
}

int get_posicao_x_min_alien (Alien* alien){
	return alien->posicao_x - alien->delta_x;
	puts("fodase");
}

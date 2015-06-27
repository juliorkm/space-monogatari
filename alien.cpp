#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "alien.h"
#include "player.h"

#define altura_sprites 35
#define largura_sprites 36

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y) {
	alien->posicao_x = posicao_x;
	alien->posicao_y = posicao_y;

	alien->vivo = true;

	alien->direcao_atual = ESQUERDA;

	inicializa_sprites_alien (alien);

	alien->delta_x = al_get_bitmap_width(alien->sprites[0])/2;
}

void inicializa_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			inicializa_alien (&alien[i][j], posicao_x + i * (largura_sprites + largura_sprites/2),
									posicao_y + j * (altura_sprites + altura_sprites/2) ); 

}

void finaliza_alien (Alien* alien) {
	finaliza_sprites_alien(alien);
}

void desenha_alien (Alien* alien) {
	int flags = 0;
  
	if (alien->direcao_atual == DIREITA)
		flags = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_bitmap (alien->sprites[alien->sprite_atual], 
					alien->posicao_x - alien->delta_x, 
					alien->posicao_y,
					flags);
  
	alien->sprite_atual = (alien->sprite_atual + 1) % 2;

}

void desenha_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA]) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			if (alien[i][j].vivo)
				desenha_alien (&alien[i][j]);
}

void inicializa_sprites_alien (Alien* alien) {
	alien->sprites[0] = al_load_bitmap("resources/alien.png");
	alien->sprites[1] = al_load_bitmap("resources/alien1-2.png");
	alien->sprite_atual = 0;

	if (alien->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo resources/alien.png");
		exit(0);
	}

	if (alien->sprites[1] == NULL) {
		puts("Erro ao carregar o arquivo resources/alien1-2.png");
		exit(0);
	}
}

void finaliza_sprites_alien (Alien* alien) {
	al_destroy_bitmap(alien->sprites[0]);
}

void move_alien (Alien* alien, DIRECAO direcao) {
	if (direcao == ESQUERDA) {
		alien->posicao_x -= DISTANCIA_PASSO_ALIEN;
		alien->direcao_atual = ESQUERDA;
	}
	if (direcao == DIREITA) {
		alien->posicao_x += DISTANCIA_PASSO_ALIEN;
		alien->direcao_atual = DIREITA;
	}
	if (direcao == CIMA) {
		alien->posicao_y -= DISTANCIA_PASSO_ALIEN;
		alien->direcao_atual = CIMA;
	}
	if (direcao == BAIXO) {
		alien->posicao_y += DISTANCIA_PASSO_ALIEN;
		alien->direcao_atual = BAIXO;
	}
}

void move_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao) {
	if (direcao == ESQUERDA) {
		for (int i = 0; i < COLUNAS_TROPA; i++) {
			for (int j = 0; j < LINHAS_TROPA; j++) {
				move_alien (&alien[i][j], ESQUERDA);
			}
		}
	}

	if (direcao == DIREITA) {
		for (int i = 0; i < COLUNAS_TROPA; i++) {
			for (int j = 0; j < LINHAS_TROPA; j++) {
				move_alien (&alien[i][j], DIREITA);
			}
		}
	}

	if (direcao == CIMA) {
		for (int i = 0; i < COLUNAS_TROPA; i++) {
			for (int j = 0; j < LINHAS_TROPA; j++) {
				move_alien (&alien[i][j], CIMA);
			}
		}
	}

	if (direcao == BAIXO) {
		for (int i = 0; i < COLUNAS_TROPA; i++) {
			for (int j = 0; j < LINHAS_TROPA; j++) {
				move_alien (&alien[i][j], BAIXO);
			}
		}
	}

}

void rota_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA]) {
	if (alien[0][0].direcao_atual == ESQUERDA && get_posicao_x_min_alien(&alien[0][0]) > 0 + 5)
		move_tropa (alien, ESQUERDA);
	if (get_posicao_x_min_alien(&alien[0][0]) <= 0 + 5)// ||
//			get_posicao_x_max_alien(&alien[COLUNAS_TROPA][0]) == largura - 5)
		move_tropa (alien, BAIXO);
}

int get_posicao_x_max_alien (Alien* alien){
	return alien->posicao_x + alien->delta_x;
}

int get_posicao_x_min_alien (Alien* alien){
	return alien->posicao_x - alien->delta_x;
}

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "game.h"
#include "player.h"

void inicializa_player (Player* player, double posicao_x, double posicao_y) {
	player->posicao_x = posicao_x;
	player->posicao_y = posicao_y;
	player->projetil_cooldown = PROJETIL_COOLDOWN;

	player->bitmap = al_load_bitmap("resources/player4.png");
	if (player->bitmap == NULL) {
		puts("Erro ao carregar o arquivo \"resources/player4.png\"");
		exit(0);
	}

	if (SCALE_BITMAPS) {
		player->largura = LARGURA_PLAYER*(LARGURA_DISPLAY/640.0);
		player->altura = ALTURA_PLAYER*(ALTURA_DISPLAY/480.0);
	}
	else {
		player->largura = LARGURA_PLAYER;
		player->altura = ALTURA_PLAYER;
	}

	player->delta_x = player->largura/2;
	player->delta_y = player->altura/2;
}

void finaliza_player (Player* player) {
	al_destroy_bitmap(player->bitmap);
}

void desenha_player (Player* player) {
	int flags = 0;
  
	if (player->direcao_atual == DIREITA)
		flags = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_scaled_bitmap(player->bitmap,
						  0, 
						  0,
						  al_get_bitmap_width(player->bitmap),
						  al_get_bitmap_height(player->bitmap),

						  player->posicao_x - player->delta_x,
						  player->posicao_y + player->delta_y,
						  player->largura,
						  player->altura,

						  flags);
}

void move_player (Player* player, DIRECAO direcao) {
	if (direcao == ESQUERDA) {
		player->posicao_x -= DISTANCIA_PASSO_PLAYER;
		player->direcao_atual = ESQUERDA;
	}
	if (direcao == DIREITA) {
		player->posicao_x += DISTANCIA_PASSO_PLAYER;
		player->direcao_atual = DIREITA;
	}
}


void colisao_player_vs_projetil (Jogo *jogo) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		if(((verifica_se_ponto_dentro(get_posicao_x_min_projetil(&jogo->conjunto_projeteis[i]),
									  get_posicao_y_max_projetil(&jogo->conjunto_projeteis[i]),
									  &jogo->player))
		    || (verifica_se_ponto_dentro (get_posicao_x_max_projetil(&jogo->conjunto_projeteis[i]),
									      get_posicao_y_max_projetil(&jogo->conjunto_projeteis[i]),
										  &jogo->player)))
			&& jogo->conjunto_projeteis[i].direcao == BAIXO) {

				copy_projetil (&jogo->conjunto_projeteis[i], &jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
				desenha_projetil (&jogo->conjunto_projeteis[i]);
				finaliza_projetil (&jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
				jogo->numero_de_projeteis--;
				jogo->hud.lives--;

				return;
		}
	}
}

int get_posicao_x_min_player (Player* player) {
	return player->posicao_x - player->delta_x;
}

int get_posicao_x_max_player (Player* player) {
	return player->posicao_x + player->delta_x;
}

int get_posicao_y_min_player (Player* player) {
	return player->posicao_y + player->delta_y;
}

int get_posicao_y_max_player (Player* player) {
	return player->posicao_y + 3*player->delta_y;
}

int get_posicao_x_centro_player (Player* player) {
	return player->posicao_x - player->largura/12;
}

bool verifica_se_ponto_dentro (float x, float y, Player* player) {
	float coordenada_1[2]= {get_posicao_x_min_player(player), get_posicao_y_max_player(player)};
	float coordenada_2[2]= {get_posicao_x_max_player(player), get_posicao_y_max_player(player)};
	float coordenada_3[2]= {get_posicao_x_min_player(player) + player->delta_x, get_posicao_y_min_player(player)};
	float coordenada_4[2]= {x, y};

	if (calcular_area(coordenada_1, coordenada_2, coordenada_3) == calcular_area(coordenada_1, coordenada_2, coordenada_4)
															     + calcular_area(coordenada_1, coordenada_3, coordenada_4)
														   	     + calcular_area(coordenada_2, coordenada_3, coordenada_4))
		return true;
	else
		return false;
}

float calcular_area (float coordenada1[], float coordenada2[], float coordenada3[]) {
	float x = coordenada1[0]*coordenada2[1]
	        + coordenada1[1]*coordenada3[0]
	        + coordenada2[0]*coordenada3[1] 
	        - coordenada2[1]*coordenada3[0] 
	        - coordenada1[0]*coordenada3[1] 
	        - coordenada1[1]*coordenada2[0];

	if (x >= 0)
		return x;
	else
		return -x;
}
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "alien.h"
#include "game.h"

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y) {
	alien->posicao_x = posicao_x;
	alien->posicao_y = posicao_y;

	alien->vivo = true;

	alien->velocidade = DISTANCIA_PASSO_ALIEN;

	alien->direcao_atual = DIREITA;

	inicializa_sprites_alien (alien);

	alien->delta_x = LARGURA_SPRITES_ALIEN/2;
	alien->delta_y = ALTURA_SPRITES_ALIEN/2;
}

void inicializa_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], int posicao_x, int posicao_y) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++) {
			inicializa_alien (&alien[i * LINHAS_TROPA + j], posicao_x + i * (LARGURA_SPRITES_ALIEN + LARGURA_SPRITES_ALIEN/2),
									posicao_y + j * (ALTURA_SPRITES_ALIEN + ALTURA_SPRITES_ALIEN/2) ); 
/*if (i!=0 && j%2==0) alien[i * LINHAS_TROPA + j].vivo = false;*/} 

}

void finaliza_alien (Alien* alien) {
	finaliza_sprites_alien(alien);
}

void desenha_alien (Alien* alien) {
	int flags = 0;
  
	if (alien->direcao_atual == DIREITA)
		flags = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_scaled_bitmap(alien->sprites[alien->sprite_atual],
						  0, 
						  0,
						  al_get_bitmap_width(alien->sprites[alien->sprite_atual]),
						  al_get_bitmap_height(alien->sprites[alien->sprite_atual]),

						  alien->posicao_x - alien->delta_x,
						  alien->posicao_y,
						  LARGURA_SPRITES_ALIEN,
						  ALTURA_SPRITES_ALIEN,

						  flags);
}

void desenha_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA]) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++) {
			if (alien[i * LINHAS_TROPA + j].vivo)
				desenha_alien (&alien[i * LINHAS_TROPA + j]);
		}
}

void inicializa_sprites_alien (Alien* alien) {
	alien->sprites[0] = al_load_bitmap("resources/alien1.png");
	alien->sprites[1] = al_load_bitmap("resources/alien1-2.png");
	alien->sprite_atual = 0;

	if (alien->sprites[0] == NULL) {
		puts("Erro ao carregar o arquivo \"resources/alien1.png\"");
		exit(0);
	}

	if (alien->sprites[1] == NULL) {
		puts("Erro ao carregar o arquivo \"resources/alien1-2.png\"");
		exit(0);
	}
}

void finaliza_sprites_alien (Alien* alien) {
	al_destroy_bitmap(alien->sprites[0]);
}

void muda_direcao_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], DIRECAO direcao) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			alien[i * LINHAS_TROPA + j].direcao_atual = direcao;
}

void move_alien (Alien* alien, DIRECAO direcao) {
	ALLEGRO_BITMAP* temp = alien->sprites[0];
	alien->sprites[0] = alien->sprites[1];
	alien->sprites[1] = temp;

	if (direcao == ESQUERDA) {
		alien->posicao_x -= alien->velocidade;
		alien->direcao_atual = ESQUERDA;
	}
	if (direcao == DIREITA) {
		alien->posicao_x += alien->velocidade;
		alien->direcao_atual = DIREITA;
	}
	if (direcao == CIMA) {
		alien->posicao_y -= alien->velocidade;
		alien->direcao_atual = CIMA;
	}
	if (direcao == BAIXO) {
		alien->posicao_y += alien->velocidade;
		alien->direcao_atual = BAIXO;
	}
}

void move_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], DIRECAO direcao) {
//	if (direcao == ESQUERDA) {
	for (int i = 0; i < COLUNAS_TROPA; i++) {
		for (int j = 0; j < LINHAS_TROPA; j++) {
			move_alien (&alien[i * LINHAS_TROPA + j], direcao);
		}
	}
}

void rota_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], Jogo* jogo) {
	if (alien[0].direcao_atual == ESQUERDA && get_posicao_x_min_alien(&alien[0]) > 0 + 10 + alien[0].velocidade)
		move_tropa (alien, ESQUERDA);

	if (get_posicao_x_min_alien(&alien[0]) <= 0 + 10 + alien[0].velocidade) {
			move_tropa (alien, BAIXO);
			muda_direcao_tropa(alien, DIREITA);
	}

	if (get_posicao_x_max_alien(&alien[(COLUNAS_TROPA-1) * LINHAS_TROPA + 0]) >= jogo->largura - 10 - alien[0].velocidade) {
			move_tropa (alien, BAIXO);
			muda_direcao_tropa(alien, ESQUERDA);
	}

	if (alien[(COLUNAS_TROPA-1) * LINHAS_TROPA + 0].direcao_atual == DIREITA && get_posicao_x_max_alien(&alien[(COLUNAS_TROPA-1) * LINHAS_TROPA + 0]) < jogo->largura - 10 - alien[0].velocidade)
		move_tropa (alien, DIREITA);

}

void atira_tropa (Alien alien[COLUNAS_TROPA * LINHAS_TROPA], Projetil* projetil) {
	int pode_atirar[COLUNAS_TROPA];
	int quem_atira_x;
	int quem_atira_y;
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = LINHAS_TROPA; j > -2; j++) {
			if (j == -1) {
				pode_atirar[i] = -1;
				break;
			}
			if (alien[i + COLUNAS_TROPA + j].vivo == true) {
				pode_atirar[i] = j;
				break;
			}
		}

	srand(time(NULL));
	quem_atira_x = rand() % COLUNAS_TROPA;
	while (pode_atirar[quem_atira_x] < 0) {
puts("i tried");
		quem_atira_x = (quem_atira_x+1) % COLUNAS_TROPA;
	}
	quem_atira_y = pode_atirar[quem_atira_x];

	inicializa_projetil (projetil, alien[quem_atira_x * LINHAS_TROPA + quem_atira_y].posicao_x +
		alien[quem_atira_x * LINHAS_TROPA + quem_atira_y].delta_x,
		alien[quem_atira_x * LINHAS_TROPA + quem_atira_y].posicao_y + al_get_bitmap_height(alien[0].sprites[0]), BAIXO);
}

void colisao_alien_vs_projetil (Jogo *jogo) {
	for (int i = 0; i < jogo->numero_de_projeteis; i++) {
		for (int j = 0; j < COLUNAS_TROPA; j++) {
			for (int v = 0; v < LINHAS_TROPA; v++) {
				if ((!(get_posicao_x_min_projetil(&jogo->conjunto_projeteis[i]) > get_posicao_x_max_alien(&jogo->alien[j * LINHAS_TROPA + v])
					|| get_posicao_y_min_projetil(&jogo->conjunto_projeteis[i]) > get_posicao_y_max_alien(&jogo->alien[j * LINHAS_TROPA + v])
					|| get_posicao_y_max_projetil(&jogo->conjunto_projeteis[i]) < get_posicao_y_min_alien(&jogo->alien[j * LINHAS_TROPA + v])
					|| get_posicao_x_max_projetil(&jogo->conjunto_projeteis[i]) < get_posicao_x_min_alien(&jogo->alien[j * LINHAS_TROPA + v])))
					&& jogo->alien[j * LINHAS_TROPA + v].vivo) {

						copy_projetil (&jogo->conjunto_projeteis[i], &jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);
						desenha_projetil (&jogo->conjunto_projeteis[i]);
						finaliza_projetil (&jogo->conjunto_projeteis[jogo->numero_de_projeteis-1]);

						jogo->numero_de_projeteis--;
						jogo->hud.score += PONTOS_ALIEN;

						jogo->alien[j * LINHAS_TROPA + v].vivo = false;

						return;
				}
			}
		}
	}
}

int get_posicao_x_min_alien (Alien* alien){
	return alien->posicao_x - alien->delta_x;
}

int get_posicao_x_max_alien (Alien* alien){
	return alien->posicao_x + alien->delta_x;
}

int get_posicao_y_min_alien (Alien* alien){
	return alien->posicao_y - alien->delta_y;
}

int get_posicao_y_max_alien (Alien* alien){
	return alien->posicao_y + alien->delta_y;
}

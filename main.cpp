#include <stdio.h>
#include <allegro5/allegro.h>

#include "game.h"
#include "player.h"
#include "alien.h"

int main(int argc, char **argv) {

    Jogo jogo;

    Alien alien[LINHAS_TROPA][COLUNAS_TROPA];

    inicializa_jogo (&jogo, 640, 480);

    loop_de_jogo (&jogo);

    al_rest(5);

    finaliza_jogo (&jogo);

    return 0;
}

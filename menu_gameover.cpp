#include "menu_gameover.h"
#include <allegro5/allegro_primitives.h>
#include "estado_jogo.h"

MenuGameOver::MenuGameOver(GameOverReason reason, int inimigos_abatidos) 
    : reason(reason), inimigos_abatidos(inimigos_abatidos) {
    botao_x = LARGURA_TELA / 2 - 100;
    botao_y = ALTURA_TELA / 2 + 50;
    botao_largura = 200;
    botao_altura = 50;
}

void MenuGameOver::desenhar(ALLEGRO_FONT* fonte) const {
   
    switch(reason) {
        case VITORIA:
            al_draw_text(fonte, al_map_rgb(0, 255, 0),
                        LARGURA_TELA / 2, ALTURA_TELA / 4,
                        ALLEGRO_ALIGN_CENTER, "VITÓRIA!");
            al_draw_text(fonte, al_map_rgb(255, 255, 255),
                        LARGURA_TELA / 2, ALTURA_TELA / 3,
                        ALLEGRO_ALIGN_CENTER, "Você defendeu a base com sucesso!");
            break;

        case BASE_DESTRUIDA:
            al_draw_text(fonte, al_map_rgb(255, 0, 0),
                        LARGURA_TELA / 2, ALTURA_TELA / 4,
                        ALLEGRO_ALIGN_CENTER, "DERROTA!");
            al_draw_text(fonte, al_map_rgb(255, 255, 255),
                        LARGURA_TELA / 2, ALTURA_TELA / 3,
                        ALLEGRO_ALIGN_CENTER, "A base foi destruída!");
            break;

        case JOGADOR_MORTO:
            al_draw_text(fonte, al_map_rgb(255, 0, 0),
                        LARGURA_TELA / 2, ALTURA_TELA / 4,
                        ALLEGRO_ALIGN_CENTER, "DERROTA!");
            al_draw_text(fonte, al_map_rgb(255, 255, 255),
                        LARGURA_TELA / 2, ALTURA_TELA / 3,
                        ALLEGRO_ALIGN_CENTER, "Você morreu!");
            break;
    }

   
    al_draw_textf(fonte, al_map_rgb(255, 255, 255),
                 LARGURA_TELA / 2, ALTURA_TELA / 2,
                 ALLEGRO_ALIGN_CENTER, "Inimigos Abatidos: %d", inimigos_abatidos);

   
    al_draw_filled_rectangle(botao_x, botao_y,
                           botao_x + botao_largura, botao_y + botao_altura,
                           al_map_rgb(0, 255, 0));
                           
    al_draw_text(fonte, al_map_rgb(0, 0, 0),
                 LARGURA_TELA / 2, botao_y + botao_altura/4,
                 ALLEGRO_ALIGN_CENTER, "Jogar Novamente");
}

bool MenuGameOver::jogarNovamente(float mouse_x, float mouse_y, bool mouse_clicado) const {
    return mouse_clicado &&
           mouse_x >= botao_x && mouse_x <= botao_x + botao_largura &&
           mouse_y >= botao_y && mouse_y <= botao_y + botao_altura;
}

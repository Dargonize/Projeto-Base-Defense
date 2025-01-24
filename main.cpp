#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "estado_jogo.h"
#include "menu_inicial.h"
#include "menu_gameover.h"

const float FPS = 60.0;
enum GameState
{
    MENU_INICIAL,
    JOGANDO,
    GAME_OVER
};

ALLEGRO_FONT *fonte = nullptr;

int main()
{
    srand(time(NULL));

    if (!al_init())
    {
        std::cerr << "Falha ao inicializar o Allegro!" << std::endl;
        return -1;
    }

    if (!al_init_primitives_addon())
    {
        std::cerr << "Falha ao inicializar primitivas!" << std::endl;
        return -1;
    }

    if (!al_init_font_addon())
    {
        std::cerr << "Falha ao inicializar addon de fontes!" << std::endl;
        return -1;
    }

    if (!al_init_ttf_addon())
    {
        std::cerr << "Falha ao inicializar addon TTF!" << std::endl;
        return -1;
    }

    if (!al_init_acodec_addon())
    {
        std::cerr << "Falha ao inicializar addon de áudio!" << std::endl;
        return -1;
    }

    if (!al_install_audio())
    {
        std::cerr << "Falha ao inicializar audio!" << std::endl;
        return -1;
    }

    al_reserve_samples(10);

    if (!al_install_mouse())
    {
        std::cerr << "Falha ao inicializar o mouse!" << std::endl;
        return -1;
    }

    if (!al_install_keyboard())
    {
        std::cerr << "Falha ao inicializar o teclado!" << std::endl;
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!display)
    {
        std::cerr << "Falha ao criar o display!" << std::endl;
        return -1;
    }

    // Ativa modo tela cheia
    al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);

    fonte = al_load_font("arial.ttf", 24, 0);
    if (!fonte)
    {
        std::cerr << "Falha ao carregar a fonte!" << std::endl;
        al_destroy_display(display);
        return -1;
    }

    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_KEYBOARD_STATE teclas;

    if (!fila_eventos)
    {
        std::cerr << "Falha ao criar fila de eventos!" << std::endl;
        al_destroy_font(fonte);
        al_destroy_display(display);
        return -1;
    }

    if (!timer)
    {
        std::cerr << "Falha ao criar timer!" << std::endl;
        al_destroy_event_queue(fila_eventos);
        al_destroy_font(fonte);
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    MenuInicial menu_inicial;
    EstadoJogo *estado = nullptr;
    MenuGameOver *menu_gameover = nullptr;

    GameState game_state = MENU_INICIAL;
    bool executando = true;
    bool redesenhar = true;

    float mouse_x = 0, mouse_y = 0;
    bool mouse_botao_esquerdo = false;
    bool tecla_p_pressionada = false;

    al_start_timer(timer);

    while (executando)
    {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);
        al_get_keyboard_state(&teclas);

        if (evento.type == ALLEGRO_EVENT_TIMER)
        {
            if (game_state == JOGANDO && !estado->estaPausado())
            {
                estado->atualizar(&teclas, mouse_x, mouse_y);

                if (estado->jogoAcabou() || estado->vitoria())
                {
                    game_state = GAME_OVER;
                    if (estado->vitoria())
                    {
                        menu_gameover = new MenuGameOver(VITORIA, estado->getInimigosAbatidos());
                    }
                    else if (estado->getBase().estaDestruida())
                    {
                        menu_gameover = new MenuGameOver(BASE_DESTRUIDA, estado->getInimigosAbatidos());
                    }
                    else
                    {
                        menu_gameover = new MenuGameOver(JOGADOR_MORTO, estado->getInimigosAbatidos());
                    }
                    mouse_botao_esquerdo = false;
                }
            }
            redesenhar = true;
        }
        else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            executando = false;
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouse_x = evento.mouse.x;
            mouse_y = evento.mouse.y;
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (evento.mouse.button & 1)
            {
                mouse_botao_esquerdo = true;
                if (game_state == MENU_INICIAL)
                {
                    Dificuldade dif = menu_inicial.verificarSelecao(mouse_x, mouse_y, true);
                    if (menu_inicial.foiSelecionado())
                    {
                        game_state = JOGANDO;
                        estado = new EstadoJogo(dif);
                    }
                }
            }
            if (evento.mouse.button & 2 && game_state == JOGANDO && !estado->estaPausado())
            {
                estado->getJogador().definirDestino(evento.mouse.x, evento.mouse.y);
            }
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if (evento.mouse.button & 1)
            {
                mouse_botao_esquerdo = false;
            }
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                executando = false;
            }
            else if (evento.keyboard.keycode == ALLEGRO_KEY_P && game_state == JOGANDO)
            {
                if (!tecla_p_pressionada)
                {
                    estado->alternarPause();
                    tecla_p_pressionada = true;
                }
            }
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (evento.keyboard.keycode == ALLEGRO_KEY_P)
            {
                tecla_p_pressionada = false;
            }
        }

        if (redesenhar && al_is_event_queue_empty(fila_eventos))
        {
            redesenhar = false;
            al_clear_to_color(al_map_rgb(20, 20, 20));

            switch (game_state)
            {
            case MENU_INICIAL:
                menu_inicial.desenhar(fonte);
                break;

            case JOGANDO:
                if (estado)
                {
                    estado->desenhar();
                    if (estado->estaPausado())
                    {
                        al_draw_text(fonte, al_map_rgb(255, 255, 255),
                                     LARGURA_TELA / 2, ALTURA_TELA / 2,
                                     ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");
                    }
                }
                break;

            case GAME_OVER:
                if (menu_gameover)
                {
                    menu_gameover->desenhar(fonte);
                    if (menu_gameover->jogarNovamente(mouse_x, mouse_y, mouse_botao_esquerdo))
                    {
                        delete estado;
                        delete menu_gameover;
                        estado = nullptr;
                        menu_gameover = nullptr;
                        game_state = MENU_INICIAL;
                        mouse_botao_esquerdo = false;
                    }
                }
                break;
            }

            al_flip_display();
        }
    }

    delete estado;
    delete menu_gameover;

    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(display);

    return 0;
}

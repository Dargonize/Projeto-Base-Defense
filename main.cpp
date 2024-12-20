#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "enemy.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60.0

int main() {
    // Inicializa Allegro
    if (!al_init()) {
        return -1;
    }

    // Inicializa o módulo de primitivas
    if (!al_init_primitives_addon()) {
        return -1;
    }

    // Cria a janela
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        return -1;
    }

    // Inicializa o temporizador
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        al_destroy_display(display);
        return -1;
    }

    // Inicializa o teclado
    if (!al_install_keyboard()) {
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }

    // Inicializa o mouse
    if (!al_install_mouse()) {
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }

    // Cria a fila de eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    if (!event_queue) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    // Registra as fontes de eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Inicializa a semente aleatória
    srand(time(NULL));

    // Cria o jogador
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    // Lista de inimigos
    std::vector<Enemy> enemies;

    // Inicia o timer
    al_start_timer(timer);

    bool redraw = true;
    bool running = true;
    
    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Lógica de atualização aqui
            player.move();
            for (auto& enemy : enemies) {
                enemy.move(player.x, player.y);
            }
            
            // Spawn de inimigos baseado no timer
            static float enemy_spawn_timer = 0.0f;
            enemy_spawn_timer += 1.0f / FPS;
            if (enemy_spawn_timer > 2.0f) {
                enemies.push_back(Enemy(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
                enemy_spawn_timer = 0.0f;
            }
            
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (ev.mouse.button == 2) {  // Botão direito do mouse
                player.move_to(ev.mouse.x, ev.mouse.y);
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            player.draw();
            for (const auto& enemy : enemies) {
                enemy.draw();
            }
            al_flip_display();
        }
    }

    // Limpeza
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);
    
    return 0;
}
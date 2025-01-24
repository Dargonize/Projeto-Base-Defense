#include "base.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

void Base::atualizar() {
   if (vida < vida_maxima) {
       tempo_regeneracao += 1.0f / 60.0f;
       if (tempo_regeneracao >= 1.0f) {
           vida++;
           tempo_regeneracao = 0.0f;
       }
   }
}

void Base::desenhar() const {
  
   al_draw_circle(x, y, raio, al_map_rgb(0, 0, 255), 5);
   
   float porcentagem_vida = (float)vida / vida_maxima;
   

   unsigned char cor_r = 255 * (1 - porcentagem_vida);
   unsigned char cor_g = 255 * porcentagem_vida;
   unsigned char cor_b = 0;
   
  
   al_draw_arc(x, y, raio + 10, 0, porcentagem_vida * 2 * ALLEGRO_PI, 
               al_map_rgb(cor_r, cor_g, cor_b), 5);
}

void Base::receberDano(int dano) {
   vida -= dano;
   if (vida < 0) vida = 0;
}

bool Base::estaDestruida() const {
   return vida <= 0;
}

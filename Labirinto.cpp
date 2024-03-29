#include "Labirinto.h"
#include "Coordenada.h"
#include "ListaCoordenadas.h"
#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <array> 

void Labirinto::setNome_arquivo(const char *nome){
    this->nome_arquivo = nome;
}

void Labirinto::exibir_labirinto(){
    al_clear_to_color(al_map_rgb(0,0,0)); //Cor de background da tela
    mapa_desenho = al_load_bitmap("./imagenstrab/bloco.png");
    for(Coordenada& coordenada : coordenadas_tijolo){
        al_draw_bitmap(mapa_desenho,TAM_LADO*coordenada.getX(),TAM_LADO*coordenada.getY(),0);
    }

    

}

void Labirinto::carregarPosicaoDosTijolos(){
    int x, y;
    FILE* arquivoDoLabirinto = fopen("./imagenstrab/coordenadas.txt", "r");
    if(arquivoDoLabirinto == NULL){
        printf("Erro em abrir o arquivo de posição dos tijolos!");
        exit(1);
    }
    int i = 0;
    while (fscanf(arquivoDoLabirinto, "%d %d", &x, &y) == 2){
        coordenadas_tijolo.addCoordenada(Coordenada(x,y));
 
       matriz_colisao[y][x]= TIJOLO;
        i++;
        
    }
    fclose(arquivoDoLabirinto);
}


void Labirinto::exibir_pilulas(){
    int indiceX;
    int indiceY;
    
    pilula_desenho = al_load_bitmap("./imagenstrab/sprite_pilula2.png");
    for(Coordenada& coordenada : coordenadas_pilulas){
        if(matriz_colisao[coordenada.getY()][coordenada.getX()] == PILULA){
            indiceX = coordenada.getX();
            indiceY = coordenada.getY();
            al_draw_bitmap_region(pilula_desenho, TAM_LADO*(int)frame_pilula, 0, TAM_LADO, TAM_LADO, TAM_LADO*indiceX ,TAM_LADO*indiceY,0);
            altera_frame_pilula();
        }

    }
    
}

int Labirinto::conta_pilulas(){
    int total = 0;
    for(int i = 0 ; i<ORDEM ; i++){
       for(int j = 0 ; j <ORDEM; j++){
            if(matriz_colisao[i][j] == PILULA){
                total++;
            }
      }
   }
    return total;

}
void Labirinto::carregarPosicaoDasPilulas(){
    for(int i = 0; i< ORDEM ; i++){
        for(int j = 0; j<ORDEM ; j++){
            if(matriz_colisao[j][i] == CELULA_VAZIA){
                coordenadas_pilulas.addCoordenada(Coordenada(i,j));
                matriz_colisao[j][i]= PILULA; 
            }
        }
    }
}

void Labirinto::altera_frame_pilula(){
      frame_pilula += 0.1f;
      if(frame_pilula > 6){
         frame_pilula -= 6;
      }
}

Labirinto::Labirinto(){
    for(int i = 0; i < ORDEM; i++){
        for(int j=0; j < ORDEM; j++){
            matriz_colisao[i][j] = CELULA_VAZIA;
        }
    }
}



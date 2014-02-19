#pragma once

#include"pacman.h"
#include"utils.h"
#include"fantome.h"
#include"terrain.h"


bool testgain(terrain& T);

string stringify(int x);
void affiche_vies(int restvies);

void affiche_score(int score);
void initialise_score(int& score);
void incremente_score(pacman& P,int& score,int compteur,bool VITA,bool gain,bool increment,int fantomes_morts);
void affiche_meilleurscore(int meilleurscore);

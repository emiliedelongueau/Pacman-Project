#include "pacman.h"


pacman::pacman() {
};

pacman::pacman(int x, int y) {

	etat = 0;
	i=x;
	j=y;
	dir = droite;
	tmpDir = droite;
	changeDir = true;
	gomme=false;

}

pacman::~pacman() {
		
}


void pacman::tourne(Direction dir1) {
	dir = dir1;
}

void pacman::affiche(NativeBitmap pacman_debut, NativeBitmap pacman_normal, NativeBitmap pacman_vitamine, int nb_w, int nb_h) { //affiche la bonne image selon si pacman est au debut, normal ou mange une vitamine
	switch (etat) {
	case 0:
		putNativeBitmap(nb_w*j, nb_h*i, pacman_debut);
		break;
	case 1: 
		putNativeBitmap(nb_w*j, nb_h*i,pacman_normal);
		break;
	case 2:
		putNativeBitmap(nb_w*j, nb_h*i, pacman_vitamine);
		break;
	}
}


void pacman::avance(terrain& T,NativeBitmap rien, NativeBitmap pacman_debut, NativeBitmap pacman_normal, NativeBitmap pacman_vitamine, int nb_w, int nb_h) {
	switch (dir) {
		case droite :
			if (i==7 && j==20) {
				putNativeBitmap(nb_w*j, nb_h*i, rien);
				T(i,j)=0;
				j=0;
				if (T(7,0)==1)
					gomme=true;
				affiche(pacman_debut, pacman_normal, pacman_vitamine, nb_w, nb_h);
			} // passage secret

			else if (T(i,j+1)!=3) {
				putNativeBitmap(nb_w*j, nb_h*i, rien);
				T(i,j)=0;
				j+=1;
				if (T(i,j)==1)
					gomme=true;
				affiche(pacman_debut, pacman_normal, pacman_vitamine, nb_w, nb_h);
			}
			break;

		case haut : 
			if (T(i-1,j)!=3) {
				putNativeBitmap(nb_w*j, nb_h*i, rien);
				T(i,j)=0;
				i-=1;
				if (T(i,j)==1)
					gomme=true;
				affiche(pacman_debut, pacman_normal, pacman_vitamine, nb_w, nb_h);
			}
			break;

		case gauche :
			if ( i == 7 && j == 0 ) {
				putNativeBitmap(nb_w*j, nb_h*i, rien);
				T(i,j)=0;
				j=20;
				if (T(7,20)==1)
					gomme=true;
				affiche(pacman_debut, pacman_normal, pacman_vitamine, nb_w, nb_h);
			} //passage secret

			else if (T(i,j-1)!=3) {
				putNativeBitmap(nb_w*j, nb_h*i, rien);
				T(i,j)=0;
				j-=1;
				if (T(i,j)==1)
					gomme=true;
				affiche(pacman_debut, pacman_normal, pacman_vitamine, nb_w, nb_h);
			}
			break;

		case bas :
			if (T(i+1,j)!= 3 && T(i+1,j)!=4) {
				putNativeBitmap(nb_w*j, nb_h*i, rien);
				T(i,j)=0;
				i+=1;
				if (T(i,j)==1)
					gomme=true;
				affiche(pacman_debut, pacman_normal, pacman_vitamine, nb_w, nb_h);
			}
			break;
	}
	
}


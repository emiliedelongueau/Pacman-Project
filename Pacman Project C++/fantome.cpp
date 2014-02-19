#include"fantome.h"


fantome::fantome() {
}

fantome::~fantome() {

}

void fantome::initialise(int x, int y,int etat_ini,int tmp_ini,Direction dir_ini) {
	etat = etat_ini; 
	tmp = tmp_ini;
	i=x;
	j=y;
	dir = dir_ini;
	compteurDebut=0;
}


void fantome::tourne(Direction dir1) {
	dir = dir1;
}

void fantome::affiche(NativeBitmap fantome_normal, NativeBitmap fantome_vitamine, int nb_w, int nb_h) { //affiche la bonne image 
	switch (etat) {

	case 6: 
		putNativeBitmap(nb_w*j, nb_h*i,fantome_normal);
		break;
	case 7:
		putNativeBitmap(nb_w*j, nb_h*i, fantome_vitamine);
		break;
	case 8:
		putNativeBitmap(nb_w*j, nb_h*i,fantome_normal);
		break;

	}
}

void fantome::afficheTmp(NativeBitmap rien, NativeBitmap gomme, NativeBitmap vitamine, NativeBitmap maison, NativeBitmap porte, int nb_w, int nb_h) {
	switch(tmp) {
	case 0 : 
		putNativeBitmap(nb_w*j,nb_h*i,rien);
		break;
	case 1 : 
		putNativeBitmap(nb_w*j,nb_h*i,gomme);
		break;
	case 2 : 
		putNativeBitmap(nb_w*j,nb_h*i,vitamine);
		break;
	case 4 : 
		putNativeBitmap(nb_w*j,nb_h*i,porte);
		break;
	case 5 : 
		putNativeBitmap(nb_w*j,nb_h*i,maison);
		break;
	}
}

void fantome::avance(terrain& T,NativeBitmap rien, NativeBitmap gomme, NativeBitmap vitamine, NativeBitmap maison, NativeBitmap porte, NativeBitmap fantome_normal, NativeBitmap fantome_vitamine, int nb_w, int nb_h) {
	switch (dir) {
	case droite :
		if (i==7 && j==20) {
			afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
			tmp = T(7,0);
			j=0;
			affiche(fantome_normal, fantome_vitamine, nb_w, nb_h);
		} // passage secret

		else if (T(i,j+1)!=3) {
			afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
			tmp = T(i,j+1);
			j+=1;
			affiche(fantome_normal, fantome_vitamine, nb_w, nb_h);
		}
		break;

	case haut : 
		if (T(i-1,j)!=3) {
			afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
			tmp=T(i-1,j);
			i-=1;
			affiche(fantome_normal, fantome_vitamine, nb_w, nb_h);
		}
		break;

	case gauche :
		if ( i == 7 && j == 0 ) {
			afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
			tmp=T(7,20);
			j=20;
			affiche(fantome_normal, fantome_vitamine, nb_w, nb_h);
		} //passage secret

		else if (T(i,j-1)!=3) {
			afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
			tmp=T(i,j-1);
			j-=1;
			affiche(fantome_normal, fantome_vitamine, nb_w, nb_h);
		}
		break;

	case bas :
		if (T(i+1,j)!= 3 && T(i+1,j)!=4) {
			afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
			tmp=T(i+1,j);
			i+=1;
			affiche(fantome_normal, fantome_vitamine, nb_w, nb_h);
		}
		break;
	}

}


void fantome::choisirDir(pacman P, terrain& T) { //poursuite du pacman
	if (P.i-i == 0 ) {
		if (P.j-j > 0 && T(i,j+1)!=3) 
			dir = droite;
		else if (P.j-j < 0) 
			dir = gauche;
	}


	else if (P.j-j == 0 ) {
		if (P.i-i > 0 && T(i+1,j)!=3)
			dir = bas;
		else if (P.i-i < 0) 
			dir = haut;
	}

	else if (P.i-i > 0) {
		if (P.j-j > 0) {
			if (P.j-j > P.i-i) {
				if (T(i,j+1)!=3) 
					dir = droite;
				else 
					dir = bas;	
			}
			else {
				if (T(i+1,j)!=3) 
					dir = bas;
				else 
					dir = droite;
			}
		}

		else {
			if (j-P.j > P.i-i) {
				if (T(i,j-1)!=3) 
					dir = gauche;
				else 
					dir = bas;
			}
			else {
				if (T(i+1,j)!=3)
					dir = bas;
				else 
					dir = gauche;
			}
		}
	}

	else {
		if (P.j-j > 0) {
			if (P.j-j > i-P.i) {
				if (T(i,j+1)!=3) 
					dir = droite;
				else
					dir = haut;
			}

			else {
				if (T(i-1,j)!=3) 
					dir = haut;
				else 
					dir = droite;
			}
		}

		else {
			if (j-P.j >i-P.i) {
				if (T(i,j-1)!=3) 
					dir = gauche;
				else 
					dir = haut;
			}
			else {
				if (T(i-1,j)!=3) 
					dir = haut;
				else 
					dir = gauche;
			}
		}
	}
}


void fantome::fuirDir(pacman P, terrain& T) { //fuite du pacman
	if (P.i-i == 0 ) {
		if(T(i+1,j)!=3)
			dir=bas;
		else if(T(i-1,j)!=3)
			dir=haut;
		else 
			if (P.j-j > 0)
				dir= gauche;
			else dir=droite;

	}

	else if (P.j-j == 0 ) {
		if(T(i,j+1)!=3)
			dir=droite;
		else if(T(i,j-1)!=3)
			dir=gauche;
		else 
			if (P.i-i > 0)
				dir= haut;
			else dir=bas;
	}

	else if (P.i-i > 0) {
		if (P.j-j > 0) {
			if (P.j-j > P.i-i) {
				if (T(i-1,j)!=3) 
					dir = haut;
				else 
					dir = gauche;
			}
			else {
				if (T(i,j-1)!=3) 
					dir = gauche;
				else 
					dir = haut;
			}
		}

		else {
			if (j-P.j > P.i-i) {
				if (T(i-1,j)!=3) 
					dir = haut;
				else 
					dir = droite;
			}
			else {
				if (T(i,j+1)!=3) 
					dir = droite;
				else 
					dir = haut;
			}
		}
	}

	else {
		if (P.j-j > 0) {
			if (P.j-j > i-P.i) {
				if (T(i+1,j)!=3) 
					dir = bas;
				else 
					dir = gauche;
			}

			else {
				if (T(i,j-1)!=3) 
					dir = gauche;
				else 
					dir = bas;
			}
		}

		else {
			if (j-P.j >i-P.i) {
				if (T(i+1,j)!=3) 
					dir = bas;
				else 
					dir = droite;
			}
			else {
				if (T(i,j+1)!=3) 
					dir = droite;
				else 
					dir = bas;
			}
		}
	}
}


bool fantome::mangepacman(pacman& P) {
	if (etat == 6 && P.i == i && P.j == j)
		return true;
	else
		return false;
}

bool fantome::meurt(pacman& P) {
	if (etat == 7 && P.i == i && P.j == j)
		return true;
	else
		return false;
}











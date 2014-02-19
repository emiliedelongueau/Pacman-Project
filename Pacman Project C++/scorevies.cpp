#include"scorevies.h"


bool testgain(terrain& T)
{	
	bool gain = true;
for(int i=0;i<T.L && gain;i++) {
	for(int j=0;j<T.C && gain;j++) {
		if (T(i,j)==1 || T(i,j)==2) {
			gain = false;
		}
	}
}
return gain;
}


/////////////////Affichage du score et des vies//////////////////////////////////////////////////

string stringify(int x){ //convertit un entier en string(utile pour l'affichage du score et du nombre de vies)
	std::ostringstream o;
	o<<x;
	return o.str();
}

void affiche_vies(int restvies)
{
	fillRect(550,10,200,30,WHITE);
	drawString(550,10,"nombre de vies="+stringify(restvies),BLACK);
}

void affiche_score(int score){
	fillRect(550,40,200,30,WHITE);
	drawString(550,40,"score ="+stringify(score),RED);
}


void initialise_score(int& score) {
	score=0;
	affiche_score(score);
}


void incremente_score(pacman& P,int& score,int compteur,bool VITA,bool gain,bool increment,int fantomes_morts) {
	if(VITA && compteur==0)
		score+=50;
	if(P.gomme) {
		score+=10;
		P.gomme=false;
	}
	if(gain) {
		score+=500;
	}

	if(increment) {
		switch(fantomes_morts) { //plus on mange de fantomes au cours de la meme vita, plus on marque le nombre de points inscrits est eleve
		case 1:
			score+=200;
			break;
		case 2:
			score+=400;
			break;
		case 3:
			score+=800;
			break;
		case 4:
			score+=1600;
			break;
		}
	}
	affiche_score(score);
}




void affiche_meilleurscore(int meilleurscore){
	fillRect(550,70,200,30,WHITE);
	drawString(550,70,"meilleur score ="+stringify(meilleurscore),GREEN);
}


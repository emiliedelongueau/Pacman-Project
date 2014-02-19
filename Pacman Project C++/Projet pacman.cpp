// Imagine++ project
// Project:  Projet pacman
// Author:   Vianney
// Date:     2011/1/14


#include "pacman.h"
#include "fantome.h"
#include "terrain.h"
#include"scorevies.h"
#include "utils.h"
#include <fstream>
using namespace std;

const int largeurImagette = 24;
const int hauteurImagette = 24;




int main()
{
	terrain A(16,21);
	openWindow(A.C*largeurImagette+600,A.L*hauteurImagette);

	//////////////////////////CHARGEMENT IMAGETTES ///////////////////////////////

	byte* rgb1; //tableaux de bytes pour stocker les images du terrain : vitamines,murs...
	byte* rgb2; 
	byte* rgb3; 
	byte* rgb4; 
	byte* rgb5;  
	byte* rgb6;
	byte* rgb7; //pour stocker les imagettes du pacman 
	byte* rgb8; 
	byte* rgb9;
	byte* rgb10;
	byte* rgb11;

	NativeBitmap mur(largeurImagette,hauteurImagette); // 0 rien, 1 gomme, 2 vitamine, 3 mur, 4 porte, 5 maison
	NativeBitmap maison(largeurImagette,hauteurImagette);
	NativeBitmap porte(largeurImagette,hauteurImagette);
	NativeBitmap gomme(largeurImagette,hauteurImagette);
	NativeBitmap vitamine(largeurImagette,hauteurImagette);
	NativeBitmap rien(largeurImagette,hauteurImagette);
	NativeBitmap pacman_debut(largeurImagette,hauteurImagette);
	NativeBitmap pacman_normal(largeurImagette,hauteurImagette);
	NativeBitmap pacman_vitamine(largeurImagette,hauteurImagette);
	NativeBitmap fantome_normal(largeurImagette,hauteurImagette);
	NativeBitmap fantome_vitamine(largeurImagette,hauteurImagette);

	int nb_w;
	int nb_h;

	loadColorImage("mur.bmp",rgb1,nb_w,nb_h);
	loadColorImage("gomme.bmp",rgb2,nb_w,nb_h);
	loadColorImage("maison.bmp",rgb3,nb_w,nb_h);
	loadColorImage("porte.bmp",rgb4,nb_w,nb_h);
	loadColorImage("vitamine.bmp",rgb5,nb_w,nb_h);
	loadColorImage("rien.bmp",rgb6,nb_w,nb_h);
	loadColorImage("pacman_debut.bmp",rgb7,nb_w,nb_h);
	loadColorImage("pacman_normal.bmp",rgb8,nb_w,nb_h);
	loadColorImage("pacman_vitamine.bmp",rgb9,nb_w,nb_h);
	loadColorImage("fantome_normal.bmp",rgb10,nb_w,nb_h);
	loadColorImage("fantome_vitamine.bmp",rgb11,nb_w,nb_h);



	mur.setColorImage(0,0,rgb1,nb_w,nb_h);
	gomme.setColorImage(0,0,rgb2,nb_w,nb_h);
	maison.setColorImage(0,0,rgb3,nb_w,nb_h);
	porte.setColorImage(0,0,rgb4,nb_w,nb_h);
	vitamine.setColorImage(0,0,rgb5,nb_w,nb_h);
	rien.setColorImage(0,0,rgb6,nb_w,nb_h);
	pacman_debut.setColorImage(0,0,rgb7,nb_w,nb_h);
	pacman_normal.setColorImage(0,0,rgb8,nb_w,nb_h);
	pacman_vitamine.setColorImage(0,0,rgb9,nb_w,nb_h);
	fantome_normal.setColorImage(0,0,rgb10,nb_w,nb_h);
	fantome_vitamine.setColorImage(0,0,rgb11,nb_w,nb_h);

	delete[] rgb1;
	delete[] rgb2;
	delete[] rgb3;
	delete[] rgb4;	
	delete[] rgb5;
	delete[] rgb6;
	delete[] rgb7;
	delete[] rgb8;
	delete[] rgb9;
	delete[] rgb10;
	delete[] rgb11;
	/////////////////////////////////////////////////////////////////////////////

	////////////////////////// INITIALISATION ///////////////////////////////////
	int meilleurscore=0;
	int restvies=5;
	int score=0;
	bool gain=false;
	

	drawString(A.C*largeurImagette+10,110,"CLIQUEZ SUR L'ECRAN POUR COMMENCER",BLACK,20);

	while(click())//boucle pour recommencer le jeu apres avoir perdu ou gagne
	{
		restvies=5;
		gain=false;
		fillRect(A.C*largeurImagette+10,110,700,50,WHITE);//cache le "Cliquez l'ecran pour commencer" ou "vous avez gagne ou perdu"

		do //boucle s'il reste des vies apres etre mort 
		{

			A.rempliTerrain("plan.txt");
			A.afficheTerrain(rien,gomme,vitamine,mur,porte, maison, nb_w, nb_h);

			affiche_vies(restvies);//affiche le nombre de vies restantes
			affiche_meilleurscore(meilleurscore);
			initialise_score(score);
			


			pacman P(10,10);
			P.affiche(pacman_debut,pacman_normal,pacman_vitamine,nb_w,nb_h);

			fantome F[4];
			for(int i=0;i<4;i++) {
				F[i].initialise(7,10,6,5,droite);
				F[i].affiche(fantome_normal,fantome_vitamine,nb_w,nb_h);
			}

			milliSleep(3000);
			P.etat = 1 ;


			bool death = false ;
			bool VITA = false ; // true si le pacman mange une vitamine
			int compteur = 0;   // calcul le nombre de tours pendant lesquels pacman subit l'effet de la vitamine
			int fantomes_morts=0;//nombre de fantomes manges au cours de la meme prise de vitamine,pour le score
			bool increment=false;//true si un fantome a ete mange dans la boucle:le score est alors incremente
			//////////////////////////////// JEU ///////////////////////////////////////////////

			do {

			
				switch (Clavier()) {

				case KEY_RIGHT: 
					if(A(P.i,P.j+1)!=3) {
						P.tourne(droite); 
						P.changeDir = true; 
					}
					else {
						P.tmpDir = droite;//retient la direction souhaitee pour faire tourner le pacman quand ce sera possible
						P.changeDir = false;// retient que le pacman n'a pas tourne car il y avait un mur
					}
					break;

				case KEY_DOWN: 
					if(A(P.i+1,P.j)!=3) {
						P.tourne(bas); 
						P.changeDir = true;
					}
					else {
						P.tmpDir = bas;
						P.changeDir = false;
					}
					break;

				case KEY_LEFT:
					if(A(P.i,P.j-1)!=3) {
						P.tourne(gauche);
						P.changeDir = true;
					}
					else {
						P.tmpDir = gauche;
						P.changeDir = false;
					}
					break;

				case KEY_UP: 
					if(A(P.i-1,P.j)!=3) {
						P.tourne(haut);
						P.changeDir = true;
					}
					else {
						P.tmpDir = haut;
						P.changeDir = false;
					}
					break;

				}


				if (P.changeDir == false) { // fait tourner le pacman si possible dans la direction souhaitee aux boucles de deplacement precedentes
					switch (P.tmpDir) {     

					case droite : 
						if(A(P.i,P.j+1)!=3)
							P.tourne(droite); 

						break;

					case bas : 
						if(A(P.i+1,P.j)!=3)
							P.tourne(bas); 

						break;

					case gauche :
						if(A(P.i,P.j-1)!=3)
							P.tourne(gauche);

						break;

					case haut : 
						if(A(P.i-1,P.j)!=3)
							P.tourne(haut);

						break;

					}
				}
				


				if (VITA = true  && compteur <=35) {
					compteur+=1;
				}  


				if (A(P.i,P.j)==2) { //Pacman mange une vitamine
					P.etat = 2;
					for(int k=0;k<4;k++) {
						if(F[k].etat!=8) 
							F[k].etat = 7; //les fantomes peuvent etre manges
					}
					VITA = true ;
					compteur = 0;
					fantomes_morts=0; //sert pour l'incrementation du score
				} 


				if (compteur>35) { //fin de l'effet vitamine
					P.etat = 1;
					for(int k=0;k<4;k++) {
						if(F[k].etat == 8 ) {
							F[k].compteurDebut = 0; //les fantomes morts vont pouvoir ressortir du repere
						}
							F[k].etat = 6; 
					}
					VITA = false;
					compteur = 0;
				} 


				for(int k=0;k<4;k++) {
					if (F[k].mangepacman(P)) 
						death = true;   // pacman meurt s'il rencontre un fantome

					if (F[k].meurt(P)) { //si meurt, le fantome est mange et replace dans le repere
						F[k].etat=8;
						F[k].afficheTmp(rien,gomme,vitamine, maison, porte,nb_w,nb_h);
						F[k].i=7;
						F[k].j=10;
						F[k].tmp=5;
						F[k].affiche(fantome_normal, fantome_vitamine,nb_w,nb_h);
						fantomes_morts+=1;
						increment=true;//le score sera incremente a la fin de la boucle
					}  

					
					/////////////Deplacement des fantomes////////////////
					if(F[k].etat!=8) {
						if(F[k].compteurDebut>=8*k && F[k].compteurDebut<=8*k+2) { //fantomes sortent du repere l'un apres l'autre
							F[k].dir=haut;
							F[k].avance(A,rien,gomme,vitamine,maison,porte,fantome_normal,fantome_vitamine,nb_w,nb_h);
						}
						else if(F[k].compteurDebut>=8*k+3 && F[k].compteurDebut<=8*k+6) {
							if(k%2==0)
								F[k].dir=droite;
							else F[k].dir=gauche;//un fantome sur deux part a droite(resp.gauche) a la sortie du repere
							F[k].avance(A,rien,gomme,vitamine,maison,porte,fantome_normal,fantome_vitamine,nb_w,nb_h);
						}
						else if(F[k].compteurDebut>8*k+6) { 
							if(F[k].etat==7 && compteur%2 == 0) { //si VITA, le fantôme fuit le pacman et avance un coup sur deux
								F[k].fuirDir(P,A);
								F[k].avance(A,rien,gomme,vitamine,maison,porte,fantome_normal,fantome_vitamine,nb_w,nb_h);
							}
							
								
							else if(F[k].etat==6) { //sinon il le poursuit
								F[k].choisirDir(P,A);
								F[k].avance(A,rien,gomme,vitamine,maison,porte,fantome_normal,fantome_vitamine,nb_w,nb_h);
							}
						
						}
						F[k].compteurDebut +=1;
					}
				}
			
				P.avance(A,rien,pacman_debut,pacman_normal,pacman_vitamine,nb_w,nb_h);


				if(testgain(A))  {    //teste s'il reste des gommes ou vitamines dans le terrain
					gain=true;
					drawString(A.C*largeurImagette+10,110,"GAGNE! CLIQUEZ POUR RECOMMENCEZ",BLACK,20);
				}

				incremente_score(P,score,compteur,VITA,gain,increment,fantomes_morts);
				increment=false;
				
				milliSleep(150);

			} while (!death && !gain);

			if(score>meilleurscore) //actualise le meilleur score
				meilleurscore=score;

			if (restvies==0 && !gain){
				drawString(A.C*largeurImagette+10,110,"PERDU! CLIQUEZ POUR RECOMMENCEZ",BLACK,20);
			}

			restvies-=1;
		}
		while(restvies>=0 && !gain);

		milliSleep(5000);
	}





	endGraphics();

	return 0;

}
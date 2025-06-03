#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>


// taille du serpent
#define TAILLE 10
// dimensions du plateau
#define LARGEUR_PLATEAU 80	
#define HAUTEUR_PLATEAU 40
#define MIN_POS_X 1
#define MIN_POS_Y 1
// position initiale de la tête du serpent
#define X_INITIAL_S_1 40
#define Y_INITIAL_S_1 13
#define X_INITIAL_S_2 40
#define Y_INITIAL_S_2 27
// nombre de pommes à manger pour gagner
#define NB_POMMES 10
// temporisation entre deux déplacements du serpent (en microsecondes)
#define ATTENTE 100000
// caractères pour représenter le serpent
#define CORPS 'X'
#define TETE_S_1 '1'
#define TETE_S_2 '2'
// touches de direction ou d'arrêt du jeu
#define HAUT 'z'
#define BAS 's'
#define GAUCHE 'q'
#define DROITE 'd'
#define STOP 'a'
// caractères pour les éléments du plateau
#define BORDURE '#'
#define VIDE ' '
#define POMME '6'
#define POSITION_PORTAIL 2
//est le nombre de chemin que peut emprunter le serpent
#define NOMBRE_DISTANCE_POSSIBLE 5
//cordonnée des portails
#define PORTAIL_X (LARGEUR_PLATEAU / POSITION_PORTAIL)
#define PORTAIL_Y (HAUTEUR_PLATEAU / POSITION_PORTAIL)
//definifition de tout les chemin
#define CHEMIN_0 0 //chemin sans portail
#define CHEMIN_1 1 //portail gauche
#define CHEMIN_2 2 //portail haut
#define CHEMIN_3 3 //portail droite
#define CHEMIN_4 4 //portail bas

#define LARGEUR_PAVE 5
#define HAUTEUR_PAVE 5
#define NB_PAVES 6

// définition d'un type pour le plateau : tPlateau
// Attention, pour que les indices du tableau 2D (qui commencent à 0) coincident
// avec les coordonées à l'écran (qui commencent à 1), on ajoute 1 aux dimensions
// et on neutralise la ligne 0 et la colonne 0 du tableau 2D (elles ne sont jamais
// utilisées)
typedef char tPlateau[LARGEUR_PLATEAU+1][HAUTEUR_PLATEAU+1];


void initPlateau(tPlateau plateau, int lesPavesX[], int lesPavesY[]);
void dessinerPlateau(tPlateau plateau);
void ajouterPomme(tPlateau plateau, int lesPommesX[], int lesPommesY[], int pommeActuel);
void afficher(int, int, char);
void effacer(int x, int y);
void dessinerSerpent1();
void dessinerSerpent2();
void progresser1(char direction, tPlateau plateau, bool * collision1, bool * pomme);
void progresser2(char direction, tPlateau plateau, bool * collision1, bool * pomme);
void gotoxy();
void choisirDirection1();
void choisirDirection2();
int calculDistance1();
int calculDistance2();
int kbhit();
bool estSurPave1();
bool estSurPave2();
char ChercheDirectionSure1(char directionActuelle, tPlateau plateau);
char ChercheDirectionSure2(char directionActuelle, tPlateau plateau);
bool VerifieDirectionSure1(char direction, tPlateau plateau);
bool VerifieDirectionSure2(char direction, tPlateau plateau);
void disable_echo();
void enable_echo();




//variable vu pour tous pour simplifié le nombre de paramètre dans les fonctions
//surtout celle de estSurSerpent
int lesX1[TAILLE];
int lesY1[TAILLE];

int lesX2[TAILLE];
int lesY2[TAILLE];


int main(){
	// 2 tableaux contenant les positions des éléments qui constituent le serpent

    // coordonées des pommes
    int lesPommesX[NB_POMMES] = {40, 75, 78, 2, 9, 78, 74, 2, 72, 5};
	int lesPommesY[NB_POMMES] = {20, 38, 2, 2, 5, 38, 32, 38, 32, 2};
	//coordonnees des paves
    int lesPavesX[NB_PAVES] = { 4, 73, 4, 73, 38, 38};
	int lesPavesY[NB_PAVES] = { 4, 4, 33, 33, 14, 22};

    // initialisation de la pomme actuel a mangé
    int pommeActuel = 0;


	// représente la touche frappée par l'utilisateur : touche de direction ou pour l'arrêt
	char touche;

	//direction courante du serpent (HAUT, BAS, GAUCHE ou DROITE)
	char direction1;
    char direction2;

	// le plateau de jeu
	tPlateau lePlateau;

	bool termine = false;


    //serpent 1
	bool pommeMangee1 = false;
    bool collision1=false;
    // compteur de pommes mangées
    int nbPommes1 = 0;
    int nombreDeplacement1 = 0;
    direction1 = DROITE;

    // initialisation de la position du serpent : positionnement de la
	// tête en (X_INITIAL, Y_INITIAL), puis des anneaux à sa gauche
    //pour serpent 1
    for(int i=0 ; i<TAILLE ; i++){
		lesX1[i] = X_INITIAL_S_1-i;
		lesY1[i] = Y_INITIAL_S_1;
	}


    //serpent 2
    bool pommeMangee2 = false;
    bool collision2=false;
    // compteur de pommes mangées
    int nbPommes2 = 0;
    int nombreDeplacement2 = 0;
    direction2 = GAUCHE;


    // initialisation de la position du serpent : positionnement de la
	// tête en (X_INITIAL, Y_INITIAL), puis des anneaux à sa droite
    //pour serpent 2
    for(int i=0 ; i<TAILLE ; i++){
		lesX2[i] = X_INITIAL_S_2+i;
		lesY2[i] = Y_INITIAL_S_2;
	}




	//pour la durée d'execution
	clock_t debut, fin;
    double tempsEcoule;



	// mise en place du plateau
	initPlateau(lePlateau, lesPavesX, lesPavesY);
	system("clear");
	dessinerPlateau(lePlateau);


	srand(time(NULL));
	ajouterPomme(lePlateau, lesPommesX, lesPommesY, pommeActuel);

	// initialisation : le serpent se dirige vers la DROITE
	dessinerSerpent1();
    dessinerSerpent2();

	disable_echo();
	
    
	touche = DROITE;
	
	//lance le chrono
	debut = clock();

	// boucle de jeu. Arret si touche STOP, si collision avec une bordure ou
	// si toutes les pommes sont mangées
	do {
        choisirDirection1(lesPommesX, lesPommesY, pommeActuel, &direction1);
        choisirDirection2(lesPommesX, lesPommesY, pommeActuel, &direction2);
		progresser1(direction1, lePlateau, &collision1, &pommeMangee1);
        progresser2(direction2, lePlateau, &collision2, &pommeMangee2);
        
        gotoxy(1, 50);
        printf("direction serpent 1: %s ", &direction1);
        printf("direction serpent 2: %s ", &direction2);


		if (pommeMangee1){
            nbPommes1++;
            pommeActuel++;
			termine = (pommeActuel==NB_POMMES);
			if (!termine){
				ajouterPomme(lePlateau, lesPommesX, lesPommesY, pommeActuel);
				pommeMangee1 = false;
			}	
			
		}
        if (pommeMangee2){
            nbPommes2++;
            pommeActuel++;
			termine = (pommeActuel==NB_POMMES);
			if (!termine){
				ajouterPomme(lePlateau, lesPommesX, lesPommesY, pommeActuel);
				pommeMangee2 = false;
			}	
			
		}
		//calcul le nombre de déplacement a chauqe tour de boucle
        nombreDeplacement1++;
        nombreDeplacement2++;


		if (!termine){
			if (!collision1 && !collision2){
				usleep(ATTENTE);
				if (kbhit()==1){
					touche = getchar();
				}
			}
		}
        usleep(ATTENTE);
	} while (touche != STOP && !collision1  && !collision2 && !termine);

	fin = clock();

    enable_echo();
	gotoxy(1, HAUTEUR_PLATEAU+3);

	//system("clear");
	tempsEcoule = (double)(fin - debut) / CLOCKS_PER_SEC;

	printf ("Duree = %.10fs\n", tempsEcoule);
	if(termine){
        if(pommeMangee1 > pommeMangee2)
        {
		    printf("Le serpent 1 a gagné en %d mouvement, et %d pomme mangées \n", nombreDeplacement1, nbPommes1);
            printf("Le serpent 2 a perdu en %d mouvement, et %d pomme mangées \n", nombreDeplacement1, nbPommes2);
        }
        else if (pommeMangee1 < pommeMangee2)
        {
		    printf("Le serpent 1 a perdu en %d mouvement, et %d pomme mangées \n", nombreDeplacement1, nbPommes1);
            printf("Le serpent 2 a gangé en %d mouvement, et %d pomme mangées \n", nombreDeplacement1, nbPommes2);
        }
        else
        {
            printf("Égalitée %d pomme mangée", pommeMangee1); // peut importe le serpent vu que égalité
        }
	} else {
		printf("Nombre de mouvement avant arret pour le serpent 1: %d \n", nombreDeplacement1);
		printf("Nombre de mouvement avant arret pour le serpent 2: %d \n", nombreDeplacement1);
	}
	
	return EXIT_SUCCESS;
}


/************************************************/
/*		FONCTIONS ET PROCEDURES DU JEU 			*/
/************************************************/
void initPlateau(tPlateau plateau, int lesPavesX[], int lesPavesY[]){
	// initialisation du plateau avec des espaces
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		for (int j=1 ; j<=HAUTEUR_PLATEAU ; j++){
			plateau[i][j] = VIDE;
		}
	}
	// Mise en place la bordure autour du plateau
	// première ligne
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		if (LARGEUR_PLATEAU/POSITION_PORTAIL==i){
			plateau[i][1]=VIDE;
		} else {
		plateau[i][1] = BORDURE;
		}
	}


	// lignes intermédiaires
	for (int j=1 ; j<=HAUTEUR_PLATEAU ; j++){
		if (HAUTEUR_PLATEAU/POSITION_PORTAIL==j){
			plateau[1][j] = VIDE;
			plateau[LARGEUR_PLATEAU][j] = VIDE;
		} else {
			plateau[1][j] = BORDURE;
			plateau[LARGEUR_PLATEAU][j] = BORDURE;
			}
		}


	// dernière ligne
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		if (LARGEUR_PLATEAU/POSITION_PORTAIL==i){
			plateau[i][HAUTEUR_PLATEAU] = VIDE;
		} else {
		plateau[i][HAUTEUR_PLATEAU] = BORDURE;
		}
	}

	for (int p = 0; p < NB_PAVES; p++){
		for(int l = 0; l < LARGEUR_PAVE; l++){
			for (int h = 0; h < HAUTEUR_PAVE; h++){
				plateau[lesPavesX[p] + l][lesPavesY[p] + h] = BORDURE;
			}
		}
	}
}

void dessinerPlateau(tPlateau plateau){
	// affiche eà l'écran le contenu du tableau 2D représentant le plateau
	for (int i=1 ; i<=LARGEUR_PLATEAU ; i++){
		for (int j=1 ; j<=HAUTEUR_PLATEAU ; j++){
			afficher(i, j, plateau[i][j]);
		}
	}
}

void ajouterPomme(tPlateau plateau, int lesPommesX[], int lesPommesY[], int pommeActuel){
	// génère aléatoirement la position d'une pomme,
	// vérifie que ça correspond à une case vide
	// du plateau puis l'ajoute au plateau et l'affiche
	plateau[lesPommesX[pommeActuel]][lesPommesY[pommeActuel]]=POMME;
	afficher(lesPommesX[pommeActuel], lesPommesY[pommeActuel], POMME);
}

void afficher(int x, int y, char car){
	gotoxy(x, y);
	printf("%c", car);
	gotoxy(1,1);
}

void effacer(int x, int y){
	gotoxy(x, y);
	printf(" ");
	gotoxy(1,1);
}

void dessinerSerpent1(){
	// affiche les anneaux puis la tête
	for(int i=1 ; i<TAILLE ; i++){
		afficher(lesX1[i], lesY1[i], CORPS);
	}
	afficher(lesX1[0], lesY1[0],TETE_S_1);
}

void dessinerSerpent2(){
	// affiche les anneaux puis la tête
	for(int i=1 ; i<TAILLE ; i++){
		afficher(lesX2[i], lesY2[i], CORPS);
	}
	afficher(lesX2[0], lesY2[0],TETE_S_2);
}

void progresser1(char direction, tPlateau plateau, bool * collision1, bool * pomme){
	// efface le dernier élément avant d'actualiser la position de tous les 
	// élémentds du serpent avant de le  redessiner et détecte une
	// collision avec une pomme ou avec une bordure
    direction = ChercheDirectionSure1(direction, plateau);

	effacer(lesX1[TAILLE-1], lesY1[TAILLE-1]);

	for(int i=TAILLE-1 ; i>0 ; i--){
		lesX1[i] = lesX1[i-1];
		lesY1[i] = lesY1[i-1];
	}
	//faire progresser1 la TETE_S_1 dans la nouvelle direction
	switch(direction){
		case HAUT : 
			lesY1[0] = lesY1[0] - 1;
			break;
		case BAS:
			lesY1[0] = lesY1[0] + 1;
			break;
		case DROITE:
			lesX1[0] = lesX1[0] + 1;
			break;
		case GAUCHE:
			lesX1[0] = lesX1[0] - 1;
			break;
	}
	*pomme = false;
	// détection d'une "collision" avec une pomme
	if (plateau[lesX1[0]][lesY1[0]] == POMME){
		*pomme = true;
		// la pomme disparait du plateau
		plateau[lesX1[0]][lesY1[0]] = VIDE;
	}
	// détection d'une collision avec la bordure
	else if (plateau[lesX1[0]][lesY1[0]] == BORDURE){
		*collision1 = true;
	}
	
	if (lesX1[0] < MIN_POS_X) { //si sort à gauche
        lesX1[0] = LARGEUR_PLATEAU;
    } else if (lesX1[0] > LARGEUR_PLATEAU) { //si sort à droite
        lesX1[0] = MIN_POS_X;
    }

    if (lesY1[0] < MIN_POS_Y) { //si sort en haut
        lesY1[0] = HAUTEUR_PLATEAU;
    } else if (lesY1[0] > HAUTEUR_PLATEAU) { //si sort en bas
        lesY1[0] = MIN_POS_Y;
    }

   	dessinerSerpent1();
}

void progresser2(char direction, tPlateau plateau, bool * collision2, bool * pomme){
	// efface le dernier élément avant d'actualiser la position de tous les 
	// élémentds du serpent avant de le  redessiner et détecte une
	// collision avec une pomme ou avec une bordure
    direction = ChercheDirectionSure2(direction, plateau);

	effacer(lesX2[TAILLE-1], lesY2[TAILLE-1]);

	for(int i=TAILLE-1 ; i>0 ; i--){
		lesX2[i] = lesX2[i-1];
		lesY2[i] = lesY2[i-1];
	}
	//faire progresser1 la TETE_S_1 dans la nouvelle direction
	switch(direction){
		case HAUT : 
			lesY2[0] = lesY2[0] - 1;
			break;
		case BAS:
			lesY2[0] = lesY2[0] + 1;
			break;
		case DROITE:
			lesX2[0] = lesX2[0] + 1;
			break;
		case GAUCHE:
			lesX2[0] = lesX2[0] - 1;
			break;
	}
	*pomme = false;
	// détection d'une "collision" avec une pomme
	if (plateau[lesX2[0]][lesY2[0]] == POMME){
		*pomme = true;
		// la pomme disparait du plateau
		plateau[lesX2[0]][lesY2[0]] = VIDE;
	}
	// détection d'une collision avec la bordure
	else if (plateau[lesX2[0]][lesY2[0]] == BORDURE){
		*collision2 = true;
	}
	
	if (lesX2[0] < MIN_POS_X) { //si sort à gauche
        lesX2[0] = LARGEUR_PLATEAU;
    } else if (lesX2[0] > LARGEUR_PLATEAU) { //si sort à droite
        lesX2[0] = MIN_POS_X;
    }

    if (lesY2[0] < MIN_POS_Y) { //si sort en haut
        lesY2[0] = HAUTEUR_PLATEAU;
    } else if (lesY2[0] > HAUTEUR_PLATEAU) { //si sort en bas
        lesY2[0] = MIN_POS_Y;
    }

   	dessinerSerpent2();
}


//procédure qui choisit la direction en fonction des coordonées de la pomme
//et de celle de la TETE_S_1

void choisirDirection1(int lesPommesX[], int lesPommesY[], int pommeActuel, char *direction){
    int chemin;
    chemin = calculDistance1(lesPommesX, lesPommesY, pommeActuel);
    //si chemin sans portail
     switch (chemin)
    {
    case CHEMIN_0:
        //cas 0 : Chemin direct vers la pomme
        // Si la pomme est plus proche sans utiliser de portail, on va vers la pomme.
        if (lesX1[0] < lesPommesX[pommeActuel]) 
        {
            *direction = DROITE; 
        } 
        else if(lesX1[0] > lesPommesX[pommeActuel])
        {
            *direction = GAUCHE; 
        }
        if (lesY1[0] < lesPommesY[pommeActuel]) 
        {
            *direction = BAS; 
        } 
        else if (lesY1[0] > lesPommesY[pommeActuel]) 
        {
            *direction = HAUT; 
        } 

        break;

    case CHEMIN_1:
        if (lesY1[0] > PORTAIL_Y){
            *direction = HAUT;
        }
        else if (lesY1[0] < PORTAIL_Y){
            *direction = BAS;
        }
        else{
        *direction = GAUCHE;
        }
        break;

    case CHEMIN_2:
        if (lesX1[0] > PORTAIL_X){
            *direction = GAUCHE;
        }
        else if(lesX1[0] < PORTAIL_X){
            *direction = DROITE;
        }
        else{
            *direction = HAUT;
        }
        break;

    case CHEMIN_3:
        if (lesY1[0] > PORTAIL_Y){
            *direction = HAUT;
        }
        else if (lesY1[0] < PORTAIL_Y){
            *direction = BAS;
        }
        else{
        *direction = DROITE;
        }
        break;

    case CHEMIN_4:
        if (lesX1[0] > PORTAIL_X){
            *direction = GAUCHE;
        }
        else if(lesX1[0] < PORTAIL_X){
            *direction = DROITE;
        }
        else{
            *direction = BAS;
        }
        break;
    }
}

void choisirDirection2(int lesPommesX[], int lesPommesY[], int pommeActuel, char *direction){
    int chemin;
    chemin = calculDistance2(lesPommesX, lesPommesY, pommeActuel);
    //si chemin sans portail
     switch (chemin)
    {
    case CHEMIN_0:
        //cas 0 : Chemin direct vers la pomme
        // Si la pomme est plus proche sans utiliser de portail, on va vers la pomme.
        if ((lesPommesY[pommeActuel] - lesY2[0]) < 0) 
        {
            *direction = HAUT; 
        } 
        else if ((lesPommesY[pommeActuel] - lesY2[0]) > 0) 
        {
            *direction = BAS; 
        } 
        else if ((lesPommesX[pommeActuel] - lesX2[0]) < 0) 
        {
            *direction = GAUCHE; 
        } 
        else 
        {
            *direction = DROITE; 
        }
        break;

    case CHEMIN_2:
        if (lesX2[0] > PORTAIL_X){
            *direction = GAUCHE;
        }
        else if(lesX2[0] < PORTAIL_X){
            *direction = DROITE;
        }
        else{
            *direction = HAUT;
        }
        break;

    case CHEMIN_4:
        if (lesX2[0] > PORTAIL_X){
            *direction = GAUCHE;
        }
        else if(lesX2[0] < PORTAIL_X){
            *direction = DROITE;
        }
        else{
            *direction = BAS;
        }
        break;

    case CHEMIN_1:
        if (lesY2[0] > PORTAIL_Y){
            *direction = HAUT;
        }
        else if (lesY2[0] < PORTAIL_Y){
            *direction = BAS;
        }
        else{
        *direction = GAUCHE;
        }
        break;

    case CHEMIN_3:
        if (lesY2[0] > PORTAIL_Y){
            *direction = HAUT;
        }
        else if (lesY2[0] < PORTAIL_Y){
            *direction = BAS;
        }
        else{
        *direction = DROITE;
        }
        break;
    }
}



//fonction qui calcul la distance la plus courte entre la TETE_S_1 et la
//pomme. elle renvoit l'indice du chemin a prendre
int calculDistance1(int lesPommesX[], int lesPommesY[], int pommeActuel){
    //disttance portail
    int distancePG, distancePD, distancePB, distancePH;
    //distance portail et la pomme
    int distPGAPomme, distPDAPomme, distPBAPomme, distPHAPomme;
    //distance total
    int distance[NOMBRE_DISTANCE_POSSIBLE];
    //minimum et indice minimum
    int min,imin;

    //distance tête du serpent -> portail bas
    distancePB = abs(lesX1[0] - PORTAIL_X) + abs(lesY1[0] - HAUTEUR_PLATEAU);
    //distance tête du serpent -> portail droit
    distancePD = abs(lesX1[0] - LARGEUR_PLATEAU) + abs(lesY1[0] - PORTAIL_Y);
    //distance tête du serpent -> portail gauche
    distancePG = abs(lesX1[0] - MIN_POS_X) + abs(lesY1[0] - PORTAIL_Y);
    //distance tête du serpent -> portail haut
    distancePH = abs(lesX1[0] - PORTAIL_X) + abs(lesY1[0] - MIN_POS_Y);

    //distance entre chaque portail et la pomme
    distPGAPomme = abs(lesPommesX[pommeActuel] - MIN_POS_X) + abs(lesPommesY[pommeActuel] - PORTAIL_Y);
    distPDAPomme = abs(lesPommesX[pommeActuel] - LARGEUR_PLATEAU) + abs(lesPommesY[pommeActuel] - PORTAIL_Y);
    distPBAPomme = abs(lesPommesX[pommeActuel] - PORTAIL_X) + abs(lesPommesY[pommeActuel] - HAUTEUR_PLATEAU);
    distPHAPomme = abs(lesPommesX[pommeActuel] - PORTAIL_X) + abs(lesPommesY[pommeActuel] - MIN_POS_Y);

    //calcul des distances totales pour chaque chemin
    distance[CHEMIN_0] = abs(lesPommesX[pommeActuel] - lesX1[0]) + abs(lesPommesY[pommeActuel] - lesY1[0]); //distance directe
    distance[CHEMIN_1] = distancePG + distPDAPomme;  //distance via portail gauche
    distance[CHEMIN_2] = distancePH + distPBAPomme;  //distance via portail haut
    distance[CHEMIN_3] = distancePD + distPGAPomme;  //distance via portail droit
    distance[CHEMIN_4] = distancePB + distPHAPomme;  //distance via portail bas
  

    min = distance[CHEMIN_0];
    imin = CHEMIN_0;
    //ACHANGER ET METTRE 1
    gotoxy(1, 41);

    //affichage pour débuguer ne pas regarder
    for(int i = 0; i < NOMBRE_DISTANCE_POSSIBLE; i++){
        printf("chemin = %d en %d ",i, distance[i]);
        if (distance[i] < min){
            min = distance[i];
            imin = i;
        }
    }
    printf("chemin a prendre %d", imin);
    return imin;
}


//fonction qui calcul la distance la plus courte entre la TETE_S_1 et la
//pomme. elle renvoit l'indice du chemin a prendre
int calculDistance2(int lesPommesX[], int lesPommesY[], int pommeActuel){
    //disttance portail
    int distancePG, distancePD, distancePB, distancePH;
    //distance portail et la pomme
    int distPGAPomme, distPDAPomme, distPBAPomme, distPHAPomme;
    //distance total
    int distance[NOMBRE_DISTANCE_POSSIBLE];
    //minimum et indice minimum
    int min,imin;

    //distance tête du serpent -> portail bas
    distancePB = abs(lesX2[0] - PORTAIL_X) + abs(lesY2[0] - HAUTEUR_PLATEAU);
    //distance tête du serpent -> portail droit
    distancePD = abs(lesX2[0] - LARGEUR_PLATEAU) + abs(lesY2[0] - PORTAIL_Y);
    //distance tête du serpent -> portail gauche
    distancePG = abs(lesX2[0] - MIN_POS_X) + abs(lesY2[0] - PORTAIL_Y);
    //distance tête du serpent -> portail haut
    distancePH = abs(lesX2[0] - PORTAIL_X) + abs(lesY2[0] - MIN_POS_Y);

    //distance entre chaque portail et la pomme
    distPGAPomme = abs(lesPommesX[pommeActuel] - MIN_POS_X) + abs(lesPommesY[pommeActuel] - PORTAIL_Y);
    distPDAPomme = abs(lesPommesX[pommeActuel] - LARGEUR_PLATEAU) + abs(lesPommesY[pommeActuel] - PORTAIL_Y);
    distPBAPomme = abs(lesPommesX[pommeActuel] - PORTAIL_X) + abs(lesPommesY[pommeActuel] - HAUTEUR_PLATEAU);
    distPHAPomme = abs(lesPommesX[pommeActuel] - PORTAIL_X) + abs(lesPommesY[pommeActuel] - MIN_POS_Y);

    //calcul des distances totales pour chaque chemin
    distance[CHEMIN_0] = abs(lesPommesX[pommeActuel] - lesX2[0]) + abs(lesPommesY[pommeActuel] - lesY2[0]); //distance directe
    distance[CHEMIN_1] = distancePG + distPDAPomme;  //distance via portail gauche
    distance[CHEMIN_2] = distancePH + distPBAPomme;  //distance via portail haut
    distance[CHEMIN_3] = distancePD + distPGAPomme;  //distance via portail droit
    distance[CHEMIN_4] = distancePB + distPHAPomme;  //distance via portail bas
  

    min = distance[CHEMIN_0];
    imin = CHEMIN_0;
    //ACHANGER ET METTRE 1
    gotoxy(1, 42);

    //affichage pour débuguer ne pas regarder
    for(int i = 0; i < NOMBRE_DISTANCE_POSSIBLE; i++){
        printf("chemin = %d en %d ",i, distance[i]);
        if (distance[i] < min){
            min = distance[i];
            imin = i;
        }
    }
    printf("chemin a prendre %d", imin);
    return imin;
}



bool estSurPave1(tPlateau plateau, int x, int y) { //verifie si une position est occupée par un pave
    return plateau[x][y] == BORDURE;
}



bool estSurPave2(tPlateau plateau, int x, int y) { //verifie si une position est occupée par un pave
    return plateau[x][y] == BORDURE;
}


char ChercheDirectionSure1(char directionActuelle, tPlateau plateau) { //cherche une direction sure pour eviter les collisions
    if (lesY1[0] > lesY1[1] && directionActuelle == HAUT) {
        if (VerifieDirectionSure1(DROITE, plateau))
        { 
            return DROITE;
        }
       if (VerifieDirectionSure1(GAUCHE, plateau))
       {
            return GAUCHE;
       }
    }
    
    //haut et bas
    if (lesY1[0] < lesY1[1] && directionActuelle == BAS) {
        if (VerifieDirectionSure1(DROITE, plateau)) 
        {
            return DROITE;
        }
        if (VerifieDirectionSure1(GAUCHE, plateau))
        {
            return GAUCHE;
        }
    }
    
    //gauche et droite
    if (lesX1[0] < lesX1[1] && directionActuelle == DROITE) {
        if (VerifieDirectionSure1(HAUT, plateau))
        {
            return HAUT;
        } 
        if (VerifieDirectionSure1(BAS, plateau))
        {
            return BAS;
        }
    }
    
    //droite et gauche
    if (lesX1[0] > lesX1[1] && directionActuelle == GAUCHE) {
        if (VerifieDirectionSure1(HAUT, plateau)) 
        {
            return HAUT;
        }
        if (VerifieDirectionSure1(BAS, plateau)) 
        {
            return BAS;
        }
    }

    if (VerifieDirectionSure1(directionActuelle, plateau)) //verifie si la direction actuelle est sure
    { 
        return directionActuelle; //si oui on la garde
    }
    else if (VerifieDirectionSure1(GAUCHE, plateau)) //regarde si gauche est sure
    { 
        return GAUCHE; 
    }
    else if (VerifieDirectionSure1(DROITE, plateau))  //regarde si droite est sure
    {
        return DROITE; 
    }
    else if (VerifieDirectionSure1(HAUT, plateau)) //regarde si haut est sur
    {
        return HAUT; 
    }
    else if (VerifieDirectionSure1(BAS, plateau))//regarde si bas est sure
    { 
        return BAS;
    }
    return directionActuelle; //sinon renvoie la direction actuel
}


char ChercheDirectionSure2(char directionActuelle, tPlateau plateau) { //cherche une direction sure pour eviter les collisions
    if (lesY2[0] > lesY2[1] && directionActuelle == HAUT) {
        if (VerifieDirectionSure2(DROITE, plateau))
        { 
            return DROITE;
        }
       if (VerifieDirectionSure2(GAUCHE, plateau))
       {
            return GAUCHE;
       }
    }
    
    //haut et bas
    if (lesY2[0] < lesY2[1] && directionActuelle == BAS) {
        if (VerifieDirectionSure2(DROITE, plateau)) 
        {
                return DROITE;
        }
        if (VerifieDirectionSure2(GAUCHE, plateau))
        {
                return GAUCHE;
        }
    }
    
    //gauche et droite
    if (lesX2[0] < lesX2[1] && directionActuelle == DROITE) {
        if (VerifieDirectionSure2(HAUT, plateau))
        {
                return HAUT;
        } 
        if (VerifieDirectionSure2(BAS, plateau))
        {
                return BAS;
        }
    }
    
    //droite et gauche
    if (lesX2[0] > lesX2[1] && directionActuelle == GAUCHE) {
        if (VerifieDirectionSure2(HAUT, plateau)) 
        {
                return HAUT;
        }
        if (VerifieDirectionSure2(BAS, plateau)) 
        {
                return BAS;
        }
    }
        
    if (VerifieDirectionSure2(directionActuelle, plateau)) //verifie si la direction actuelle est sure
    { 
        return directionActuelle; //si oui on la garde
    }
    else if (VerifieDirectionSure2(HAUT, plateau)) //regarde si haut est sur
    {
        return HAUT; 
    }
    else if (VerifieDirectionSure2(BAS, plateau))//regarde si bas est sure
    { 
        return BAS;
    }
    else if (VerifieDirectionSure2(GAUCHE, plateau)) //regarde si gauche est sure
    { 
        return GAUCHE; 
    }
    else if (VerifieDirectionSure2(DROITE, plateau))  //regarde si droite est sure
    {
        return DROITE; 
    }
    return directionActuelle; //sinon renvoie la direction actuel
}



bool VerifieDirectionSure1(char direction, tPlateau plateau) {
    int x = lesX1[0];
    int y = lesY1[0];
    
    switch (direction) {
        case HAUT: 
            y--; 
            break;  
        case BAS: 
            y++; 
            break;                                                                   
        case GAUCHE: 
            x--; 
            break;                                                                
        case DROITE: 
            x++; 
            break;                                                                
    }

    // Gérer le passage d'un côté à l'autre du plateau
    x = (x + LARGEUR_PLATEAU - 1) % LARGEUR_PLATEAU + 1;
    y = (y + HAUTEUR_PLATEAU - 1) % HAUTEUR_PLATEAU + 1;

    // Vérifier les collisions avec:
    //1.bordure
    //2.corps du serpent 1
    //3.corps du serpent 2
    //4.pave
    bool directionSure = 
        plateau[x][y] != BORDURE &&
        !estSurPave1(plateau, x, y);

    // Vérifier la collision avec le corps du serpent 1
    for (int i = 1; i < TAILLE; i++) {
        if (lesX1[i] == x && lesY1[i] == y) {
            directionSure = false;
            break;
        }
    }

    // Vérifier la collision avec le corps du serpent 2
    for (int i = 0; i < TAILLE; i++) {
        if (lesX2[i] == x && lesY2[i] == y) {
            directionSure = false;
            break;
        }
    }

    return directionSure;
}

// Faire de même pour VerifieDirectionSure2

bool VerifieDirectionSure2(char direction, tPlateau plateau) {
    int x = lesX2[0];
    int y = lesY2[0];
    
    switch (direction) {
        case HAUT: 
            y--; 
            break;  
        case BAS: 
            y++; 
            break;                                                                   
        case GAUCHE: 
            x--; 
            break;                                                                
        case DROITE: 
            x++; 
            break;                                                                
    }

    // Gérer le passage d'un côté à l'autre du plateau
    x = (x + LARGEUR_PLATEAU - 1) % LARGEUR_PLATEAU + 1;
    y = (y + HAUTEUR_PLATEAU - 1) % HAUTEUR_PLATEAU + 1;

    // Vérifier les collisions avec:
    //1.bordure
    //2.corps du serpent 1
    //3.corps du serpent 2
    //4.pave
    bool directionSure = 
        plateau[x][y] != BORDURE &&
        !estSurPave2(plateau, x, y);

    // Vérifier la collision avec le corps du serpent 1
    for (int i = 0; i < TAILLE; i++) {
        if (lesX1[i] == x && lesY1[i] == y) {
            directionSure = false;
            break;
        }
    }

    // Vérifier la collision avec le corps du serpent 2
    for (int i = 1; i < TAILLE; i++) {
        if (lesX2[i] == x && lesY2[i] == y) {
            directionSure = false;
            break;
        }
    }

    return directionSure;
}

/************************************************/
/*		 	   FONCTIONS UTILITAIRES  			*/
/************************************************/
void gotoxy(int x, int y) { 
    printf("\033[%d;%df", y, x);
}

int kbhit(){
	// la fonction retourne :
	// 1 si un caractere est present
	// 0 si pas de caractere présent
	int unCaractere=0;
	struct termios oldt, newt;
	int ch;
	int oldf;

	// mettre le terminal en mode non bloquant
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
	ch = getchar();

	// restaurer le mode du terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
	if(ch != EOF){
		ungetc(ch, stdin);
		unCaractere=1;
	} 
	return unCaractere;
}

// Fonction pour désactiver l'echo
void disable_echo() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Désactiver le flag ECHO
    tty.c_lflag &= ~ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour réactiver l'echo
void enable_echo() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Réactiver le flag ECHO
    tty.c_lflag |= ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}
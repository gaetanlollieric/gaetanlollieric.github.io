#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <termios.h> 
#include <string.h> 
#include <fcntl.h> 
#include <stdbool.h>
#include <time.h>

#define TETE 'O' 
#define CORPS 'X' 
#define VIDE ' ' 
#define STOP 'a' 
#define TAILLE_DEBUT 10 //longueur du serpent au début = à N
#define MAX_TAILLE 39 //taille max
#define DROITE 'd'
#define GAUCHE 'q'
#define HAUT 'z'
#define BAS 's'
#define INIT_DIRECTION 'd'
#define MIN_POS_Y 1
#define MIN_POS_X 1
#define TIMER 200000
#define POSITION_DEPART_Y 20 //y pour hauteur
#define POSITION_DEPART_X 40   //x pour largeur
#define NB_PAVE 4
#define TAILLE_PAVE 5
#define LARGEUR 80
#define HAUTEUR 40
#define OBSTACLE '#'
#define POMME '6'
#define PLACEMENT_PORTAIL 2 //a 2 pour le milieu attention si cette valeur passe a 0 alors il fuadra penser a la division par 0 ;)
#define NOMBRE_MAX_POMME_MANGE 10
#define VITESS_AUGMENTE 10000


void enableEcho();
void disableEcho();
void gotoXY(int x, int y);
void afficher(int x, int y, char c);
void effacer(int x, int y);
void dessinerSerpent(int lesX[], int lesY[]);
void progresser(int lesX[], int lesY[], char direction, bool *collision, bool *mange);
void ajouterPomme();
void initPlateau();
void dessinerPlateau();
int kbhit();


typedef char grille[LARGEUR][HAUTEUR];
grille plateau;


int tailleSerpent = TAILLE_DEBUT; //defini ici pour quelle soit vu par toutes les procédure / fonction

int main() {
    //creation des tableaux regroupant les coordonees des éléments du serpent
    int lesX[TAILLE_DEBUT + NOMBRE_MAX_POMME_MANGE], lesY[TAILLE_DEBUT + NOMBRE_MAX_POMME_MANGE];  
    //on initialise le tableau au maximun de sa taille c'est a dire la taille de début + le nombre max de pomme


    char touche, direction;
    direction = INIT_DIRECTION;
    touche = 0; // 0 pour être différent de a et rentrer dans la boucle tant que

    int i; //i pour la boucle for des initialisations de coordonées
    
    bool collision;
    collision = false;

    bool mange;
    mange = false;

    int vitesse = TIMER;
    int nombresPommesManges = 0;


    //initialisation de la pos de départ
    for (i = 0; i < TAILLE_DEBUT; i++) {
        lesX[i] = POSITION_DEPART_X - i; //le corps s etend a gauche
        lesY[i] = POSITION_DEPART_Y;
    }

    system("clear");
    disableEcho();
    initPlateau();
    ajouterPomme();
    dessinerPlateau();
    

    //boucle principale
    while ((touche != STOP) && (!collision) && (nombresPommesManges < NOMBRE_MAX_POMME_MANGE)) {
        //affiche le serpent à la nouvelle position
        dessinerSerpent(lesX, lesY);

        //efface l'ancienne position de la queue du serpent
        effacer(lesX[tailleSerpent - 1], lesY[tailleSerpent - 1]);

        //determine la nouvelle position
        progresser(lesX, lesY, direction, &collision, &mange);

        //verifie si une pomme a été mangé
        if (mange){
            ajouterPomme();
            dessinerPlateau();
            nombresPommesManges ++;
            vitesse -= VITESS_AUGMENTE;
            mange = false;
            //efface l'anclienne pomme du plateau
            plateau[lesX[0]-1][lesY[0]-1] = VIDE; //pour éviter le décalage
            tailleSerpent ++;
        }

        // pause pour le déplacement
        usleep(vitesse);


        if (kbhit()==1) {
            touche = getchar();

            if (touche == STOP){ //pour afficher proprement la fin
                system("clear");
            }
            //empecher le demi tour
            if ((direction != DROITE && touche == GAUCHE)
            || (direction != GAUCHE && touche == DROITE)
            || (direction != HAUT && touche == BAS)
            || (direction != BAS && touche == HAUT)) {
                direction = touche;
            }
        }

    }
    //system("clear");
    if (nombresPommesManges == NOMBRE_MAX_POMME_MANGE){ //regarde si la partie est gagné ou non en fonction du nombre de pomme mangé
        printf("C'est gagné !");
    } else if (touche == STOP){
        printf("Partie arreté");
    } else {
        printf("Perdu");
    }
    enableEcho();
    return EXIT_SUCCESS;
}

void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//fonction pour afficher un caractère à la position (x, y)
void afficher(int x, int y, char c) {
    gotoXY(x, y);
    printf("%c", c);
}

//fonction qui efface un caractere aux positions (x,y) fait appel a affiche pour eviter la redondance
void effacer(int x, int y) {
    afficher(x, y, VIDE);
}

//fonction pour dessiner chaque élément du serpent (corps et tete)
void dessinerSerpent(int lesX[], int lesY[]) {
    int i;
    for (i = 0; i < tailleSerpent; i++) {
        if (i == 0) {
            afficher(lesX[i], lesY[i], TETE); //tete du serpent
        } else {
            afficher(lesX[i], lesY[i], CORPS); //corps du serpent
        }
    }
    fflush(stdout);
}

void progresser(int lesX[], int lesY[], char direction, bool *collision, bool *mange) {
    int i;

    // pour faire avancer le corps du serpent
    for (i = tailleSerpent - 1; i > 0; i--) {
        lesX[i] = lesX[i - 1];
        lesY[i] = lesY[i - 1];
    }

    //mettre a jour la position de la tete si changement de direction
    switch (direction) {
        case HAUT:
            lesY[0] -= 1;
            break;
        case BAS:
            lesY[0] += 1;
            break;
        case GAUCHE:
            lesX[0] -= 1;
            break;
        case DROITE:
            lesX[0] += 1;
            break;
    }

    //gere les portails
    if (lesX[0] < MIN_POS_X) { //si sort à gauche
        lesX[0] = LARGEUR;
    } else if (lesX[0] > LARGEUR) { //si sort à droite
        lesX[0] = MIN_POS_X;
    }

    if (lesY[0] < MIN_POS_Y) { //si sort en haut
        lesY[0] = HAUTEUR;
    } else if (lesY[0] > HAUTEUR) { //si sort en bas
        lesY[0] = MIN_POS_Y;
    }

    //verifie la collision avec le corps
    for (i = 1; i < tailleSerpent; i++) {//commence a un pour ne pas comparer la tete avec la tete
        if (lesX[0] == lesX[i] && lesY[0] == lesY[i]) {
            *collision = true;
        }
    }

    //verifie la collision avec les obstacles ou les ppommes
    if (plateau[lesX[0]-1][lesY[0]-1] == OBSTACLE) { //-1 au coordonée de la tete pour eviter un déclage
        *collision = true;
    } else if (plateau[lesX[0]-1][lesY[0]-1] == POMME) {//-1 au coordonée de la tete pour eviter un déclage
        *mange = true;
    }
}


void initPlateau() {
    int l, h; //l = largeur h = hauteur
    int coordoneesX, coordoneesY; 
    //remplit le tableau avec du VIDE
    for (h = 0; h < HAUTEUR; h++) {
        for (l = 0; l < LARGEUR; l++) {
            plateau[l][h] = VIDE;
        }
    }

    //placer les bordures avec des portails
    for (l = 0; l < LARGEUR; l++) {
        if (l == LARGEUR / PLACEMENT_PORTAIL) {
            plateau[l][0] = VIDE; //portail haut
            plateau[l][HAUTEUR - 1] = VIDE; //portail bas
        } else {
            plateau[l][0] = OBSTACLE; //bord haut
            plateau[l][HAUTEUR - 1] = OBSTACLE; //bord bas
        }
    }

    for (h = 0; h < HAUTEUR; h++) {
        if (h == HAUTEUR / PLACEMENT_PORTAIL) {
            plateau[0][h] = VIDE; //portail gauche
            plateau[LARGEUR - 1][h] = VIDE; //portail droit
        } else {
            plateau[0][h] = OBSTACLE; //bord gauche
            plateau[LARGEUR - 1][h] = OBSTACLE; //bord droit
        }
    }

    srand(time(NULL));

    //placage des pavés
    for (int p = 0; p < NB_PAVE; p++) {
        do {
            coordoneesX = 1 + rand() % (LARGEUR - TAILLE_PAVE - 2); //minimum 1 pour éviter bordures
            coordoneesY = 1 + rand() % (HAUTEUR - TAILLE_PAVE - 2); //minimum 1 pour éviter bordures
        } while (coordoneesX < 1 || coordoneesY < 1 || 
                coordoneesX > LARGEUR - TAILLE_PAVE - 1 || coordoneesY > HAUTEUR - TAILLE_PAVE - 1); //regarde si les pavés ne colle pas comme prévu

        for (l = 0; l < TAILLE_PAVE; l++) {
            for (h = 0; h < TAILLE_PAVE; h++) {
                plateau[coordoneesX + l][coordoneesY + h] = OBSTACLE;
            }
        }
    }

}

void dessinerPlateau() {
    int h, l;
    for (h = 0; h < HAUTEUR; h++) { //commence à 0 pour inclure toutes les lignes
        for (l = 0; l < LARGEUR; l++) { // commence à 0 pour inclure toutes les colonnes
            afficher(l + 1, h + 1, plateau[l][h]); //affiche le caractere du plateau
        }
    }
    fflush(stdout);
}

void ajouterPomme(){
    int XPomme;
    int YPomme;
    srand(time(NULL));
    do{
        XPomme = rand() % LARGEUR; //défini les coordonées de la pomme
        YPomme = rand() % HAUTEUR;
    } while (plateau[XPomme][YPomme] != VIDE);
    plateau[XPomme][YPomme] = POMME; //place la pomme au cordonée aléatoire
}


void disableEcho() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Desactiver le flag ECHO
    tty.c_lflag &= ~ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

void enableEcho() {
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Reactiver le flag ECHO
    tty.c_lflag |= ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

int kbhit() { 
    int unCaractere = 0; 
    struct termios oldt, newt; 
    int ch; 
    int oldf; 

    tcgetattr(STDIN_FILENO, &oldt); 
    newt = oldt; 
    newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); 
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); 
    ch = getchar(); 

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    fcntl(STDIN_FILENO, F_SETFL, oldf); 
    if (ch != EOF) { 
        ungetc(ch, stdin); 
        unCaractere = 1; 
    }  
    return unCaractere; 
}
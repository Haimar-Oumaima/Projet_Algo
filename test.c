#include <SDL.h>
//#include <SDL2/SDL_image>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <time.h>

SDL_bool estDansIntervalle(SDL_Event E, SDL_Rect rect)
{
    int x= E.button.x;
    int y= E.button.y;
    if(x>rect.x && x<rect.x+rect.w && y>rect.y && y<rect.y+rect.h)
    {
        return SDL_TRUE;
    }
    else return SDL_FALSE;
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;  
}

//SDL_bool est_Dans_Intervalle();
//void bouton_Selectionne(SDL_Renderer* ,SDL_Rect);
//void bouton_Non_Selectionne(SDL_Renderer* ,SDL_Rect);

typedef enum ORIENTATION
{
	HORIZONTALE,
	VERTICALE,
	NORMALE
} ORIENTATION;

typedef enum EXTREMITE_COMPATIBLE
{
	GAUCHE,
	DROITE,
	LES_DEUX,
	HAUT,
	BAS,
	AUCUN_DOMINO,
} EXTREMITE_COMPATIBLE;

typedef struct DOMINO
{
	int valeur1; // Valeur Bas ou Gauche du domino
	int valeur2; // Valeur Haut ou Droite du domino
	ORIENTATION orientation;
} DOMINO;

int est_double(DOMINO domino);

typedef struct
{
    int x, y;
} POINT;


typedef struct COORDONNEES
{
	int ligne;
	int colonne;
	POINT coin;
} COORDONNEES;

struct domino {
   int haut;
   int bas;
};


typedef struct Dominos
{
	int nombreGauche, nombreDroite;
}DOMINOS;


float alea_float()
{
	static int init_alea = 1;
	if (init_alea) 
		srand(time(NULL));

	init_alea = 0;
	return (float)rand() / (float)RAND_MAX;
}

// Renvoie un int dans l'intervalle [0..N[
// soit N valeurs différentes de 0 à N-1
int alea_int(int N)
{ 
	return (int)(N*alea_float());
}

DOMINOS pioche[28];

//créer un dominos avec des nombres par hasard
DOMINOS creer_dominos()
{
	DOMINOS this;
	this.nombreGauche = alea_int(7);
	this.nombreDroite = alea_int(7);

	return this;
}

void initialiser_pioche()
{
	int i;
	for(i=0;i<28;i++)
	{
		pioche[i] = creer_dominos();
	}
}


int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Window *w_aide = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Renderer *renderer2 = NULL;

    SDL_Texture *t_arriere_plan = NULL;
    SDL_Texture *t_logo = NULL;
    SDL_Texture *t_pioche = NULL;
    SDL_Texture *t_score = NULL;
    SDL_Texture *t_joueur = NULL;

   // SDL_Surface *ecran = NULL;
    SDL_Surface *s_logo = NULL;
    SDL_Surface *s_arriere_plan = NULL; 
    SDL_Surface *s_pioche = NULL;
    SDL_Surface *s_score = NULL;
    SDL_Surface *s_joueur = NULL;

    size_t i,j;

    int statut = EXIT_FAILURE;

    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color bleu = {0, 0, 255, 255};
    SDL_Color marron = {88, 41, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    //s_arriere_plan= SDL_LoadBMP("/dominosLogo.bmp");
    /* Initialisation, création de la fenêtre et du renderer. */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    window = SDL_CreateWindow("Dominos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 650, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

   // ecran = SDL_SetVideoMode(800, 650, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    s_arriere_plan= SDL_LoadBMP("arriere_plan.bmp");
    if(NULL == s_arriere_plan)
    {
       fprintf(stderr, "Erreur SDL_LoadBMP: %s", SDL_GetError());
       goto Quit;
    }

    s_logo= SDL_LoadBMP("LOGO.bmp");
    if(NULL == s_logo)
    {
       fprintf(stderr, "Erreur SDL_LoadBMP: %s", SDL_GetError());
       goto Quit;
    }
    s_pioche= SDL_LoadBMP("piochee.bmp");
    if(NULL == s_pioche)
    {
       fprintf(stderr, "Erreur SDL_LoadBMP: %s", SDL_GetError());
       goto Quit;
    }

     s_score= SDL_LoadBMP("score.bmp");
    if(NULL == s_score)
    {
       fprintf(stderr, "Erreur SDL_LoadBMP: %s", SDL_GetError());
       goto Quit;
    }

    s_joueur= SDL_LoadBMP("joueur.bmp");
    if(NULL == s_joueur)
    {
       fprintf(stderr, "Erreur SDL_LoadBMP: %s", SDL_GetError());
       goto Quit;
    }



    t_arriere_plan= SDL_CreateTextureFromSurface(renderer, s_arriere_plan);
    if(NULL == t_arriere_plan)
    {
         fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
         goto Quit;
    }

    t_logo= SDL_CreateTextureFromSurface(renderer, s_logo);
    if(NULL == t_logo)
    {
         fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
         goto Quit;
    }

    t_pioche= SDL_CreateTextureFromSurface(renderer, s_pioche);
    if(NULL == t_pioche)
    {
         fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
         goto Quit;
    }

    t_score= SDL_CreateTextureFromSurface(renderer, s_score);
    if(NULL == t_score)
    {
         fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
         goto Quit;
    }

    t_joueur= SDL_CreateTextureFromSurface(renderer, s_joueur);
    if(NULL == t_joueur)
    {
         fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
         goto Quit;
    }


    SDL_FreeSurface(s_arriere_plan); /* On libère la surface, on n’en a plus besoin */
    SDL_FreeSurface(s_logo); 
    SDL_FreeSurface(s_pioche); 
    SDL_FreeSurface(s_score); 
    SDL_FreeSurface(s_joueur); 

    SDL_Rect rect_arriere_plan; // la declaration des variables de type rect pour pouvoir les dessiner
    SDL_Rect rect_logo;
    SDL_Rect rect_pioche;
    SDL_Rect rect_score;
    SDL_Rect rect_joueur;

    struct domino rect_joueurr;

    SDL_QueryTexture(t_arriere_plan,NULL,NULL,&rect_arriere_plan.w,&rect_arriere_plan.h);
    SDL_QueryTexture(t_logo,NULL,NULL,&rect_logo.w,&rect_logo.h);
    SDL_QueryTexture(t_pioche,NULL,NULL,&rect_pioche.w,&rect_pioche.h);
    SDL_QueryTexture(t_score,NULL,NULL,&rect_score.w,&rect_score.h);
    SDL_QueryTexture(t_score,NULL,NULL,&rect_joueur.w,&rect_joueur.h);
  

    rect_arriere_plan.x= (800-rect_arriere_plan.w)/2;
    rect_arriere_plan.y= 0;

    rect_logo.x= (800-rect_logo.w)/2;
    rect_logo.y= 3;

    rect_pioche.x= 635;
    rect_pioche.y= 560;

    rect_score.x= 10;
    rect_score.y= 5;

    rect_joueur.x= 30;
    rect_joueur.y= 550;

    /* C’est à partir de maintenant que ça se passe. */

    SDL_RenderCopy(renderer,t_arriere_plan,NULL,&rect_arriere_plan); // copier sur la fenetre
    SDL_RenderCopy(renderer,t_logo,NULL,&rect_logo);
    SDL_RenderCopy(renderer,t_pioche,NULL,&rect_pioche);
    SDL_RenderCopy(renderer,t_score,NULL,&rect_score);
    SDL_RenderCopy(renderer,t_joueur,NULL,&rect_joueur);


    if(0 != SDL_SetRenderDrawColor(renderer, marron.r, marron.g, marron.b, marron.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

//setWindowColor(renderer, marron); //changer la couleur de la fenetre
SDL_RenderPresent(renderer);

SDL_Rect plateau = {160,60, 470, 470};
SDL_Rect joueur1 = {160,550, 470, 80};
//SDL_Rect domino = {165,554, 50, 72};
//SDL_Rect dominos = {165,554, 50, 72};
//SDL_Rect joueur2 = {140,105, 400, 80};
//SDL_Rect joueur3 = {50,195, 80, 400};
//SDL_Rect joueur4 = {550,195, 80, 400};

setWindowColor(renderer, blanc); //changer la couleur de la fenetre pour dessiner
SDL_RenderPresent(renderer);

SDL_RenderDrawRect(renderer, &plateau); 
SDL_RenderDrawRect(renderer, &joueur1); 

/*for (i=169;i<600;i+=50)
{
    for (j=69;j<500;j+=74)
    {
        SDL_Rect dominos = {i,j, 45, 72};
        SDL_RenderFillRect(renderer, &dominos); 
    }
}*/

for (i=195;i<550;i+=59){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//couleur rouge de point
    SDL_RenderDrawLine(renderer, i, 590, i+45, 590);
}
SDL_RenderPresent(renderer);

void affiche_image(char *nom, POINT coin)
{
    //int k=195;
     SDL_Rect domino = {coin.x,554, 45, 72};
    SDL_Surface *simg = SDL_LoadBMP(nom);
    SDL_Texture *img= SDL_CreateTextureFromSurface(renderer, simg);
   // SDL_Rect position_img;
   // position_img.x = coin.x;
   // position_img.y = 40-coin.y;
//    SDL_BlitSurface(img, NULL, ecran, &position_img);
    SDL_RenderCopy(renderer,img,NULL,&domino);
    //coin.x+=59;
    //SDL_RenderPresent(renderer);
}


initialiser_pioche();

	for(i=0;i<8;i++)
	{
		printf("%d",pioche[i].nombreGauche);
		printf("%d\n",pioche[i].nombreDroite);
	}

int x;
int y;

POINT coin;
char nom_image[100];
coin.x =195;
	for(i=0;i<7;i++)
	{
		x=pioche[i].nombreGauche;
        y=pioche[i].nombreDroite;
        
      
    sprintf(nom_image, "./%d%d.bmp", pioche[i].nombreGauche,pioche[i].nombreDroite);

    
  //  coin.y=554;

    affiche_image(nom_image, coin);
    coin.x+=59;
    SDL_RenderPresent(renderer);
     //coin.x+=195;
     //coin.y+=554;
	}


/*
void affiche_domino(DOMINO domino_a_afficher, POINT coin, EXTREMITE_COMPATIBLE direction)
{
    char nom_image[100];

    if (domino_a_afficher.orientation == HORIZONTALE)
    {
        if (domino_a_afficher.valeur1 > domino_a_afficher.valeur2)
        {
            sprintf(nom_image, "./img_dominos/bmp_horizontal/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
        }
        else if (est_double(domino_a_afficher) && direction == DROITE)
        {
            sprintf(nom_image, "./img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
            coin.y += 20;
        }
        else if (est_double(domino_a_afficher) && direction == GAUCHE)
        {
            sprintf(nom_image, "./img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
            coin.y += 20;
            coin.x += 35;
        }
        else
            sprintf(nom_image, "./img_dominos/bmp_horizontal_inverse/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    }
    if (domino_a_afficher.orientation == VERTICALE)
    {
        if (domino_a_afficher.valeur1 > domino_a_afficher.valeur2)
        {
            sprintf(nom_image, "./img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur2, domino_a_afficher.valeur1);
        }
        else if (est_double(domino_a_afficher))
        {
            sprintf(nom_image, "./img_dominos/bmp_horizontal/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
            coin.x -= 40;
        }
        else
            sprintf(nom_image, "./img_dominos/bmp_vertical_inverse/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    }

    affiche_image(nom_image, coin);
    printf("///////Le domino a ete affiche avec SUCCES///////\n");
}
*/


//SDL_Delay(9398);

/*  setWindowColor(renderer, marron); //changer la couleur de la fenetre
   SDL_RenderPresent(renderer);
   SDL_Delay(2000);*/
/*
SDL_bool programme_lance = SDL_TRUE;

while(programme_lance)
{
    SDL_Event event; //gestion des evenements, tous les evens seront ici
    
    while(SDL_PollEvent(&event)//capturer les evenements sans couper l'execution de programme
    {
        switch (event.type)
        {



            case SDL_QUIT;
                programme_lance = SDL_FALSE;
                break;

            default:
                break;
         }
    }
}*/

SDL_Delay(9498);

Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}
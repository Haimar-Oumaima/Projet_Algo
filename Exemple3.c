/******************************************
 * Exemple 3
 ******************************************/

#include "graphics.h" 
 
int main()
{   
	int i;
	POINT P1, P2;
	
	init_graphics(1100,700); /* (largeur, hauteur) */

//	affiche_auto_off(); // Passe en mode d'affichage manuel
	
	/* Lignes horizontales */
	P1.x = 0; P1.y = 0 ;
	P2.x = 1100; P2.y = 0 ;
	for(i=0;i<700; i=i+2)
	{
		draw_line(P1, P2, blanc);
		P1.y = i;
		P2.y = i;
	}
	
	// affiche tous les ordres de "draw" donnés depuis le dernier 
	// affiche_all ou le dernier affiche_auto_off()
//	affiche_all(); 
	wait_clic();
		
	/* Lignes verticales */
	P1.x = 0; P1.y = 0 ;
	P2.x = 0; P2.y = 700 ;
	for(i=0;i<1100; i=i+4)
	{
		draw_line(P1, P2, rouge);
		P1.x = i;
		P2.x = i;
	}

    wait_escape();    
    return(0);
}

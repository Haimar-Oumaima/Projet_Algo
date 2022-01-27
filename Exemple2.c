/******************************************
 * Exemple 2
 ******************************************/

#include "graphics.h" 
 
int main()
{   

	POINT P1, P2;	
	
	init_graphics(500,350); /* (largeur, hauteur) */

	P1.x = 0; P1.y = 0;
	P2.x = 200; P2.y = 100;

	draw_fill_rectangle(P1,P2,rouge);
	draw_fill_circle(P2, 50, vert);
	draw_line (P1,P2,jaune);
	

	int i;
	for(i=0;i<3;i++)
	{
		P1 = wait_clic();
		draw_circle(P1, 25, blanc);
	}
	
    wait_escape();    
    return(0);
}

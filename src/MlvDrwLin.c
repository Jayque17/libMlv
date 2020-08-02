/******************************************************************************/
/* draw_line : Dessine un segment de droite dans une fenetre prealablement    */
/*             creee par la fonction "create_window".                         */
/*             Les extremites du segment sont definies par deux points donnes */
/*             en parametre. Soit un point (x,y), x correspond aux abscisses  */
/*             selon l'axe horizontal oriente de gauche a droite, y correspond*/
/*             aux ordonnees selon l'axe vertical oriente de haut en bas.     */
/*                                                                            */
/* draw_line (                                                                */
/*    int           x1,                 Coordonnee en X du premier point      */
/*    int           y1,                 Coordonnee en Y du premier point      */
/*    int           x2,                 Coordonnee en X du deuxieme point     */
/*    int           y2,                 Coordonnee en Y du deuxieme point     */
/*    char          *color_name,        Couleur du trait (voir "rgb.txt")     */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include <stdio.h>
#include <MlvX.h>
#include <MlvProcC.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void draw_line (
   int              x1,                 /* X-coordinate of segment beginning  */
   int              y1,                 /* Y-coordinate of segment beginning  */
   int              x2,                 /* X-coordinate of segment end        */
   int              y2,                 /* Y-coordinate of segment end        */
   char             *color_name,        /* drawing color                      */
   MlvStruct        *x_var)             /* global X structure pointer         */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   unsigned long    color;              /* display color */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if (color_name == NULL)
   {
      fprintf(stderr,"draw_line : A color shall be specified.\n");
      return;
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "draw_line : x_var is a null pointer\n");
      return;
   }
/******************************************************************************/
/* Get the closest color from colormap                                        */
/******************************************************************************/
   if (get_color(color_name,x_var,&color) != 1)
   {
      fprintf (stderr, "draw_line : Cannot get color \"%s\"\n",
         color_name);
      return;
   }
/******************************************************************************/
/* Draw with selected color                                                   */
/******************************************************************************/
   XSetForeground (x_var->display,x_var->gc,color);
   XDrawLine (x_var->display,x_var->pixmap,x_var->gc,x1,y1,x2,y2);
}

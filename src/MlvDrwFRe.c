/******************************************************************************/
/* draw_filled_rectangle : Dessine un rectangle plein dans une fenetre        */
/*                  prealablement creee par la fonction "create_window".      */
/*                  Le rectangle est defini par les coordonnees de son coin   */
/*                  superieur gauche (x,y), sa largeur et sa  hauteur.        */
/*                  La coordonnee x correspond aux abscisses selon l'axe      */
/*                  horizontal oriente de gauche a droite, y correspond aux   */
/*                  ordonnees selon l'axe vertical oriente de haut en bas.    */
/*                  La couleur ("gray") specifie le niveau de gris a utiliser */
/*                  pour le remplissage.                                      */
/*                                                                            */
/* draw_filled_rectangle (                                                    */
/*    int           x,                  Coordonnee en X du coin sup. gauche   */
/*    int           y,                  Coordonnee en Y du coin sup. gauche   */
/*    int           width,              Largeur du rectangle (en pixels)      */
/*    int           height,             Hauteur du rectangle (en pixels)      */
/*    char          *color_name,        Couleur de remplissage ("rgb.txt")    */
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
void draw_filled_rectangle (
   int              x,                  /* X-coordinate of upper-left corner  */
   int              y,                  /* Y-coordinate of upper-left corner  */
   int              width,              /* rectangle width                    */
   int              height,             /* rectangle height                   */
   char             *color_name,        /* drawing color                      */
   MlvStruct        *x_var)             /* global X structure pointer         */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   unsigned long    color;              /* drawing color in colormap */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if (color_name == NULL)
   {
      fprintf(stderr,"draw_filled_rectangle : A color shall be specified.\n");
      return;
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "draw_filled_rectangle : x_var is a null pointer\n");
      return;
   }

/******************************************************************************/
/* Get the closest color from colormap                                        */
/******************************************************************************/
   if (get_color(color_name,x_var,&color) != 1)
   {
      fprintf (stderr, "draw_filled_rectangle : Cannot get color \"%s\"\n",
         color_name);
      return;
   }
/******************************************************************************/
/* Handle negative dimensions in a "user-friendly" way                        */
/******************************************************************************/
   if (width < 0)
   {
      width = -width;
      x -= width;
   }
   if (height < 0)
   {
      height = -height;
      y -= height;
   }
/******************************************************************************/
/* Draw with selected color                                                   */
/******************************************************************************/
   XSetFillStyle (x_var->display,x_var->gc,FillSolid);
   XSetForeground (x_var->display,x_var->gc,color);
   XFillRectangle(x_var->display,x_var->pixmap,x_var->gc,x,y,width+1,
                  height+1);
}

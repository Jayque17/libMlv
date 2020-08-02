/******************************************************************************/
/* draw_point :Dessine un point dans  une fenetre prealablement creee par la  */
/*             fonction "create_window".                                      */
/*                                                                            */
/* draw_point (                                                               */
/*    int           x,                  Coordonnee en X du point              */
/*    int           y,                  Coordonnee en Y du point              */
/*    char          *color_name,        Couleur du trace (voir "rgb.txt")     */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include  <stdio.h>
#include  <MlvX.h>
#include <MlvProcC.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void draw_point (
   int              x,                  /* X-coordinate of point              */
   int              y,                  /* Y-coordinate of point              */
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
      fprintf(stderr,"draw_point : A color shall be specified.\n");
      return;
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "draw_point : x_var is a null pointer\n");
      return;
   }
/******************************************************************************/
/* Get the closest color from colormap                                        */
/******************************************************************************/
   if (get_color(color_name,x_var,&color) != 1)
   {
      fprintf (stderr, "draw_point : Cannot get color \"%s\"\n",
         color_name);
      return;
   }
/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   XSetForeground (x_var->display,x_var->gc,color);
   XDrawPoint (x_var->display,x_var->pixmap,x_var->gc,x,y);
}

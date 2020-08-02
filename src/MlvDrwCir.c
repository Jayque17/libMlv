/******************************************************************************/
/* draw_circle : Dessine un cercle a une position et avec un rayon specifies  */
/*               en parametre.                                                */
/*                                                                            */
/* draw_circle (                                                              */
/*    int           x,                  Coordonnee en X du centre             */
/*    int           y,                  Coordonnee en Y du centre             */
/*    int           radius,             Rayon du cercle                       */
/*    char          *color_name,        Couleur du trace (voir "rgb.txt")     */
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
void draw_circle (
   int              x,                  /* X-coordinate of center             */
   int              y,                  /* Y-coordinate of center             */
   int              radius,             /* circle radius                      */
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
      fprintf(stderr,"draw_circle : A color shall be specified.\n");
      return; 
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "draw_circle : x_var is a null pointer\n");
      return;
   }
/******************************************************************************/
/* Get the closest color from colormap                                        */
/******************************************************************************/
   if (get_color(color_name,x_var,&color) != 1)
   {
      fprintf (stderr, "draw_circle : Cannot get color \"%s\"\n",
         color_name);
      return; 
   }
/******************************************************************************/
/* Change foreground color                                                    */
/******************************************************************************/
   XSetForeground (x_var->display,x_var->gc,color);
/******************************************************************************/
/* Draw circle                                                                */
/******************************************************************************/
   XDrawArc (x_var->display,x_var->pixmap,x_var->gc,x-radius,y-radius,
             2*radius,2*radius,0,360*64);
}

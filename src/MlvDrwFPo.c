/******************************************************************************/
/* draw_filled_polygone : Dessine un polygone plein, de couleur "gray", avec  */
/*                    le nombre de sommets "npoints". Le tableau "poly"       */
/*                    contient un nombre "npoints" de structures de type      */
/*                    XPoint. Cette structure possede 2 champs "x" et "y" de  */
/*                    type SHORT INT.                                         */
/*                                                                            */
/*                    Exemple:   XPoint pts[3] = { {1,1}, {3,4}, {2,3} };     */
/*                                ...                                         */
/*                               draw_filled_polygone(pts, 3, BLACK, x_var);  */
/*                                                                            */
/* draw_filled_polygone (                                                     */
/*    XPoint        poly[],             Liste des points                      */
/*    int           npoints,            Nombre de sommets du polygone         */
/*    char          *color_name,        Couleur de remplissage ("rgb.txt")    */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include <MlvX.h>
#include <stdio.h>
#include <stdlib.h>
#include <MlvProcC.h>
   
/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void draw_filled_polygone (
   XPoint           poly[],             /* Coordinates of points              */
   int              npoints,            /* Number of vertices                 */
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
      fprintf(stderr,"draw_filled_polygone : A color shall be specified.\n");
      return;
   }
   if (npoints < 3)
   {
      fprintf(stderr, "draw_filled_polygone : needs at least 3 points...\n");
      return;
   }
   if ((x_var == NULL) || (poly == NULL))
   {
      fprintf (stderr, "draw_filled_polygone : Wrong parameter\n");
      return;
   }
/******************************************************************************/
/* Get the closest color from colormap                                        */
/******************************************************************************/
   if (get_color(color_name,x_var,&color) != 1)
   {
      fprintf (stderr, "draw_filled_polygone : Cannot get color \"%s\"\n",
         color_name);
      return;
   }
/******************************************************************************/
/* Draw with selected color                                                   */
/******************************************************************************/
   XSetFillStyle (x_var->display,x_var->gc,FillSolid);
   XSetForeground (x_var->display,x_var->gc,color);
   XFillPolygon(x_var->display,x_var->pixmap,x_var->gc,poly,npoints,Complex,
                CoordModeOrigin);
}

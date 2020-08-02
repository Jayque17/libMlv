/******************************************************************************/
/* draw_string :    Affiche un texte dans une fenetre creee par create_window */
/*                  La position du texte est passee en parametre. Celle-ci    */
/*                  correspond a la position inferieure gauche du premier     */
/*                  caractere (comprendre inferieur comme base des lettres).  */
/*                  La fonction gere aussi les fontes systeme. On peut connai-*/
/*                  tre la liste des fontes disponible en tapant par exemple  */
/*                  la commande UNIX 'xlsfonts'.                              */
/*                                                                            */
/*                  La couleur ("gray") specifie le niveau de gris a utiliser */
/*                  pour le dessin du contour et le remplissage.              */
/*                                                                            */
/* draw_string (                                                              */
/*    int           x,                  Coordonnee en X du coin inf. gauche   */
/*    int           y,                  Coordonnee en Y du coin inf. gauche   */
/*    char          *text,              Texte a afficher                      */
/*    char          *font_name          Nom de la fonte a utiliser            */
/*    char          *color_name,        Couleur du trace (voir "rgb.txt")     */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include  <stdio.h>
#include  <string.h>
#include  <MlvX.h>
#include <MlvProcC.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void draw_string (
   int              x,                  /* X-coordinate of text beginning     */
   int              y,                  /* Y-coordinate of text beginning     */
   char             *text,              /* text to be displayed               */
   char             *font_name,         /* name of the selected font          */
   char             *color_name,        /* drawing color                      */
   MlvStruct        *x_var)             /* global X structure pointer         */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   unsigned long    color;              /* display color                      */
   Font             font_id;            /* font identity                      */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((text == NULL) || (font_name == NULL) || (x_var == NULL))
   {
        fprintf (stderr, "draw_string : Wrong parameter\n");
        return;
   }
   if (color_name == NULL)
   {
      fprintf(stderr,"draw_string : A color shall be specified.\n");
      return;
   }
/******************************************************************************/
/* Get the closest color from colormap                                        */
/******************************************************************************/
   if (get_color(color_name,x_var,&color) != 1)
   {
      fprintf (stderr, "draw_string : Cannot get color \"%s\"\n",
         color_name);
      return;
   }
   XSetForeground (x_var->display,x_var->gc,color);
/******************************************************************************/
/* Set font                                                                   */
/******************************************************************************/
   if (strlen(font_name) > 1)
   {
      font_id = XLoadFont(x_var->display, font_name);
      XSetFont(x_var->display, x_var->gc, font_id);
   }
/******************************************************************************/
/* Draw string on top of specified window and display                         */
/******************************************************************************/
   XDrawString (x_var->display,x_var->pixmap,x_var->gc,x,y,text,strlen(text));
}

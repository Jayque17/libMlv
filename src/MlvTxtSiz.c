/******************************************************************************/
/* text_size :  Calcule les dimensions en pixels d'une chaine de caracteres   */
/*              donnee et pour une police de caracteres (on dit aussi fonte)  */
/*              donnee.                                                       */
/*                                                                            */
/*              Cette fonction permet de calculer les dimensions (largeur,    */
/*              hauteur et elevation) d'un message a afficher, et donc        */
/*              d'adapter l'interface pour centrer et aligner les textes.     */
/*                                                                            */
/*              Les parametres "text", "font_name" et "x_var" sont en entree  */
/*              de la fonction. "width", "height" et "ascent" sont en sortie. */
/*                                                                            */
/* text_size (                                                                */
/*    char          *text,              Texte qu'on desirera afficher         */
/*    char          *font_name          Nom de la fonte a utiliser            */
/*    int           *width,             Largeur totale du texte (en pixels)   */
/*    int           *height,            hauteur du texte (du plus bas au plus */
/*                                      haut). Par exemple "pb" a une hauteur */
/*                                      superieure a celle de "ab".           */
/*    int           *ascent,            Hauteur au dessus de la base du texte */
/*                                      (baseline). Par exemple, "pb" et "ab" */
/*                                      ont la meme elevation (ascent).       */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including file                                                             */
/******************************************************************************/
#include <stdio.h>
#include <MlvX.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void text_size (
   char             *text,              /* Text to be displayed */
   char             *font,              /* Name of the font to be used */
   int              *width,             /* width of the text to be assessed */
   int              *height,            /* font height                */
   int              *ascent,            /* font height above baseline */
   MlvStruct        *x_var)             /* global X structure pointer */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   XFontStruct *font_struct;
   int         direction, font_ascent, font_descent;
   XCharStruct overall;

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((text == NULL)    ||
       (font == NULL)    ||
       (width == NULL)   ||
       (height == NULL)  ||
       (ascent == NULL))
   {
      fprintf (stderr, "text_size : Wrong parameter\n");
      return;
   }

/******************************************************************************/
/* Load font_struct                                                           */
/******************************************************************************/
   if ((font_struct = XLoadQueryFont (x_var->display,font)) == NULL)
   {
      fprintf(stderr, "text_size : Warning : Cannot load font \"%s\"\n", font);
      return;
   }
   else
   {
      XTextExtents(font_struct, text, strlen(text), &direction, &font_ascent,
                   &font_descent, &overall);
      *height = font_ascent + font_descent;
      *width  = overall.width;
      *ascent = font_ascent;
   }
   XFreeFont(x_var->display,font_struct);
}

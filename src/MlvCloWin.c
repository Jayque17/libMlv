/******************************************************************************/
/* close_window : Ferme une fenetre precedemment ouverte par "create_window". */
/*                cette fonction est particulierement utile lorsqu'on a ouvert*/
/*                une deuxieme fenetre, et qu'on souhaite la fermer sans      */
/*                quitter le programme.                                       */
/*                                                                            */
/*                Attention : La structure standard "x_var" d'une fenetre     */
/*                fermee ne contient plus d'imformation pertinente. Ne plus   */
/*                l'utiliser pour l'affichage tant qu'une fenetre n'ait ete   */
/*                ouverte par "create_window" en passant cette structure.     */
/*                                                                            */
/* close_window (                                                             */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include  <stdio.h>
#include  <MlvX.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void close_window (
   MlvStruct        *x_var)             /* global X structure pointer */
{
/*----------------------------------------------------------------------------*/
/* Check parameters                                                           */
/*----------------------------------------------------------------------------*/
   if (x_var == NULL)
   {
      fprintf (stderr, "close_window : x_var is a null pointer\n");
      return;
   }
/*----------------------------------------------------------------------------*/
/* Close window                                                               */
/*----------------------------------------------------------------------------*/
   XDestroyWindow (x_var->display,x_var->window);
   XCloseDisplay(x_var->display);
   x_var->display = NULL;
   x_var->window = 0;
}

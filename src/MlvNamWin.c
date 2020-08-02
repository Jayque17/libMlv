/******************************************************************************/
/* name_window: Change le titre d'une fenetre.                                */
/*                                                                            */
/* name_window (                                                              */
/*    char          *name,              Nouveau titre de la fenetre           */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include  <stdio.h>
#include  <string.h>
#include  <MlvX.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void name_window (
   char                *name,              /* new window name                 */
   MlvStruct           *x_var)             /* global X structure pointer      */
{
/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((name == NULL) ||
       (strlen(name) == 0))
   {
      fprintf (stderr,"name_window: Wrong parameters\n");
      return;
   }
/******************************************************************************/
/* Change window name                                                         */
/******************************************************************************/
   XStoreName(x_var->display, x_var->window, name);
   XFlush(x_var->display);
}

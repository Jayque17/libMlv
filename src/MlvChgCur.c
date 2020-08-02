/******************************************************************************/
/* change_cursor :  Change la forme du pointeur de la souris en utilisant une */
/*                  des fontes predefinies.                                   */
/*                                                                            */
/* change_cursor (                                                            */
/* int              cursor,             Numero de curseur entre 0 et          */
/*                                      MAX_CURSOR = 152                      */
/*                                      Curseurs particuliers:                */
/*                                      - BUSY_CURSOR  : une montre           */
/*                                      - READY_CURSOR : une fleche           */
/*    MlvStruct     *x_var)             Structure standard toujours passee    */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include <stdio.h>
#include <MlvX.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void change_cursor (
   int            cursor,       /* Number of requested cursor */
   MlvStruct      *x_var)       /* global X structure pointer */
{
/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((cursor < 0) || (cursor > MAX_CURSOR))
   {
      fprintf(stderr,"change_cursor : cursor must be in range [0-%d]\n",
         MAX_CURSOR);
      return;
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "change_cursor : x_var is a null pointer\n");
      return;
   }
/******************************************************************************/
/* Change cursor                                                              */
/******************************************************************************/
   XDefineCursor(x_var->display,x_var->window,XCreateFontCursor(x_var->display,
      cursor));
   XFlush (x_var->display);
}

/******************************************************************************/
/* mouse_wait : Suspend l'execution jusqu'au prochain clic souris et retourne */
/*              les coordonnees du point vise ou des valeurs negatives en     */
/*              cas d'echec.                                                  */
/*                                                                            */
/* mouse_wait (                                                               */
/*    int           *x,                 Coordonnee en X du point attendu      */
/*    int           *y,                 Coordonnee en Y du point attendu      */
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
void mouse_wait (
   int              *x,                 /* coordonnee x a initialiser */
   int              *y,                 /* coordonnee y a initialiser */
   MlvStruct        *x_var)             /* global X structure pointer */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   XEvent           event;              /* pointer on union event */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((x == NULL) || (y == NULL) || (x_var == NULL))
   {
      fprintf (stderr, "mouse_wait : Wrong parameter\n");
      return;
   }

/******************************************************************************/
/* Flush the event queue                                                      */
/******************************************************************************/
   while (XPending(x_var->display))
   {
      XNextEvent (x_var->display,&event);
      if (event.type == Expose)
      {
/******************************************************************************/
/*       Put the pixmap into the window                                       */
/******************************************************************************/
         XCopyArea(x_var->display,x_var->pixmap,x_var->window,x_var->gc,0,0,
                   x_var->width,x_var->height,0,0);
         x_var->displayCount = x_var->displayCount + 1;
         XFlush (x_var->display);
      }
   }
/******************************************************************************/
/* Loop on X events                                                           */
/******************************************************************************/
   do
   {
      XNextEvent(x_var->display,&event);
      if (event.type == Expose)
      {
/******************************************************************************/
/*       Put the pixmap into the window                                       */
/******************************************************************************/
         XCopyArea(x_var->display,x_var->pixmap,x_var->window,x_var->gc,0,0,   
                   x_var->width,x_var->height,0,0);   
         x_var->displayCount = x_var->displayCount + 1;   
         XFlush (x_var->display);   
         continue;
      }
   }
   while ((event.type != ButtonPress) && 
          (event.xbutton.window == x_var->window));
   *x = event.xbutton.x;
   *y = event.xbutton.y;
}

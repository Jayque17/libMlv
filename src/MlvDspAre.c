/******************************************************************************/
/* display_area : Affiche tout ou partie de la fenetre.                       */
/*                La fonction "display_window" utilise cette fonction pour    */
/*                re-afficher (on dit aussi rafraichir) toute la fenetre.     */
/*                                                                            */
/*                Lorsque seulement une partie de la fenetre doit etre        */
/*                rafraichie, il est conseillee de ne re-afficher que cette   */
/*                partie. Le gain de temps peut etre tres sensible.           */
/*                                                                            */
/*                Le rectangle est defini par les coordonnees de son coin     */
/*                superieur gauche (x,y), sa largeur et sa hauteur.           */
/*                                                                            */
/* display_area (                                                             */
/*    int           x,                  Coordonnee en X du coin sup. gauche   */
/*    int           y,                  Coordonnee en Y du coin sup. gauche   */
/*    int           width,              Largeur de la partie a rafraichir     */
/*    int           height,             Hauteur de la partie a rafraichir     */
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
void display_area (
   int              x,                  /* X-coordinate of upper-left corner  */
   int              y,                  /* Y-coordinate of upper-left corner  */
   int              width,              /* rectangle width                    */
   int              height,             /* rectangle height                   */
   MlvStruct        *x_var)             /* global X structure pointer         */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   XEvent           event;              /* structure used to get events */
   int              done;               /* "event loop is done" flag */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((x_var == NULL)           ||
       (x_var->display == NULL)  ||
       (x_var->window == 0))
   {
      fprintf(stderr,
         "display_area : Global variables not correctly initialized\n");
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
/* Case of refreshing                                                         */
/******************************************************************************/
   if (x_var->displayCount > 0)
   {
      XCopyArea(x_var->display, x_var->pixmap, x_var->window, x_var->gc, x, y,
                 width + 1, height + 1, x, y);
      x_var->displayCount = x_var->displayCount + 1;
      XFlush (x_var->display);  
      return;
   }

/******************************************************************************/
/* Events loop                                                                */
/******************************************************************************/
   done = 0;
   while (!done) {
      XNextEvent (x_var->display, &event);
      switch (event.type) {
         case Expose:
/******************************************************************************/
/*          Put the pixmap into the window                                    */
/******************************************************************************/
            XCopyArea(x_var->display,x_var->pixmap,x_var->window,x_var->gc,0,0,
                      x_var->width,x_var->height,0,0);
            x_var->displayCount = x_var->displayCount + 1;
            XFlush (x_var->display);
            done = 1;
            break;
         case ButtonPress:
            XCloseDisplay (x_var->display);
            return;
         default:
            break;
      }
   }
}


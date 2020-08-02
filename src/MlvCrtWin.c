/******************************************************************************/
/* create_window : Cree une fenetre vide dans laquelle un motif pourra etre   */
/*                 dessine. Le nom du display destination ainsi que les       */
/*                 dimensions de la fenetre sont passees en parametres.       */
/*                                                                            */
/*                 Le nom du display sur lequel doit etre affiche la fenetre  */
/*                 est une chaine de caracteres ecrite selon la syntaxe X     */
/*                 standard: <host:board.screen> (exemple: "carol:0.0").      */
/*                 Lorsque l'on desire ouvrir la connection sur l'ecran par   */
/*                 defaut, la valeur NULL doit etre passee.                   */
/*                                                                            */
/*                 create_window doit etre la premiere procedure a appeler.   */
/*                                                                            */
/*                 create_window (display_name, width, height,                */
/*                                global_variables);                          */
/*                 . display_name: Nom de l'ecran destination.                */
/*                 . width  : Largeur de la fenetre (en pixels).              */
/*                 . height : Hauteur de la fenetre (en pixels).              */
/*                 . global_variables : Structure standard passee a toutes    */
/*                                      les procedures de la librairie.       */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <MlvX.h>

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
void create_window (
   char             *display_name,      /* name of server/screen to be connect*/
   int              width,              /* required width of window           */
   int              height,             /* required height of window          */
   MlvStruct        *x_var)             /* global X structure pointer         */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   XSetWindowAttributes window_attributes; /* required to manage auto-refresh */
   XSizeHints       window_size_hints;  /* used to forbid user resizing       */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if ((height <= 0)   ||   (height > MAXLINES))
   {
      fprintf(stderr,"create_window : Height must be in range [1-%d]\n",
         MAXLINES);
      exit(5);
   }
   if ((width <= 0)    ||   (width > MAXPIXELS))
   {
      fprintf(stderr,"create_window : Width must be in range [1-%d]\n",
         MAXPIXELS);
      exit(5);
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "create_window : x_var is a null pointer\n");
      return;
   }
/******************************************************************************/
/* connect to X server                                                        */
/******************************************************************************/
   if ((x_var->display=XOpenDisplay(display_name)) == NULL)
   {
      fprintf(stderr,"create_window : cannot connect to X server %s\n",
         XDisplayName(display_name));
      exit(5);
   }
/******************************************************************************/
/* Report default and passed values                                           */
/******************************************************************************/
   x_var->width        = width;
   x_var->height       = height;
   x_var->screen       = DefaultScreen (x_var->display);
   x_var->gc           = DefaultGC(x_var->display,x_var->screen);
   x_var->displayCount = 0;
/******************************************************************************/
/* Create the window                                                          */
/******************************************************************************/
   if ((x_var->window=XCreateSimpleWindow (x_var->display,
        RootWindow(x_var->display,x_var->screen),
        0,0,x_var->width,x_var->height,BORDERWIDTH, BlackPixel(x_var->display,
        x_var->screen), WhitePixel(x_var->display,x_var->screen))) == 0)
   {
      fprintf(stderr,"create_window : cannot create the window \n");
      exit(5);
   }

   XSelectInput (x_var->display,x_var->window,
                 ButtonPressMask | KeyPressMask | ExposureMask );

   XSetFunction (x_var->display,x_var->gc,GXcopy);
/******************************************************************************/
/* Make manage auto-refresh by X server                                       */
/******************************************************************************/
   if ((XDoesSaveUnders(ScreenOfDisplay(x_var->display, x_var->screen)) == True)
       && (XDoesBackingStore(ScreenOfDisplay(x_var->display, x_var->screen))
           == Always))
   {
      window_attributes.save_under    = True; 
      window_attributes.backing_store = Always;
      XChangeWindowAttributes (x_var->display,x_var->window,
         CWSaveUnder | CWBackingStore,&window_attributes);
   }
/******************************************************************************/
/* Unable user resizing                                                       */
/******************************************************************************/
   window_size_hints.max_width = width;
   window_size_hints.min_width = width;
   window_size_hints.width     = width;
   window_size_hints.max_height = height;
   window_size_hints.min_height = height;
   window_size_hints.height     = height;
   window_size_hints.flags = PSize | PMinSize | PMaxSize;
   XSetStandardProperties(x_var->display, x_var->window, NULL, NULL, 0, NULL, 0,
      &window_size_hints);
/******************************************************************************/
/* Display the window                                                         */
/******************************************************************************/
   XMapWindow (x_var->display,x_var->window);
/******************************************************************************/
/* Create the pixmap on which figures are drawn                               */
/******************************************************************************/
   if ((x_var->pixmap=XCreatePixmap(x_var->display,x_var->window,width,height,
        DefaultDepth(x_var->display,x_var->screen))) == 0)
   {
      fprintf(stderr,
         "create_window : Cannot create the pixmap on display \"%s\"\n",
         XDisplayName(display_name));
      exit(5);
   }
/*****************************************************************************/
/* Set foreground and background                                             */
/*****************************************************************************/
   XSetForeground(x_var->display, x_var->gc, WhitePixel(x_var->display,
                  x_var->screen));
   XFillRectangle(x_var->display, x_var->pixmap, x_var->gc, 0,0,width,height);
   XSetForeground(x_var->display, x_var->gc, BlackPixel(x_var->display,
                  x_var->screen));
/******************************************************************************/
/* Flush the output buffer                                                    */
/******************************************************************************/
   XFlush (x_var->display);
}

/******************************************************************************/
/* MlvX.h contient les constantes ainsi que les definitions des types         */
/* utilises par les fonctions de la librairie graphique Xlib                  */
/******************************************************************************/
#ifndef MLVX_H
#define MLVX_H

#include  <X11/X.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include  <X11/Xos.h>
#include  <X11/Xatom.h>

/******************************************************************************/
/* Definitions des constantes                                                 */
/******************************************************************************/
#define             BORDERWIDTH  (unsigned int)5
#define             MAXLINES     (768  - BORDERWIDTH)
#define             MAXPIXELS    (1024 - BORDERWIDTH)

#define             BLACK        0
#define             black        BLACK   /* pour compatibilite v3 */
#define             WHITE        1
#define             white        WHITE

#define             MAX_CURSOR   152

/******************************************************************************/
/* Structure globale des variables du serveur X                               */
/******************************************************************************/
typedef struct {
   Display          *display;          /* pointeur sur la struture Display */
   int              screen;            /* identification de l'ecran */
   Window           window;            /* struture Window (pointeur) */
   int              width;             /* largeur de la fenetre */
   int              height;            /* hauteur de la fenetre */
   int              displayCount;      /* nombre d'ecrans deja crees */
   GC               gc;                /* contexte graphique */
   Pixmap           pixmap;            
} MlvStruct;                           

#endif

/******************************************************************************/
/* MlvTypeC.h contient les definitions de type pour tout programme C          */
/* utilisant la librairie graphique.                                          */
/******************************************************************************/

#ifndef _MLVTYPEC_
#define _MLVTYPEC_

#include <stdlib.h>
#include <sys/wait.h>

#ifndef __LIBMLV__
#define __LIBMLV__ 4
#endif

#include "MlvX.h"

typedef MlvStruct   MlvType;            

/* Curseurs speciaux pour change_cursor() */
#define BUSY_CURSOR  150
#define READY_CURSOR 132

/* Codes de retour de event_wait():       */
/* - codes souris ( code >= LMB )         */
#define LMB 301    /* LeftMouseButton     */
#define MMB 302    /* MiddleMouseButton   */
#define RMB 303    /* RightMouseButton    */

/* - codes touches ( code < LMB )         */
#define K_ENTER        256
#define K_BACKSPACE    257
#define K_UP           258
#define K_DOWN         259
#define K_RIGHT        260
#define K_LEFT         261
#define K_SHIFT        262
#define K_DELETE       263
#define K_TAB          264
#define K_CTRL         265
#define K_ALT          266
#define K_CAPS_LOCK    267
#define K_NUM_LOCK     268
#define K_HOME         269
#define K_PAGE_UP      270
#define K_PAGE_DOWN    271
#define K_ESCAPE       272
#define K_INSERT       273
#define K_END          274

/* Les codes 7 bits affichables sont compris entre ces 2 valeurs: */
#define MIN_PRINT_KEY  ' '
#define MAX_PRINT_KEY  126

/* Modes de traitement des evenements par event_check */
#define NO_FLUSH       0   /* tous les evenements sont conserves      */
#define FLUSH          1   /* les evenements "en trop" sont detruits  */

#endif

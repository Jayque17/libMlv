/******************************************************************************/
/* MlvProcC.h contient les declarations des procedures pour tout programme    */
/* C utilisant la librairie graphique.                                        */
/******************************************************************************/

#ifndef _MLVTYPEC_
#include "MlvTypeC.h"
#endif

void change_cursor         (int cursor,MlvType *x_var);

void close_window          (MlvType *x_var);

void create_window         (char* display_name, int width, int height, MlvType *x_var);

void display_area          (int x,int y,int width,int height,MlvType *x_var);

#define display_window(x_var) \
   display_area(0, 0, (x_var)->width, (x_var)->height, x_var);

void draw_circle           (int x, int y, int radius, char *color_name, MlvType *x_var);

void draw_filled_circle    (int x, int y, int radius, char *color_name, MlvType *x_var);

void draw_filled_polygone  (XPoint poly[], int npoints, char *color_name, MlvType *x_var);

void draw_filled_rectangle (int x, int y, int width, int height, char *color_name, MlvType *x_var);

void draw_line             (int x1, int y1, int x2, int y2, char *color_name, MlvType *x_var);

void draw_point            (int x, int y, char *color_name, MlvType *x_var);

void draw_rectangle        (int x, int y, int width, int height, char *color_name,MlvType *x_var);

void draw_string           (int x, int y, char *text, char *font, char *color_name, MlvType *x_var);

void event_check           (int *pressed, int *x, int *y, int flush, MlvType *x_var);

void event_wait            (int *pressed, int *x, int *y, MlvType *x_var);

int  get_color             (char *color_name, MlvType *x_var, unsigned long *color);

void mouse_wait            (int *x, int *y, MlvType *x_var);

void name_window           (char *name, MlvType *x_var);

#define random(x) mlvrandom(x)

int  mlvrandom             (int range);

void text_size             (char *text,char *font, int *width, int *height, int *ascent,MlvType *x_var);

void wait_micros           (int micros);

void wait_seconds          (int seconds);

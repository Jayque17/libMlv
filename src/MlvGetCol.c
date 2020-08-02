/******************************************************************************/
/* get_color : Cette fonction interne (non destinee a etre utilisee par les   */
/*             etudiants) permet de retrouver l'entree du pixel dans la       */
/*             colormap par defaut correspondant a la couleur desiree dont le */
/*             nom est passe en parametre.                                    */
/*             Cette fonction retourne 0 en cas d'erreur et 1 autrement.      */
/*                                                                            */
/* get_color (                                                                */
/*    char          *color_name,        nom de la couleur (voir "rgb.txt")    */
/*    MlvStruct     *x_var,             Structure standard toujours passee    */
/*    unsigned long *color)             Entree correspondante dans la colormap*/
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <MlvX.h>

/******************************************************************************/
/* Macro definitions                                                          */
/******************************************************************************/
#define nint(float_value)  (((float_value)-(int)(float_value) > 0.5)?          \
                            (int)(float_value)+1 : (int)(float_value))

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
int get_color (
   char             *color_name,       /* color name in "rgb.txt"             */
   MlvStruct        *x_var,            /* global X structure pointer          */
   unsigned long    *color)            /* colormap entry to be retrieved      */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   XColor           rgb_db_def;        /* structure returned by XParseColor   */
   int              required_depth;    /* expected depth when getting visual */
   int              status;            /* status returned by X function call */
   int              red_colormap_entries; /* nb.of possible values for Red */
   int              red_offset;         /* left offset to match the Red mask*/
   int              green_colormap_entries; /* nb.of possible values for Green*/
   int              green_offset;       /* left offset to match the Green mask*/
   int              blue_colormap_entries; /* nb.of possible values for Blue */
   int              blue_offset;         /* left offset to match the Blue mask*/
   XVisualInfo      visual_info;        /* structure used to get visual info */
   int              icolor_red;         /* color value for component red */
   int              icolor_green;       /* color value for component green */
   int              icolor_blue;        /* color value for component blue */
   int              bits_per_rgb;        /* bits nb.per RGB pixel in frame buf*/
   int              bytes_per_rgb;       /* bytes nb.per RGB pixel in frame bu*/

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if (color_name == NULL)
   {
      fprintf(stderr,"get_color : A color shall be specified.\n");
      return(0);
   }
   if (x_var == NULL)
   {
      fprintf (stderr, "get_color : x_var is a null pointer\n");
      return(0);
   }
/******************************************************************************/
/* Get the color definition from "rgb.txt" database                           */
/******************************************************************************/
   if (XParseColor(x_var->display,XDefaultColormap(x_var->display,
       DefaultScreen(x_var->display)),color_name,&rgb_db_def) == 0)
   {
      fprintf (stderr,"get_color : Cannot get color \"%s\" from database.\n",
         color_name);
      fprintf (stderr,"Check that this name is present in \"rgb.txt\" file.\n");
      return(0);
   }
/******************************************************************************/
/* Get the TrueColor visual                                                   */
/******************************************************************************/
   required_depth = 24;
   do
   {
      if ((status=XMatchVisualInfo(x_var->display,DefaultScreen(x_var->display),
           required_depth,TrueColor,&visual_info)) == 0)
      {
         required_depth = required_depth - 1;
      }
   } while ((status == 0) && (required_depth >= 8)); 
   if (required_depth < 8)
   {
      fprintf (stderr,
         "get_color : Cannot get a TrueColor visual for whatever depth.\n");
      return (0);
   }
/*============================================================================*/
/* Check that the number of bits per pixels in frame buffer is multiple of 8  */
/*============================================================================*/
   bits_per_rgb = BitmapUnit(x_var->display);
   if (required_depth == 16)
      bits_per_rgb = 16;
   if (bits_per_rgb % 8 != 0) 
   {
      fprintf (stderr,"get_color : Only number of bits per pixels in ");
      fprintf (stderr,"frame buffer multiple of 8 are supported.\n");
      return (0);
   }
   bytes_per_rgb = bits_per_rgb / 8;
/******************************************************************************/
/* Analyze the way Red, Green and Blue component are mapped in frame buffer   */
/******************************************************************************/
/* Red component                                                              */
/*----------------------------------------------------------------------------*/
   red_colormap_entries = visual_info.red_mask;
   red_offset           = 0;
   while ((red_colormap_entries & 0x00000001) == 0)
   {
      red_offset           = red_offset + 1;
      red_colormap_entries = (red_colormap_entries >> 1);
   }
   red_colormap_entries = red_colormap_entries + 1;
/*----------------------------------------------------------------------------*/
/* Green component                                                            */
/*----------------------------------------------------------------------------*/
   green_colormap_entries = visual_info.green_mask;
   green_offset           = 0;
   while ((green_colormap_entries & 0x00000001) == 0)
   {
      green_offset           = green_offset + 1;
      green_colormap_entries = (green_colormap_entries >> 1);
   }
   green_colormap_entries = green_colormap_entries + 1;
/*----------------------------------------------------------------------------*/
/* Blue component                                                             */
/*----------------------------------------------------------------------------*/
   blue_colormap_entries = visual_info.blue_mask;
   blue_offset           = 0;
   while ((blue_colormap_entries & 0x00000001) == 0)
   {
      blue_offset           = blue_offset + 1;
      blue_colormap_entries = (blue_colormap_entries >> 1);
   }
   blue_colormap_entries = blue_colormap_entries + 1;
/******************************************************************************/
/* Generate the pixel value from the RGB components                           */
/******************************************************************************/
/* Set RGB values according to their colormap entries                         */
/*----------------------------------------------------------------------------*/
   icolor_red   = nint((float)red_colormap_entries  * rgb_db_def.red   / 65536);
   if (icolor_red >= red_colormap_entries)
      icolor_red = red_colormap_entries - 1;
   icolor_green = nint((float)green_colormap_entries* rgb_db_def.green / 65536);
   if (icolor_green >= green_colormap_entries)
      icolor_green = green_colormap_entries - 1;
   icolor_blue  = nint((float)blue_colormap_entries * rgb_db_def.blue  / 65536);
   if (icolor_blue >= blue_colormap_entries)
      icolor_blue = blue_colormap_entries - 1;
/*----------------------------------------------------------------------------*/
/* Combine the three components according to their masks                      */
/*----------------------------------------------------------------------------*/
   *color = (icolor_red   << red_offset)    |
            (icolor_green << green_offset)  |
            (icolor_blue  << blue_offset);
/******************************************************************************/
/* Return Success status                                                      */
/******************************************************************************/
   return (1);
}

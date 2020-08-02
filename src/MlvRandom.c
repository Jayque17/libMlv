/******************************************************************************/
/* random : Genere un nombre aleatoire dans l'intervalle defini par l'utili-  */
/*          sateur.                                                           */
/*          Soit range, l'entier defini comme etant la borne superieure de    */
/*          l'intervalle, "random" retourne une valeur dans l'intervalle :    */
/*          [0,(range-1)]                                                     */
/*                                                                            */
/* random (                                                                   */
/*    int           range)              Borne superieure de l'intervalle      */
/******************************************************************************/

/******************************************************************************/
/* Including files                                                            */
/******************************************************************************/
#include  <stdio.h>
#include  <stdlib.h>
#include  <MlvX.h>

/******************************************************************************/
/* main                                                                       */
/* Note: Ce programme connu sous le nom de "random" a l'exterieur est renomme */
/* "mlvrandom" pour ne pas interferer avec les librairies mathematiques et    */
/* systeme presentes sur les sites.                                           */
/******************************************************************************/
int mlvrandom (
   int              range)              /* range of output random number */
{
/******************************************************************************/
/* Local variables                                                            */
/******************************************************************************/
   int              random_number;      /* random number to be returned */
   static int       random_initialized; /* first call flag              */

/******************************************************************************/
/* Check parameters                                                           */
/******************************************************************************/
   if (range < 1)
   {
      fprintf (stderr,"random : Wrong parameter\n");
      return (-1);
   }
/******************************************************************************/
/* Case of first call ==> initialize random seed                              */
/******************************************************************************/
   if (random_initialized == 0)
   {
      srand ((unsigned int)getpid());
      random_initialized = 1;
   }
/******************************************************************************/
/* Compute and return random number                                           */
/******************************************************************************/
   random_number = rand();
   random_number = (double)range * (double)random_number / (double)RAND_MAX;
   if (random_number < 0)
      random_number = 0;
   if (random_number >= range)
      random_number = range - 1;
   return (random_number);
}


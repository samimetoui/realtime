/**
 * Header LecteurEcrivain.h
 * Auteur: Sami Metoui
 * Description: déclarations de la structure
 * et des méthodes LecteurEcrivain
 *
 */

#ifndef LECTEURECRIVAIN_H_INCLUDED
#define LECTEURECRIVAIN_H_INCLUDED

/**
* Strucure LecteurEcrivain
*/

struct LecteurEcrivain {
  int nb_lecteur;
  int nb_ecriv_atten;
  int data;
  pthread_mutex_t lock;
  pthread_cond_t lecteur;
  pthread_cond_t ecrivain;
};

typedef struct LecteurEcrivain s_le;

/**
 * Prototype des fonctions
 */

int lire(s_le*,int);
void ecrire(s_le*,int,int);
void ecrire_data(s_le*,int,int);
int lire_data(s_le*,int);

#endif // LECTEURECRIVAIN_H_INCLUDED

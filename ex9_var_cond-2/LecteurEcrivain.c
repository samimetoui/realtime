/**
* Fichier: LecteurEcrivain.c
* Auteur: Sami Metoui
* description: fonctions utilisées
* par l'objet Lecteurecrivain
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "LecteurEcrivain.h"

/**
 * Fonction : lire()
 * Description : Démarre un lecteur tant qu'il n'y pas d'écrivain
 * en attente.
 * Entrée : pointeur sur structure LecteurEcrivain
 *          entier, id de l'objet
 * Sortie : entier, data lue
 */

int lire(s_le* this,int t_id) {
  int readdat;
  pthread_mutex_lock(&this->lock);
  while (this->nb_ecriv_atten > 0) {
    pthread_cond_wait(&this->lecteur,&this->lock);
  }
  this->nb_lecteur++;
  pthread_mutex_unlock(&this->lock);
  readdat=lire_data(this,t_id);
  pthread_mutex_lock(&this->lock);
  this->nb_lecteur--;
  if(this->nb_lecteur==0) pthread_cond_signal(&this->ecrivain);
  pthread_mutex_unlock(&this->lock);
  return readdat;
}

/**
 * Fonction : ecrire()
 * Description : Démarre une ecriture lorsqu'il n'y pas de lecteurs
 * et libère l'ecrivain en attente lorsque la lecture est achevée
 * sinon libère tout les lecteurs en en attente.
 * Entrée : pointeur sur structure LecteurEcrivain
 *          entier, data à écrire
 *          entier, id de l'objet
 */

void ecrire(s_le* this, int data,int t_id) {
  pthread_mutex_lock(&this->lock);
  this->nb_ecriv_atten++;
  while(this->nb_lecteur>0) {
    pthread_cond_wait(&this->ecrivain,&this->lock);
  }
  this->nb_ecriv_atten--;
  ecrire_data(this,data,t_id);
  if(this->nb_ecriv_atten>0) pthread_cond_signal(&this->ecrivain);
  else pthread_cond_broadcast(&this->lecteur);
  pthread_mutex_unlock(&this->lock);
}

/**
 * Fonction ecrire_data()
 * Entrée : pointeur sur structure LecteurEcrivain
 *          entier, data à écrire
 *          entier, id de l'objet
 */

void ecrire_data(s_le* this,int dat,int t_id) {
  printf("Ecrivain %i - data %i\n",t_id,dat);
  this->data=dat;
}

/**
 * Fonction lire_data()
 * Entrée : pointeur sur structure LecteurEcrivain
 *          entier, id de l'objet
 * Sortie : entier, data lue
 */

int lire_data(s_le* this,int t_id) {
  printf("Lecteur %i - data %i\n",t_id,this->data);
  return this->data;
}

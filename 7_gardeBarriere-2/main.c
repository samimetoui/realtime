/**
 * Programme gardebarrière
 * Auteur: Sami Metoui
 * Description : Démarre plusieurs threads courses. Chaque course
 * comprend plusieurs tours. Le tours suivant commence lorsque
 * tout les coureurs sont arrivés. Cette exemple implémente
 * une barrière réutilisable qui utilise un tourniquet.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "barriere.h"

void attenteCoureur(int*);
void* course(void*);

/**
 * MAIN
 */

int main(int argc, char *argv[])
{
  pthread_t threads[NB_COUREUR];

  int t[NB_COUREUR];
  int i;

  for (i=0; i<NB_COUREUR; i++) t[i]=i+1;

  sem_init (&mutex,0,1);
  sem_init (&barriere,0,0);
  sem_init (&barriere2,0,1);

  for(i=0; i<NB_COUREUR; i++) pthread_create(&threads[i], NULL,course,(void*)(&t[i]));
  for(i=0; i<NB_COUREUR; i++) pthread_join(threads[i], NULL);

  return 0;
}

/**
 * Fonction attenteCoureur()
 * Description : fonction de temporisation
 * Entrée : entier, id du coureur
 */

void attenteCoureur(int* Id)
{
  int tempo = (float)rand()/RAND_MAX * (*Id) * 100 + 100;
  usleep(10000*tempo);
}

/**
 * Fonction course()
 * Démarre la course pour un coureur et fait NB_TOURS
 * Affiche la position du coureur dans la course.
 * Entrée: pointeur de void sur entier, Id du coureur
 */

void* course(void* coureur) {

  int i;
  for(i=0; i<NB_TOUR; i++) {

    attenteCoureur((int*) coureur);
    reusableBarrier((int*) coureur,i);
  }
  pthread_exit(NULL);
}



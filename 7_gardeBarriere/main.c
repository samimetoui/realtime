/**
 * Programme gardebarrière
 * Auteur: Sami Metoui
 * Description : Démarre plusieurs threads courses. Chaque course
 * comprend plusieurs tours. Le tours suivant commence lorsque
 * tout les coureurs sont arrivés. Cette exemple et une non-solution
 * mise en évidence par une temporisation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_COUREUR 3
#define NB_TOUR 4

int count = 0;
sem_t mutex;
sem_t barriere;

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

  for(i=0; i<NB_COUREUR; i++) pthread_create(&threads[i], NULL,course,(void*)(&t[i]));
  for(i=0; i<NB_COUREUR; i++) pthread_join(threads[i], NULL);

  return 0;
}

/**
 * Fonction attenteCoureur()
 * temporisation aléatoire calculée sur base d'un entier
 * Entrée: entier, Id de l'appel
 */

void attenteCoureur(int* Id)
{
  int tempo = (float)rand()/RAND_MAX * (*Id) * 100 + 100;
  usleep(100*tempo);
}

/**
 * Fonction course()
 * Démarre une course de NB_TOURS pour un coureur
 * Le dernier coureur libère les autres coureurs
 * Entrée: pointeur de void sur entier, Id du coureur
 */

void* course(void* coureur) {

  int i,j;

  for(i=0; i<NB_TOUR;i++) {
    attenteCoureur((int*) coureur);
    sem_wait(&mutex);
    count++;
    if (count == NB_COUREUR) { //dernier coureur
      //usleep(7000);    // <- met en évidence la non réutilisabilité de la barrière
      count = 0;
      for(j=0;j<NB_COUREUR-1;j++) sem_post(&barriere); //libère tous les autres coureurs
      printf("Le coureur %i arrive.\n",*(int*) coureur+10*i);
      printf("Les coureurs repartent. %i è(r)me tour.\n",i+1);
      sem_post(&mutex);
    }
    else {
      //
      printf("Le coureur %i arrive.\n",*(int*) coureur+10*i);
      sem_post(&mutex); if(i==0) usleep(70000);    // <- met en évidence la non réutilisabilité de la barrière
      sem_wait(&barriere) ;
    }
  }
  pthread_exit(NULL);
}



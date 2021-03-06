/**
 * Programme : vendeurTicket
 * Auteur: Sami Metoui
 * Description: Démarre plusieurs instances du thread
 * vendeurTickets() qui décrémentent le nombre de tickets
 * jusque 0. Utilise un semaphore au lieu d'un mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_TICKET 10
#define NB_VENDEUR 5

int NbTicket = NB_TICKET;
sem_t sem;

void printTime();
void attenteClient(int* Id);
void* vendeurTicket(void* data);

/**
 * MAIN
 */

int main(int argc, char *argv[])
{

    pthread_t threads[NB_VENDEUR];

    int rc,i;
    int t[NB_VENDEUR];

    for (i=0; i<5; i++) t[i]=i+1;

    sem_init (&sem,0,1);

    for(i=0; i<NB_VENDEUR; i++)
    {
        rc = pthread_create(&threads[i], NULL,vendeurTicket,(void*)(&t[i]));
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(i=0; i<NB_VENDEUR; i++) pthread_join(threads[i], NULL);

    printf("\nSOLD OUT !\n");

    return 0;
}

/**
 * fonction printTime()
 * Affiche l'heure hh:mm:ss
 */

void printTime()
{
    time_t curtime;
    struct tm *loctime;
    char buffer[256];

    curtime = time (NULL);
    loctime = localtime (&curtime);
    strftime (buffer, 256,"%H:%M:%S - ", loctime);
    printf("%s",buffer);
}

/**
 * Fonction attenteClient()
 * temporisation aléatoire calculée sur base de l'Id du vendeur
 * Entrée: entier, Id de l'appel
 */

void attenteClient(int* Id)
{
    int tempo = (float)rand()/RAND_MAX * (*Id) * 100 + 100;
    usleep(10000*tempo);
}

/**
 * Fonction vendeurTicket()
 * Décrémente le nombre de tickets restants dans une section protégée
 * par un mutex et affiche l'heure, l'Id du vendeur et le nombre
 * de tickets restants
 */

void* vendeurTicket(void* VendeurID)
{

    int finTicket=1;

    while (finTicket == 1)
    {

        attenteClient((int*) VendeurID);
        sem_wait(&sem);
        if (NbTicket > 0)
        {
            //usleep(1000000);
            NbTicket--;
            printTime();
            printf("Vendeur %d : il reste %d tickets\n",  (*(int*)VendeurID), NbTicket);
        }
        else finTicket = 0;

        sem_post(&sem);
    }
    pthread_exit(NULL);

    return NULL;
}


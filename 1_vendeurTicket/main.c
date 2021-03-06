/**
 * Programme : vendeurTicket
 * Auteur: Sami Metoui
 * Description: exécute la fonction vendeurTickets()
 * tant qu'il y a des tickets à vendre.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NB_TICKET 10
#define NB_VENDEUR 5

int NbTicket = NB_TICKET;
void attenteClient();
void vendeurTicket(int);
void printTime();
void attenteClient(int);
void vendeurTicket(int);

/**
 * MAIN
 */

int main(int argc, char *argv[])
{
    int i;
    do
    {
        for (i = 0; i < NB_VENDEUR; i++) vendeurTicket(i);
    }
    while (NbTicket > 0);
    printf("\nSOLD OUT !\n");
    system("PAUSE");
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
 * temporisation aléatoire calculée sur base d'un entier
 * Entrée: entier, Id de l'appel
 */

void attenteClient(int Id)
{
    int tempo = (float)rand()/RAND_MAX * Id * 100 + 100;
    usleep(10000*tempo);
}

/**
 * Fonction vendeurTicket()
 * Décrémente le nombre de tickets et affiche l'heure,
 * l'Id du vendeur et le nombre de tickets restants
 */

void vendeurTicket(int VendeurID)
{
    attenteClient(VendeurID);
    NbTicket--;
    printTime();
    printf("Vendeur %d : il reste %d tickets\n", VendeurID, NbTicket);
}

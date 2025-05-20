#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>

#define OBRADA_DAT "obrada.txt"
#define STATUS_DAT "status.txt"

int trenutni_broj = 1;

void handle_sigusr1(int sig) {
    printf("Trenutni broj koji se koristi u obradi: %d\n", trenutni_broj);
}

void handle_sigterm(int sig) {
    FILE *status_file = fopen(STATUS_DAT, "w");
    if (status_file == NULL) {
        perror("Otvaranje status.txt");
        exit(1);
    }
    fprintf(status_file, "%d\n", trenutni_broj);
    fclose(status_file);
    printf("Zatvaranje programa, trenutni broj je: %d\n", trenutni_broj);
    exit(0);
}

void handle_sigint(int sig) {
    FILE *status_file = fopen(STATUS_DAT, "w");
    if (status_file == NULL) {
        perror("Otvaranje status.txt");
        exit(1);
    }
    fprintf(status_file, "0\n");
    fclose(status_file);
    printf("Program prekinut, status postavljen na 0.\n");
    exit(0);
}

int zadnji_broj_obrada() {
    FILE *obrada_file = fopen(OBRADA_DAT, "r");
    if (obrada_file == NULL) {
        return 0; 
    }
    int zadnji = 0;
    int broj;
    while (fscanf(obrada_file, "%d", &broj) != EOF) {
        zadnji = broj;
    }
    fclose(obrada_file);
    return zadnji;
}

int main() {
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGTERM, handle_sigterm);
    signal(SIGINT, handle_sigint);

    int zadnji = zadnji_broj_obrada();

    if (zadnji > 0) {
        trenutni_broj = (int)sqrt(zadnji) + 1;  
    } else {
        trenutni_broj = 1;
    }

    while (1) {
        FILE *status_file = fopen(STATUS_DAT, "w");
        if (status_file == NULL) {
            perror("Otvaranje status.txt");
            return 1;
        }
        fprintf(status_file, "0\n"); 
        fclose(status_file);

        FILE *obrada_file = fopen(OBRADA_DAT, "a");
        if (obrada_file == NULL) {
            perror("Otvaranje obrada.txt");
            return 1;
        }

        fprintf(obrada_file, "%d\n", trenutni_broj * trenutni_broj);  
        fclose(obrada_file);

        printf("Kvadrat broja %d upisan u obrada.txt\n", trenutni_broj);
        trenutni_broj++;  

        sleep(5);  
    }
    
    return 0;
}


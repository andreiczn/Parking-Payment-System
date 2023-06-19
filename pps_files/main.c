#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLATE_LENGTH 10
#define MAX_LOCATION 50

int main() {
    //FILE *f;
    //f = fopen("istoric_plati.txt", "a"); // fisierul de istoric, deschis in modul append

    while (1) {
        // meniu principal
        int option_choice = 0;
        system("cls");
        printf("Meniu\n");
        printf("\n");
        printf("Buna ziua! Ati accesat sistemul de plata online a parcarii.\n");
        printf("Va rugam selectati una dintre urmatoarele optiuni, tastand cifra corespunzatoare acesteia:\n");
        printf("\n");
        printf("\n1. Catre plata parcarii\n");
        printf("2. Catre istoricul platilor dumneavoastra\n");
        printf("\n");
        printf("Introduceti optiunea dvs, apoi apasati enter: ");
        do {
            scanf("%d", &option_choice);
        } while (option_choice < 1 || option_choice > 2);

        // 1.plata parcarii
        if (option_choice == 1) {

            // alegerea zonei
            float priceperhr = 0;
            int zone_choice = 0;
            char zona[10];
            system("cls");
            do {
                printf("Dintre urmatoarele zone, selectati-o pe cea dorita:\n");
                printf("\n");
                printf("1. zona galbena (1 RON/hr)\n");
                printf("2. zona rosie (1.5 RON/hr)\n");
                printf("3. zona verde (2 RON/hr)\n");
                printf("\n");
                printf("Pentru anularea procesului si revenirea la meniul principal, tastati 0.\n");
                printf("Introduceti optiunea dvs, apoi apasati enter: ");
                scanf("%d", &zone_choice);
            } while (zone_choice < 0 || zone_choice > 3);
            if (zone_choice == 0) {
                option_choice = 0;
                continue; // inapoi la meniul principal
            } else if (zone_choice == 1) {
                priceperhr = 1;
                strcpy(zona, "galbena");
            } else if (zone_choice == 2) {
                priceperhr = 1.5;
                strcpy(zona, "rosie");
            } else if (zone_choice == 3) {
                priceperhr = 2;
                strcpy(zona, "verde");
            }

            fflush(stdin);

            //introducere strada/locatie
            system("cls");
            char locatie[MAX_LOCATION] = {};
            int return1 = 0;
            do{
                printf("Introduceti numele strazii/zonei corespunzatoare locatiei autovehiculului dvs (ex: Strada Popa Sapca),\napoi apasati enter:\n");
                printf("Pentru anularea procesului si revenirea la meniul principal, apasati 0.\n");
                fgets(locatie, 50, stdin);
                locatie[strcspn(locatie, "\n")] = 0;
                //fflush(stdin);
                if(strcmp(locatie, "0") == 0){
                    return1 = 1;
                    break;
                }
            } while(strlen(locatie) <0);
            if(return1)
                continue;

            fflush(stdin);

            //introducere numar de inmatriculare
            system("cls");
            char license_plate[MAX_PLATE_LENGTH] = {};
            int return_to_main = 0;
            do {

                printf("Introduceti numarul de inmatriculare al vehiculului dvs (ex. TM99XYZ sau B999ABC), apoi apasati enter:\n");
                printf("Pentru anularea procesului si revenirea la meniul principal, apasati 0.\n");
                scanf("%s", license_plate);
                if (strcmp(license_plate, "0") == 0) {
                    return_to_main = 1;
                    break; // înapoi la meniul principal
                    }
            } while (strlen(license_plate) != 7);
            if (return_to_main)
                continue;


            // introducerea duratei parcarii si calcularea timpului in functie de aceasta
            system("cls");
            unsigned int parktime;
            unsigned int initialparktime;
            float price = 0;
                    do {
            printf("Introduceti durata intervalului parcarii, in minute: \n");
            printf("Pentru anularea procesului si revenirea la meniul principal, tastati 0.\n");
            printf("\n");
            printf("Optiunea dvs:");

            scanf("%d", &parktime);
            initialparktime = parktime;
            if (parktime == 0) {
                continue;
            } else if (parktime <= 60) {
                price = priceperhr;
            } else {
                while (parktime > 60) {
                    price = price + priceperhr;
                    parktime = parktime - 60;
                }
                price = price + priceperhr;
            }
        } while (parktime < 0);
        if (parktime == 0) {
            printf("Programul revine la meniul principal.\n");
            continue;
        }

        // adaugarea datelor in fisier
        FILE *fp;
        fp = fopen("istoric_plati.txt", "a");
        if (fp == NULL) {
            printf("Eroare la deschiderea fisierului!\n");
            exit(1);
        }
        fprintf(fp, "Nr. Inmatriculare: %s, Zona: %s, %s, Durata Parcarii: %d minute, Pret: %.2f RON\n", license_plate, zona, locatie, initialparktime, price);
        fclose(fp);

        // confirmare sau anulare
        system("cls");
        printf("Urmeaza sa achitati suma de %.2f RON pentru parcarea autovehiculului cu numarul de inmatriculare ", price);
        int i = 0;
        for (i = 0; i < strlen(license_plate); i++) {
            printf("%c", license_plate[i]);
        }
        printf("\n");
        printf("pe zona ");
        for (i = 0; i < strlen(zona); i++) {
            printf("%c", zona[i]);
        }
        printf(", pe durata de %d minute. Tastati 1 pentru a confirma tranzactia,\nsau 0 pentru a anula procesul si a reveni la meniul principal: ", initialparktime);
        int fin;
        scanf("%d", &fin);
        if (fin == 1) {
            system("cls");
            printf("Tranzactia dumneavoastra a fost inregistrata si va putea fi vizualizata in meniul istoricului in curand.\n");
            printf("O zi buna! :)");
            break;
        } else if (fin == 0) {
            continue;
        }
    }
    //istoricul parcarilor si al platilor efectuate
    else if (option_choice == 2) {
        system("cls");
        printf("Istoricul platilor dumneavoastra:\n\n");

        FILE *fp;
        char line[100];
        fp = fopen("istoric_plati.txt", "r");
        if (fp == NULL) {
            printf("Nu exista inca nicio tranzactie inregistrata.\n");
        } else {
            while (fgets(line, sizeof(line), fp)) {
                printf("%s", line);
            }
            fclose(fp);
        }

        printf("\n\nApasati orice tasta pentru a reveni la meniul principal.");
        fflush(stdin);
        getchar();
        continue;
    }
}
return 0;
}

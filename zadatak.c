#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define HEX_BUFFER_SIZE 3 

// Pretvorbu stringa u heksadecimalni format
void stringToHex(const char *str, char *hexStr) {
    while (*str) {
        sprintf(hexStr, "%02X", (unsigned char)*str);
        hexStr += 2;
        str++;
    }
    *hexStr = '\0'; // Završni null karakter
}

// Formatiranje datuma u obliku DD-MM-YYYY
void formatDate(char *date) {
    char formattedDate[11];
    snprintf(formattedDate, sizeof(formattedDate), "%.2s-%.2s-%s", date + 0, date + 3, date + 6);
    strcpy(date, formattedDate);
}

// Učitavanje CSV datoteke i obradu podataka
void processCSVFile(const char *inputFile, const char *outputFile) {
    FILE *file;
    while (1) {
        file = fopen(inputFile, "r");
        if (file) break;
        perror("Nije moguće otvoriti ulaznu datoteku");
        printf("Unesite ispravnu putanju do ulazne CSV datoteke: ");
        scanf("%s", inputFile);
    }

    FILE *outFile = fopen(outputFile, "w");
    if (!outFile) {
        perror("Nije moguće otvoriti izlaznu datoteku");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    char ime[100], prezime[100], datum[11];
    char imeHex[200], prezimeHex[200], datumHex[100];

    printf("%-20s %-20s %-20s %-20s %-20s %-20s\n", "Ime", "Prezime", "Datum rodenja", "Ime (hex)", "Prezime (hex)", "Datum (hex)");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%99[^,],%99[^,],%10s", ime, prezime, datum) == 3) {
            formatDate(datum);
            stringToHex(ime, imeHex);
            stringToHex(prezime, prezimeHex);
            stringToHex(datum, datumHex);
            
            printf("%-20s %-20s %-20s %-20s %-20s %-20s\n",  strupr(ime),  strupr(prezime), datum, imeHex, prezimeHex , datumHex);
            
            fprintf(outFile, "%s %s %s %s %s %s\n", ime, prezime, datum, imeHex, prezimeHex , datumHex);
        }
    }

    printf("\nPodaci su obradeni i spremljeni u '%s'.\n", outputFile);

    fclose(file);
    fclose(outFile);
}

int main() {
    char inputFile[200], outputFile[200];

    printf("Unesite putanju do ulazne CSV datoteke: ");
    scanf("%s", inputFile);
    printf("Unesite putanju do ili za kraciju izlazne CSV datoteke: ");
    scanf("%s", outputFile);

    processCSVFile(inputFile, outputFile);

    return 0;
}
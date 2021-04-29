/*  Ankit Das
    Sequential File Organization in C */

#include <stdio.h>

#define RECORD_COUNT 3
#define FILENAME "students.dat"
#define FILE_READ_FORMAT "%s %lli"         
#define FILE_WRITE_FORMAT "%s %lli\n" 
#define PRINT_FORMAT "NAME: %s \nPRN: %lli"

typedef struct {
    char name[20];
    long long int prn;
} Student;

int search(long long int prn) {
    FILE *fin = fopen(FILENAME, "r");

    if (fin == NULL) {
        return 0;                          
    }

    Student student;
    while (fscanf(fin, FILE_READ_FORMAT, &student.name, &student.prn) != EOF) {
        if (prn == student.prn) {
            printf("\nRECORD FOUND!\n");
            printf(PRINT_FORMAT, student.name, student.prn);
            fclose(fin);
            return 1;
        }
    }

    fclose(fin);
    printf("\nRECORD NOT FOUND\n");
    return 1;
}

int main() {
    FILE *fout = fopen(FILENAME, "w");
    long long int prn;
    unsigned int choice = 0;

    if (fout == NULL) {
        printf("ERROR OPENING FILE!");
        return 1;
    }

    for (int i = 0; i < RECORD_COUNT; ++i) {
        Student student;
        printf("ENTER NAME: ");
        scanf("%s", &student.name);
        printf("ENTER PRN: ");
        scanf("%lli", &student.prn);

        fprintf(fout, FILE_WRITE_FORMAT, student.name, student.prn);
    }
    
    fclose(fout);
    
    while(1){  
        printf("\n1. SEARCH\n");
        printf("2. EXIT\n");
        printf("ENTER CHOICE: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("ENTER PRN: ");
                scanf("%lli", &prn);
                if(search(prn)){
                    break;
                }
            
            case 2:
                return 0;
        }
    }

    return 0;
}

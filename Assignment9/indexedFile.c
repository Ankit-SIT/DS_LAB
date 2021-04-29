/* Ankit Das
   Indexed File Organization in C */

#include<stdio.h>

#define SIZE_MAX 10
#define RECORD_FILE_NAME "records.dat"
#define INDEX_FILE_NAME "index.dat"
#define PRINT_FORMAT "\nNAME: %s \nKEY: %d\n"

typedef struct Record {
	char name[10];
	int key;
} Record;  

void createIndex(long index[], int key, long relativeAddress){
	index[key] = relativeAddress;
}

void writeRecord(FILE *file, Record record){
	fwrite(&record, sizeof(record),1 ,file);
}

int main(){
	long relativeAddress;
	int key;
    int choice;
    int i;
    int create;

	Record record;
	long index[SIZE_MAX];
	
	FILE *recordFile = NULL;
    FILE *indexFile = NULL;

	for(i = 0; i < SIZE_MAX; i++)
		index[i] = -1;
	
	recordFile = fopen(RECORD_FILE_NAME, "w");
	relativeAddress = 0;
	
	while(create){
        printf("1. ADD\n");
        printf("2. RETRIEVE\n");
        printf("ENTER CHOICE: ");
        scanf("%d", &choice); 

        switch(choice){
            case 1:
                while(1){
		        	printf("ENTER NAME: ");
		            scanf("%s", record.name);
                    printf("ENTER KEY: ");
                    scanf("%d", &record.key);

                    printf("\n");
                    if(index[record.key] != -1)
                        printf("KEY EXISTS! TRY AGAIN!\n");

                    else 
                        break;
		        }

                createIndex(index, record.key, relativeAddress);
		        writeRecord(recordFile, record);
		        relativeAddress = ftell(recordFile);
                break;

		    case 2:
                create = 0;
                break;
        }
	}

	indexFile = fopen(INDEX_FILE_NAME, "w");
	fwrite(index, sizeof(index), 1, indexFile);
	fclose(recordFile);
	fclose(indexFile);


    while(1) {    
	    printf("1. DISPLAY\n");
        printf("2. RETRIEVE\n");
        printf("3. EXIT\n");
        printf("ENTER CHOICE: ");
        scanf("%d", &choice); 

		indexFile = fopen(INDEX_FILE_NAME,"r");
		fread(index, sizeof(index), 1, indexFile);
		fclose(indexFile);

	    recordFile = fopen(RECORD_FILE_NAME, "r");
        
        switch(choice){
            case 1:
	    	    while(fread(&record,sizeof(record),1,recordFile) != 0){
	    		    printf(PRINT_FORMAT, record.name, record.key);
                }
                break;

            case 2:
	    		printf("ENTER KEY: ");
	    		scanf("%d", &key);
	    		relativeAddress = index[key]; 
	    		if((fseek(recordFile, relativeAddress,SEEK_SET)) != 0){
	    			printf("RECORD NOT FOUND!\n");
	    			break;
	    		}
	    		fread(&record, sizeof(record), 1, recordFile);
	    		printf(PRINT_FORMAT, record.name, record.key);	
                break;
                
            case 3:
                printf("EXITING! \n");
	    	    fclose(recordFile);
                return 0;

            default:
                printf("\nINVALID CHOICE! TRY AGAIN!\n");
        } 
    }  
}

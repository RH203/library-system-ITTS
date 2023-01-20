#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define book
#define MAX_TITLE_BOOK 75
#define MAX_AUTHOR 75
#define MAX_CATEGORY 75
#define MAX_SIZE_BOOK 75
//define book

//define data
#define MAX_NAME_STUDENTS 25
//define data

//struct
typedef struct
{
    char titleBook[MAX_TITLE_BOOK];
    char authorBook[MAX_AUTHOR];
    char categoryBook[MAX_CATEGORY];
    int codeBook;
}Book;


//struct


void add(Book x[],int total){         // add (1)
    for(int i = 0; i < total; i++){
        fflush(stdin);
        printf("Masukan Judul Buku ke-%d: ", i + 1);
        scanf("%[^\n]s", x[i].titleBook);
        fflush(stdin);
        printf("Masukan Penulis Buku: ");
        scanf("%[^\n]s", x[i].authorBook);
        fflush(stdin);
        printf("Masukan Kategori Buku: ");
        scanf("%[^\n]s", x[i].categoryBook);
        fflush(stdin);
        printf("Masukan Kode Buku: ");
        scanf("%d", &x[i].codeBook);
    }
}

void see_data(Book* x, int* total) {
    FILE* file = fopen("data-book.txt", "r");
    if (file == NULL) {
        perror("Failed: ");
        return;
    }
    *total = 0;
    while(fscanf(file, "%[^,], %[^,], %[^,], %d", x[*total].titleBook, x[*total].authorBook, x[*total].categoryBook, &x[*total].codeBook) == 4) {
      (*total)++;  
    }
    fclose(file);
}

void output_see(Book x[], int y){
    for(int i = 0; i < y; i++){
        printf("Nomor: %d\n", i+1);
        printf("Title: %s\n", x[i].titleBook);
        printf("Author: %s\n", x[i].authorBook);
        printf("Category: %s\n", x[i].categoryBook);
        printf("Code: %d\n", x[i].codeBook);
        printf("\n");
    }
}


void save(Book* x, int total){ // save(3) = save data yang diinput kedalam data-book.txt
    FILE* file = fopen("data-book.txt", "a");
    if(file == NULL){
        perror("failed: ");
    }

    for(int i = 0; i < total; i++){
        fprintf(file, "%s, %s, %s, %d\n", x[i].titleBook, x[i].authorBook, x[i].categoryBook, x[i].codeBook);
    }
    fclose(file);
    printf("\nData saved successfully to database");
}

void change(Book x[], int y){
    int index_data;
    fflush(stdin);
    printf("Enter the data number you want to change: ");
    scanf("%d", &index_data);
    fflush(stdin);

    // ganti data
    printf("Masukan Judul baru: ");
    scanf("%[^\n]s", x[index_data - 1].titleBook);
    fflush(stdin);
    printf("Masukan Author buku baru: ");
    scanf("%[^\n]s", x[index_data - 1].authorBook);
    fflush(stdin);
    printf("Masukan Category buku baru: ");
    scanf("%[^\n]s", x[index_data - 1].categoryBook);
    fflush(stdin);
    printf("Masukan Kode buku baru: ");
    scanf("%d", &x[index_data - 1].codeBook);
    fflush(stdin);
}


void search(Book x[], int total){
    fflush(stdin);
    int searchCode, found = 0;
    printf("Masukan Code buku: \n");
    scanf("%d", &searchCode);

    for(int i = 0; i < total; i++){
        if(searchCode == x[i].codeBook){
            printf("Buku ditemukan di urutan ke-%d\n", i+1);
            printf("Title: %s\n", x[i].titleBook);
            printf("Author: %s\n", x[i].authorBook);
            printf("Category: %s\n", x[i].categoryBook);
            printf("Code: %d\n", x[i].codeBook);
            found = 1;
        }
    }
    if(!found){
        printf("The book code you are looking for doesn't exist, please read the book data first");
    }
}

void sort(Book x[], int total){
    for(int i = 0; i < total; i++){
        for(int j = 1 + i; j < total; j++){
            if(strcmp(x[i].titleBook, x[j].titleBook) > 0){
                Book temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    for(int i = 0; i < total; i++){
        printf("Nomor buku ke-%d\n", i+1);
        printf("Title: %s\n", x[i].titleBook);
        printf("Author: %s\n", x[i].authorBook);
        printf("Category: %s\n", x[i].categoryBook);
        printf("Code: %d\n", x[i].codeBook);
        printf("\n");
    }
}

int totalBook(char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed: ");
        return 0;
    }
    int count = 0;
    char buffer[MAX_SIZE_BOOK];
    while(fgets(buffer, MAX_SIZE_BOOK, file) != NULL){
      count++;  
    }
    fclose(file);
    return count;
}



int main (){
    //declare
    char password[25] = "admin", username[25] = "admin";
    char checkPass[25], checkUser[25], back_menu, contentFile[100];
    Book data[MAX_SIZE_BOOK];
    FILE* file;
    int menu_program, jumlah, limit = 0, num_totalBook;
    //declare

    do{
        printf("Input Username: ");
        scanf("%s", checkUser);
        printf("\nInput Password: ");
        scanf("%s", checkPass);
        if(strcmp(checkUser, username) == 0 && strcmp(checkPass, password) == 0){
            printf("\tSuccessful Login!\n");
            break;
        }else{
            printf("Password or Username wrong!\n");
        }
        limit++;
    }while(limit < 3);
    
    if(limit > 3){
        printf("\nToo many request, please try again in 30 sec!");
    }

    do{
        if(limit < 3){
            printf("\n\t================================================");
            printf("\n\tLibrary System Institut Teknologi Telkom Surabaya");
            printf("\n\t================================================");
            printf("\n\t1. Add Data");
            printf("\n\t2. Read Data");
            printf("\n\t3. Change/Update Data");
            printf("\n\t4. Search Data");
            printf("\n\t5. Sort Data");
            printf("\n\t6. Count how many books are in the database");
            printf("\n\t0. Exit");
            printf("\n\tInput Menu: ");
            scanf("%d", &menu_program);
                }

            switch (menu_program){
            case 1:
                printf("\nHow many books will be input: ");
                scanf("%d", &jumlah);
                fflush(stdin);
                add(data, jumlah);
                save(data, jumlah);
            break;
            case 2:
                see_data(data, &jumlah);
                output_see(data, jumlah);
                break;
            case 3:
                file = fopen("data-book.txt", "w");
                change(data, jumlah);
                    // simpen data
                    if(file == NULL){
                        perror("Failed: ");
                    }
                    for(int i = 0; i < jumlah; i++){
                        fprintf(file, "%s, %s, %s, %d\n", data[i].titleBook, data[i].authorBook, data[i].categoryBook, data[i].codeBook);
                    }
                    fclose(file);
                break;
            case 4:
                search(data, jumlah);
                break;
            case 5:
                see_data(data, &jumlah);
                sort(data, jumlah);
                file = fopen("data-book.txt", "w");
                if(file == NULL){
                    printf("File doesn't exist");
                }
                for(int i = 0; i < jumlah; i++){
                    fprintf(file, "%s, %s, %s, %d\n", data[i].titleBook, data[i].authorBook, data[i].categoryBook, data[i].codeBook);
                    }
                    fclose(file);
                break;
            case 6:
                num_totalBook = totalBook("data-book.txt");
                printf("The total number of books in the current database: %d Book", num_totalBook);
                break;
            default:
                break;
            }
        }while(menu_program != 0);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAXC 512    /* sabitler tanimlanir */
#define MAXR (MAXC + 1) / 2
#define MAXV 200


//belirli bir aralik icinde random sayi olusturmak icin fonksiyon
size_t generateRandom(size_t lower, size_t upper)
{
    int i;

    size_t num = (rand() %
                  (upper - lower + 1)) + lower;
    return num;
}



//ciktiyi istenilen sure kadar bekletmek icin fonksiyon
void delay(int number_of_seconds)
{
    int milli_seconds = 1 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds)
        ;
}

//Labirenti DFS icinde gezerken yazdirmak icin kullanilan fonksiyon
void printMazeDfs(char a[][MAXC + 1], size_t row, size_t nrow, size_t col, size_t ncol, size_t i, size_t k){
    for (row = 0; row < nrow; row++) {
        for (col = 0; col < ncol; col++) {

            a[i][k] = '*';
            putchar (a[row][col]);
        }
        putchar ('\n');
    }

}

//Labirenti yazdirmak icin kullanilan fonksiyon
void printMazeNormal(char a[][MAXC + 1], size_t row, size_t nrow, size_t col, size_t ncol){
    for (row = 0; row < nrow; row++) {
        for (col = 0; col < ncol; col++) {
            putchar (a[row][col]);
        }
        putchar ('\n');
    }

}

//DFS fonksiyonu
void DFS(int matrix[][MAXC+1], size_t starta, size_t startb, size_t n, int visited[][MAXV], char a[][MAXC+1], size_t row, size_t nrow, size_t col,size_t ncol){
    int j;
    int static found = 0; //yolun bulunup bulunmadigini tutan degisken
    int static points = 0; //puanlari tutan degisken
    int count = 0; //toplamda kac yonun acik oldugunu tutan degisken
    if (found == 0){

        system("cls");
        printMazeDfs(a, row, nrow, col, ncol, starta, startb);
        printf("Toplam puan: %d", points);
        delay(100);
        visited[starta][startb] = 1;
        int yukari, asagi, sag, sol;
        //her yon icin dogru yanlis degiskenleri
        yukari = matrix[starta-1][startb];
        asagi = matrix[starta+1][startb];
        sag = matrix[starta][startb+1];
        sol = matrix[starta][startb-1];
        if (yukari == 1){
            count += 1;
        }
        if (sag == 1){
            count += 1;
        }
        if (sol == 1){
            count += 1;
        }
        if (asagi == 1){
            count += 1;
        }
        if((yukari == 1 || yukari == 2) && visited[starta-1][startb] == 0 && found == 0){
            if (yukari == 2) {
                points += 10;
            }
            DFS(matrix, starta-1, startb, n, visited,a, row, nrow, col, ncol);
        } else if (yukari == 4){
            printf("\nBulundu");
            found = 1;
            return;}

        if((sag == 1 || sag == 2) && visited[starta][startb+1] == 0 && found == 0){
            if (sag == 2) {
                points += 10;
            }
            DFS(matrix, starta, startb+1, n, visited, a, row, nrow, col, ncol);
        } else if (sag == 4){
            printf("\nBulundu");
            found = 1;
            return;}

        if((sol == 1 || sol == 2) && visited[starta][startb-1] == 0 && found == 0){
            if (sol == 2) {
                points += 10;
            }
            DFS(matrix, starta, startb-1, n, visited,a, row, nrow, col, ncol);
        }else if (sol == 4){
            printf("\nBulundu");
            found = 1;
            return;}

        if((asagi == 1 || asagi == 2) && visited[starta+1][startb] == 0 && found == 0){
            if (asagi == 2) {
                points += 10;
            }
            DFS(matrix, starta+1, startb, n, visited,a, row, nrow, col, ncol);
        }else if (asagi == 4){
            printf("\nBulundu");
            found = 1;
            return;}


    }
    if(count == 1){
        points -= 5;
    }
}

int main () {
    srand(time(0));
    int i= 0, j =0, k = 0, found = 0;
    int visited[MAXV][MAXV] = {0};
    size_t row = 0, col = 0, nrow = 0, ncol = 0, startrow, startcol, endrow, endcol;
    char a[MAXR][MAXC+1] = {""};

    int b[MAXC+1][MAXC+1];

    FILE *fp = fopen ("maze.txt", "r");

    if (!fp) {  /* dosyanin acilip acilmadigini kontrol et */
        perror ("file open failed");
        return 1;
    }
    printf("+, -, |: Duvar\n"
           "O: Elma\n"
           "*: Izlenilen yol\n");
    while (row < MAXR && fgets (a[row], MAXC, fp)) {
        size_t len = strlen (a[row]);       /* satir sayisi */
        if (len && a[row][len-1] == '\n')   /* diziye sigip sigmadigi kontrol edilir */
            a[row][--len] = 0;  /* \n karakteri cikarilir*/
        else if (len == MAXC) {
            fprintf (stderr, "error: row exceeds %d chars.\n", MAXC);
            return 1;
        }
        if (!row)
            ncol = len;
        if (ncol != len) {
            fprintf (stderr, "hata: (%lu) sutunlar (%lu) satirda esit degil.\n",
                     len, row);
            return 1;
        }
        // matrisi yazdir
        for (col = 0; col < ncol; col++){
            if(a[row][col] == 'b'){
                startrow = row;
                startcol = col;
            }
            else if(a[row][col] == 'c'){
                endrow = row+2;
                endcol = col;
            }
            putchar (a[row][col]);
        }
        putchar ('\n');

        row++;  /* satir sayisini arttir */
    }
    if (fp != stdin) fclose (fp);   /* dosyayi kapat */
    nrow = row;                     /* toplam satir sayisini sakla */


    puts ("\nElmalari labirente yerlestirmek icin entera basin: \n");
    system("pause");
    size_t randomApple = generateRandom(0, 20);
    while (randomApple > 0){
        size_t randomRow = generateRandom(0, nrow-1);
        size_t randomCol = generateRandom(0, ncol-1);
        if(randomCol && a[randomRow][randomCol] == ' ' && (a[randomRow][randomCol+1] != '+' || a[randomRow][randomCol-1] != '+')){
            a[randomRow][randomCol] = 'O';
            randomApple = randomApple-1;
        }
    }
    printMazeNormal(a, row, nrow, col, ncol);
    printf("\nYol bulmak icin herhangi bir tusa basin: \n");
    system("pause");


    for (row = 0; row < nrow; row++) {
        for (col = 0; col < ncol; col++) {
            if (a[row][col] == '+' || a[row][col] == '-' || a[row][col] == '|'){
                b[row][col] = 0;
            }
            else if(a[row][col] == 'b'){
                b[row][col] = 3;
            }
            else if(a[row][col] == 'c'){
                b[row][col] = 4;
            }
            else if(a[row][col] == 'O'){
                b[row][col] = 2;
            }
            else{
                b[row][col] = 1;
            }
        }
    }

    size_t man;
    man = nrow*ncol;
    DFS(b, startrow, startcol,man, visited, a, row, nrow, col, ncol);

    return 0;
}



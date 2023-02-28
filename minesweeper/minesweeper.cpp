// minesweeper.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

//#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define BMAGENTA   "\x1B[95m"
#define COLOR0 "\x1B[93m"
#define REDBG "\x1B[41m"
#define RESET "\x1B[0m"

int *pointeurSize = NULL;

/*const int size = 10;
int grid[size][size];
char display[size][size];*/
int toPlace;

// compter le nombre de mines adjacentes à une case
int countNearby(int row, int col, int size, int** grid, char** display) {
    int R, C, count;
    count = 0;
    for (R = -2; R < 1; R++) {
        for (C = -2; C < 1; C++)
        {
            if (!(row + R < 0 || col + C < 0)) {
                if (row + R < size && col + C < size) {
                    if (grid[row + R][col + C] == 1 && !(R == -1 && C == -1)) {
                        count++;
                        //printf("[%d][%d] TRUE %d %d\n", row + R, col + C, R, C);
                    }
                }
            }
        }
    }
    //convertir int en string
    char nearby = count + '0';
    display[row-1][col-1] = nearby;

    //si il n'y a aucune mine autour, découvrir les cases adjacentes
    if (count == 0) {
        int rRelativeToInput, cRelativeToInput;
        for (rRelativeToInput = -2; rRelativeToInput < 1; rRelativeToInput++) {
            for (cRelativeToInput = -2; cRelativeToInput < 1; cRelativeToInput++) {
                if (!(row + rRelativeToInput < 0) && !(col + cRelativeToInput < 0) && (row + rRelativeToInput < size) && (col + cRelativeToInput < size)) {
                    if (display[row + rRelativeToInput][col + cRelativeToInput] == '?' || display[row + rRelativeToInput][col + cRelativeToInput] == 'F') {
                        //printf("\nCalling countNearby(%d,%d)\n", row + rRelativeToInput + 1, col + cRelativeToInput + 1);
                        countNearby(row + rRelativeToInput + 1, col + cRelativeToInput + 1, size, grid, display);
                    }
                }
                
            }
        }
    }
    return(count);
}


bool checkWin(int size, char** display) {
    int count, row, col;
    count = 0;
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (display[row][col] == '?' || display[row][col] == 'F') {
                count++;

            }
        }

    }
    if (count == toPlace) {
        return true;
    }
    else {
        return false;
    }

}

void showgrid(int** adress, int size)
{
    int row, col;
    for (row = -1; row < size; row++) {
        //printf("ROW: %d\n", row);
        for (col = -1; col < size; col++) {
            if (row == -1) {
                printf("%d ", col + 1);
            }
            else if (col == -1) {
                printf("%d ", row + 1);
            }
            else if (adress[row][col] == 1) {
                printf("\033[22;31m%i\033[0m ", adress[row][col]);
            }
            else if (adress[row][col] == 0) {
                printf("%i ", adress[row][col]);
            }
            
            if (col == size - 1) {
                printf("\n");
            }
        }

        
    }
}

void showdisplay(char** display, int size) {
    // display
    for (int row = -1; row < size; row++) {
        for (int col = -1; col < size; col++) {
            if (row == -1) {
                printf(BMAGENTA "%d " RESET, col + 1);
            }
            else if (col == -1) {
                if (size > 99) {
                    if (row==99) {
                        printf(BMAGENTA "%d " RESET, row + 1);
                    }
                    else if (row > 8) {
                        printf(BMAGENTA "%d  " RESET, row + 1);
                    }
                    else {
                        printf(BMAGENTA "%d   " RESET, row + 1);
                    }
                }
                else if(size > 9){
                    if (row == 9) {
                        printf(BMAGENTA "%d " RESET, row + 1);
                    }
                    else {
                        printf(BMAGENTA "%d  " RESET, row + 1);
                    }
                } else {
                    printf(BMAGENTA "%d " RESET, row + 1);
                }
            }
            else {
                if (display[row][col] == 'F') {
                    printf(REDBG "%c" RESET " ", display[row][col]);
                }
                else if (display[row][col] == '?' /* || display[row][col] == '0'*/) {
                    printf("%c ", display[row][col]);
                }
                else {
                     switch (display[row][col])
                     {
                     case '0':
                         printf(COLOR0 "%c " RESET, display[row][col]);
                         break;
                     case '1':
                         printf(BLUE "%c " RESET, display[row][col]);
                         break;
                     case '2':
                         printf(GREEN "%c " RESET, display[row][col]);
                         break;
                     case '3':
                         printf(RED "%c " RESET, display[row][col]);
                         break;
                     case '4':
                         printf(MAGENTA "%c " RESET, display[row][col]);
                         break;
                     case '5':
                         printf(YELLOW "%c " RESET, display[row][col]);
                         break;
                     case '6':
                         printf(CYAN "%c " RESET, display[row][col]);
                         break;
                     default:
                         printf("%c ", display[row][col]);
                         break;
                     }
                }
            
            }
            if (col == size - 1) {
                printf("\n");
            }
        }
    }
}

void reveal(char** display, int** grid, int size) { //cherche un endroit avec 0 mines autour et le reveal (marche pas)

    int count = 0;
    for (int row = -1; row < size; row++) {
        for (int col = -1; col < size; col++) {
            for (int R = -2; R < 1; R++) {
                for (int C = -2; C < 1; C++)
                {
                    if (!(row + R < 0 || col + C < 0)) {
                        if (row + R < size && col + C < size) {
                            if (grid[row + R][col + C] == 0 && !(R == -1 && C == -1)) {
                                count++;
                                //printf("[%d][%d] TRUE %d %d\n", row + R, col + C, R, C);
                            }
                        }
                    }
                }
            }
            if (count > 1) {
                printf("found at: [%d][%d]", row, col);
                countNearby(row + 1, col + 1, size, grid, display);
            }
        }
    }
}

int main() {
    bool lost = false;
    int difficulty = 0;
    int size=10;
    
    printf("Choisir une taille pour la grille de jeu: ");
    scanf_s("%d", &size);

    /* initialisation de la grid */
    int** grid = (int **)malloc(size * sizeof(int*)); // initialise les rows qui vont contennir les colonnes

    for (int num = 0; num < size; num++) {
        int* col = (int *)malloc(size * sizeof(int)); //initialise les array des colonnes
        grid[num] = col; //mettre la colone dans la row
    }
    // valeurs de base
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            grid[row][col] = 0;
        }
    }

    // initialisation de la grille display
    char** display = (char **)malloc(size * sizeof(char*)); // initialise les rows qui vont contennir les colonnes

    for (int num = 0; num < size; num++) {
        char* col = (char*)malloc(size * sizeof(char)); //initialise les array des colonnes
        display[num] = col; //mettre la colone dans la row
    }
    // valeurs de base
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (display[row][col]) {
                display[row][col] = '?';
            }
        }
    }

    printf("Size: %dx%d", size, size);


    int row, col;
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            grid[row][col] = 0;
        }
    }
    // grid à afficher
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            display[row][col] = '?';
        }
    }

    //populate with mines
    printf("\nChoisir la difficulte (entre 0 et 3): ");
    scanf_s("%d", &difficulty);

    //change number of mines depending on difficulty
    switch (difficulty)
    {
    case 1:
        printf("\nDifficulty: Easy\n");
        printf("\nSize: %d", size);
        toPlace = (size*size)/6;
        break;
    case 2:
        printf("\nDifficulty: Medium\n");
        toPlace = (size * size) / 5;
        break;
    case 3:
        printf("\nDifficulty: Hard\n");
        toPlace = (size * size) / 4;
        break;
    default:
        printf("\nChoisir la difficulte (entre 0 et 3): ");
        scanf_s("%d", &difficulty);
        break;
    }

    // RNG
    srand(time(NULL));
    int placed;
    printf(" Mines: \033[22;31m%d\033[0m\n", toPlace);
    // Randomly place mines
    for (placed = 0; placed < toPlace; placed++) {
        int rr = rand() % size;
        int rc = rand() % size;
        //no duplicates
        if (grid[rr][rc] == 0)
        {
            grid[rr][rc] = 1;
            //printf("%d, %d\n", rr, rc);
        }
        else {
            placed = placed - 1;
        }
    }

    while (!lost)
    {
        // display
        showgrid(grid, size);
        system("cls"); //clear console
        showdisplay(display, size);
        //reveal(display, grid, size);

        int inputR, inputC;
        char option;
        bool valide = false;
        while (!valide) {
            // récupérer les coordonnées
            printf("\nEntrez les coordonees de la case ainsi: Ligne Colone (and flag)\nex: 1 3\n");
            scanf_s("%d %d %c", &inputR, &inputC, &option);
            // Check si la case est valide
            if ((inputC <= size && inputC > 0) && (inputR <= size && inputR > 0)) {
                valide = true;
                if (option == 'f') {
                    printf("test");
                    if (display[inputR - 1][inputC - 1] == 'F') {
                        printf("F");
                        display[inputR - 1][inputC - 1] = '?';
                    } else {
                        display[inputR - 1][inputC - 1] = 'F';
                    }
                }
                printf("\noption: %c\n", option);
            }
            else { // redemander si elle ne l'est pas
                printf("\nCoordonees invalides, reessayez\n");
            }
        }
        // check si la case à été découverte
        if (display[inputR - 1][inputC - 1] == '?') {
            if (grid[inputR - 1][inputC - 1] == 1) {
                if (option != 'f') {
                    display[inputR - 1][inputC - 1] = 'X';
                    lost = true;
                    printf("\nPERDU!\n");
                }
            }
            else if (option != 'f'){
                countNearby(inputR, inputC, size, grid, display);
            }
        }
        if (checkWin(size, display)) {
            printf("\n Bravo, vous avez gagné! \n");
            return(0);
        }


        //CHECK FOR MINES
        /*if (grid[inputR - 1][inputC - 1] == 1) {
            lost = true;
            printf("Perdu !");
        }*/
    }
    free(display);
    free(grid);
    return 0;
}

/* int main()
{
    //création de 'pi' sur le tas
    int ** pi = (int **) malloc(sizeof(int*) * 10);
    for(int i = 0; i < 10; ++i)
    {
        pi[i] = (int*) malloc(sizeof(int) * 10);
    }

    //destruction manuelle de 'pi'
    free(pi);

    return 0;
} 
*/

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
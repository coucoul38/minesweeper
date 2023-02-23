// minesweeper.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

//#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int size = 10;
int grid[size][size];
char display[size][size];

// compter le nombre de mines adjacentes à une case
int countNearby(int row, int col) {
    int R, C, count;
    count = 0;
    for (R = -1; R < 2; R++) {
        for (C = -1; C < 2; C++)
        {
            if (!(row + R < 0 || col + C < 0)) {
                //printf("Checking coordinates [%d][%d]", row + R, col + C);
                if (grid[row + R][col + C] == 1) {
                    count++;
                }
            }
        }
    }
    //printf("\nNearby: %d\n", count);
    // display le nombre
    //convertir int en string
    char nearby = count + '0';
    //printf("\n Changing [%d][%d]\n", row, col);
    display[row][col] = nearby;
    //si il n'y a aucune mine autour, découvrir les cases adjacentes
    int rRelativeToInput, cRelativeToInput;
    if(count == 0){
        for (rRelativeToInput = -1; rRelativeToInput < 2; rRelativeToInput++) {
            for (cRelativeToInput = -1; cRelativeToInput < 2; cRelativeToInput++) {
                if (display[row + rRelativeToInput][col + cRelativeToInput] == '?' || display[row + rRelativeToInput][col + cRelativeToInput] == 'F') {
                    countNearby(row + rRelativeToInput, col + cRelativeToInput);
                    printf("\nCalling countNearby(%d,%d)\n", row + rRelativeToInput, col + cRelativeToInput);
                }
            }
        }
    }
    return(count);
}

int main() {
    bool lost = false;
    int difficulty = 0;

    /* initialisation de la grid */
    printf("\nSize: %dx%d",size, size);
    

    int row, col;
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            grid[row][col] = 0;
        }
    }
    // grid à afficher
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            display[row][col] = '?' ;
        }
    }
    
    //populate with mines
    /*printf("\nChoisir la difficulte (entre 0 et 3): ");
    scanf_s("$d", &difficulty);
    printf("Difficulty: %d", difficulty);*/
    int toPlace;
    //change number of mines depending on difficulty
    switch (difficulty)
    {
    case 0:
        toPlace = 20;
    default:
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
        } else {
            placed = placed - 1;
        }
    }

    while (!lost)
    {   
        // display
        for (row = -1; row < size; row++) {
            //printf("ROW: %d\n", row);
            for (col = -1; col < size; col++) {
                if (row == -1) {
                    printf("\033[22;34m%d\033[0m ", col+1);
                } else if (col == -1) {
                    printf("\033[22;34m%d\033[0m ", row+1);
                } else {
                    if (display[row][col] == 'F') {
                        printf("\033[22;31m%c\033[0m ", display[row][col]);
                    }
                    else if(display[row][col] == '?'){
                        printf("%c ", display[row][col]);
                    }
                    else {
                        printf("\033[22;33m%c\033[0m ", display[row][col]);
                    }
                    
                }

                if (col == size - 1) {
                    printf("\n");
                }
            }
        }
        printf("\n");
        for (row = -1; row < size; row++) {
            //printf("ROW: %d\n", row);
            for (col = -1; col < size; col++) {
                if (row == -1) {
                    printf("%d ", col + 1);
                }
                else if (col == -1) {
                    printf("%d ", row + 1);
                } else if(grid[row][col]==1){
                    printf("\033[22;31m%i\033[0m ", grid[row][col]);
                } else {
                    printf("%i ", grid[row][col]);
                }

                if (col == size - 1) {
                    printf("\n");
                }
            }
        }

        int inputR, inputC;
        char option='d';
        bool valide = false;
        while (!valide) {
            // récupérer les coordonnées
            printf("\nEntrez les coordonees de la case ainsi: Ligne Colone (and flag)\nex: 1 3\n");
            scanf_s("%d %d %c", &inputR, &inputC, &option);
            // Check si la case est valide
            if ((inputC <= size && inputC > 0) && (inputR <= size && inputR > 0)) {
                valide = true;
                if (option == 'f') {
                    display[inputR-1][inputC-1] = 'F';
                }
                printf("\noption: %c\n", option);
            } else { // redemander si elle ne l'est pas
                printf("\nCoordonees invalides, reessayez\n");
            }
        }
        // check si la case à été découverte
        if(display[inputR-1][inputC-1] == '?') {
            if(grid[inputR-1][inputC-1] == 1) {
                if (option != 'f') {
                    display[inputR - 1][inputC - 1] = 'X';
                    lost = true;
                    printf("\nPERDU!\n");
                }
            } else {
                countNearby(inputR-1, inputC-1);
            }
        }
        
        //CHECK FOR MINES
        /*if (grid[inputR - 1][inputC - 1] == 1) {
            lost = true;
            printf("Perdu !");
        }*/
    }
    return 0;
}



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

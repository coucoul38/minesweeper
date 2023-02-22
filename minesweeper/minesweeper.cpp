// minesweeper.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

//#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main() {
    bool lost = false;
    const int size = 10;
    int difficulty = 0;

    /* initialisation de la grid */
    printf("\nSize: %dx%d",size, size);
    int grid[size][size];
    char display[size][size];

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


    srand(time(NULL));
    int placed;
    printf(" Mines: %d\n", toPlace);
    //Randomly place mines
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
        
        //Displaying array elements
        //printf("\nLen: %d", len);
        printf("Two Dimensional array elements:\n");
        for (row = 0; row < size; row++) {
            //printf("ROW: %d\n", row);
            for (col = 0; col < size; col++) {
                printf("%c ", display[row][col]);
                if (col == size - 1) {
                    printf("\n");
                }
            }
        }

        for (row = 0; row < size; row++) {
            //printf("ROW: %d\n", row);
            for (col = 0; col < size; col++) {
                printf("%d ", grid[row][col]);
                if (col == size - 1) {
                    printf("\n");
                }
            }
        }

        int inputR, inputC;
        bool valide = false;
        while (!valide) {
            printf("\nEntrez les coordonees de la case ainsi: Ligne Colone\nex: 1 3\n");
            scanf_s("%d %d", &inputR, &inputC);
            // Check si la case est valide
            if ((inputC <= size && inputC > 0) && (inputR <= size && inputR > 0)) {
                valide = true;
            }
            // redemander si elle ne l'est pas
            else {
                printf("\nCoordonees invalides, reessayez\n");
            }
        }
        // check si la case à été découverte
        if(display[inputR][inputC] == '?') {
            if(grid[inputR][inputC] == 1) {
                display[inputR][inputC] = 'X';
                lost = true;
            }
            else{
                printf("\nCounting\n");
                int count = 0;
                //compter le nombre de mines autour
                int R, C;
                for(R = -2; R <1; R++) {
                    for(C = -2; C <1 ; C++)
                    {
                        if (!(inputR + R < 0 || inputC + C < 0)) {
                            printf("Checking coordinates [%d][%d]", inputR + R, inputC + C);
                            if (grid[inputR + R][inputC + C] == 1) {
                                count++;
                            }
                        }
                    }
                }
                printf("\nNearby: %d\n", count);
                // display le nombre
                //convertir int en string
                char nearby = count + '0';
                display[inputR-1][inputC-1] = nearby;
            }
        }
        
        //CHECK FOR MINES
        if (grid[inputR-1][inputC-1] == 1) {
            lost = true;
            printf("Perdu !");
        }
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

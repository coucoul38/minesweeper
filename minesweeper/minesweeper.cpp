// minesweeper.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

//#include <iostream>

#include <stdlib.h>
#include <stdio.h>

int main() {
    bool lost = false;
    const int size = 10;
    int difficulty = 0;

    /* initialisation de la grid */
    printf("\nSize: %dx%d",size, size);
    int grid[size][size];
    /*Counter variables for the loop*/
    int row, col;
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            grid[row][col] = 0;
        }
    }
    
    //populate with mines
    /*printf("\nChoisir la difficulte (entre 0 et 3): ");
    scanf_s("$d", &difficulty);
    printf("Difficulty: %d", difficulty);*/
    int toPlace;
    switch (difficulty)
    {
    case 0:
        toPlace = 10;
    default:
        break;
    }



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
                printf("%d ", grid[row][col]);
                //printf("%d%d ", row, col);
                if (col == size - 1) {
                    printf("\n");
                }
            }
        }
        int inputR, inputC;
        printf("Entrez les coordonees de la case ainsi: Ligne Colone\nex: 1 0\n");
        scanf_s("%d %d", &inputR, &inputC);
        printf("Row: %d, Col: %d", inputR, inputC);
        
        //CHECK FOR MINES
        if (grid[inputR][inputC] == 1) {
            lost = true;
            printf("Perdu !");
        }
        lost = true;
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

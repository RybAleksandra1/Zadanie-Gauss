#include "gauss.h"
#include <math.h>  // Może się przydać do abs() w przyszłości, warto dodać

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int n = mat->r;
    int k, i, j;
    double factor;

    // Sprawdzamy czy macierze w ogole istnieja i czy maja dobre wymiary 
    if (!mat || !b || mat->r != mat->c || mat->r != b->r) {
        return 1; // Błąd błędnych danych
    }

    // TRYWIALNA ELIMINACJA GAUSSA 

    // petla po kolumnach (krokach eliminacji)
    for(k = 0; k < n - 1; k++) {
        
        // Sprawdzenie czy element na diagonalnej nie jest 0
        if (mat->data[k][k] == 0) {
            return 1; // Blad, mamy dzielenie przez 0 (macierz osobliwa)
        }

        // petla po wierszach 
	for(i = k + 1; i < n; i++) {
            
            // Obliczenie wspolczynnika, przez ktory mnozymy wiersz k
            factor = mat->data[i][k] / mat->data[k][k];

            // Odejmowanie wiersza k od wiersza i w macierzy A
            // Zaczynamy od j=k, bo elementy wczesniej sa juz wyzerowane
            for(j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            // To samo odejmowanie dla wektora wynikow b
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0; // Sukces
}

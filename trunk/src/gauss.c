#include "gauss.h"
#include <math.h>  // Może się przydać do abs() w przyszłości, warto dodać

// Wybór elementu diagonalnego

int pivot_selection(Matrix *mat, Matrix *b, int k) {
    int max_row = k; // Zakladamy ze biezacy wiersz ma najwiekszy element
    double max_val = fabs(mat->data[k][k]); // Pobieramy wartosc bezwzgledna elementu diagonalnego

    // Przeszukujemy kolumne k ponizej elementu na przekatnej
    for (int i = k + 1; i < mat->r; i++) {
        // Porównujemy wartości bezwzględne, aby znaleźć element najdalszy od zera
        if (fabs(mat->data[i][k]) > max_val) {
            max_val = fabs(mat->data[i][k]);
            max_row = i; // Zapamiętujemy indeks wiersza z większym elementem
        }
    }

    // Jesli znalezlismy wiersz z wiekszym elementem (max_row != k) to zamieniamy go z biezacym
    if (max_row != k) {
        // Zamiana wierszy w macierzy A (mat)
        // Zamieniamy tylko wskazniki do wierszy (data[i])
        double *tmp_row = mat->data[k];
        mat->data[k] = mat->data[max_row];
        mat->data[max_row] = tmp_row;

        // Zamiana wierszy w wektorze B
        // Tutaj zamieniamy konkretne wartosci (double), bo b to wektor (kolumna)
        double tmp_b = b->data[k][0];
        b->data[k][0] = b->data[max_row][0];
        b->data[max_row][0] = tmp_b;
    }
    return 0;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    // Sprawdzamy czy macierze w ogole istnieja i czy maja dobre wymiary 
    if (!mat || !b || mat->r != mat->c || mat->r != b->r) {
        return 1; // Błąd błędnych danych
    }

    int n = mat->r;
    int k, i, j;
    double factor;

    // TRYWIALNA ELIMINACJA GAUSSA 

    // petla po kolumnach (krokach eliminacji)
    for(k = 0; k < n - 1; k++) {

        // Wybieramy najlepszy pivot dla bieżącej kolumny
        pivot_selection(mat, b, k);
        
        // Sprawdzenie czy element na diagonalnej nie jest 0
        if (mat->data[k][k] == 0) {
            return 1; // Blad, mamy dzielenie przez 0 (macierz osobliwa)
        }

        // Sprawdzamy osobliwosc - jesli po zamianie pivot nadal jest bliski 0, 
        // oznacza to, że cala kolumna jest zerowa (uklad sprzeczny lub nieoznaczony)
        if (fabs(mat->data[k][k]) < 1e-12) {
            return 1; // błąd - macierz osobliwa
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

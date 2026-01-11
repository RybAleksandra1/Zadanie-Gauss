#include "gauss.h"
#include <stdio.h>
#include <math.h>  // potrzebne do funkcji fabs() 

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
 * wynik 
 *  0 - eliminacja gaussa zakonczona sukcesem
 *  1 - macierz osobliwa czyli dzielenie przez 0!!
 */
int eliminate(Matrix *mat, Matrix *b){
    int n = mat->r;
    int k, i, j;
    int max_row;     //indeks dla wiersza z najwieksza wartoscia
    double factor;
    double temp;     // zmienna temp(temporary) pomocnicza do zamiany wierszy

    // spr czy macierz jest i czy ma dobry wymiar
    if (!mat || !b || mat->r != mat->c || mat->r != b->r) {
        fprintf(stderr, "Blad: Nieprawidlowe rozmiary macierzy lub brak danych!\n");
        return 1; // bledne dane 
    }

    // tu mamy glowna petle eliminacji gaussa
    // petla idzie po kolumnach
    for(k = 0; k < n - 1; k++) {
        
       // tu cos nowego - wybor elementu glownego 
        // Szukamy wiersza z najwieksza wartosica bezwzgledna w kolumnie k
        max_row = k;
        for (i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > fabs(mat->data[max_row][k])) {
                max_row = i;
            }
        }

        // jak znajdziemy lepszy wiersz zamieniamy go
        if (max_row != k) {
            // Zamiana wierszy w macierzy A 
            for (j = k; j < n; j++) { 
                temp = mat->data[k][j];
                mat->data[k][j] = mat->data[max_row][j];
                mat->data[max_row][j] = temp;
            }
            
            // Zamiana wierszy w wektorze b (wazny krok!!)
            temp = b->data[k][0];
            b->data[k][0] = b->data[max_row][0];
            b->data[max_row][0] = temp;
        }
       
        // Sprawdzenie czy po zamianie element na diagonalnej nadal nie jest zerowy
        if (mat->data[k][k] == 0) {
            return 1; // Blad, macierz osobliwa
        }

        // Dalsza czesc taka sama jak dla trywialnej elimincji gaussa
        for(i = k + 1; i < n; i++) {
            
            // Obliczenie wspolczynnika
            factor = mat->data[i][k] / mat->data[k][k];

            // Odejmowanie wiersza k od wiersza i w macierzy A
            for(j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            // To samo odejmowanie dla wektora wynikow b
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0; // oznacza sukces
}

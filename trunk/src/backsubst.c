#include "backsubst.h" // Dołącza definicję struktury Matrix i prototyp funkcji
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	// Weryfikacja rozmiarow macierzy - macierz 'mat' musi byc kwadratowa (r x r)
	// oraz macierze 'b' i 'x' muszą mieć tyle samo wierszy co 'mat' 
	if (mat->r != mat->c || mat->r != b->r || mat->r != x->r) {
		return 2; // Błąd nieprawidłowych rozmiarów macierzy
    }

	// Przypisujemy rozmiar macierzy do zmiennej n dla czytelności
    int n = mat->r; 

	// Algorytm podstawiania wstecznego 

	// Petla ktora przechodzi od ostatniego wiersza (n-1) do pierwszego (0)
	for (int i = n - 1; i >= 0; i--) {
		// Zmienna pomocnicza s, w której będziemy gromadzić sumę znanych
		// elementów, które "przenosimy na drugą stronę" równania
        double s = 0;

		// Sumujemy iloczyny znanych już wartości x[j] i współczynników macierzy
        for (int j = i + 1; j < n; j++) {
			// Mnożymy współczynnik macierzy przez obliczoną już niewiadomą i dodajemy do sumy s
            s += mat->data[i][j] * x->data[j][0];
        }

        // Sprawdzamy, czy nie dzielimy przez zero (element na diagonali rowny zero)
        if (mat->data[i][i] == 0) {
            return 1;
        }

        // Obliczamy wartość x[i] (niewiadomą)
		// b->data[i][0] - wyraz wolny z prawej strony równania
        x->data[i][0] = (b->data[i][0] - s) / mat->data[i][i];

	}

	// Wsteczne podstawienie zakonczone sukcesem
	return 0;
}

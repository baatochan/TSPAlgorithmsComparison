# Projektowanie efektywnych algorytmów
## Zadanie projektowe nr 3: Algorytm populacyjny

| Autor | Prowadzący | Termin |
| :-: | :-: | :-: |
| Bartosz Rodziewicz (226105) | Mgr inż. Radosław Idzikowski | Piątek, 7:30 |

### Opis problemu
Wybranym prze mnie problemem optymalizacyjnym jest Travelling Salesman Problem, czyli Problem Komiwojażera.

Polega on na znalezieniu minimalnego cyklu Hamiltona w pełnym grafie ważonym. Cykl Hamiltona to taki cykl w grafie, w którym każdy wierzchołek grafu odwiedzany jest dokładnie raz (plus powrót do wierzchołka początkowego).

Jest to problem NP-trudny.

![Graf dla 5 miast](../report-stage1/graphs/graph2.png)

Powyżej znajduje się przykładowy graf dla 5-ciu miast. Każda krawędź posiada wagę, różną dla przejść w jedną i drugą stronę.

W programie graf jest reprezentowany jako macierz `n`x`n` z wagami przejść, gdzie `n` oznacza liczbę miast.

### Metoda rozwiązania
#### Algorytmy Brute Force i Branch and Bound
W sprawozdaniu z etapu 1 dokładnie opisałem działanie i moją implementację powyższych algorytmów, więc nie będę tutaj tego powtarzać.

Są to algorytmy dokładne, więc zawsze znajdą najbardziej optymalny wynik, jednak posiadają bardzo dużą złożoność obliczeniową (w obu przypadkach `O(n!)`).

#### Algorytm Tabu Search
W sprawozdaniu z etapu 2 dokładnie opisałem działanie i moją implementację powyższego algorytmu, więc nie będę tutaj tego powtarzać.

#### Algorytm genetyczny

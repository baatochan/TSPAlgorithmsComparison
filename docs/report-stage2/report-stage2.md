# Projektowanie efektywnych algorytmów
## Zadanie projektowe nr 2: Algorytm poszukiwania lokalnego

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
Wybranym przeze mnie algorytmem przeszukiwania lokalnego jest algorytm Tabu Search, czyli przeszukiwanie z zakazami.

Algorytm ten, jest tak na prawdę ideą i jego implementacje mogą znacząco się różnić od siebie.

Główny zarys tego algorytmu wygląda następująco:
* Algorytm wyznacza w jakiś sposób początkowe rozwiązanie,
* Algorytm przeszukuje otoczenie tego rozwiązania (otoczeniem jest zbiór innych rozwiązań różniących się od obecnego rozwiązanie o jeden Ruch; Ruch, jak i otoczenie definiowane jest poprzez implementacje),
* Z pośród wszystkich rozwiązań w danym otoczeniu algorytm wybiera najlepsze i Ruch dodawany jest do listy zabronionych ruchów na jakiś okres kadencji (czas, bądź liczba iteracji),
* Algorytm kończy pracę, gdy nastąpi spełnienie warunku satysfakcjonującego (czas, bądź liczba iteracji), zwraca wtedy najlepsze dotąd znalezione rozwiązanie.

Algorytm w żaden sposób nie gwarantuje znalezienie najbardziej optymalnego rozwiązania, jednak znacząco skraca czas wyznaczania w miarę optymalnego rozwiązania (użytkownik decyduje ile czasu algorytm pracuje).

Jeśli dla danej instancji problemu nie jest znane rozwiązanie optymalne, nie ma też żadnej możliwości aby oszacować stopnia błędu znalezionego przez algorytm rozwiązania.

Lista tabu służy zabezpieczeniu algorytmu przed zablokowaniem się w okolicy jednego lokalnego optimum.

Celem zwiększenia szansy znalezienia globalnego optimum w algorytmie stosuje się różne metody dywersyfikacji poszukiwań.

Moja implementacja bazuje na następujących cechach:
* Początkowe rozwiązanie znajdywane jest za pomocą zachłannego algorytmu najbliższego sąsiada (nearest neighbor algorithm). _Statystycznie algorytm ten znajduje rozwiązanie o 25% dłuższe niż najlepsze rozwiązanie przy całkowicie losowym rozłożeniu miast._
* Ruchem w moim algorytmie jest wymiana dwóch miast ze sobą w trasie (algorytm zakłada spójność grafu (asymetryczność jest dozwolona)).
* Otoczeniem rozwiązania (otoczenie typu swap) jest więc każde rozwiązanie różniące się od obecnego pozycją dwóch miast (złożoność obliczeniowa jednej iteracji to `O(n^2)`).
* Na liście tabu przechowywane są pary wierzchołków zakazując ich ponownej wymiany przez ustalony przez użytkownika okres czasu (domyślnie `0.5 * ilośćWierzchołków`).
* Zaimplementowane kryterium aspiracji (opcjonalne, domyślnie włączone) pozwala na wykonanie ruchu znajdujące się na liście tabu jeśli prowadzi ono do poprawienia najlepszego rozwiązania dotychczas znalezionego.
* Strategią dywersyfikacji (opcjonalną, domyślnie włączoną) jest wyznaczenie nowego, całkowicie losowego, rozwiązania po określonej liczbie iteracji (domyślnie 10 tys.) bez poprawy najlepszego znalezionego rozwiązania.
* Kryterium satysfakcji jest czas pracy algorytmu po którym następuje przerwanie pracy algorytmu (domyślnie 10(s)). _Czas pracy algorytmu sprawdzany jest po każdym przeszukaniu sąsiedztwa, więc nie jest całkowicie dokładny. Średnio algorytm wykonuje się 10% dłużej niż podany przez użytkownika czas._

Ponieważ algorytm oparty na metodzie Tabu Search jest algorytmem niedeterministycznym, nie można dla niego w całości określić czasowej złożoności obliczeniowej. Można jednak podać złożoność obliczeniową pojedynczego przeglądu całego sąsiedztwa, która dla sąsiedztwa typu swap
wynosi `O(n^2)`.

# SWDISK

## Symulator
program konsolowy, c++, c++14, std

umozliwia
* wczytanie z pliku
* generowanie
* uruchomienie algo
* parametry
* benchmarki

graf jako macierz

## Algorytmy
* Branch&Bound,
* TabuSearch,
* Algorytm genetyczny,
* Symulowane wyżarzanie

## Branch and bound
implementacja na rekur brute forcie  
sprawdzanie koljenych wierzholkow  
dodatkowe wyliczanie dolnego ograniczenia  
dolne ograniczenie - najlepsze do znalezienia rozwiazanie w poddrzewie  
u nas - minimalny koszt odwiedzenia pozostalych wierzcholkow  
do kazdego wierzcholka wchodzisz i wychodzisz  
dolne ograniczenie + aktualna trasa  

## Tabu search
* otoczenie swap - ruch zmiana dwoch miast
* lista tabu - pary miast
* zaimplementowana aspiracja
* zaimplementowana dywersyfikacja - po X ruchcach bez poprawy szukanie nowego otoczenia
* algorytm konczy prace po czasie

## Genetyk
* genotyp - trasa komiwojazera
* fenotyp dlugosc trasy
* losowa startowa populacja
* wielkosc populacji parametrem
* krzysowanie OX (ordered crossover) - dwojka dzieci, podzial genomu rodzica dwoma punktami, lewa i prawa czesc dziecko 1 otrzymuje od rodzica 1, a srodek jest ustalany na podstawie rodzica 2
* mutacja wierzcholkowa
* dwa wspolczynniki

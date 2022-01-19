# SWDISK

## Genetyczny
heurytyka, nie gwarantuje rozwiazania

popularny, populacyjny

dzialanie z biologi, gatunki rozwijaja

zarys:
* poczatkowa populacja (zalezy od implementacji jak)
* ocena i odrzucenie (fenotyp)
* tworzenie nowego pokolenia
* krzyzowanie osobnikow - laczenie genotypu, co to genotyp
* nowe osobniki mutacja (wierzcholkow/krawedzi)
* nowe osobniki do calej populacji
* ocena i odrzucenie
* do spelnienia jakosci badz ograniczenia

potencjalne parametry
- wielksoc populacji
- wspolczynnik krzyzowania
- wspolczynnik mutacji
- kryterium jakosci
- ograniczenie - czas, brak poprawy
- metoda mutacji
- metoda generacji populacji
- metoda krzyzowania

## Tabu search
przesuzkaiwanie z zakazami, algorytm przeszukiwania lokalnego

malo specyzowany, duzo zalezy od implementacji

zarys:
- wyzanczenie poczatkowego rozwiazania
- przeszukiwanie otoczenia, o jeden ruch
- najlepsze z otoczenia, ruch do listy tabu, lokalne optima
- reapet, koniec gdy spelnienia jakosci badz ograniczenia

miozliwa aspiracja - ruch z tabu, poprawienie najlepszego rozwiazania

mozliwa dywersyfikacja - nowe rozwiazanie startowe

potencjalne parametry:
- metoda generacji poczatkowego rozwiazania
- metoda ruchu, czyli posrednio otoczenia
- czas trwania tabu
- kryterium aspiracji (tak nie)
- kryterium dywersyfikacji (tak nie)
- co ile dywersyfikacja
- metoda dywersyfikacji
- kryterium jakosci
- ograniczenie - czas, brak poprawy

## Branch and bound
modyfikacja brute force'a

reukryncyjnie drzewo rozwiazan

ocena poddrzew - najlepsze znane roziwazanie i najlepsze mozliwe do osiagniecia (aktualna dllugosc od poczatku i dolne ograniczenie)

najlepsze mozliwe rozwiazanie gorsze niz znane, odciecie

oszczednosc

algorytm moze byc brute forcem

najwazneijsza metoda dolnego ograniczenia

akualna odleglosc od startu najprostsza metoda

metoda minimalnego kosztu odwiedzenia kasztego wierzcholka

dolne ograniczenie grafu, raz wejsc i raz wyjsc

przy przechdzeniu przez graf zmniejszanie dolnej granicy o odwiedzone wierzcholki

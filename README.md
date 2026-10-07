**Polski** · [English](README.en.md)

---

# Matura z informatyki, poziom rozszerzony - algorytm Euklidesa, NWD i NWW

> ### 🎬 Wideo z omówieniem
> Pełne omówienie algorytmu Euklidesa krok po kroku znajdziesz na moim kanale YouTube:
> **[Link do filmu na YouTube](https://youtu.be/Vbek_yMpdRU)**
>
> Na filmie omawiam teorię NWD i NWW, rozpisuję obie wersje algorytmu Euklidesa na liczbach 84 i 36, a potem implementuję i uruchamiam je w Pythonie i w C++.

---

## Opis

Repozytorium dotyczy dwóch algorytmów, które trzeba znać na maturze z informatyki. Pierwszy wyznacza NWD, czyli największy wspólny dzielnik. Drugi wyznacza NWW, czyli najmniejszą wspólną wielokrotność. Oba należą do puli algorytmów wymaganych na egzaminie, a w zadaniach maturalnych zdarzało się już do nich nawiązywać.

W kodzie znajdują się trzy wersje algorytmu Euklidesa wyznaczające NWD:

- wersja z odejmowaniem,
- wersja z resztą z dzielenia,
- wersja rekurencyjna.

NWW jest wyznaczane na podstawie NWD. Wszystkie funkcje są zaimplementowane w Pythonie i w C++. Teoria z rozpisanymi przykładami znajduje się w pliku `TEORIA.txt`.

## Wymagania

- Python 3.6 lub nowszy, kod korzysta z f-stringów
- Kompilator C++ obsługujący standard C++11 lub nowszy, kod korzysta z typu `long long`
- Brak zewnętrznych zależności. Wersja w Pythonie nie importuje żadnych modułów, a wersja w C++ używa tylko nagłówka `<iostream>`

## Uruchomienie

Pobranie repozytorium:

```bash
git clone https://github.com/kmprograms/matura-algorytm-euklidesa
cd matura-algorytm-euklidesa
```

Wersja w Pythonie:

```bash
python app.py
```

Wersja w C++:

```bash
g++ -std=c++17 -O2 -o app app.cpp
./app
```

Oba programy wyznaczają NWD liczb 84 i 36 trzema metodami oraz ich NWW. Wyniki wypisują w czterech wierszach.

## Struktura projektu

| Plik | Opis |
| --- | --- |
| `app.py` | Funkcje `nwd_odejmowanie`, `nwd_dzielenie`, `nwd_rek` i `nww` w języku Python |
| `app.cpp` | Te same funkcje w języku C++ |
| `TEORIA.txt` | Teoria: definicje, własności NWD i NWW, pseudokod obu wersji algorytmu Euklidesa, rozpisane kroki i złożoność |
| `README.md` | Opis repozytorium po polsku |
| `README.en.md` | Opis repozytorium po angielsku |

## Teoria i sposób rozwiązania

### Dzielniki, NWD i NWW

Liczba `d` jest dzielnikiem liczby `a`, jeśli `a` dzieli się przez `d` bez reszty. Na przykład 12 jest dzielnikiem liczby 36, bo 36 podzielone przez 12 daje 3 i resztę 0.

NWD dwóch liczb to największa liczba, która dzieli obie te liczby bez reszty. NWW dwóch liczb to najmniejsza dodatnia liczba, która dzieli się bez reszty przez każdą z nich. Jeśli NWD dwóch liczb wynosi 1, mówimy, że te liczby są względnie pierwsze. Przykładem są liczby 8 i 15.

Przykład dla liczb 84 i 36:

| Zbiór | Liczby |
| --- | --- |
| Dzielniki 84 | 1, 2, 3, 4, 6, 7, 12, 14, 21, 28, 42, 84 |
| Dzielniki 36 | 1, 2, 3, 4, 6, 9, 12, 18, 36 |
| Wspólne dzielniki | 1, 2, 3, 4, 6, 12 |
| Wielokrotności 84 | 84, 168, 252, ... |
| Wielokrotności 36 | 36, 72, 108, 144, 180, 216, 252, ... |

Największy wspólny dzielnik to 12, więc `NWD(84, 36) = 12`. Pierwsza wspólna wielokrotność to 252, więc `NWW(84, 36) = 252`.

### Rozkład na czynniki pierwsze

W szkole NWD liczy się zwykle przez rozkład na czynniki pierwsze:

- `84 = 2² · 3 · 7`
- `36 = 2² · 3²`

Do NWD bierzesz czynniki wspólne z mniejszym wykładnikiem, czyli `NWD = 2² · 3 = 12`. Do NWW bierzesz wszystkie czynniki z większym wykładnikiem, czyli `NWW = 2² · 3² · 7 = 252`. Siódemki nie ma w rozkładzie liczby 36. Wygodnie jest przyjąć, że występuje tam w potędze zerowej, czyli jako 1. Wtedy do NWD trafia mniejszy wykładnik 0, a do NWW większy wykładnik 1.

Ta metoda dobrze pokazuje, czym jest NWD i NWW. W programie jest jednak wolna, bo rozkład dużej liczby na czynniki wymaga wielu dzieleń. Dlatego w kodzie stosujemy algorytm Euklidesa.

### Własności, na których opiera się algorytm Euklidesa

1. `NWD(a, 0) = a`
2. `NWD(a, b) = NWD(a - b, b)` dla `a > b`
3. `NWD(a, b) = NWD(b, a mod b)` dla `b > 0`
4. `NWD(a, b) · NWW(a, b) = a · b`. Sprawdzenie: 12 · 252 = 3024 oraz 84 · 36 = 3024.
5. `NWD(a, b, c) = NWD(NWD(a, b), c)` i tak samo dla NWW. NWD trzech liczb liczymy po kolei. Najpierw NWD dwóch pierwszych liczb, potem NWD tego wyniku i trzeciej liczby.

Dlaczego działa własność 2? Pary (84, 36) oraz (48, 36) mają dokładnie te same wspólne dzielniki: 1, 2, 3, 4, 6 i 12. Weźmy dzielnik 6. Liczba 84 to 14 szóstek, a 36 to 6 szóstek. Ich różnica, czyli 48, to 8 szóstek. Ogólnie, jeśli `d` dzieli `a` oraz `b`, to dzieli też ich różnicę. Jeśli `d` dzieli `b` oraz `a - b`, to dzieli też ich sumę, czyli `a`. Przy przejściu od pary `a`, `b` do pary `a - b`, `b` żaden wspólny dzielnik nie znika i żaden nowy się nie pojawia. Dlatego NWD się nie zmienia.

Dlaczego działa własność 3? Reszta z dzielenia to wynik wielokrotnego odejmowania. Od 84 odejmujemy 36 i zostaje 48. Od 48 znowu odejmujemy 36 i zostaje 12. To samo daje dzielenie z resztą: 84 podzielone przez 36 to 2 i reszta 12. Każde odejmowanie zachowuje NWD zgodnie z własnością 2, więc `NWD(84, 36) = NWD(48, 36) = NWD(12, 36) = NWD(36, 12)`. Kolejność liczb w NWD nie ma znaczenia.

### Algorytm Euklidesa z odejmowaniem

To starsza wersja algorytmu. Na wejściu są dwie liczby naturalne `a` i `b`, obie większe od zera. Na wyjściu jest ich NWD. Pseudokod z pliku `TEORIA.txt`:

```
dopóki a ≠ b wykonuj
    jeżeli a > b
        a ← a - b
    w przeciwnym razie
        b ← b - a
zwróć a
```

Przebieg dla liczb 84 i 36:

| Krok | `a` | `b` | Operacja |
| --- | --- | --- | --- |
| 0 | 84 | 36 | `a > b`, więc `a ← 84 - 36` |
| 1 | 48 | 36 | `a > b`, więc `a ← 48 - 36` |
| 2 | 12 | 36 | `a < b`, więc `b ← 36 - 12` |
| 3 | 12 | 24 | `a < b`, więc `b ← 24 - 12` |
| 4 | 12 | 12 | `a = b`, koniec, NWD = 12 |

Ta wersja ma dwie wady. Jeśli jedna z liczb jest równa zero, pętla nigdy się nie kończy, bo odejmowanie zera niczego nie zmienia. Dla liczb o bardzo różnej wielkości algorytm działa długo. NWD z miliona i jedynki wymaga 999 999 odejmowań.

### Algorytm Euklidesa z resztą z dzielenia

Dlatego w praktyce i na maturze używa się wersji z resztą z dzielenia. Wystarczy w niej, że co najmniej jedna z liczb jest różna od zera. Pseudokod z pliku `TEORIA.txt`:

```
dopóki b ≠ 0 wykonuj
    r ← a mod b
    a ← b
    b ← r
zwróć a
```

Przebieg dla liczb 84 i 36:

| Krok | `a` | `b` | `r = a mod b` |
| --- | --- | --- | --- |
| 0 | 84 | 36 | 12 |
| 1 | 36 | 12 | 0 |
| 2 | 12 | 0 | `b = 0`, koniec, NWD = 12 |

Wersja z odejmowaniem potrzebowała pięciu kroków, a ta tylko trzech.

### Wersja rekurencyjna

Ten sam algorytm można zapisać rekurencyjnie, korzystając z własności 1 i 3:

- `NWD(a, b) = a`, gdy `b = 0`
- `NWD(a, b) = NWD(b, a mod b)`, gdy `b > 0`

Gdy `b` jest równe zero, rekurencja się kończy i zwracane jest `a`. W przeciwnym razie funkcja wywołuje samą siebie dla `b` oraz `a mod b`.

### Złożoność

Wersja z odejmowaniem wykonuje najwyżej o jedno odejmowanie mniej, niż wynosi większa z liczb. Tyle odejmowań potrzeba na przykład dla miliona i jedynki. Wersja z resztą z dzielenia ma złożoność logarytmiczną względem mniejszej z liczb.

Dokładne ograniczenie podaje twierdzenie Lamégo. Jeśli `a ≥ b` oraz `b > 0`, liczba dzieleń nie przekracza pięciokrotności liczby cyfr liczby `b`. Dla 89 i 55 to najwyżej 10 dzieleń, a algorytm wykonuje ich 9. Jeśli `a < b`, pierwsze dzielenie tylko zamienia liczby miejscami. Wtedy dochodzi jedno dzielenie.

Najgorszym przypadkiem są dwie kolejne liczby Fibonacciego. Przy `a > b` są one najmniejszą parą, która wymaga danej liczby dzieleń. Na przykład 89 i 55 to najmniejsza para, dla której algorytm wykonuje 9 dzieleń. Przy `a ≥ b` żadna para z `a` nie większym od 89 nie wymaga więcej dzieleń.

Na maturze najważniejsze jest zapamiętanie, że wersja z resztą z dzielenia ma złożoność logarytmiczną i jest szybsza od wersji z odejmowaniem.

## Zgodność z ograniczeniami maturalnymi

Implementacja zakłada kategorię zadań maturalnych, w których nie wolno używać funkcji wbudowanych. Python ma w module `math` funkcje `gcd` i `lcm`, które od razu wyznaczają NWD i NWW, ale kod z nich nie korzysta. NWD i NWW liczą wyłącznie samodzielnie napisane funkcje. Używają one pętli `while`, instrukcji `if`, rekurencji, porównań, operatorów `-`, `*` i `%` oraz dzielenia całkowitego (`//` w Pythonie, `/` na liczbach całkowitych w C++).

Założenia dotyczące danych:

- `nwd_odejmowanie` działa tylko dla `a > 0` i `b > 0`. Na maturze najprawdopodobniej takie będą założenia.
- `nwd_dzielenie` i `nwd_rek` wymagają, żeby co najmniej jedna z liczb była różna od zera.
- `nww` wymaga, żeby obie liczby były dodatnie.

## Wyniki

Oba programy liczą wartości dla `a = 84` i `b = 36`.

Wersja w Pythonie wypisuje:

```
nwd odejmowanie:   12
nwd dzielenie:     12
nwd rekurencyjnie: 12
nww: 252
```

Wersja w C++ wypisuje:

```
nwd odejmowanie:   12
nwd dzielenie:     12
nwd rekurencyjnie: 12
nww:               252
```

Wydruki różnią się tylko wyrównaniem ostatniego wiersza. Wszystkie trzy wersje algorytmu dają NWD równe 12, a NWW wynosi 252. To zgadza się z obliczeniami ręcznymi z części teoretycznej.

## Uwagi implementacyjne

Nazwy funkcji wskazują wersję algorytmu: `nwd_odejmowanie`, `nwd_dzielenie` i `nwd_rek`. Funkcja `nww` korzysta z `nwd_dzielenie`. Wszystkie funkcje są oddzielone od funkcji `main`, w której znajdują się tylko wywołania dla przykładowych danych.

W Pythonie wersja z resztą z dzielenia używa przypisania wielokrotnego `a, b = b, a % b`, które aktualizuje obie zmienne w jednej linii. W C++ potrzebna jest zmienna pomocnicza `r`:

```cpp
long long nwd_dzielenie(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```

NWW jest wyznaczane z własności 4, czyli `NWW = a · b / NWD`. W Pythonie liczby całkowite nie mają limitu wielkości, więc kolejność działań nie ma znaczenia. Najpierw jest mnożenie, a potem dzielenie całkowitoliczbowe:

```python
def nww(a: int, b: int) -> int:
    """Iloczyn NWD i NWW jest równy iloczynowi liczb a i b, dlatego NWW = a * b / NWD"""
    return a * b // nwd_dzielenie(a, b)
```

W C++ kolejność ma znaczenie. Iloczyn `a * b` może nie zmieścić się w typie `long long` i spowodować przepełnienie. Dlatego najpierw dzielimy `a` przez NWD, a dopiero potem mnożymy przez `b`. Wynik się nie zmienia, bo `a` zawsze dzieli się przez NWD bez reszty:

```cpp
long long nww(long long a, long long b) {
    return a / nwd_dzielenie(a, b) * b;
}
```

W wersji C++ wszystkie funkcje używają typu `long long`, żeby obsłużyć większe liczby. Wykorzystano nagłówek `<iostream>` i `using namespace std`, żeby zachować zgodność z tym, czego używa się w szkole.

Ciekawostka historyczna: oryginalnym algorytmem Euklidesa jest wariant z odejmowaniem. Wersja z resztą z dzielenia to jego późniejsza, zoptymalizowana odmiana. Na maturze warto znać obie wersje, wiedzieć, czym się różnią, i umieć je zaimplementować.
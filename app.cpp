#include <iostream>

using namespace std;

// NWD metodą odejmowania. Działa tylko dla a > 0 i b > 0.
long long nwd_odejmowanie(long long a, long long b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

// NWD metodą reszt z dzielenia.
long long nwd_dzielenie(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}


// NWD rekurencyjnie
long long nwd_rek(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return nwd_rek(b, a % b);
}

// Iloczyn NWD i NWW jest równy iloczynowi liczb a i b, więc
// NWW = a * b / NWD.
// Mnożenie a * b daje dużą liczbę, która może nie zmieścić się w typie
// long long. Dlatego najpierw dzielimy a przez NWD, a dopiero potem
// mnożymy przez b. Wynik się nie zmienia, bo a zawsze dzieli się przez
// NWD bez reszty. Liczby a i b muszą być dodatnie.
long long nww(long long a, long long b) {
    return a / nwd_dzielenie(a, b) * b;
}

int main() {
    long long a = 84, b = 36;
    cout << "nwd odejmowanie:   " << nwd_odejmowanie(a, b) << "\n";
    cout << "nwd dzielenie:     " << nwd_dzielenie(a, b) << "\n";
    cout << "nwd rekurencyjnie: " << nwd_rek(a, b) << "\n";
    cout << "nww:               " << nww(a, b) << "\n";
    return 0;
}
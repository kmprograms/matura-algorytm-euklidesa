def nwd_odejmowanie(a: int, b: int) -> int:
    """NWD metodą odejmowania. Działa tylko dla a > 0 i b > 0."""
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a


def nwd_dzielenie(a: int, b: int) -> int:
    """NWD metodą reszt z dzielenia"""  
    while b != 0:
        a, b = b, a % b
    return a


def nwd_rek(a: int, b: int) -> int:
    """NWD rekurencyjnie"""
    if b == 0:
        return a
    return nwd_rek(b, a % b)   


def nww(a: int, b: int) -> int:
    """Iloczyn NWD i NWW jest równy iloczynowi liczb a i b, dlatego NWW = a * b / NWD"""
    return a * b // nwd_dzielenie(a, b)


def main() -> None:
    a, b = 84, 36
    print(f'nwd odejmowanie:   {nwd_odejmowanie(a, b)}')
    print(f'nwd dzielenie:     {nwd_dzielenie(a, b)}')
    print(f'nwd rekurencyjnie: {nwd_rek(a, b)}')
    print(f'nww: {nww(a, b)}')


if __name__ == "__main__":
    main()    
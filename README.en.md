[Polski](README.md) · **English**

---

# Matura in Computer Science, extended level - Euclidean algorithm, GCD and LCM

> ### 🎬 Video walkthrough
> A complete step-by-step walkthrough of the Euclidean algorithm is available on my YouTube channel:
> **[Link to the YouTube video](https://youtu.be/Vbek_yMpdRU)**
>
> In the video I go through the theory of GCD and LCM, trace both versions of the Euclidean algorithm on the numbers 84 and 36, and then implement and run them in Python and C++.

---

## Description

This repository covers two algorithms you need to know for the matura exam in computer science. The first one finds the GCD, the greatest common divisor (Polish: NWD). The second one finds the LCM, the least common multiple (Polish: NWW). Both belong to the set of algorithms required at the exam, and matura tasks have already referred to them in the past.

The code contains three versions of the Euclidean algorithm that compute the GCD:

- the subtraction version,
- the remainder (modulo) version,
- the recursive version.

The LCM is computed from the GCD. All functions are implemented in Python and C++. The theory with worked examples is in the `TEORIA.txt` file.

## Requirements

- Python 3.6 or newer, the code uses f-strings
- A C++ compiler supporting C++11 or newer, the code uses the `long long` type
- No external dependencies. The Python version imports no modules, and the C++ version uses only the `<iostream>` header

## Running the code

Clone the repository:

```bash
git clone https://github.com/kmprograms/matura-algorytm-euklidesa
cd matura-algorytm-euklidesa
```

Python version:

```bash
python app.py
```

C++ version:

```bash
g++ -std=c++17 -O2 -o app app.cpp
./app
```

Both programs compute the GCD of 84 and 36 using three methods, as well as their LCM. They print the results on four lines.

## Project structure

| File | Description |
| --- | --- |
| `app.py` | The `nwd_odejmowanie`, `nwd_dzielenie`, `nwd_rek` and `nww` functions in Python |
| `app.cpp` | The same functions in C++ |
| `TEORIA.txt` | Theory: definitions, properties of GCD and LCM, pseudocode of both versions of the Euclidean algorithm, step-by-step traces and complexity |
| `README.md` | Repository description in Polish |
| `README.en.md` | Repository description in English |

## Theory and solution approach

### Divisors, GCD and LCM

A number `d` is a divisor of a number `a` if `a` is divisible by `d` with no remainder. For example, 12 is a divisor of 36, because 36 divided by 12 gives 3 with remainder 0.

The GCD of two numbers is the largest number that divides both of them with no remainder. The LCM of two numbers is the smallest positive number that is divisible by each of them with no remainder. If the GCD of two numbers is 1, we say the numbers are coprime. An example is the pair 8 and 15.

Example for the numbers 84 and 36:

| Set | Numbers |
| --- | --- |
| Divisors of 84 | 1, 2, 3, 4, 6, 7, 12, 14, 21, 28, 42, 84 |
| Divisors of 36 | 1, 2, 3, 4, 6, 9, 12, 18, 36 |
| Common divisors | 1, 2, 3, 4, 6, 12 |
| Multiples of 84 | 84, 168, 252, ... |
| Multiples of 36 | 36, 72, 108, 144, 180, 216, 252, ... |

The greatest common divisor is 12, so `GCD(84, 36) = 12`. The first common multiple is 252, so `LCM(84, 36) = 252`.

### Prime factorization

At school, the GCD is usually computed through prime factorization:

- `84 = 2² · 3 · 7`
- `36 = 2² · 3²`

For the GCD you take the common factors with the smaller exponent, so `GCD = 2² · 3 = 12`. For the LCM you take all factors with the larger exponent, so `LCM = 2² · 3² · 7 = 252`. The factor 7 does not appear in the factorization of 36. It is convenient to assume it appears there with exponent zero, that is as 1. Then the GCD gets the smaller exponent 0 and the LCM gets the larger exponent 1.

This method shows well what the GCD and LCM are. In a program, however, it is slow, because factorizing a large number requires many divisions. That is why the code uses the Euclidean algorithm.

### Properties behind the Euclidean algorithm

1. `GCD(a, 0) = a`
2. `GCD(a, b) = GCD(a - b, b)` for `a > b`
3. `GCD(a, b) = GCD(b, a mod b)` for `b > 0`
4. `GCD(a, b) · LCM(a, b) = a · b`. Check: 12 · 252 = 3024 and 84 · 36 = 3024.
5. `GCD(a, b, c) = GCD(GCD(a, b), c)`, and the same holds for the LCM. The GCD of three numbers is computed step by step. First the GCD of the first two numbers, then the GCD of that result and the third number.

Why does property 2 hold? The pairs (84, 36) and (48, 36) have exactly the same common divisors: 1, 2, 3, 4, 6 and 12. Take the divisor 6. The number 84 is 14 sixes, and 36 is 6 sixes. Their difference, 48, is 8 sixes. In general, if `d` divides both `a` and `b`, it also divides their difference. If `d` divides both `b` and `a - b`, it also divides their sum, which is `a`. When moving from the pair `a`, `b` to the pair `a - b`, `b`, no common divisor is lost and no new one appears. That is why the GCD does not change.

Why does property 3 hold? The remainder of a division is the result of repeated subtraction. Subtract 36 from 84 and you get 48. Subtract 36 from 48 again and you get 12. Division with remainder gives the same result: 84 divided by 36 is 2 with remainder 12. Each subtraction preserves the GCD according to property 2, so `GCD(84, 36) = GCD(48, 36) = GCD(12, 36) = GCD(36, 12)`. The order of the numbers in the GCD does not matter.

### Euclidean algorithm with subtraction

This is the older version of the algorithm. The input is two natural numbers `a` and `b`, both greater than zero. The output is their GCD. Pseudocode from the `TEORIA.txt` file (written in Polish: `dopóki ... wykonuj` means "while ... do", `jeżeli` means "if", `w przeciwnym razie` means "else", `zwróć` means "return"):

```
dopóki a ≠ b wykonuj
    jeżeli a > b
        a ← a - b
    w przeciwnym razie
        b ← b - a
zwróć a
```

Trace for the numbers 84 and 36:

| Step | `a` | `b` | Operation |
| --- | --- | --- | --- |
| 0 | 84 | 36 | `a > b`, so `a ← 84 - 36` |
| 1 | 48 | 36 | `a > b`, so `a ← 48 - 36` |
| 2 | 12 | 36 | `a < b`, so `b ← 36 - 12` |
| 3 | 12 | 24 | `a < b`, so `b ← 24 - 12` |
| 4 | 12 | 12 | `a = b`, end, GCD = 12 |

This version has two drawbacks. If one of the numbers equals zero, the loop never ends, because subtracting zero changes nothing. For numbers of very different size, the algorithm runs for a long time. The GCD of one million and one requires 999 999 subtractions.

### Euclidean algorithm with the remainder of division

That is why in practice and at the matura exam the remainder version is used. In this version it is enough for at least one of the numbers to be non-zero. Pseudocode from the `TEORIA.txt` file:

```
dopóki b ≠ 0 wykonuj
    r ← a mod b
    a ← b
    b ← r
zwróć a
```

Trace for the numbers 84 and 36:

| Step | `a` | `b` | `r = a mod b` |
| --- | --- | --- | --- |
| 0 | 84 | 36 | 12 |
| 1 | 36 | 12 | 0 |
| 2 | 12 | 0 | `b = 0`, end, GCD = 12 |

The subtraction version needed five steps, while this one needs only three.

### Recursive version

The same algorithm can be written recursively, using properties 1 and 3:

- `GCD(a, b) = a` when `b = 0`
- `GCD(a, b) = GCD(b, a mod b)` when `b > 0`

When `b` equals zero, the recursion ends and `a` is returned. Otherwise the function calls itself with `b` and `a mod b`.

### Complexity

The subtraction version performs at most one subtraction fewer than the larger of the two numbers. That many subtractions are needed, for example, for one million and one. The remainder version has logarithmic complexity with respect to the smaller of the two numbers.

Lamé's theorem gives an exact bound. If `a ≥ b` and `b > 0`, the number of divisions does not exceed five times the number of digits of `b`. For 89 and 55 that is at most 10 divisions, and the algorithm performs 9. If `a < b`, the first division only swaps the numbers. In that case one extra division is added.

The worst case is two consecutive Fibonacci numbers. For `a > b` they are the smallest pair that requires a given number of divisions. For example, 89 and 55 are the smallest pair for which the algorithm performs 9 divisions. For `a ≥ b`, no pair with `a` not greater than 89 requires more divisions.

For the matura exam, the most important thing to remember is that the remainder version has logarithmic complexity and is faster than the subtraction version.

## Compliance with matura constraints

The implementation assumes the category of matura tasks in which built-in functions are not allowed. Python has the `gcd` and `lcm` functions in the `math` module, which compute the GCD and LCM directly, but the code does not use them. The GCD and LCM are computed only by self-written functions. They use `while` loops, `if` statements, recursion, comparisons, the `-`, `*` and `%` operators, and integer division (`//` in Python, `/` on integers in C++).

Input assumptions:

- `nwd_odejmowanie` works only for `a > 0` and `b > 0`. These will most likely be the assumptions at the matura exam.
- `nwd_dzielenie` and `nwd_rek` require at least one of the numbers to be non-zero.
- `nww` requires both numbers to be positive.

## Results

Both programs compute the values for `a = 84` and `b = 36`.

The Python version prints:

```
nwd odejmowanie:   12
nwd dzielenie:     12
nwd rekurencyjnie: 12
nww: 252
```

The C++ version prints:

```
nwd odejmowanie:   12
nwd dzielenie:     12
nwd rekurencyjnie: 12
nww:               252
```

The outputs differ only in the alignment of the last line. All three versions of the algorithm return a GCD of 12, and the LCM is 252. This matches the manual calculations from the theory section.

## Implementation notes

The function names indicate the algorithm version: `nwd_odejmowanie` (subtraction), `nwd_dzielenie` (remainder of division) and `nwd_rek` (recursive). The `nww` (LCM) function uses `nwd_dzielenie`. All functions are separated from the `main` function, which contains only the calls for the sample data.

In Python, the remainder version uses multiple assignment `a, b = b, a % b`, which updates both variables in a single line. In C++, a helper variable `r` is needed:

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

The LCM is computed from property 4, that is `LCM = a · b / GCD`. In Python, integers have no size limit, so the order of operations does not matter. The multiplication comes first, followed by integer division:

```python
def nww(a: int, b: int) -> int:
    """Iloczyn NWD i NWW jest równy iloczynowi liczb a i b, dlatego NWW = a * b / NWD"""
    return a * b // nwd_dzielenie(a, b)
```

In C++, the order matters. The product `a * b` may not fit in the `long long` type and cause an overflow. That is why `a` is first divided by the GCD, and only then multiplied by `b`. The result does not change, because `a` is always divisible by the GCD with no remainder:

```cpp
long long nww(long long a, long long b) {
    return a / nwd_dzielenie(a, b) * b;
}
```

In the C++ version, all functions use the `long long` type to handle larger numbers. The code uses the `<iostream>` header and `using namespace std` to stay compatible with what is used at school.

A bit of history: the original Euclidean algorithm is the subtraction variant. The remainder version is its later, optimized form. For the matura exam it is worth knowing both versions, understanding how they differ, and being able to implement them.
# Lab_6_Polinomios-CES_10
A CES-10 Lab, which implements a polynomial calculator

## Input

1. The polynomials' factors will be given in the form:
   
    > $\pm$ax^b meaning $\pm ax^b$

2. Factors can be at any order.
3. The null polynomial is written as:

    > "+0x^0;"

4. Except for the null polynomial, zero coefficients must **not** be written.
5. There is no rule for blank spaces between the factors of a polynomial.
6. Each polynomial ends in a semicolon.

## Output

1. The answers must be numbered.
2. The null polynomial must be written as:

   > $0;$

3. For all the other polynomials, do as following:

   * The factors must be in decrescent order of degree.
   * Do not write: "$+$" to the left of the head factor, factors with coefficient zero, expoent "$1$" or "$x^0$"
   * There must be exactly one single space before and after each "$+$" or "$-$" signal.
   * Use lowercase "$x$"

## Examples

* "- 2x^4 +       3x^3 + x^2 - x + 1;"
* "+x^3 -4x+ 2;"
* "- x^2 +4x+1;"
* "+    0x^0;"
  
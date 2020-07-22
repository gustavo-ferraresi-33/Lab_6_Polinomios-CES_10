/* Date: 12/07/2020
 * Author: Gustavo Ferraresi Gottschild
 * Compiled with: g++ 7.5.0 
 */

#include <iostream>
#include <cstdlib> // For "EXIT_FAILURE"
#include <fstream> 

#include "Polynomial.hpp"

using namespace std;

/* 
 * Prototypes
 */
void checkErr(bool cond,       string msg);
void initMess(ofstream &output);
void readPoly(ifstream &input, Polynomial *poly);


int main()
{
    /* 
     * Variable Declarations 
     */
    Polynomial *p1   = nullptr, // Input 1
               *p2   = nullptr, // Input 2
               *pOut = nullptr; // Result
    num_coef coef; // Coefficient of a polynomial
    int op = -1;   // Operation to be performed

    // Opening the input file
    ifstream input("/home/gustavoferraresi/Documents/ITAndroids/Estudo/POO/Lab_6_Polinomios-CES_10/Input", ifstream::in);
    checkErr( ! input.fail(), "Error! Input file not found!");
    // Opening the output file
    ofstream output("/home/gustavoferraresi/Documents/ITAndroids/Estudo/POO/Lab_6_Polinomios-CES_10/Output", ofstream::out);

    // Initial message
    initMess(output);
    
    vector<num_coef> cf = {-1, -1, 3, -5};
    auto p = new(nothrow) Polynomial(TYPE_INPUT);
    for(int i = 0; i < 4; i++)
        p->setCoeff(cf.at(i), i);
    p->printPoly(output);

    return 0;
}

/*
 * Function bodies 
 */

/* DONE */
// Check for error
void checkErr(bool cond, string msg)
{
                    cout << "@@@ CheckErr()" << endl;
    if(cond == false)
    {
        cout << msg << endl << endl;
        exit(EXIT_FAILURE);
    }
}

/* DONE */
// Initial message to the user
void initMess(ofstream &output)
{
                    cout << "@@@ initMess()" << endl;
    output << "########################################################" << endl;
    output << "###############  POLYNOMIAL  CALCULATOR  ###############" << endl;
    output << "########################################################" << endl;
}

/* WRITTEN, NOT TESTED */
// Read a polynomial
void readPoly(ifstream &input, Polynomial *poly)
{
                    cout << "@@@ readPoly()" << endl;                    
    // Variable declaration
    num_coef coef;     // Coefficient of the polynomial
    int deg = -1;      // Degree of a term of the polynomial
    char chAux = '\0'; // Auxiliar variable

    poly = new(nothrow) Polynomial(TYPE_INPUT);

    do
    {
        input >> chAux;
        if(chAux == CH_END)
            break;
        input >> coef;
        checkErr(coef >= 0, "Error! Invalid coefficient!");
        // Checking the signal validity
        switch(chAux)
        {
            case '+':                                                      break;
            case '-': coef = - coef;                                       break;
            default : checkErr(false, "Error! Invalid signal character!"); break;
        }
        input >> chAux; // Read "x"
        checkErr(chAux == 'x', "Error! Polynomial variable is not \"x\"!");
        input >> chAux; // Read "^"
        checkErr(chAux == '^', "Error! Power operator is not \"^\"!");
        input >> deg; // Degree of the term
        checkErr(deg >= 0, "Error! Invalid term degree!");
        poly->setCoeff(coef, deg);
    } while(chAux != CH_END);
}

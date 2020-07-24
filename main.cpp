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
void readPoly(ifstream &input, Polynomial **ptrPoly);
void readOperation(char *ptrOp, ifstream &input);
void executeOperation(char op, Polynomial *p1, Polynomial *p2, Polynomial **ptrResult_1, Polynomial **ptrResult_2);
void sumPoly(Polynomial *term1, Polynomial *term2, Polynomial **ptrSum);
void multiPoly(Polynomial *fact1, Polynomial *fact2, Polynomial **ptrProduct);
void divPoly(Polynomial *dividend, Polynomial *divisor, Polynomial **ptrQuotient, Polynomial **ptrRemainder);


int main()
{
    /* 
     * Variable Declarations 
     */
    Polynomial *p1    = nullptr, // Input 1
               *p2    = nullptr, // Input 2
               *pOut1 = nullptr, // Result 1
               *pOut2 = nullptr; // Result 2
    num_coef coef; // Coefficient of a polynomial
    char op = -1;  // Operation to be performed

    // Opening the input file
    ifstream input("/home/gustavoferraresi/Documents/ITAndroids/Estudo/POO/Lab_6_Polinomios-CES_10/Input", ifstream::in);
    checkErr( ! input.fail(), "Error! Input file not found!");
    // Opening the output file
    ofstream output("/home/gustavoferraresi/Documents/ITAndroids/Estudo/POO/Lab_6_Polinomios-CES_10/Output", ofstream::out);

    // Initial message
    initMess(output);

    for(int i = 0; i < 10; i++)
    {
        readOperation(&op, input);
        readPoly(input, &p1);
        readPoly(input, &p2);
        executeOperation(op, p1, p2, &pOut1, &pOut2);
        output << endl << endl << "@@" << i + 1 <<": ";
        pOut1->printPoly(output);
    }

    return 0;
}

/*
 * Function bodies 
 */

/* DONE */
// Check for error
void checkErr(bool cond, string msg)
{
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
    output << "########################################################" << endl;
    output << "###############  POLYNOMIAL  CALCULATOR  ###############" << endl;
    output << "########################################################" << endl;
}

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY */
// Read a polynomial
void readPoly(ifstream &input, Polynomial **ptrPoly)
{
                    cout << "@@@ readPoly()" << endl;                    
    // Variable declaration
    num_coef coef;     // Coefficient of the polynomial
    int deg = -1;      // Degree of a term of the polynomial
    char chAux = '\0'; // Auxiliar variable

    delete *ptrPoly;
    *ptrPoly = new(nothrow) Polynomial(TYPE_INPUT);

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
        checkErr(chAux == 'x' || chAux == 'X', "Error! Polynomial variable is not \"x\"!");
        input >> chAux; // Read "^"
        checkErr(chAux == '^', "Error! Power operator is not \"^\"!");
        input >> deg;   // Degree of the term
        checkErr(deg >= 0, "Error! Invalid term degree!");
        (*ptrPoly)->setCoeff(coef, deg);
    } while(chAux != CH_END);
}

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY */
void readOperation(char *ptrOp, ifstream &input)
{
                    cout << "@@@ readOperation()" << endl;    
    input >> *ptrOp;
    checkErr(   *ptrOp == 'S' || *ptrOp == 's' 
             || *ptrOp == 'P' || *ptrOp == 'p'
             || *ptrOp == 'D' || *ptrOp == 'd'
             , "Error! Invalid operation initial!");
}

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY, BUT IT IS NOT COMPLETED YET */
void executeOperation(char op, Polynomial *p1, Polynomial *p2, Polynomial **ptrResult_1, Polynomial **ptrResult_2)
{
                    cout << "@@@ executeOperation()" << endl;

    // Making the result polynomials become identically null polynomials
    delete *ptrResult_1;
    delete *ptrResult_2;
    *ptrResult_1 = new(nothrow) Polynomial(TYPE_OUTPUT);
    *ptrResult_2 = new(nothrow) Polynomial(TYPE_OUTPUT);

    switch(op)
    {
        case 'S':
        case 's': 
            sumPoly(p1, p2, ptrResult_1);
            break;
        case 'P':
        case 'p':
            multiPoly(p1, p2, ptrResult_1);
            break;
        case 'D':
        case 'd':                               
            break; 
        default : 
            checkErr(false, "Error! Invalid operation!");
            break;
    }
}

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY */
void sumPoly(Polynomial *term1, Polynomial *term2, Polynomial **ptrSum)
{
                    cout << "@@@ sumPoly()" << endl;        
    for(int i = 0; i <= G_MAX_IN; i++)
    {
        (*ptrSum)->setCoeff(term1->getCoef(i) + term2->getCoef(i), i);
    }
}

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY */
void multiPoly(Polynomial *fact1, Polynomial *fact2, Polynomial **ptrProduct)
{
                    cout << "@@@ multiPoly()" << endl;        
    for(int i = 0; i <= G_MAX_IN; i++)
        for(int j = 0; j <= G_MAX_IN; j++)
        {
            (*ptrProduct)->setCoeff((*ptrProduct)->getCoef(i + j) 
                                        + fact1->getCoef(i) * fact2->getCoef(j)
                                    , i + j);
        }
}

/* I HAVE NOT STARTED TO WRITE IT YET */
void divPoly(Polynomial *dividend, Polynomial *divisor, Polynomial **ptrQuotient, Polynomial **ptrRemainder)
{
    /* ESCRITO DE FORMA ZOADA SOH PRA EU CONSEGUIR COMPILAR */
                    cout << "@@@ diviPoly()" << endl;        
                int i;
    do
    {
        i = i;
    } while(false);
    
}
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
void checkErr
(bool cond,            string msg);
void initMess
(ofstream &output);
void readPoly
(ifstream &input,      Polynomial **ptrPoly);
void readOperation
(char *ptrOp,          ifstream &input);
void executeOperation
(char op,              Polynomial *p1,      Polynomial *p2,           Polynomial **ptrResult_1,
                       Polynomial **ptrResult_2);
void sumPoly
(Polynomial *term1,    Polynomial *term2,   Polynomial **ptrSum);
void multiPoly
(Polynomial *fact1,    Polynomial *fact2,   Polynomial **ptrProduct);
void divPoly
(Polynomial *dividend, Polynomial *divisor, Polynomial **ptrQuotient, Polynomial **ptrRemainder);
            /* void divPoly(Polynomial *dividend, Polynomial *divisor, Polynomial **ptrQuotient, Polynomial **ptrRemainder, ofstream &DEBUGoutput); */


int main()
{
    /* 
     * Variable Declarations 
     */
    Polynomial *p1    = nullptr, // Input 1
               *p2    = nullptr, // Input 2
               *pOut1 = nullptr, // Result 1
               *pOut2 = nullptr; // Result 2
    num_coef  coef;  // Coefficient of a polynomial
    char op = '\0';  // Operation to be performed

    // Opening the input file
    ifstream input("/home/gustavoferraresi/Documents/ITAndroids/Estudo/POO/Lab_6_Polinomios-CES_10/Input", ifstream::in);
    checkErr( ! input.fail(), "Error! Input file not found!");
    // Opening the output file
    ofstream output("/home/gustavoferraresi/Documents/ITAndroids/Estudo/POO/Lab_6_Polinomios-CES_10/Output", ofstream::out);

    // Initial message
    initMess(output);

    for(int i = 0; i < 14; i++)
    {
        readOperation(&op, input);
        readPoly(input, &p1);
        readPoly(input, &p2);
        /* 
         * PROBLEM:
         * THE DIVISION OPERANDS ARE ACTUALLY BEING READ APROPRIATELY, BUT,
         * WHEN THEY ARE PASSED TO THE "divPoly()" FUNCTION, THE DIVIDEND BECOMES
         * IDENTICALLY NULL
         */
                    /*              if(op == 'D' || op == 'd')
                                    {
                                        output << "$$$$$$ Division operands at ( " << i + 1 << " ):" << endl;
                                        output << "$$$ Dividend:  ";
                                        p1->printPoly(output);
                                        output << "$$$ Divisor:  ";
                                        p2->printPoly(output);
                                        output << endl;
                                    }
                    
                                    if(op != 'D' && op != 'd')
                                        executeOperation(op, p1, p2, &pOut1, &pOut2);
                                    else
                                    {
                                        delete pOut1;
                                        delete pOut2;
                                        pOut1 = new(nothrow) Polynomial(TYPE_OUTPUT);
                                        pOut2 = new(nothrow) Polynomial(TYPE_OUTPUT);
                                        divPoly(p1, p2, &pOut1, &pOut2, output);
                                    }
                    */
        executeOperation(op, p1, p2, &pOut1, &pOut2);
        output << endl << endl << "@@" << i + 1 <<": ";
        pOut1->printPoly(output);
        // Printig the remainder of the division
        if(op == 'D' || op == 'd')
        {
            output << "com resto  ";
            pOut2->printPoly(output);
        }
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

    // Initializing the polynomial being read as identically null 
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
            divPoly(p1, p2, ptrResult_1, ptrResult_2);
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

/* WRITTEN AND CHECKED, BUT NOT TESTED */
/* 
 * PROBLEM:
 * DA SEGUNDA DIVISAO EM DIANTE, O POLINOMIO "DIVIDENDO"
 * ESTAH COMECANDO A DIVISAO COMO SENDO IDENTICAMENTE
 * NULO
 */
/* void divPoly(Polynomial *dividend, Polynomial *divisor, Polynomial **ptrQuotient, Polynomial **ptrRemainder, ofstream &DEBUGoutput) */

void divPoly(Polynomial *dividend, Polynomial *divisor, Polynomial **ptrQuotient, Polynomial **ptrRemainder)
{
                    cout << "@@@ diviPoly()" << endl;        

    // Variable declaration
    int degTermQuot       = -1; // Degree of a quotient term
    num_coef coefTermQuot =  0; // Coefficient of a quotient term
                  /*   int DEBUGstep = 1; */

    do
    {

                    /*                 DEBUGoutput << "### iteration:  " << DEBUGstep << endl;
                                    DEBUGoutput << "###### DIVIDEND:  ";
                                    dividend->printPoly(DEBUGoutput);
                                    DEBUGoutput << "###### DIVISOR:  ";
                                    divisor->printPoly(DEBUGoutput);
                                    DEBUGoutput << "###### QUOTIENT:  ";
                                    (*ptrQuotient)->printPoly(DEBUGoutput);
                                    DEBUGoutput << "###### REMAINDER:  ";
                                    (*ptrRemainder)->printPoly(DEBUGoutput);
                     */
        degTermQuot = dividend->degPoly(TYPE_INPUT) - divisor->degPoly(TYPE_INPUT);
        // If the division can not be continued
        if(degTermQuot < 0)
            break;

        coefTermQuot = dividend->getCoef(dividend->degPoly(TYPE_INPUT)) / divisor->getCoef(divisor->degPoly(TYPE_INPUT));

        // Setting up the quotient's coefficient
        (*ptrQuotient)->setCoeff(coefTermQuot, degTermQuot);
        
        // Updating the dividend
        // The update process is made like this to ensure its RUBUSTNESS
        // Updating the dividend's previous leader coefficient to ZERO
        dividend->setCoeff(0, divisor->degPoly(TYPE_INPUT) + degTermQuot);
        //Updating the dividend's othr coefficients
        for(int i = divisor->degPoly(TYPE_INPUT) - 1; i >= 0; i--)
        {
            dividend->setCoeff(dividend->getCoef(degTermQuot + i)  - coefTermQuot * divisor->getCoef(i), degTermQuot + i);
        }
                            /* DEBUGstep++; */

    } while(degTermQuot >= 0);

    *ptrRemainder = dividend;
}
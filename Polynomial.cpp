#include <iostream>

#include "Polynomial.hpp"

// Constructor
Polynomial::Polynomial(Type newType)
{
    this->type = newType;
    if(this->type == TYPE_INPUT)
        this->coefficients.resize(G_MAX_IN + 1);
    if(this->type == TYPE_OUTPUT)
        this->coefficients.resize(G_MAX_OUT + 1);
}

/*-----------------------  Getters  -----------------------*/

Type Polynomial::getType()
{
    return this->type;
}

num_coef Polynomial::getCoef(int deg)
{
    return this->coefficients.at(deg);
}

/*-----------------------  Setters  -----------------------*/

void Polynomial::setType(Type newType)
{
    this->type = newType;
}

void Polynomial::setCoeff(num_coef newCoeff, int deg)
{
    this->coefficients.at(deg) = newCoeff;
}

/*-------------------  Other functions  -------------------*/

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY */
void Polynomial::printPoly(ofstream &output)
{
                        cout << "@@@ Polynomial::printPoly()" << endl;
    // Variable declaration
    int deg    = -1, // Degree of the polynomial
        maxDeg = -1; // Maximum polynomial's degree
    bool isNull = true; // Says if the polynomial is null
    
    if(this->type == TYPE_INPUT)
        maxDeg = G_MAX_IN;
    else
        maxDeg = G_MAX_OUT;

    // Checking the polynomial degree
    for(int i = maxDeg; i >= 0; i--)
        if(this->coefficients.at(i) != 0)
        {
            deg = i;
            isNull = false;
            break;
        }
    
    // If the polynomial is null
    if(isNull)
    {
        output << "0 ";
    }
    // If the polynomial is not null
    else
    {
        for(int i = deg; i >= 0; i--)
            if(this->coefficients.at(i) != 0)
            {
                // Writing the signal of the polynomial's coefficients which need it
                if(i < deg)
                {
                    if(this->coefficients.at(i) > 0)
                        output << "+";
                    else
                        output << "-";
                    // One blank space as a SIGNAL SEPARATOR 
                    output << " ";
                }
                else if(this->coefficients.at(i) < 0)
                {
                    // One blank space BEFORE and one AFTER the "-" signal
                    output << " - ";
                }

                // If the coefficient does not have module "1" or is the independent term
                if( (this->coefficients.at(i) != 1 && this->coefficients.at(i) != -1) 
                    || i == 0                                                         
                  )
                {
                    // Printing the MODULE of the coefficient
                    // OBS: an "if-else" structure is used because of its robustness
                    if(this->coefficients.at(i) >= 0)
                        output <<   this->coefficients.at(i);
                    else
                        output << - this->coefficients.at(i);
                }                

                if(i > 0)
                    output << "x";
                if(i > 1)
                {
                    output << "^";
                    output << i;
                }
                // One blank space as a TERM SEPARATOR
                output << " ";
            }
    }
    // Inserting the ending character
    output << CH_END << endl << endl;   
}

/* WRITTEN, CHECKED AND TESTED: IT IS WORKING PROPERLY */
int Polynomial::degPoly(Type polyType)
{
    // Variable declaration
    int maxDeg = -1; // Maximum polynomial degree
    
    switch(polyType)
    {
        case TYPE_INPUT: 
            maxDeg = G_MAX_IN;
            break;
        case TYPE_OUTPUT: 
            maxDeg = G_MAX_OUT;
            break;
        default:
            cout << "Error! Invalid polynomial type!" << endl << endl;
            exit(EXIT_FAILURE);
            break;
    }

    for(int i = maxDeg; i >= 0; i--)
    {
        if(this->coefficients.at(i) != 0)
            return i;
    }

    //If the polynomial is identically null
    return G_NULL;
}
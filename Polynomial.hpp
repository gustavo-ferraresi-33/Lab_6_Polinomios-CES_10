#include <fstream>
#include <vector>

#include "Constants_and_Types.hpp"
#include "Enum_Types.hpp"

using namespace std;

#ifndef LAB_6_POLYNOMIAL
#define LAB_6_POLYNOMIAL

class Polynomial
{
    private:
    
        /* CONVENTION FOR THE POLYNOMIAL COEFFICIENTS:
         * The coefficient of the term of degree "deg" of the polynomial
         * is the element "coefficients.at(deg)"
         */
        vector<num_coef> coefficients; // Coefficients of the polynomial
        Type type;                     // Type of the polynomial: input or output
    
    public:

        Polynomial(Type newType);

        /*-----------------------  Getters  -----------------------*/

        Type     getType();
        num_coef getCoef(int deg);

        /*-----------------------  Setters  -----------------------*/
        void setType(Type newType);
        void setCoeff(num_coef newCoeff, int deg);

        /*-------------------  Other functions  -------------------*/
        void printPoly(ofstream &output);
        int  degPoly(Type polyType);

};

#endif // LAB_6_POLYNOMIAL
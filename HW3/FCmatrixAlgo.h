#include <iostream>
#include <vector>
#include<Eigen/Core>

using namespace std;
using namespace Eigen;


class FCmatrixAlgo {
        public:
        FCmatrixAlgo() = default; // compiler do it
        ~FCmatrixAlgo() = default;

        static void GaussElimination(
        Matrix<double,Dynamic,Dynamic>&, // matrix coeffs
        Matrix<double,Dynamic,1>& // vector of constants
        ); //no pivoting

        static void GaussEliminationPivot(
        Matrix<double,Dynamic,Dynamic>& , // matrix coeff
        Matrix<double,Dynamic,1>& , // vector of constants
        VectorXi&//Matrix<int,Dynamic,1>&  row order indexing
        ); 

        static void LUdecomposition(
        Matrix<double,Dynamic,Dynamic>&, //matrix coeff
        Matrix<int,Dynamic,1>&, //row order indexing
        bool bpivot=false); //no pivoting


};

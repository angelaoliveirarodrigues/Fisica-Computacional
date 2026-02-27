// sistemas li
#include <Eigen/Dense>

int main(){
    Eigen::Matrix<double,10,3> M1;      //criar uma matriz de doubles 10 por 3 
    M1<<1,2,3,4,5,6,7,8,9,      
    10,11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,30;



    //Matriz dinamica 10 pr 3
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> M2(10,3);

    //replicate


    cout<<M1.rows() //dá o número de linhas
        <<M1.cols() //dá o número de colunas
    

    //loop over matrix rows
    for(auto v:M1.rowwise()){
        cout<<v<<endl;
    }

    //loop over matrix cols

    for(auto v:M1.colswise()){
        cout<<v<<endl;
    }

    //loop over matrix columns
    for(for i=0; i<M1.cols(); i++){
        cout<</*Falta aqui completar*/ <<endl;
    }
}

//
//create Matrices

MatrixXf M1 (2,2);
MatrixXf M2 (2,2);
MatrixXf M3 (2,2);

M1<<1,2,3,4;
M2<<5,6,7,8;

MR=(M1.array()+4).matrix()*M1; // Adicionar 4 a cada entrada da matriz; reconstruir a matriz e multiplicá-la por M1


MR=(M1.array()*M2.array()).matrix()*M1; //Multiplicar as matrizes, voltar a reconstruir a matrix e multiplicá-la pot M1


Eigen::Matrix3d A =Eigen::Matrix3d::Random();

//Calcular a soma
A.sum();

//Produto de todos os elementos
A.prod();

//Média 
A.mean();

//

#include <iostream>
#include <vector>
#include <initializer_list>
#include <map>
#include <functional>
#include <cmath>
#include <string>

using namespace std;


class Xvar {
    public:
    Xvar(): x(0) {;};
    Xvar(int ndepen):vardepe(ndepen){;};
    Xvar(vector<double> x_):x(x_) {;}; // passing vector

    // using initializer list to build object: X({1,2})
    Xvar(const initializer_list<double>& v) : x(v) {;};
    //~Xvar(){ printf("[%s]\n", __PRETTY_FUNCTION__);};
    ~Xvar()=default;

    // copy constructor
    Xvar(const Xvar& Xp){
         vardepe=Xp.vardepe;
         x=Xp.x;
    } 

    Xvar& operator=(const Xvar&); // assignment operator
    Xvar operator+(const Xvar&); // operator+
    double& operator[](int); // X[i]
    friend Xvar operator*(double, const Xvar&); // scalar*X 

    friend ostream& operator<< (std::ostream&, const Xvar&);

    vector<double>& X(){return x;}; // accessor to x

protected:
    vector<double> x;
    int vardepe;

};

//Implementação

Xvar& Xvar::operator=(const Xvar& Xp){
    vardepe= Xp.vardepe;
    x=Xp.x;
    return *this;
}
/*
Xvar Xvar::operator+(const Xvar& Xp){
    return Xvar(x+Xp.x);
}  */

Xvar Xvar::operator+(const Xvar& Xp) {
    Xvar X(vardepe);
    X.x.resize(vardepe);
    X.vardepe=vardepe; //atribui um número de variáveis dependentes ao novo elemento da class
        for (int i = 0; i < vardepe; i++) { // percorre todos os elementos do vetor para fazer a soma
            X.x[i]=x[i]+Xp.x[i];
        }
    return X;
}


double& Xvar::operator[](int n){
    if(n<0 || n>= vardepe){ //verifica se é possível existir esse indice 
        cout<< "Não existe nehnum termo com esse índice !"<<endl;        
    }
    return x[n];
}

Xvar operator*(double s, const Xvar& Xp){
    Xvar X;
    X.vardepe=Xp.vardepe;
    X.x.resize(Xp.vardepe+1);
    for (int i = 0; i <Xp.vardepe-1; i++)
    {
       X.x[i]=s*Xp.x[i];
    }
    
    return X;
} 


std::ostream& operator<< (std::ostream& s, const Xvar& Xp){
    s << "{";
    for (int i = 0; i < Xp.x.size() - 1; i++) {
        s << Xp.x[i] << ",";
    }
    s << Xp.x[Xp.x.size() - 1] << "}";
    return s;
}
  

class ODEpoint : public Xvar {

    public:
        ODEpoint() : t(-1), Xvar() {;}
        ODEpoint(double t_, Xvar a_) : t(t_), Xvar(a_) {;}
        ODEpoint(double t_, const vector<double>& v) : t(t_), Xvar(v) {;}
        ODEpoint(double t_, const std::initializer_list<double>& v) : t(t_), Xvar(v) {;}

        void SetODEpoint(double t_, Xvar& p);
        void SetODEpoint(double t_, const initializer_list<double>& v);
        void SetODEpoint(double t_, vector<double> v);

        double& T() { return t;} // accessor to time

    private:
    double t; // time
};


//Implementação

void ODEpoint::SetODEpoint(double t_, Xvar& p){
    t=t_ ;
    Xvar::operator=(p);
}

void ODEpoint::SetODEpoint(double t_, const initializer_list<double>& v){
   t=t_;
   Xvar::operator=(v);
}

void ODEpoint::SetODEpoint(double t_, vector<double> v){
    t=t_;
    Xvar::operator=(v);
}


class ODEsolver {
    public:
    ODEsolver(const vector<function<double(ODEpoint)>>& Func):F_(Func){;}
    ~ODEsolver(){ printf("[%s]\n", __PRETTY_FUNCTION__);}

    // set functions
    int SetODEfunc(const vector<function<double(ODEpoint)>>& Func){
       F_=Func;  
       return 0;
    };

    // solver methods
    const vector<ODEpoint>& Euler(ODEpoint i, double step, double T);
    const vector<ODEpoint>& PredictorCorrector(ODEpoint i, double step,double T);
    const vector<ODEpoint>& LeapFrog(ODEpoint i, double step, double T);
    const vector<ODEpoint>& RK2(ODEpoint i, double step, double T);
    const vector<ODEpoint>& RK4(ODEpoint i, double step, double T);
    const vector<ODEpoint>& Trapezoidal(ODEpoint i, double step, double T);

    const vector<function<double(ODEpoint)>> & F() {return F_;};
    map<string, vector<ODEpoint>> getMS() const { return MS; }


    private:
    vector<function<double(ODEpoint)>> F_;
    map<string, vector<ODEpoint>> MS; // key: "euler", "trapezoidal",

};

const vector<ODEpoint>& ODEsolver::Euler(ODEpoint i, double step, double T) {
    vector<ODEpoint> V1;
    V1.push_back(i);

    while (V1.back().T() < T) { // Enquanto o tempo for menor que o tempo total
        ODEpoint Pcurrent = V1.back();
        vector<double> novoX(Pcurrent.X().size());

        for (int n = 0; n < Pcurrent.X().size(); n++) { 
            novoX[n] = Pcurrent.X()[n] + step * F()[n](Pcurrent);
        }
        V1.push_back(ODEpoint(V1.back().T() + step, novoX));
    }
    MS.insert({"euler", V1});
    return MS["euler"];
}


const vector<ODEpoint>& ODEsolver::PredictorCorrector(ODEpoint i, double step,double T){
    vector<ODEpoint> V2;
    V2.push_back(i);

    while (V2.back().T() < T) {
        ODEpoint Pcurrent = V2.back();
        vector<double> newX;
        newX.reserve(Pcurrent.X().size());

        for (size_t n = 0; n < Pcurrent.X().size(); n++) {
            double newValue = Pcurrent.X()[n] + 0.5*step * F()[n](Pcurrent);
            newX.push_back(newValue);
        }

        ODEpoint Pnext(Pcurrent.T() + step*0.5, newX);
        
        newX.clear();

        for (size_t n = 0; n < Pcurrent.X().size(); n++) {
            double newValue = Pcurrent.X()[n] + 0.5 * step * (F()[n](Pcurrent) + F()[n](Pnext));
            newX.push_back(newValue);
        }

        ODEpoint Pcorrected(Pcurrent.T() + step, newX);
        V2.push_back(Pcorrected);
    }
    MS.insert({ "pcorrector", V2 });
    
    return MS["pcorrector"];
}


const vector<ODEpoint>& ODEsolver::LeapFrog(ODEpoint i, double step, double T) {
    vector<ODEpoint> V;
    V.push_back(i);

    while (V.back().T() < T) {
        ODEpoint Pcurrent = V.back();
        vector<double> novoX(Pcurrent.X().size());

        for (int n = 0; n < Pcurrent.X().size(); n++) {
            ODEpoint Pnext(Pcurrent.T() + step, Pcurrent.X());

            Pnext.X()[n] += step * F()[n](Pcurrent);
            novoX[n] = Pcurrent.X()[n] + 2.0 * step * F()[n](Pnext);
        }

        V.push_back(ODEpoint(V.back().T() + step, novoX));
    }

    MS["leap_frog"] = V;
    return MS["leap_frog"];
}

const vector<ODEpoint>& ODEsolver::RK2(ODEpoint i, double step, double T) {
    vector<ODEpoint> V; //vetor para armazenas os pontos de solução
    V.push_back(i); //inicializar com  os valores i
    while (V.back().T() <= T) {
        ODEpoint Pcurrent = V.back(); //Vamos utilizar o último ponto de V como o ponto atual
        vector<double> novoX; //vetor para armezenar os novos valores
        novoX.resize(Pcurrent.X().size());
        for (int n = 0; n < Pcurrent.X().size(); n++) {
            double K1 = step * F()[n](Pcurrent); //calcular K1
            ODEpoint Pnext(Pcurrent.T(),Pcurrent.X());
            Pnext.T() += step/2;
            Pnext.X()[n] =Pcurrent.X()[n] +K1/2;
            double K2 =step *F()[n](Pnext);
            novoX[n] = Pcurrent.X()[n] + K1 / 2 + K2; //aplicar RK
        }
        V.push_back(ODEpoint(V.back().T() + step, novoX)); // adicionar a solução a V para cada componente n; 
    }
    
    
    MS.insert({"RK2", V});
    return MS["RK2"];
}


const vector<ODEpoint>& ODEsolver::RK4(ODEpoint i, double step, double T){
    vector<ODEpoint> V;
    V.push_back(i);

    while(V.back().T() < T){
        ODEpoint Pcurrent = V.back();
        vector<double> novoX;
        novoX.resize(Pcurrent.X().size());

        for (int n = 0; n < Pcurrent.X().size(); n++){
            double K1 = step * F()[n](Pcurrent);
            ODEpoint Pnext(Pcurrent.T(),Pcurrent.X());
            Pnext.T() += step/2;
            Pnext.X()[n] =Pcurrent.X()[n] +K1/2;
            double K2 =step *F()[n](Pnext);
            Pnext.T() += step/2;
            Pnext.X()[n] =Pcurrent.X()[n] +K2/2;
            double K3 =step *F()[n](Pnext);
            Pnext.T() += step/2;
            Pnext.X()[n] =Pcurrent.X()[n] +K3;
            double K4 =step *F()[n](Pnext);
            novoX[n] = Pcurrent.X()[n] + (K1 + 2.0 * K2 + 2.0 * K3 + K4) / 6.0;
        }
        V.push_back(ODEpoint(V.back().T() + step, novoX));
    }

    MS.insert({"RK4", V});
    return MS["RK4"];
}


const vector<ODEpoint>& ODEsolver::Trapezoidal(ODEpoint i, double step, double T) {
    vector<ODEpoint> trajectory;
    trajectory.push_back(i);

    while (trajectory.back().T() < T) {
        ODEpoint currentPoint = trajectory.back();
        ODEpoint nextPoint(currentPoint.T() + step, currentPoint.X());

        for (size_t j = 0; j < currentPoint.X().size(); ++j) {
            double x_current = currentPoint.X()[j];
            double t_current = currentPoint.T();

            // Calculation of the rate of change at the current point using the Trapezoidal method
            double k1 = F_[j](currentPoint);
            double k2 = F_[j](nextPoint);

            // Calculation of the new value of x using the Trapezoidal method
            double x_next = x_current + step * (k1 + k2) / 2.0;
            nextPoint.X()[j] = x_next;  // Update the value directly in the X vector
        }

        trajectory.push_back(nextPoint);
    }

    MS["trapezoidal"] = trajectory;
    return MS["trapezoidal"];
}






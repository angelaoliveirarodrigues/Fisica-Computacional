#include <array>
#include <string>
#include <cstdio>
#include <iostream>

#include "TROOT.h"

using namespace std;

////Classes declaration

class Point2D{
//Declaração da class
    public:
    Point2D(float x=0, float y=0, string name= ""); //construtor
    virtual ~Point2D()=default; //destrutor
    Point2D(const Point2D&); //construtor cópia

//Operator

Point2D operator=(const Point2D&);
Point2D operator+(const Point2D&);
Point2D operator-(const Point2D&);
Point2D operator+=(const Point2D&);//P1+=P2 <=> P1=P1+P2
Point2D operator-=(const Point2D&); //P1-=P2 <=> P1=P1-P2
Point2D operator*(float scalar); //P*scalar
    

  //output
  friend ostream& operator<< (ostream&, const Point2D&);
    void Print() const;

protected:
    //precisamos de armazenar as coordenadas
    string name; //string que vai armazenar o nome do ponto
    array<float, 2> coo;//fazer uma array com as coordenadas
};

//Class herança
class Point3D:public Point2D{
    public:

    Point3D(float x, float y, float z_, string name_=""): Point2D(x,y,name), z(z_) {}; // estamos a usar o construtor de Point2D

    void Print() const;
    private:
    float z;
    //x e y são colocados devido à herança
};

//Desenhar um poli
/*class polygon{
    public:
    void Draw(); 


    private:
    vector<Point2D> V;
}*/
//////////////////////////////
//Implementação do código

//construtor
Point2D::Point2D(float x, float y, string name_){ //na implementação não são colocados valores por defeito---- Construtor
    coo={x,y};
    name=name_;
    printf("[%s] %s: (%.1f, %.1f)\n", __PRETTY_FUNCTION__,name.c_str(), coo[0], coo[1]);// __func__, __PRETTY_FUNCTION__
};

/* Destrutor
Point2D::~Point2D(){ 
    printf("[%s]\n", __PRETTY_FUNCTION__);
}*/

//copia
Point2D::Point2D(const Point2D& P){
    name=P.name+"_copy";
    coo=P.coo;
    printf("[%s] %s: (%.1f, %.1f)\n", __PRETTY_FUNCTION__,name.c_str(), coo[0], coo[1]);
};

// operators
Point2D Point2D::operator=(const Point2D& P){
    if (this != &P){
        printf("this:%p | &p : %p\n", this, &P);
        name=name+"_"+P.name;
        coo=P.coo;
    };
    return *this;
};


Point2D Point2D::operator+(const Point2D& P){
    return  Point2D(coo[0]+P.coo[0], coo[1]+P.coo[1], Form("%s_sum_%s", this->name.c_str(), P.name.c_str()));//s
};


Point2D Point2D::operator-(const Point2D& P){
    return Point2D(coo[0]-P.coo[0], coo[1]-P.coo[1], Form("%s_sub_%s", this->name.c_str(), P.name.c_str()) );
};


Point2D Point2D::operator+=(const Point2D& P){
    return Point2D(coo[0]+=P.coo[0], coo[1]+=P.coo[1], Form("%s_sum_equ_%s", this->name.c_str(), P.name.c_str()) );
};


Point2D Point2D::operator-=(const Point2D& P){
    return Point2D(coo[0]-=P.coo[0], coo[1]-=P.coo[1], Form("%s_sub_equ_%s", this->name.c_str(), P.name.c_str()) );
};


Point2D Point2D::operator*(float scalar){
    return Point2D(coo[0]*scalar, coo[1]*scalar,Form("%s_sub_%s", this->name.c_str(), Point2D::name.c_str()));
};


//friends
ostream& operator<< (ostream& s , const Point2D& P){
    s << P.name<< ": ("<< P.coo[0] << "," << P.coo[1]<<")";
    return s;
};


//others
void Point2D::Print() const {
    printf("[%s] %s: (%.1f, %.1f)\n", __PRETTY_FUNCTION__,name.c_str(), coo[0], coo[1]);
};


// class inheritance
void Point3D::Print() const {
    printf("[%s] %s: (%.1f, %.1f, %.1f)\n", __PRETTY_FUNCTION__,Point2D::name.c_str(), Point2D::coo[0], Point2D::coo[1], z);
};


////////////////////////////////////////Polimorfismo
void dummy(Point2D* p){ //aceita pointeiros da base Point2D e faz print
    p->Print();
};
////////////////////////////////


///Main Program
int main(){

    {
    Point2D P0;// com os valores predefinidos
    Point2D* p=new Point2D(10,20, "Pdynamic");
    printf("%p\n", p);
    delete p; // chama o destrutor e o objeto é apagado
    };
    
    Point2D P1(1,2,"P1");

    Point2D P2(P1);
    P2.Print();

    Point2D P3=P1; 
    cout<<P3<< endl;
    
    Point2D P4; //primeiro constroi depois faz a igualdade
    P4=P1;
    cout<<P4<<endl;

    cout<< "---------------------------------------- (P12=P11)=P10 \n";
    Point2D P10(1.24, 2.1, "P10"), P11(0.3,0.11, "P11"), P12(0,0,"P12");
    (P12=P11)=P10; // O valor de P12 fica igual ao de P11 e depois fica com o valor de P10
    cout<< "P12:"<< P12 <<endl;
    cout<<"P11:"<< P11<< endl;
    cout<<"P10:"<< P10<< endl;

    cout<<"---------------------------------------- operators \n";
    Point2D P20=P10+P11; //ou Point2D P20=P10.operator+(P10)
    cout<< P20<< endl;

    cout<< "---------------------------------------- inheritance\n";
    Point3D P();
    P.Print();

    dummy(&P20);
    dummy(&P); // P é um objeto da class 2D, mas devido ao polimorfismo o print que é chamado é o print da class Point3D
}
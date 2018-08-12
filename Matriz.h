#ifndef MATRIZ_H
#define MATRIZ_H
#include <vector>
#include <iostream>

using namespace std;

template <class T>
class Matriz{
 private:
  int f,c,dim;
  vector<T> mt; 

 public:
  Matriz(int, int);
  Matriz(int, int,vector<T>);
  ~Matriz();
  void set_matriz(vector<T>);
  int get_f() ; 
  int get_c() ;
  int get_dim() ;
  T traza(); 
  vector<T> get_mt() const ;
  Matriz(const Matriz &);
  T & operator()(int, int);
  T operator()(int, int) const;
  Matriz & operator = (const Matriz<T> &); 
};

#endif

//Constructor por defecto
template <class T>
Matriz<T>::Matriz(int a,int b){
  f=a;
  c=b;
  dim=f*c;
  for (int i=0;i<dim;++i)
    {
      mt.push_back(T(0));
    }
}
  

//Constructor 
template <class T>
Matriz<T>::Matriz(int a,int b,vector<T> A){
  f=a;
  c=b;
  dim=f*c; 
  if (A.size() == dim){
    mt = A;
    }
  else {
    for (int i=0;i<dim;++i)
      {
	mt.push_back(0);
      }
  }
  
}


//Destructor
template <class T>
Matriz<T>::~Matriz(){
}

//Retorna el numero de filas
template <class T>
int Matriz<T>::get_f(){
  return f; 
}

//Retorna el numero de columnas
template <class T>
int Matriz<T>::get_c(){
  return c; 
}

//Retorna la traza de una matriz cuadrada. 
template <class T>
T Matriz<T>::traza(){
  T suma=0;
  if (c==f){
    for(int i=0; i<c; ++i){
      suma+=mt[i+(c*i)]; 
    }
    return suma;
  }
  else{
    cout<< " la matriz no tiene traza "<<endl;
  };
}

//Retorna el numero de elementos de la matriz
template <class T>
int Matriz<T>::get_dim(){
  return dim;  
}


//Retorna el vector asociado a la matriz
template <class T>
vector<T> Matriz<T>::get_mt() const {
  return mt;  
}
//Asigna un vector como los elements de una matriz
template <class T>
void Matriz<T>::set_matriz(vector<T> A){
  mt=A; 
}

//Retorna el elemento A(i,j)
template <class T>
T & Matriz<T>::operator()(int i, int j)
{
  return mt[i*c+j];
}

//Retorna el elemento A(i,j) 
template <class T>
T Matriz<T>::operator() (int i, int j) const
{
  return mt[i*c+j];
}

//Contructor de copia
template <class T>
Matriz<T>::Matriz(const Matriz<T> & A){
  f=A.f;
  c=A.c;
  vector<T> v_copia = A.get_mt();
  mt= v_copia;
}




/*##############################################################################
########################### Sobrecarga de operadores ###########################
###############################################################################*/

//------------------------------Operador cout----------------------------------
template <class T>
ostream & operator << (ostream & os ,Matriz<T> M){
  int fila=M.get_f();
  int col=M.get_c();
  //vector<double> mt=M.get_mt();
  for (int i=0;i<fila;++i){
    for (int j=0;j<col;++j){
      os << M(i,j) << " ";
    }
    os << endl; 
  }
  return os;
}

//--------------------------Operador asignacion------------------------------

template <class T>
Matriz<T> &Matriz<T>::operator = (const Matriz<T> & M){
  vector<T> v_copia=M.get_mt();  
  mt= v_copia;
  return *this; 
}






//-------------------------------Operador Suma----------------------------------
template <class T>
Matriz<T> operator + (Matriz<T> X, Matriz<T> Y){
  if (X.get_f() == Y.get_f() && X.get_c() == Y.get_c()){
    vector<T> v_sum;
    int fila=X.get_f();
    int col=X.get_c();
    for (int i=0;i<fila;++i){
      for (int j=0;j<col;++j){
	v_sum.push_back(X(i,j)+Y(i,j)); 
      } 
    }
    Matriz<T> C(fila,col,v_sum);
    return C;
  }
  else{
    cout<<" No se puede realizar la suma"<<endl;
  }
}

//--------------------------------Operador Resta--------------------------------
template <class T>
Matriz<T> operator - (Matriz<T> X, Matriz<T> Y){
  if (X.get_f() == Y.get_f() && X.get_c() == Y.get_c()){
    vector<T> v_sum;
    int fila=X.get_f();
    int col=X.get_c();
    for (int i=0;i<fila;++i){
      for (int j=0;j<col;++j){
	v_sum.push_back(X(i,j)-Y(i,j)); 
      } 
    }
    Matriz<T> C(fila,col,v_sum);
    return C;
  }
  else{
    cout<<" No se puede realizar la suma"<<endl;
  }
}

//---------------------------Operador multiplicacion por escalar---------------
template <class T>
Matriz<T> operator * (T x, Matriz<T> Y){
  T escalar = x;
  vector<T> v_mul;
  int fila=Y.get_f();
  int col=Y.get_c();
  for (int i=0;i<fila;++i){
      for (int j=0;j<col;++j){
	v_mul.push_back(escalar*Y(i,j)); 
      } 
    } 
  Matriz<T> C(Y.get_f(),Y.get_c(),v_mul);
  return C;
}




//----------------------------Operador multiplicacion---------------------------
template <class T>
Matriz<T> operator * (Matriz<T> X, Matriz<T> Y){
  int fila_x=X.get_f();
  int fila_y=Y.get_f();
  int col_x=X.get_c();
  int col_y=Y.get_c();
  //cout << fila << " "<<col <<endl; 
  if (fila_y == col_x){
    vector<T> v_mul;
    for(int i=0; i<fila_x; ++i){
      for(int j=0; j<col_y; ++j){
	double suma=0;
	for(int k=0; k<col_x; ++k){ 
	  suma +=  X(i,k)* Y(k,j);
	}; 
	v_mul.push_back(suma); 
      }
    }
    Matriz<T> C(fila_x,col_y,v_mul);
    return C;
  }
  else {
    /*cout << "No se pueden multiplicar la matriz." << endl; 
      return  ;*/ 
  }
}


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
  void set_matriz(vector<T>); //carga los elementos de un vector en un matriz.
  int get_f() ; //entrega el numero de filas.
  int get_c() ; //entrega el numero de columnas. 
  int get_dim(); //entrega la dimension fxc.
  T traza(); 
  vector<T> get_fila(int); // entrega en un vector la fila seleccionada. 
  vector<T> get_col(int); // entrega en un vector la columna seleccionada.
  vector<T> get_mt() const ; //entrega en un vector todos los elementos de la matriz. 
  Matriz(const Matriz &); //contructor de copia. 
  T & operator()(int, int); //operador que entrega el elemento f,c seleccionado.
  T operator()(int, int) const; //operador que entrega el elemento f,c seleccionado.
  Matriz & operator = (const Matriz<T> &); //operador asignación. 
  Matriz<T> inter_fila(int, int); //intercambia las filas.
  Matriz<T> multiplicar_fila(T, int); // multiplica por un numero de tipo T la fila int selecionada.
  Matriz<T> suma_fila(int, int, T x); //le suma a la fila f2, el resultado de x*f1.
  vector<vector<T> > eliminacion_gauss(Matriz<T> );
  vector<T> resolver_sistema_gauss_jordan(Matriz<T>);
  vector<T> resolver_sistema_gauss(Matriz<T>);
  Matriz<T> inversa();
  T determinante();
  
  
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
    throw "la matriz no tiene traza ";
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

//Retorna el elemento A(i,j) i=0,1,...f-1 y j=0,1, ... c-1. 
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

//Retorna la fila de una matriz. 
template <class T>
vector<T> Matriz<T>::get_fila(int numero){
  Matriz<T> M(f,c,mt);
  vector<T> vec_fila;
  for(int j=0; j<c; ++j){
    vec_fila.push_back(M(numero,j)); ; 
  }
  return vec_fila; 
}

//Retorna la columna de una matriz. 
template <class T>
vector<T> Matriz<T>::get_col(int numero){
  Matriz<T> M(f,c,mt); 
  vector<T> vec_col;
  for(int i=0; i<f; ++i){
    vec_col.push_back(M(i,numero)); 
  }
  return vec_col; 
}
//intercambia hacia arriba la fila f2 con la f1. 
template <class T>
Matriz<T> Matriz<T>::inter_fila(int f1, int f2){
  vector<T> copia_mt=mt; 
  Matriz<T> M(f,c,copia_mt);
  for(int j=0; j<c ; ++j ){
    mt[f1*c+j]=T(1)*M(f2,j);
    mt[f2*c+j]=T(1)*M(f1,j); 
  };
  return *this;  
}


//multiplica por un numero de tipo T una fila f seleccionada. 
template <class T>
Matriz<T> Matriz<T>::multiplicar_fila(T x, int f1){
  vector<T> copia_mt=mt; 
  Matriz<T> M(f,c,copia_mt);
  for(int j=0; j<c ; ++j){
    mt[f1*c+j]=x*M(f1,j);
  };
  return *this; 
}

//suma la fila f2 el resultado de x*f1. 
template <class T>
Matriz<T> Matriz<T>::suma_fila(int f2, int f1, T x){
  vector<T> copia_mt=mt; 
  Matriz<T> M(f,c,copia_mt);
  for(int j=0; j<c ; ++j){
    mt[f2*c+j]= M(f2,j)+x*M(f1,j); 
  };
  return *this;
}

//#################################################TRIANGULAR SUPERIOR####################################################333
//Por medio del eliminación de gauss el algoritmo logra hacer un matriz triangular superior, guarda en un vector de vector la matriz *this, N, como tercer argumento los elementos para de la diagonal no reducida para así calcular el determinante.  
template <class T>
vector<vector<T> > Matriz<T>::eliminacion_gauss(Matriz<T> N){
  vector<vector<T> > vec_final; 
  Matriz<T> M(f,c,mt);
  vector<T> f_determinante;
  int iteraciones=0;
  for(int j=0; j<f; ++j){
    for(int k=j; k<f-1; ++k){
      for(int i=j; i<f-1; ++i){
	if(M(i,j)<=M(i+1,j)){
	  M.inter_fila(i,i+1);
	  N.inter_fila(i,i+1);
	  ++iteraciones; 
	}
      }
    }
    T escalar= T(1)/M(j,j);
    f_determinante.push_back(M(j,j));
    M.multiplicar_fila(escalar, j);
    N.multiplicar_fila(escalar, j);
    for(int i=j; i<f-1; ++i){
      T factor =M(i+1,j); 
      M.suma_fila(i+1, j, -factor);
      N.suma_fila(i+1, j, -factor);
    } 
  }
  //Se corregi los valores de la digonal triangular superior para que cuando se calcule el determinante este quede con el signo correcto. 
  if((iteraciones%2)==0){
    f_determinante[0]*=T(1);
  }
  else{
    f_determinante[0]*=T(-1); 
    }
  vec_final.push_back(M.get_mt());
  vec_final.push_back(N.get_mt());
  vec_final.push_back(f_determinante);
  return vec_final;
}

//####################GAUSS-JORDAN###############################################################3
//Esta matriz entrega el vector que resuelve el sistema de ecuaciones por método de gauss_jordan. Se le debe pasar por argumento la matriz que tiene las soluciones.  
template <class T>
vector<T > Matriz<T>::resolver_sistema_gauss_jordan(Matriz<T> N){
  vector<T> vec_Matriz=(*this).eliminacion_gauss(N)[0];
  vector<T> vec_soluciones=(*this).eliminacion_gauss(N)[1];
  Matriz<T> M(f,c,vec_Matriz);
  Matriz<T> M_sol(N.get_f(),N.get_c(),vec_soluciones);
  for(int j=f-1; j>0; --j){
    for(int i=j; i>0; --i){  
      T factor =M(i-1,j); 
      M.suma_fila(i-1,j, -factor);
      M_sol.suma_fila(i-1,j, -factor);
    }
  }
  return M_sol.get_mt(); 
}



//####################GAUSS-JORDAN###############################################################3
//Esta matriz entrega el vector que resuelve el sistema de ecuaciones por método de gauss. Se le debe pasar por argumento la matriz que tiene las soluciones.  
template <class T>
vector<T > Matriz<T>::resolver_sistema_gauss(Matriz<T> N){
  vector<T> vec_Matriz=(*this).eliminacion_gauss(N)[0];
  vector<T> vec_sol=(*this).eliminacion_gauss(N)[1];
  vector<T> soluciones;
  int pos= vec_sol.size(); 
  for(int i=0; i<vec_sol.size();++i ){
    soluciones.push_back(T(0));    
  }
  soluciones[pos-1]=vec_sol[pos-1];
  Matriz<T> M(f,c,vec_Matriz);
  for(int i=(f-1); i>0;--i){
    T valor=T(0);
    for(int j=0; j<c; ++j){
      valor += M(i,j)*soluciones[i];
      cout<<M(i-1,j)<<endl; 
    }
    soluciones[i-1]=valor-vec_sol[i-1];
  }
  return vec_Matriz; 
}


//##########################################INVERSA###############################################3
//Función que calcula la matriz inversa de la matriz. Se le pasa una función y se le acopla la matriz identidad. 
template <class T>
Matriz<T> Matriz<T>::inversa(){
  vector<T> vec_identidad; 
  for(int i=0; i<(*this).get_dim();++i){
    vec_identidad.push_back(T(0));
  }
  for(int i=0; i<(*this).get_f();++i){
    vec_identidad[i*c+i]=T(1);
  }
  Matriz<T> M(f,c,mt);
  Matriz<T> I(f,c,vec_identidad);
  vector<T> vec_inversa=M.resolver_sistema(I);
  Matriz<T> M_inv(f,c,vec_inversa);
  return M_inv; 
}

//##############DETERMINANTE #####################################################################. 
template <class T>
T Matriz<T>::determinante(){
  //Esta escrito así por la sintaxis de la funcion. 
  vector<T> Det=(*this).eliminacion_gauss(*this)[2];
  T det=1; 
  for(int i=0; i<f; ++i){
    det=det*Det[i];
  }
  return det; 
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
  //f=M.get_f();
  //c=M.get_c(); 
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


//---------------------------Operador multiplicacion por escalar a*T---------------
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

//---------------------------Operador multiplicacion por escalar T*a---------------
template <class T>
Matriz<T> operator * (Matriz<T> Y, T x){
  return x*Y;
}

//--------------------------------Operador Resta--------------------------------
template <class T>
Matriz<T> operator - (Matriz<T> X, Matriz<T> Y){
  if (X.get_f() == Y.get_f() && X.get_c() == Y.get_c()){
    return X+(T(-1)*Y);
  }
  else{
    cout<<" No se puede realizar la suma"<<endl;
  }
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
    for(int i=0; i<v_mul.size(); ++i){
      if(v_mul[i]<=T(0.000000000000001)){
	v_mul[i]=T(0);
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

// OPerador cout para vectores. 
template <class T>
ostream & operator << (ostream & os ,vector<T> v){
  for (int i=0;i<v.size();++i){
    os << v[i]<<",";
  }
  return os;
}



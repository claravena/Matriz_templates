#include <iostream>
#include "Matriz.h"
#include <complex>


using namespace std;

int main(){
  vector<double> v1 = {1,2,3,4,1,1};
  vector<double> v2 = {2,8,3,1,1,1};
  //vector<double> v3 = {1,2,3,4,5,6,7,8,9};
  /*complex<double> w1 = {1,2};
  complex<double> w2 = {1,2};
  complex<double> w3 = {1,2};  complex<double> w4 = {1,2};*/
  
  Matriz<double> M(2,3);
  Matriz<double> G(3,2);
  //Matriz<double> C(3,3,v3);
  /*Matriz<complex<double>> M(2,2);
  vector<complex<double>> v3;
  v3.push_back(w1);
  v3.push_back(w2);
  v3.push_back(w3);
  v3.push_back(w4);*/
  M.set_matriz(v1); 
  G.set_matriz(v2);
  int fila_M= M.get_f();
  int col_M= M.get_c();
  int fila_G= G.get_f();
  int col_G= G.get_c();
  
  cout << "La matriz M de "<< fila_M<< "x"<< col_M<<" es:" <<endl; 
  cout <<  M <<endl;
  cout << "La matriz G de "<< fila_G<< "x"<< col_G<<" es:"<<endl; 
  cout << G <<endl;
  cout << "El resultado de la operación (G-G)*(M+M) es:  "<<endl; 
  cout << (G-G)*(M+M) <<endl;
  cout << "El resultado de la operacion 2.0*M*G es:"<<endl; 
  cout << 2*M*G <<endl;
  
  return 0;
}


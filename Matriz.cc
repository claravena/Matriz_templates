#include <iostream>
#include "Matriz.h"
#include <complex>


using namespace std;

int main(){
  vector<double> v1 = {0,2,3,4,1,1};
  vector<double> v2 = {2,8,3,1,1,1};
  vector<double> v3 = {2,1,-1,-8,-3,-1,2,11,-2,1,2,3};
  //vector<double> v3 = {1,2,3,4,5,6,7,8,9};
  /*complex<double> w1 = {1,2};
  complex<double> w2 = {1,2};
  complex<double> w3 = {1,2};  complex<double> w4 = {1,2};*/
  
  Matriz<double> M(2,3,v1);
  Matriz<double> G(3,4);
  //Matriz<double> C(3,3,v3);
  /*Matriz<complex<double>> M(2,2);
  vector<complex<double>> v3;
  v3.push_back(w1);
  v3.push_back(w2);
  v3.push_back(w3);
  v3.push_back(w4);*/
  //M.set_matriz(v1); 
  G.set_matriz(v3);
  int fila_M= M.get_f();
  int col_M= M.get_c();
  int fila_G= G.get_f();
  int col_G= G.get_c();
  vector<double> m= M.get_fila(1); 
  //for(int i=0; i< m.size(); ++i){
  //cout<< m[i]<<endl; 
    //}
  //cout << M<<endl;
  /*cout << "La matriz M de "<< fila_M<< "x"<< col_M<<" es:" <<endl; 
  cout <<  M <<endl;
  cout << "La matriz G de "<< fila_G<< "x"<< col_G<<" es:"<<endl; 
  cout << G <<endl;
  cout << "El resultado de la operación (G-G)*(M+M) es:  "<<endl; 
  cout << (G-G)*(M+M) <<endl;
  cout << "El resultado de la operacion 2.0*M*G es:"<<endl; 
  cout << 2*M*G <<endl;
  */
  G.multiplicar_fila(1./G(0,0),0);
  G.suma_fila(1,0,3.0);
  G.suma_fila(2,0,2.0);
  G.multiplicar_fila(1./G(1,1),1);
  G.suma_fila(2,1,-2.0);
  cout << M.ordenar()<<endl; 
  return 0;
} 

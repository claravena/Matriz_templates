#include <iostream>
#include "Matriz.h"
#include <complex>


using namespace std;

int main(){
  vector<double> v1 = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
  vector<double> v2 = {2,-1,1};
  vector<double> v3 = {1,1,0,1,3,0,1,0,2,1,0,0,4,0,0,1};
  vector<double> v4 = {1,2,3,4,5,6,7,8,0};
  Matriz<double> M(3,1,v2);
  Matriz<double> G(3,3,v4);
  //cout<<G.eliminacion_gauss(M)[1]<<endl;    
  //cout<<G.determinante()<<endl; 
  //cout<<G.inversa()<<endl;
  //cout<<A.ordenar(A)[0]<<endl;
  //cout<<M<<endl; 
  //cout<<M.traza()<<endl; 
  cout<<G.resolver_sistema_gauss_jordan(M); 
  return 0;
} 

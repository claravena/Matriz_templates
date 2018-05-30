#include <iostream>
#include "Matriz.h"

using namespace std;

int main(){
  vector<double> v1 = {1,2,3,4,1,1};
  vector<double> v2 = {2,8,3,1,1,1};
  Matriz<double> M(2,3);
  Matriz<double> G(3,2);
  Matriz<double> C(2,2);
  
  
  M.set_matriz(v1);
  //G.set_matriz(v2);
  cout <<C.get_f()<<" "<< C.get_c()<<" "<<C.get_dim()<<endl;
  C=M;
  cout <<C.get_f()<<" "<< C.get_c()<<" "<< C.get_dim()<<endl;
  //cout <<G(0,1)<<endl;
  //cout <<G(2,0)<<endl;
  //cout << G*M <<endl; 
  //cout <<M<<endl;
  //cout <<2.0*M<<endl;
  //cout <<2.0*G<<endl;
  
  return 0;
}

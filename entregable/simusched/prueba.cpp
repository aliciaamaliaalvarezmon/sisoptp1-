#include <iostream>
#include <tuple>
#include <queue>
#include <vector>


using namespace std;


int main(int argc, char* argv[]) {

 // priority_queue<tuple<int,int>, vector<tuple<int,int> >, greater<tuple<int,int> >cola;
  /*cola.push(make_tuple(8,0));
  cola.push(make_tuple(3,1));
  cola.push(make_tuple(5,2));*/

  priority_queue<int,vector<int>,greater<int> > cola;

    
  cola.push(8);
  cola.push(3);
  cola.push(5);

  int i = 0;
  for (i=0; i<3; i++){
    cout << cola.top() << endl;
    cola.pop();
    //cout << "tupla" << i << " : " << get<0>(cola.top()) << endl;
  }

  return 0;
}


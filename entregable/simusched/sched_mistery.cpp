#include "sched_mistery.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedMistery::SchedMistery(vector<int> argn) {
}

SchedMistery::~SchedMistery() {

}


void SchedMistery::load(int pid) {
  vector<int>* parametros = tsk_params(pid);
  int longitud = (*(parametros))[0];
  cout << "LONG MISTERY - Pid: " << pid << " - LONG: " << longitud << endl;
  cola.push(make_tuple(longitud, pid));
}

void SchedMistery::unblock(int pid) {
}

int SchedMistery::tick(int cpu, const enum Motivo m) {

  if (m == EXIT) {
    // Si el pid actual terminó, sigue el próximo.
    if (cola.empty()) return IDLE_TASK;
    else {
      int sig = get<1>(cola.top()); 
      cola.pop();
      return sig;
    }
  } else {
    // Siempre sigue el pid actual mientras no termine.
    if (current_pid(cpu) == IDLE_TASK && !cola.empty()) {
      int sig = get<1>(cola.top()); 
      cola.pop();
      return sig;
    } else {
      return current_pid(cpu);
    }
  }
}


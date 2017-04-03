#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	//argn[0] == numero de cores	
	for(i = 0; i < argn[0]; i++){
		ticks.push_back(argn[i+1]);
	}

	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	q.push(pid);
}

void SchedRR::unblock(int pid) {
}

int SchedRR::tick(int cpu, const enum Motivo m) {//el cpu= core corriendo, Motivo m: porque bloqueado
		if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (q.empty()) return IDLE_TASK;
		else {
			int sig = q.front(); q.pop();
			return sig;
		}
	} else {		
		if(m == TICK){
			if (current_pid(cpu) == IDLE_TASK && !q.empty()) {
			int sig = q.front(); q.pop();
			return sig;
			}else{
				if(current_time() == ticks[current_pid(cpu)]){ //no deberia pasarse de igual?	
					if (q.empty()) return current_pid(cpu);
					else {							
						int sig = q.front(); q.pop();
						q.push(current_pid(cpu));
						return sig;
					}
				//falta tirar el time a 0;
				}
			}
		}
		if(m == BLOCK){
			if(current_time() == ticks[current_pid(cpu)]){
				unblock(current_pid()); //no deberia pasarse de igual?
				if (q.empty()) return current_pid(cpu);
				else {							
					int sig = q.front(); q.pop();
					q.push(current_pid(cpu));
					return sig;
				}
			//falta tirar el time a 0;
			}


		}	
	} 
}










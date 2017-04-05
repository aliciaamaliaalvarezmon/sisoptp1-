#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	//argn[0] == numero de cores	
	for(int i = 0; i < argn[0]; i++){
		ticksXCore.push_back(argn[i+1]);
		ticksActuales.push_back(0);
		
	}
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	ready.push(pid);
}

void SchedRR::unblock(int pid) {

	for (unsigned int i = 0; i < waiting.size(); ++i)
	{
		if (waiting[i]==pid)
		{
			waiting[i]=-1;
		}
	}
	ready.push(pid);

}

int SchedRR::tick(int cpu, const enum Motivo m) 
{//el cpu= core corriendo, Motivo m: porque bloqueado
		
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (ready.empty()){ 
			return IDLE_TASK;
		}else {
			int sig = ready.front(); ready.pop();
			return sig;
		}
	} else{		
		if(m == TICK){

			if(current_pid(cpu)==	IDLE_TASK && !ready.empty()){
				int next = ready.front();
				ready.pop();
				return next;
			}else if (current_pid(cpu)==IDLE_TASK && ready.empty()){
				return IDLE_TASK;
			}else{
				ticksActuales[cpu]++;
				if (ticksActuales[cpu]==ticksXCore[cpu] && ready.empty()){
					// TODO : Revisar si va 0 o 1  Hacer graficos y comparar.
					ticksActuales[cpu]=0;
					return current_pid(cpu);
				}else{
					if (ticksActuales[cpu]==ticksXCore[cpu] && !ready.empty()){
						ticksActuales[cpu]=0;
						int next = ready.front();
						ready.pop();
						ready.push(current_pid(cpu));
						return next;
					}

				}// TODO : REVISAR
				
				return current_pid(cpu);
			}

		}else if (m==BLOCK){
				waiting.push_back(current_pid(cpu));

				if (ready.empty()){
					return IDLE_TASK;
				}else{
					int next = ready.front();
					ready.pop();
					return next;
				}

		}
		
	} 
}










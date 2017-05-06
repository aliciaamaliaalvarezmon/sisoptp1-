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


int SchedRR::dameSiguiente()
{
	if (ready.empty()){return IDLE_TASK;}
	else
	{
		int sig = ready.front();
		ready.pop();
		return sig;
	}
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	// Obtengo PID Tarea actual en CPU
	int cpid = current_pid(cpu);

	if (cpid==IDLE_TASK)
	{
		ticksActuales[cpu]=0;
		return dameSiguiente();
	}

	switch(m)
	{	// La Tarea actual NO es la IDLE
		case EXIT:
		ticksActuales[cpu]=0;
		return dameSiguiente();
		case BLOCK:
		waiting.push_back(cpid);
		ticksActuales[cpu]=0;
		return dameSiguiente();
		case TICK:
		ticksActuales[cpu]+=1;
		if (ticksActuales[cpu]==ticksXCore[cpu])
		{	ready.push(cpid);
			ticksActuales[cpu]=0;
			return dameSiguiente();
		}
		else{return cpid;}
	}


}	


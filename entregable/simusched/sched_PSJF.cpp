#include <vector>
#include <queue>
#include "sched_PSJF.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedPSJF::SchedPSJF(vector<int> argn) {

// Preemptive Shortest Job First a primera vista no se esta rigiendo por quantums, sino por la prioridad de las tareas que ejecuta
}

SchedPSJF::~SchedPSJF() {

}


void SchedPSJF::load(int pid) {
	vector<int>* hola = tsk_params(pid);//en 0 estan la prioridad, en 1 la duracion
	int prioridad = (*(hola))[0]-1; 
	int duracion = (*(hola))[1];
	colas[prioridad].emplace(duracion,pid);

}

void SchedPSJF::unblock(int pid) {
//Uy!!!,el unlock... bue, solo vienen tareas CPU, asi que no hay drama.
}

int SchedPSJF::DameSiguiente()
{
	for (int i = 0; i < 5; ++i)
	{
		if (colas[i].empty()==false)
		{
			int next = get<1>(colas[i].top());
			colas[i].pop();
			return next;	
		}
	}
	return IDLE_TASK;
}



int SchedPSJF::tick(int cpu, const enum Motivo m) //NUNCA VA A SER BLOCK!!
{//el cpu= core corriendo, Motivo m: porque bloqueado
	if (m==EXIT){return DameSiguiente();}
	if (m==TICK)
	{
		if (current_pid(cpu)==IDLE_TASK){return DameSiguiente();}
		else
		{
			int pidActual=current_pid(cpu);
			int pioridadActual=(*(tsk_params(current_pid(cpu))))[0]-1;
			int duracion=(*(tsk_params(current_pid(cpu))))[1];

			for (int i = 0; i < pioridadActual; ++i)
			{
				if (colas[i].empty()==false)
				{
				colas[pioridadActual].emplace(duracion,pidActual);
				int next = get<1>(colas[i].top());
				colas[i].pop();
				return next;
				}	
			}
			if ((colas[pioridadActual].empty()==false) && 
			(get<0>(colas[pioridadActual].top())<duracion))
			{
				colas[pioridadActual].emplace(duracion,pidActual);
				int next = get<1>(colas[pioridadActual].top());
				colas[pioridadActual].pop();
				return next;
			}
			return current_pid(cpu);
		}
	}
}
		



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
	vector<int>* datos = tsk_params(pid);//en 0 estan la prioridad, en 1 la duracion
	int prioridad = (*(datos))[0]-1; //El array tiene indices del 0 al 4 y las pioridades del 1 al 5
	int duracion = (*(datos))[1];	//Por eso resto 1.
	colas[prioridad].emplace(duracion,pid);

}

void SchedPSJF::unblock(int pid) {
//Uy!!!,el unlock... bue, solo vienen tareas CPU, asi que no hay drama.
}

int SchedPSJF::DameSiguiente()
{//Devuelve la tarea mas pioritaria y de menor duracion. En caso de que no haya tareas,devuelve la IDLE
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

/*int SchedPSJF::tick(int cpu, const enum Motivo m) //NUNCA VA A SER BLOCK!!
{	if (m==EXIT || current_pid(cpu) == IDLE_TASK)
	return DameSiguiente();
	else
	{
	load(current_pid(cpu));
	return DameSiguiente();
	}  //Esta version no la voy a probar pero apostaria a que anda
	   //Si no es exit y la tarea actual no es la idle,pushea el pid actual 
	   //y pide la siguiente tarea mas pioritaria.
	   //Si es la unica que hay o es la mas pioritaria, devuele la que pushee antes
}
*/
int SchedPSJF::tick(int cpu, const enum Motivo m) //NUNCA VA A SER BLOCK!!
{//el cpu= core corriendo, Motivo m: porque bloqueado
	if (m==EXIT){return DameSiguiente();}
	if (m==TICK)
	{
		if (current_pid(cpu)==IDLE_TASK){return DameSiguiente();}
		else
		{	//Obtengo datos de la tarea actual.
			int pidActual=current_pid(cpu);
			int pioridadActual=(*(tsk_params(current_pid(cpu))))[0]-1;
			int duracion=(*(tsk_params(current_pid(cpu))))[1];
			//Pregunto por las colas de pioridad menor en orden, si hay alguna tarea para correr
			for (int i = 0; i < pioridadActual; ++i)
			{
				if (colas[i].empty()==false)
				{
				colas[pioridadActual].emplace(duracion,pidActual); //Pusheo pid actual
				int next = get<1>(colas[i].top());
				colas[i].pop();
				return next;
				}	
			} //Si salgo del for es que las colas de pioridad mas urgente estan vacias
			if ((colas[pioridadActual].empty()==false) && //Pregunto si la cola de pioridad
			(get<0>(colas[pioridadActual].top())<duracion)) //de la tarea actual es no vacia
			{												//y si la duracion es menor
				colas[pioridadActual].emplace(duracion,pidActual);
				int next = get<1>(colas[pioridadActual].top());
				colas[pioridadActual].pop();
				return next;
			}
			return current_pid(cpu);
		}
	}
}
		



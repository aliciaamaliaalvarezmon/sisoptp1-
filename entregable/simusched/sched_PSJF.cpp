#include <vector>
#include <queue>
#include "sched_PSJF.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedPSJF::SchedPSJF(vector<int> argn) {
	colas.push_back(mypq1);
	colas.push_back(mypq2);
	colas.push_back(mypq3);
	colas.push_back(mypq4);
	colas.push_back(mypq5);

// Preemptive Shortest Job First a primera vista no se esta rigiendo por quantums, sino por la prioridad de las tareas que ejecuta
}

SchedPSJF::~SchedPSJF() {

}


void SchedPSJF::load(int pid) {
	vector<int>* hola = tsk_params(pid);//en 0 estan la prioridad, en 1 la duracion
	int prioridad = (*(hola))[0]; 
	int duracion = (*(hola))[1];

	if(prioridad==1){
		mypq1.push(make_tuple(duracion, pid));
	}
		if(prioridad==2){
		mypq2.push(make_tuple(duracion, pid));
	}
		if(prioridad==3){
		mypq3.push(make_tuple(duracion, pid));
	}
		if(prioridad==4){
		mypq4.push(make_tuple(duracion, pid));
	}
		if(prioridad==5){
		mypq5.push(make_tuple(duracion, pid));
	}
}

void SchedPSJF::unblock(int pid) {
//Uy!!!,el unlock... bue, solo vienen tareas CPU, asi que no hay drama.
}

int SchedPSJF::tick(int cpu, const enum Motivo m) //NUNCA VA A SER BLOCK!!
{//el cpu= core corriendo, Motivo m: porque bloqueado
		
	if (m == EXIT) {
		// Se va viendo quien es la siguienta tarea siguiendo las prioridades
		if (mypq1.empty()){ 
			if(mypq2.empty()){
				if(mypq3.empty()){
					if(mypq4.empty()){
						if(mypq5.empty()){
							return IDLE_TASK;
						}else{
						 int sig = get<1>(mypq5.top());
						 mypq5.pop();
						 return sig;		
						}
					}else{
						 int sig = get<1>(mypq4.top());
						 mypq4.pop();
						 return sig;
					}
				}else{
					 int sig = get<1>(mypq3.top());
					 mypq3.pop();
					 return sig;
				}
			}else{
				 int sig = get<1>(mypq2.top());
				 mypq2.pop();
				 return sig;
			}			
		}else {
			int sig = get<1>(mypq1.top());
			mypq1.pop();
			return sig;
		}
	} else{		
		if(m == TICK){
			if(current_pid(cpu)==IDLE_TASK){
				if(!mypq1.empty()){
				int next = get<1>(mypq1.top());
				mypq1.pop();
				return next;				
			}else if(mypq1.empty() && !mypq2.empty()){				
				int next = get<1>(mypq2.top());
				mypq2.pop();
				return next;	
			}else if(mypq1.empty() && mypq2.empty() && !mypq3.empty()){			
				int next = get<1>(mypq3.top());
				mypq3.pop();
				return next;
			}else if(mypq1.empty() && mypq2.empty() && mypq3.empty() && !mypq4.empty()){
				int next = get<1>(mypq4.top());
				mypq4.pop();
				return next;
			}else if(mypq1.empty() && mypq2.empty() && mypq3.empty() && mypq4.empty() && !mypq5.empty()){
				int next = get<1>(mypq5.top());
				mypq5.pop();
				return next;
			}else if(mypq1.empty() && mypq2.empty() && mypq3.empty() && mypq4.empty() && mypq5.empty()){
				return IDLE_TASK;
			}				
			}else{
				int prioridad = (*(tsk_params(current_pid(cpu))))[0];
				for(int i =1; i <= prioridad; i++){
					if(i == prioridad){
						if( !colas[i-1].empty() and get<0>(colas[i-1].top()) < prioridad){
							int next = get<1>(colas[i].top());
							colas[i-1].pop();
							colas[prioridad-1].push(make_tuple((*(tsk_params(current_pid(cpu))))[0],current_pid(cpu)));
							return next;
						}else{
							return current_pid(cpu);
						}						
					}//Si llega aca es porque es menor, osea que tiene mayor prioridad
					if(!colas[i-1].empty()){
						int next = get<1>(colas[i-1].top());
						colas[i-1].pop();
						return next;
					}
				}				
				
			}

		}
		
	} 
}






//hola



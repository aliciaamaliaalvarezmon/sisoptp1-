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
	if (ready.size()==0){return IDLE_TASK;}
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
		break;
		case BLOCK:
		waiting.push_back(cpid);
		ticksActuales[cpu]=0;
		return dameSiguiente();
		break;
		case TICK:
		ticksActuales[cpu]+=1;
		if (ticksActuales[cpu]==ticksXCore[cpu])
		{	ready.push(cpid);
			ticksActuales[cpu]=0;
			return dameSiguiente();
		}
		else{return cpid;}
		default:
		return IDLE_TASK;
	}


}	


// int SchedRR::tick(int cpu, const enum Motivo m) {
   
//   if(ticksActuales[cpu] == ticksXCore[cpu]){
//     ticksActuales[cpu] = 0;
//   }

//   int cpid = current_pid(cpu);
   
//   if( m == EXIT){
    
//     if(!ready.empty()){
//       int sig = ready.front(); ready.pop();
//       ticksActuales[cpu]++;
//       return sig;
//     }else{ 
//       return IDLE_TASK;
//     }
  
//   }else if(m == TICK){

//     if(cpid == IDLE_TASK && ready.empty()) return IDLE_TASK;
//     else if(cpid == IDLE_TASK && !ready.empty()){
//       int sig = ready.front(); ready.pop();
//       ticksActuales[cpu]++;
//       return sig;
//     }else{ 
//       if(ticksActuales[cpu] == 0 && ready.empty()){
//         ticksActuales[cpu]++;
//         return cpid;
//       }else if(ticksActuales[cpu] == 0){
//         int sig = ready.front(); ready.pop();
// 				ready.push(cpid);
//         ticksActuales[cpu]++;
//         return sig;
//       }else{ /*Si ticksActuales[cpu] != 0*/
//         ticksActuales[cpu]++;
//         return cpid;
//       }
//     }
  
//   }else{ /* m == BLOCK*/
//     waiting.push_back(cpid);
    
//     if (ready.empty()) return IDLE_TASK;
// 		else{
// 		  int sig = ready.front(); ready.pop();
//       ticksActuales[cpu]++;
// 			return sig;
//     }

//   }
// }

/*
int SchedRR::tick(int cpu, const enum Motivo m) 
{//el cpu= core corriendo, Motivo m: porque bloqueado
  cout << "CPU: " << cpu << " Motivo: " << m << endl;
  cout << "Pid: " << current_pid(cpu) << endl; 	
  cout << "ticks ac " << ticksActuales[cpu] << endl; 	
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (ready.empty()){ 
      if(ticksActuales[cpu] == ticksXCore[cpu]){
          ticksActuales[cpu] = 0;
      }
			return IDLE_TASK;
		}else {
      if(ticksActuales[cpu] == ticksXCore[cpu]){
          ticksActuales[cpu] = 0;
      }
			int sig = ready.front(); ready.pop();
			return sig;
		}
	} else{		
		if(m == TICK){

			if(current_pid(cpu)==	IDLE_TASK && !ready.empty()){
				int next = ready.front();
				ready.pop();
        if(ticksActuales[cpu] == ticksXCore[cpu]){
            ticksActuales[cpu] = 0;
        }
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

				}				
				return current_pid(cpu);
			}

		}else if (m==BLOCK){
				waiting.push_back(current_pid(cpu));

				if (ready.empty()){
					return IDLE_TASK;
				}else{
				 ticksActuales[cpu]++;
          if(ticksActuales[cpu] == ticksXCore[cpu]){
            ticksActuales[cpu] = 0;
          }

					int next = ready.front();
					ready.pop();
					return next;
				}

		}
		
	} 
}*/










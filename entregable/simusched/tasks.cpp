#include "tasks.h"
#include <iostream>

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) {
  int n = params[0];
  int bmin = params[1];
  int bmax = params[2];
  srand(5);
  //tengo que hacer n llamadas bloqueantes
	for(int i = 0; i < n; i++) {
	  //duracion al azar
    int random =  bmin + ( rand() % ( bmax - bmin + 1 ) );
		 uso_IO(pid, random);
	}
}


void TaskPajarillo(int pid , vector<int> params){
	int cant_repeticiones = params[0];
	int tiempo_cpu = params[1];
	int tiempo_bloqueo = params[2];

	for (int i = 0; i < cant_repeticiones; ++i)
	{
		uso_CPU(pid,tiempo_cpu);
		uso_IO(pid,tiempo_bloqueo);
	}
}




void TaskPriorizada(int pid , vector<int> params){
	if ((params[0] > 5) || (params[0] < 0)){
		cerr << "No hay esa prioridad" << endl;
	}
	uso_CPU(pid, params[1]);
}






void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskPajarillo, 3);
	register_task(TaskPriorizada, 2);
}

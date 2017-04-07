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

int dameRandom(int a , int b)
{
	srand(5); //Fijamos la semilla para repetir los resultados
	int random ;
	while (true)
	{	
		random = rand() % (b+1);
		if (random > a-1)
		{
			return random;
		}
	}
	
}


void TaskConsola(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
  int n = params[0];
  int ms_pid = params[1];//bmin
  int ms_io = params[2];//bmax
	for(int i = 0; i < n; i++) {//tengo que hacer n (params[0]) llamadas bloqueantes
		 //srand(5); //pone la semilla en el tiempo del pc,consume tiempo del navegador, uede ser que haa que sacarla
		// uso_IO(pid, (rand()%ms_io + ms_pid));
		 uso_IO(pid,dameRandom(ms_pid,ms_io));
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

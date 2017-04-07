#ifndef __SCHED_PSJF__
#define __SCHED_PSJF__

#include <vector>
#include <queue>
#include "basesched.h"
#include <tuple>

class SchedPSJF : public SchedBase {
	public:
		SchedPSJF(std::vector<int> argn);
        ~SchedPSJF();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::vector<std::priority_queue<std::tuple<int, int> > > colas;
		std::priority_queue<std::tuple<int,int> > mypq1;// la primera componente es la longitud y la segund la tarea.
		std::priority_queue<std::tuple<int,int> > mypq2;// l
		std::priority_queue<std::tuple<int,int> > mypq3; // la 2
		std::priority_queue<std::tuple<int,int> > mypq4;
		std::priority_queue<std::tuple<int,int> > mypq5;
};

#endif

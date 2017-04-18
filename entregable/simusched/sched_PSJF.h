#ifndef __SCHED_PSJF__
#define __SCHED_PSJF__

#include <vector>
#include <queue>
#include "basesched.h"
#include <tuple>


using namespace std;

class SchedPSJF : public SchedBase {
	public:
		SchedPSJF(std::vector<int> argn);
        ~SchedPSJF();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		
		priority_queue<tuple<int,int>, vector<tuple<int, int> >, greater<tuple<int, int> > > mypq1;// la primera componente es la longitud y la segund la tarea.
		priority_queue<tuple<int,int>, vector<tuple<int, int> >, greater<tuple<int, int> > > mypq2;// l
		priority_queue<tuple<int,int>, vector<tuple<int, int> >, greater<tuple<int, int> > > mypq3; // la 2
		priority_queue<tuple<int,int>, vector<tuple<int, int> >, greater<tuple<int, int> > > mypq4;
		priority_queue<tuple<int,int>, vector<tuple<int, int> >, greater<tuple<int, int> > > mypq5;

		
};

#endif

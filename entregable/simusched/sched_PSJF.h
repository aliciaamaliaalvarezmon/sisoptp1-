#ifndef __SCHED_PSJF__
#define __SCHED_PSJF__


#include <vector>
#include <queue>
#include "basesched.h"
#include <tuple>

using namespace std;

typedef priority_queue<tuple<int,int>, vector<tuple<int, int> >, greater<tuple<int, int> > > MiniHeap;

class SchedPSJF : public SchedBase {
	public:
		SchedPSJF(std::vector<int> argn);
        		~SchedPSJF();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		int DameSiguiente();
		MiniHeap colas[5];

		
};

#endif

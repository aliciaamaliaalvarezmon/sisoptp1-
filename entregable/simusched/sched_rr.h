#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include "basesched.h"
#include <iostream>


class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::queue<int> ready;
		std::vector<int> ticksXCore;
		std::vector<int> ticksActuales;
		std::vector<int> waiting;
		int dameSiguiente();
		//int ticks[argn[0]];
		// Completar
};

#endif

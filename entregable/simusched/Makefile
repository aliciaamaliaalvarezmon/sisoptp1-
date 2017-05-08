export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb -std=c++11
LDFLAGS= -lpthread  

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_fcfs.o sched_rr.o sched_PSJF.o
MAIN=simusched

DIR_SALIDA=resultados



.PHONY: all clean new


all: $(MAIN) 

$(DIR_SALIDA):
	mkdir $(DIR_SALIDA)


$(MAIN): $(OBJS) sched_mistery.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ejercicio1:all $(DIR_SALIDA)
	./simusched ej1.tsk 4 0 0 SchedFCFS | python2 ./graphsched.py > $(DIR_SALIDA)/ej1a.png

ejercicio2: all $(DIR_SALIDA)
	./simusched ej2.tsk 1 2 0 SchedFCFS | python2 ./graphsched.py > $(DIR_SALIDA)/ej2a.png
	./simusched ej2.tsk 2 2 0 SchedFCFS | python2 ./graphsched.py > $(DIR_SALIDA)/ej2b.png
	./simusched ej2.tsk 3 2 0 SchedFCFS | python2 ./graphsched.py > $(DIR_SALIDA)/ej2c.png

ejercicio3: all $(DIR_SALIDA)
	./simusched ej3.tsk 2 2 0 SchedFCFS | python2 ./graphsched.py > $(DIR_SALIDA)/ej3a.png
	./simusched ej3.tsk 3 2 0 SchedFCFS | python2 ./graphsched.py > $(DIR_SALIDA)/ej3b.png

ejercicio4:all $(DIR_SALIDA)
	./simusched ej4.tsk 1 2 0 SchedRR 3 | python2  ./graphsched.py > $(DIR_SALIDA)/ej4a.png
	./simusched ej4.tsk 2 1 2 SchedRR 3 2 | python2  ./graphsched.py > $(DIR_SALIDA)/ej4b.png

ejercicio5:all $(DIR_SALIDA)
	./simusched ej5a.tsk 1 0 0 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej5a.png
	./simusched ej5b.tsk 1 0 0 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej5b.png
	./simusched ej5c.tsk 2 5 1 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej5c.png

ejercicio6:all $(DIR_SALIDA)
	./simusched ej6a.tsk 2 2 1 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej6a.png
	./simusched ej6a.tsk 1 0 0 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej6b.png
	./simusched ej6b.tsk 1 0 0 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej6c.png

ejercicio7:all $(DIR_SALIDA)
	./simusched ej7a.tsk 1 1 0 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_1_psjf_1n.png
	./simusched ej7b.tsk 1 1 0 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_1_mis_1n.png
	./simusched ej7b.tsk 1 1 0 SchedRR 5 | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_1_rr_1n.png
	./simusched ej7a.tsk 2 1 0 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_1_psjf_2n.png
	./simusched ej7b.tsk 2 1 0 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_1_mis_2n.png
	./simusched ej7b.tsk 2 1 0 SchedRR 5 5| python2 ./graphsched.py > $(DIR_SALIDA)/ej7_1_rr_2n.png
	./simusched ej7c.tsk 1 1 0 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_2_psjf_1n.png
	./simusched ej7d.tsk 1 1 0 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_2_mis_1n.png
	./simusched ej7d.tsk 1 1 0 SchedRR 5 | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_2_rr_1n.png
	./simusched ej7c.tsk 2 1 0 SchedPSJF | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_2_psjf_2n.png
	./simusched ej7d.tsk 2 1 0 SchedMistery | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_2_mis_2n.png
	./simusched ej7d.tsk 2 1 0 SchedRR 5 5 | python2 ./graphsched.py > $(DIR_SALIDA)/ej7_2_rr_2n.png




%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h sched_rr.h sched_PSJF.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -fr $(OBJS) $(MAIN)  
	rm -fr $(DIR_SALIDA)

new: clean all




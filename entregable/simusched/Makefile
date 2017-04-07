export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb -std=c++11
LDFLAGS= -lpthread  

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_fcfs.o sched_rr.o sched_PSJF.o
MAIN=simusched

DIR_SALIDA=resultados



.PHONY: all clean new


all: $(MAIN) $(DIR_SALIDA)

$(DIR_SALIDA):
	mkdir $(DIR_SALIDA)


$(MAIN): $(OBJS) sched_mistery.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ejercicio1:all
	./simusched ej1.tsk 1 2 0 SchedFCFS |  ./graphsched.py > $(DIR_SALIDA)/ej1.png
 

ejercicio2: all
	./simusched ej2.tsk 1 2 0 SchedFCFS |  ./graphsched.py > $(DIR_SALIDA)/ej2A.png
	./simusched ej2.tsk 2 2 0 SchedFCFS | ./graphsched.py > $(DIR_SALIDA)/ej2B.png
	./simusched ej2.tsk 3 2 0 SchedFCFS | ./graphsched.py > $(DIR_SALIDA)/ej2C.png

ejercicio3: all
	./simusched ej3.tsk 2 2 0 SchedFCFS | ./graphsched.py > $(DIR_SALIDA)/ej3A.png
	./simusched ej3.tsk 3 2 0 SchedFCFS | ./graphsched.py > $(DIR_SALIDA)/ej3B.png
	


#ejercicio4:all

#ejercicio5:all

#ejercicio6:all

#ejercicio7:all	




%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h sched_rr.h sched_PSJF.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)  /$(DIR_SALIDA)
	rm -fr $(DIR_SALIDA)

new: clean all




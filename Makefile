all:
	gcc main_calc.c -o p_calc -fopenmp
clean:
	rm -rf *.o p_calc
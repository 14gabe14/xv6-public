#include "types.h"
#include "user.h"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf(2, "usage: exectime command argument-list\n");
		exit();
	}


	uint start_time = uptime();
    	printf(1, "uptime: %d\n", start_time);

    	int pid = fork();
    	if (pid == 0) {
        	// child process
        	exec(argv[1], &argv[1]);
    	} else {
        	// parent process
        	wait();
        	uint end_time = uptime();

        	printf(1, "uptime: %d\n", end_time);
       	 	printf(1, "Time spent: %d tick(s)\n", end_time - start_time);
    	}

    	exit();
}

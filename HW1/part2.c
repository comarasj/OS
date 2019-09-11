#include <stdio.h>
#include <sys/types.h>


int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Invalid command line syntax, run program like:\npart2 <file_name>\nWhere file_name is a file ");

	}else{
		printf("%s\n", argv[1]);
	}


}

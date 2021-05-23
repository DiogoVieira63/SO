#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char * argv[]) {
	int input_fd = open("/etc/passwd", O_RDONLY);

	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int error_fd = open ("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	dup2(input_fd, STDIN_FILENO); //set STDIN to input_fd
	dup2(output_fd, STDOUT_FILENO); 
	dup2(error_fd, STDERR_FILENO);
	
    //after use dup2, close the files you open and will not use anymore

	close(input_fd);
	close(output_fd);
	close(error_fd);

    if (!fork()){
	    char buffer[100];
        int bytes = 0;
        while((bytes = read(STDIN_FILENO, &buffer, 100)) > 0) {
           write(STDOUT_FILENO, &buffer, bytes);
           write(STDERR_FILENO, &buffer, bytes);
        }
    }
    wait (NULL);
	return 0;
}
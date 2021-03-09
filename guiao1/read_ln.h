#ifndef __READ_LN___
#define __READ_LN___

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t readln(int fd, char *line, size_t size);


#endif
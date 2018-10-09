#include "copy.h"
#include <stdio.h>
#include <errno.h>

/**
 * Copies data from intfd into outfd
 * file descriptor.
 * Returns number of copied bytes or
 * -1 on error (and leaves errno set)
 */
ssize_t copyFds(int infd, int outfd)
{
	int data;
	int writeD;
	int writeAll;
	int all = 0;
	char buff[255];
	size_t count = 255;
	char *buff_addr = &buff[0];

	while ((data = read(infd, buff, count)) > 0) {
		buff[0] = *buff_addr;
		writeD = 0;
		writeAll = 0;

		while (0 != (writeD = write(outfd, buff, data - writeAll))) {
			writeAll += writeD;
			buff[0] = buff[writeAll];
		}
		all += data; 
	}

	if (data == -1 && errno != EINTR && errno != EAGAIN) {
		return -1;
	}

	return all; 

}

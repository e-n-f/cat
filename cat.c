#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void cat(int fd) {
	char buf[2000];

	ssize_t n;
	while ((n = read(fd, buf, 2000)) > 0) {
		char *p = buf;

		while (n > 0) {
			ssize_t m = write(1, buf, n);

			if (m >= 0) {
				n -= m;
				p += m;
			} else {
				perror("write");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (n < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv) {
	if (argc == 1) {
		cat(0);
	} else {
		for (size_t i = 1; i < argc; i++) {
			int fd = open(argv[i], O_RDONLY);
			if (fd < 0) {
				perror(argv[i]);
				exit(EXIT_FAILURE);
			}

			cat(fd);

			if (close(fd) < 0) {
				perror("close");
				exit(EXIT_FAILURE);
			}
		}
	}

	return EXIT_SUCCESS;
}

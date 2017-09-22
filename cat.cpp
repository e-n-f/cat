#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>

void cat(std::istream &is) {
	char buf[2000];

	while (1) {
		is.read(buf, 2000);

		if (is.gcount() > 0) {
			std::cout.write(buf, is.gcount());
		}

		if (std::cout.fail() || std::cout.bad()) {
			std::cerr << "Error writing\n";
			exit(EXIT_FAILURE);
		}

		if (is.eof()) {
			break;
		}

		// Can't detect read failure because it also set EOF
		if (is.fail() || is.bad()) {
			std::cerr << "Error reading\n";
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char **argv) {
	if (argc == 1) {
		cat(std::cin);
	} else {
		for (size_t i = 1; i < argc; i++) {
			std::ifstream is(argv[i], std::ifstream::binary);

			if (!is) {
				std::cerr << "Error opening " << argv[i] << "\n";
				exit(EXIT_FAILURE);
			}

			cat(is);

			// Can't detect close failure because EOF already set error
			is.close();
		}
	}

	return EXIT_SUCCESS;
}

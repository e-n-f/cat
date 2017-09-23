package main

import "io"
import "os"
import "log"

func cat(fd *os.File) {
	buffer := make([]byte, 2000)

	for true {
		n, err := fd.Read(buffer)
		if err == io.EOF {
			break
		}
		if (err != nil) {
			log.Fatal(err)
		}

		var off = 0
		for off < n {
			m, err := os.Stdout.Write(buffer[off:n])
			if (err != nil) {
				log.Fatal(err)
			}

			off += m
		}
	}
}

func main() {
	if len(os.Args) < 2 {
		cat(os.Stdin)
	} else {
		for i := 1; i < len(os.Args); i++ {
			fd, err := os.Open(os.Args[i])
			if err != nil {
				log.Fatal(err)
			}

			cat(fd)

			err = fd.Close()
			if err != nil {
				log.Fatal(err)
			}
		}
	}
}

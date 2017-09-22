'use strict';

const fs = require('fs');

function cat(fd) {
	const buf = Buffer.alloc(2000);

	while (true) {
		let n;

		try {
			n = fs.readSync(fd, buf, 0, 2000);
		} catch (e) {
			console.error(e);
			process.exit(1);
		}

		if (n == 0) {
			break;
		}

		let off = 0;
		while (n > 0) {
			let m;

			try {
				m = fs.writeSync(1, buf, off, n);
			} catch (e) {
				console.error(e);
				process.exit(1);
			}

			n -= m;
			off += m;
		}
	}
}

if (process.argv.length == 2) {
	cat(0);
} else {
	for (let i = 2; i < process.argv.length; i++) {
		let fd;

		try {
			fd = fs.openSync(process.argv[i], 'r');
		} catch (e) {
			console.error(e);
			process.exit(1);
		}

		cat(fd);

		try {
			fs.closeSync(fd);
		} catch (e) {
			console.error(e);
			process.exit(1);
		}
	}
}

process.exit(0);

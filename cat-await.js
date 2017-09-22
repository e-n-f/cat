'use strict';

const fse = require('fs-extra');

async function cat(fd) {
	const buf = Buffer.alloc(2000);

	while (true) {
		let n;

		try {
			n = (await fse.read(fd, buf, 0, 2000)).bytesRead;
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
				m = (await fse.writeSync(1, buf, off, n)).bytesWritten;
			} catch (e) {
				console.error(e);
				process.exit(1);
			}

			n -= m;
			off += m;
		}
	}
}

async function main() {
	if (process.argv.length == 2) {
		await cat(0);
	} else {
		for (let i = 2; i < process.argv.length; i++) {
			let fd;

			try {
				fd = await fse.open(process.argv[i], 'r');
			} catch (e) {
				console.error(e);
				process.exit(1);
			}

			await cat(fd);

			try {
				await fse.close(fd);
			} catch (e) {
				console.error(e);
				process.exit(1);
			}
		}
	}

	process.exit(0);
}

main().then();

import java.io.*;

public class cat {
	private static void cat(InputStream is) {
		byte[] buf = new byte[2000];

		while (true) {
			int n = 0;
			try {
				n = is.read(buf);
			} catch (IOException ioe) {
				System.err.println(ioe.toString());
				System.exit(1);
			}

			if (n < 0) {
				break;
			}

			System.out.write(buf, 0, n);
			if (System.out.checkError()) {
				System.err.println("Error writing");
				System.exit(1);
			}
		}
	}

	public static void main(String[] argv) {
		if (argv.length == 0) {
			cat(System.in);
		} else {
			for (int i = 0; i < argv.length; i++) {
				FileInputStream fis = null;

				try {
					fis = new FileInputStream(argv[i]);
				} catch (FileNotFoundException e) {
					System.err.println(e.toString());
					System.exit(1);
				}

				cat(fis);

				try {
					fis.close();
				} catch (IOException ioe) {
					System.err.println(ioe.toString());
					System.exit(1);
				}
			}
		}

		System.exit(0);
	}
}

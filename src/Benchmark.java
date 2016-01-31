import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class Benchmark {
	static {
		System.loadLibrary("Benchmark");
	}

	native void multiplyUsingMat(String filename);

	native void multiplyUsingMatrix(String filename);

	private static int startMatrix, endMatrix = 5;

	public static void main(String[] args) {

		try {
			parseInput(args);
		} catch (IllegalArgumentException e) {
			System.out.println(e.getMessage());
			return;
		}

		if (startMatrix < 1) {
			startMatrix = 1;
		}
		if (startMatrix > endMatrix) {
			endMatrix = Math.min(20, startMatrix + 5);
		}
		BufferedWriter writer = null;
		try {
			File file = new File("../Matrices/benchmark_ " + startMatrix + "_" + endMatrix + ".log");
			writer = new BufferedWriter(new FileWriter(file, false));
			// benchmark part
			for (int i = startMatrix; i <= endMatrix; i++) {
				String inputFilename = "../Matrices/" + i * 100 + ".in";
				// Benchmarking java 2D array
				long startTime = System.nanoTime();
				List<Matrix> matrices = Matrix.readMatrices(inputFilename);
				Matrix res = matrices.get(0).multiplyBy(matrices.get(1));
				long estimatedTime = System.nanoTime() - startTime;
				String out = "Java Multiplication 2D array Matrix Size " + i * 100 + " took "
						+ TimeUnit.NANOSECONDS.toMillis(estimatedTime) + "Milis \n";
				System.out.println(out);
				writer.write(out);

				// Benchmarking java 1D array
				startTime = System.nanoTime();
				List<Matrix1D> mats = Matrix1D.readMatrices(inputFilename);
				Matrix1D res1D = mats.get(0).multiplyBy(mats.get(1));
				estimatedTime = System.nanoTime() - startTime;
				out = "Java Multiplication 1D array Matrix Size " + i * 100 + " took "
						+ TimeUnit.NANOSECONDS.toMillis(estimatedTime) + "Milis \n";
				System.out.println(out);
				writer.write(out);

				// Benchmarking C++ 1D array implementation
				startTime = System.nanoTime();
				new Benchmark().multiplyUsingMatrix(inputFilename);
				estimatedTime = System.nanoTime() - startTime;
				out = "C++ Multiplication Using 1d Array " + i * 100 + " took "
						+ TimeUnit.NANOSECONDS.toMillis(estimatedTime) + "Milis \n";
				writer.write(out);
				System.out.println(out);
				// Benchmarking C++ 1D array implementation

				// It is slow so above 1000X1000 matrix is not done
				if (i < 11) {
					startTime = System.nanoTime();
					new Benchmark().multiplyUsingMat(inputFilename);
					estimatedTime = System.nanoTime() - startTime;
					out = "C++ Multiplication Using 2d Array Matrix Size " + i * 100 + " took "
							+ TimeUnit.NANOSECONDS.toMillis(estimatedTime) + "Milis \n";
					System.out.println(out);
					writer.write(out);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				writer.close();
			} catch (Exception e) {
			}
		}
	}


	public static void parseInput(String[] args) throws IllegalArgumentException {
		for (int i = 0; i < args.length; i++) {
			switch (args[i]) {
			case "-s":
				i++;
				if (i == args.length) {
					throw new IllegalArgumentException("a start martice size");
				}
				if (args[i] == "-o") {
					throw new IllegalArgumentException("a start martice size");
				}
				startMatrix = (int) Integer.parseInt(args[i]);
				break;
			case "-e":
				i++;
				if (i == args.length) {
					throw new IllegalArgumentException("must supply an end martix size");
				}
				endMatrix = (int) Integer.parseInt(args[i]);
				;
				break;
			}
		}
	}

}

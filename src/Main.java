import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class Main {
	 static {
	      System.loadLibrary("Main"); // main.dll (Windows) or libhello.so (Unixes)
	   }
	
	private native List<double[][]> readMatrices(String filename);
	native double[][] multiply(String filename);
	native void multiply(String filename, String outputFilename);
	private native double[][] multiply(double[][] a, double b[][]);
	
	private static String inputFilename = null, outputFilename = null;
	
	public static void main(String[] args) {
		try{
			parseInput(args);
		}catch(IllegalArgumentException e){
			System.out.println(e.getMessage());
			return;
		}
		
		if(outputFilename != null){
			new Main().multiply(inputFilename, outputFilename);
			return;
		}
		List<double[][]> matrices = new Main().readMatrices(inputFilename);
		new Matrix(new Main().multiply(matrices.get(0), matrices.get(1))).writeMatrix("defOut.out", false);
		
	}
	
	public static void parseInput(String[] args) throws IllegalArgumentException{
		for(int i = 0; i < args.length; i++){
			switch(args[i]){
			case "-i":
				i++;
				if(i == args.length){
					throw new IllegalArgumentException("You need to supply an input filename");
				}
				if(args[i] == "-o"){
					throw new IllegalArgumentException("You need to supply an input filename");
				}
				inputFilename = args[i];
				break;
			case "-o":
				i++;
				if(i == args.length){
					throw new IllegalArgumentException("You need to supply an output filename");
				}
				if(args[i] == "-o"){
					throw new IllegalArgumentException("You need to supply an output filename");
				}
				outputFilename = args[i];
				break;
			}
		}
	}
}

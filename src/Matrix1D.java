import java.io.*;
import java.util.*;

/**
 * @author boris
 * Matrix1D class  - represents a Matrix. Implemented with a 1D array
 */
public class Matrix1D {	
	
	public double[] matrix;
	private int rows, cols;
	
	public Matrix1D(double[] matrix, int rows, int cols){
		this.matrix = matrix;
		this.rows = rows;
		this.cols = cols;
	}
	
	public Matrix1D(int size){
		matrix = new double[size * size];
	}
	
	public Matrix1D(int rows, int cols){
		matrix = new double[rows * cols];
	}
	
	
	/**
	 * Multiplies this matrix with other.
	 * Should pick the more efficient algo - didn't implement...
	 * @param other matrix to multiply by
	 * @return this*other
	 * @throws IllegalArgumentException
	 */
	public Matrix1D multiplyBy(Matrix1D other)
			throws IllegalArgumentException {
		return multiplyMatricesNaive(other);
	}
	
	
	/**
	 * A naive matrix multiplication
	 * @param b other matrix
	 * @return this * other
	 * @throws IllegalArgumentException
	 */
	private Matrix1D multiplyMatricesNaive(Matrix1D b)
			throws IllegalArgumentException {
		
		if (cols != b.rows) {
			throw new IllegalArgumentException("Matrix dimensions must agree");
		}
		double[] bMatrix = b.matrix;
		double[] result = new double[rows * b.cols];
		for (int i = 0; i < rows; i++) {	
			for(int k = 0; k < b.cols; k++){
				for(int j = 0; j < cols; j++)		
					result[i * rows + k] += matrix[i * rows + j] * bMatrix[j * cols + k];
			}				
		}

		return new Matrix1D(result, rows, b.cols);
	}
	
	/**
	 * Reads matrices from a file - expects 2
	 * @param filename the file from which to load 
	 * @return list of matrices
	 */
	public static List<Matrix1D> readMatrices(String filename) {
		BufferedReader br;
		List<Matrix1D> res = new LinkedList<Matrix1D>();
		try{
			br = new BufferedReader(new FileReader(filename));
			res.add(parseMatrix(br));
			res.add(parseMatrix(br));
		}catch (IOException e) {
			System.err.println("Error: " + e);
		}
		
		return res;
	}
	
	/**
	 * Parses a single matrix
	 * @param reader a reader with a stream to a matrix
	 * @return new Matrix1D
	 * @throws IOException
	 */
	public static Matrix1D parseMatrix(BufferedReader reader) throws IOException{
		String thisLine;
		ArrayList<String[]> tempLines = new ArrayList<String[]>();
		
		while ((thisLine = reader.readLine()) != null) {
			if (thisLine.trim().equals("")) {
				break;
			} else {				
				tempLines.add(thisLine.split("\t"));
			}
		}
		int rows = tempLines.size();
		int cols = tempLines.get(0).length;
		double[] matrix = new double[rows * cols];
		for(int i = 0; i < rows; i++){
			String[] stringLine = tempLines.get(i);
			for(int j = 0; j < stringLine.length; j++){
				matrix[i * rows + j] = (double) Integer.parseInt(stringLine[j]);
			}
			
		}
		
		return new Matrix1D(matrix, rows, cols);
	}
	
	/**
	 * Writes the matrix to a file
	 * @param outputFilename 
	 * @param append false to rewrite the whole file
	 */
	public void writeMatrix(String outputFilename, boolean append){
		BufferedWriter writer = null;
        try {
            File file = new File(outputFilename);

            writer = new BufferedWriter(new FileWriter(file, append));
            writer.write(toString());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
               
                writer.close();
            } catch (Exception e) {
            }
        }
    }
	
	
	public String toString(){
		String str = "";
		str += "--------------------------------\n";
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				str += matrix[i * rows + j] + (j == cols - 1 ? "" : "\t");
			}
			str += "\n";
		}
		str += "--------------------------------\n";
		return str;
	}
}
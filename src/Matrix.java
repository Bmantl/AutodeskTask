import java.io.*;
import java.util.*;

public class Matrix {	
	
	public double[][] matrix;
	
	public Matrix(double[][] matrix){
		this.matrix = matrix;
	}
	
	public Matrix(int size){
		matrix = new double[size][size];
	}
	
	public Matrix(int rows, int cols){
		matrix = new double[rows][cols];
	}
	
	public Matrix multiplyBy(Matrix other)
			throws IllegalArgumentException {
		return new Matrix(multiplyMatricesNaive(matrix, other.matrix));
	}
	
	
	private double[][] multiplyMatricesNaive(double[][] a, double[][] b)
			throws IllegalArgumentException {
		int aRows = a.length;
		int aCols = a[0].length;
		int bCols = b[0].length;
		if (aCols != b.length) {
			throw new IllegalArgumentException("Matrix dimensions must agree");
		}

		double[][] result = new double[aRows][bCols];
		for (int i = 0; i < aRows; i++) {	
			for(int k = 0; k < bCols; k++){
				for(int j = 0; j < aCols; j++)		
					result[i][k] += a[i][j] * b[j][k];
			}				
		}

		return result;
	}
	
	public static List<Matrix> readMatrices(String filename) {
		BufferedReader br;
		List<Matrix> res = new LinkedList<Matrix>();
		try{
			br = new BufferedReader(new FileReader(filename));
			res.add(parseMatrix(br));
			res.add(parseMatrix(br));
		}catch (IOException e) {
			System.err.println("Error: " + e);
		}
		
		return res;
	}
	
	public static Matrix parseMatrix(BufferedReader reader) throws IOException{
		String thisLine;
		ArrayList<String[]> tempLines = new ArrayList<String[]>();
		
		while ((thisLine = reader.readLine()) != null) {
			if (thisLine.trim().equals("")) {
				break;
			} else {				
				tempLines.add(thisLine.split("\t"));
			}
		}

		double[][] matrix = new double[tempLines.size()][];
		for(int i = 0; i < matrix.length; i++){
			String[] stringLine = tempLines.get(i);
			double[] line = new double[stringLine.length];
			for(int j = 0; j < line.length; j++){
				line[j] = (double) Integer.parseInt(stringLine[j]);
			}
			matrix[i] = line;
		}
		
		return new Matrix(matrix);
	}
	
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
		for(int i = 0; i < matrix.length; i++){
			for(int j = 0; j < matrix[0].length; j++){
				str += matrix[i][j] + (j == matrix[0].length-1 ? "" : "\t");
			}
			str += "\n";
		}
		str += "--------------------------------\n";
		return str;
	}
}

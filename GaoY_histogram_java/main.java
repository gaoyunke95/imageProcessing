import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class main{
	static int numRows;
	static int numCols;
	static int minVal;
	static int maxVal;
	
	
	
	private static  Scanner x;
	private static  FileInputStream fstream;
	
	public static void main(String[] args){
	
	
		try{
		 
			fstream= new FileInputStream(args[0]);
			x= new Scanner(fstream);
		}
		catch(Exception e){
			System.out.println("no file find");
		}
		
		
		numRows=x.nextInt();
		numCols=x.nextInt();
		minVal=x.nextInt();
		maxVal=x.nextInt();
		int size= maxVal+1;
		Histogram a= new Histogram(size);
	
		int input;
		while(x.hasNext()){
			input=x.nextInt();
			a.computeHistogram(input);
		}
		

		
		try {
			BufferedWriter outFile1 = new BufferedWriter(new FileWriter(args[1]));		
			outFile1.write(numRows+" "+numCols+" "+minVal+" "+maxVal+"\n");
		
				for(int i=0;i<size;i++){
					outFile1.write(i+" "+a.hist[i]+"\n");
				}
			outFile1.close();
			
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		

		
		x.close();
		
		try {
			fstream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
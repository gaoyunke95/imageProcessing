import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class main {
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
		
		int numRows=x.nextInt();
		int numCols=x.nextInt();
		int minVal=x.nextInt();
		int maxVal=x.nextInt();
		
		int sizeOfRow=numRows+2;
		int sizeOfCols=numCols+2;
		
		Ave3x3 a=new Ave3x3(sizeOfRow,sizeOfCols);

		a.numRows=numRows;
		a.numCols=numCols;
		a.minVal=minVal;
		a.maxVal=maxVal;
		a.loadImage(x);
		

		a.mirrorFramed();

		int average=0;
		
		for(int i=1; i<=numRows;i++){
			for(int j=1;j<=numCols;j++){
				average=a.loadNeighbors(i, j);

				a.Avg(i, j, average);
			
			}
		}	

	
	try {
		BufferedWriter outFile1 = new BufferedWriter(new FileWriter(args[1]));
		outFile1.write(numRows+" "+numCols+" "+a.newMin+" "+a.newMax+"\n");
	
		for(int i=1;i<=numRows;i++){
			for(int j=1;j<=numCols;j++){
				outFile1.write(a.tempAry[i][j]+" ");
			}
			outFile1.write("\n");
		}
		outFile1.close();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	x.close();
	try {
		fstream.close();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
		
	
		
	}

}

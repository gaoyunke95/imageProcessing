import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class main {
	private static  Scanner x;
	private static  FileInputStream fstream;
	static BufferedWriter outFile1;
	static BufferedWriter outFile2;
	static BufferedWriter outFile3;
	public static void main(String[] args){

		try{	 
			fstream= new FileInputStream(args[0]);
			x= new Scanner(fstream);
			outFile1 = new BufferedWriter(new FileWriter(args[1]));
			outFile2 = new BufferedWriter(new FileWriter(args[2]));
			outFile3 = new BufferedWriter(new FileWriter(args[3]));

		}
		catch(Exception e){
			System.out.println("no file find");
		}
		

		int numRows=x.nextInt();
		int numCols=x.nextInt();
		int minVal=x.nextInt();
		int maxVal=x.nextInt();
				
		connected a= new connected(numRows,numCols,minVal, maxVal);
	
		a.zeroFramed();
		a.loadImage(x);		
		a.ConnectCC_Pass1();
		
		try {
			outFile1.write("image after Pass #1 \n");
			outFile1.write(a.numRows+" "+a.numCols+" "+a.newMin+" "+a.newMax+"\n");
			//a.prettyPrint(outFile1);
			a.prettyPrint(outFile1);
			outFile1.write("\n"+"Following is EQAry of Pass#1"+"\n");
			
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(i+" ");
			}
			outFile1.write("\n");
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(a.EQAry[i]+" ");
			}
			outFile1.write("\n");
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		
		a.ConnectCC_Pass2();	
		try {
			outFile1.write("\n");
			outFile1.write("image after Pass #2 \n");
			outFile1.write(a.numRows+" "+a.numCols+" "+a.newMin+" "+a.newMax+"\n");
			a.prettyPrint(outFile1);

			outFile1.write("\n"+"Following is EQAry of Pass#2"+"\n");		
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(i+" ");
			}
			outFile1.write("\n");
			for(int i=1;i<=a.newLabel;i++){
				
				outFile1.write(a.EQAry[i]+" ");
			}
			outFile1.write("\n");
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		a.manageEQAry();
		try {
			outFile1.write("\n");
			outFile1.write("\n"+"Following is EQAry after remanage"+"\n");
			
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(i+" ");
			}
			outFile1.write("\n");
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(a.EQAry[i]+" ");
			}
			outFile1.write("\n");
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		a.ConnectCC_Pass3();
		try {
			outFile1.write("\n");
			outFile1.write("image after Pass #3 \n");
			outFile1.write(a.numRows+" "+a.numCols+" "+a.newMin+" "+a.count+"\n");
			
			a.prettyPrint(outFile1);
			
			outFile1.write("\n"+"Following is EQAry of Pass#3 \n");
			
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(i+" ");
			}
			outFile1.write("\n");
			for(int i=1;i<=a.newLabel;i++){
				outFile1.write(a.EQAry[i]+" ");
			}
			outFile1.write("\n");
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		try {
			outFile2.write(a.numRows+" "+a.numCols+" "+a.newMin+" "+a.count+"\n");
			a.prettyPrintForOutput2(outFile2);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		
		try {
			outFile3.write(a.numRows+" "+a.numCols+" "+a.newMin+" "+a.count+"\n");
			a.printCCProperty(outFile3);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		
	try {
		x.close();
		fstream.close();
		outFile1.close();
		outFile2.close();
		outFile3.close();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
		
	
		
	}

}
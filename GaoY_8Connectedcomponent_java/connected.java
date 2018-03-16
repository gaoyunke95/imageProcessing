import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Scanner;

public class connected {
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int newLabel=0;
	int sameLabel;
	int count;
	Property[] PropertyAry;
	
	int[][] zeroFrameAry;
	int[] NeighborAry=new int[5];
	int[] EQAry;
	

	connected(int numRow, int numCols,int minVal, int maxVal)
	{
		this.numRows=numRow;
		this.numCols=numCols;
		this.minVal=minVal;
		this.maxVal=maxVal;
		zeroFrameAry=new int[numRow+2][numCols+2];
		int size=(numRow*numCols)/2;
		EQAry= new int[size];
		for(int i=0;i<size;i++){
			EQAry[i]=i;
		}
	
	}
	void zeroFramed(){
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				zeroFrameAry[i][j]=0;
			}
		}
	}
	void loadImage(Scanner x){	
		int input;
		
		for(int i=1;i<=numRows;i++){
			for(int j=1; j<=numCols;j++){
				input=x.nextInt();
				zeroFrameAry[i][j]=input;
			}
		}
	}
	void loadNeighborsForP1(int i, int j){
		
		int index=0;
		
		int r=i-1;
		for(int c=j-1;c<=j+1;c++){			
			NeighborAry[index]=zeroFrameAry[r][c];				
			index++;
		}
		
		NeighborAry[index]=zeroFrameAry[i][j-1];

	}
	
	void loadNeighborsForP2(int i, int j){
		
		int index=0;

		int r=i;
		for(int c=j;c<=j+1;c++){
			NeighborAry[index]=zeroFrameAry[r][c];
			index++;
		}
		
		r=i+1;
		for(int c=j-1;c<=j+1;c++){			
			NeighborAry[index]=zeroFrameAry[r][c];				
				
			index++;
		}
		
	
	}

	void ConnectCC_Pass1(){
		newLabel=0;

		for(int i=1;i<=numRows;i++){
			for(int j=1; j<=numCols;j++){
				int newMin=100000;
				int newMax=0;
				
				if(zeroFrameAry[i][j]>0){
					loadNeighborsForP1(i,j);				
					for(int z=0;z<4;z++){
					
						if(NeighborAry[z]>0){
							if(NeighborAry[z]<newMin){
								newMin=NeighborAry[z];
							}
							if(NeighborAry[z]>newMax){
								newMax=NeighborAry[z];
							}
						}
					}
					
					if(zeroFrameAry[i][j]==0){
						zeroFrameAry[i][j]=0;
						this.newMin=0;
					}
					else{
						if(newMax==0){
							newLabel++;
							zeroFrameAry[i][j]=newLabel;
								
						}
						//case2
						else if(newMin==newMax){
							zeroFrameAry[i][j]=newMin;
						}
						//case 3;
						else{
							zeroFrameAry[i][j]=newMin;
							EQAry[newMax]=newMin;
						}
					

					}
				}

			}
		}
		
		this.newMax=newLabel;
	}
	
	void ConnectCC_Pass2(){
	

		for(int i=numRows+1;i>1;i--){
			for(int j=numCols+1; j>1;j--){		
				int newMin=1000000;
				int newMax=0;

				if(zeroFrameAry[i][j]>0){
					loadNeighborsForP2(i,j);
					
					for(int z=0;z<=4;z++){
						if(NeighborAry[z]>0){
							if(NeighborAry[z]<newMin){
								newMin=NeighborAry[z];
							}
							if(NeighborAry[z]>newMax){
								newMax=NeighborAry[z];
							}
						}
					}
					if(zeroFrameAry[i][j]==0){
						zeroFrameAry[i][j]=0;
						this.newMin=0;
					}
					else{
						if(newMax==0){
							;		
						}
						//case2
						else if(newMin==newMax){
							;
						}
						//case 3;
						else{
							zeroFrameAry[i][j]=newMin;
							EQAry[newMax]=newMin;
						}
					}
				}

			}
		}
		this.newMax=newLabel;
		
	}
	
	void manageEQAry(){
		count=0;
		for(int i=1;i<=newLabel;i++){
			if(EQAry[i]==i){
				count++;
				EQAry[i]=count;
			}
			else{
				EQAry[i]=EQAry[EQAry[i]];
			}
		}
	}
	
	void ConnectCC_Pass3(){
		PropertyAry= new Property[count+1];
		for(int index=0;index<=count;index++){
			PropertyAry[index]=new Property();
		}
		for(int i=1;i<=numRows;i++){
			for(int j=1;j<=numCols;j++){
				if(zeroFrameAry[i][j]>0){
					zeroFrameAry[i][j]=EQAry[zeroFrameAry[i][j]];
					
					PropertyAry[zeroFrameAry[i][j]].numpixels++;
					
					if(PropertyAry[zeroFrameAry[i][j]].minRow>i){
						PropertyAry[zeroFrameAry[i][j]].minRow=i;
					}
					if(PropertyAry[zeroFrameAry[i][j]].minCol>j){
						PropertyAry[zeroFrameAry[i][j]].minCol=j;
					}
					if(PropertyAry[zeroFrameAry[i][j]].maxRow<i){
						PropertyAry[zeroFrameAry[i][j]].maxRow=i;
					}
					if(PropertyAry[zeroFrameAry[i][j]].maxCol<j){
						PropertyAry[zeroFrameAry[i][j]].maxCol=j;
					}
					
				}
			}
		}
	}
	
	void prettyPrint(BufferedWriter outFile1) throws IOException{
		for(int i=0;i<=numRows+1;i++){
			for(int j=0;j<=numCols+1;j++){
				if(zeroFrameAry[i][j]==0){
					outFile1.write("   ");
				}
				else if(zeroFrameAry[i][j]<10){
					outFile1.write(zeroFrameAry[i][j]+"  ");
				}
				else
					outFile1.write(zeroFrameAry[i][j]+" ");
			}
			outFile1.write("\n");
		}
	}
	
	void prettyPrintForOutput2(BufferedWriter outFile2) throws IOException{
		for(int i=1;i<=numRows;i++){
			for(int j=1;j<=numCols;j++){
					outFile2.write(zeroFrameAry[i][j]+" ");
			}
			outFile2.write("\n");
		}
	}
	
	void printCCProperty(BufferedWriter outFile3) throws IOException{
		outFile3.write(count+"\n");
		for(int i=1;i<=count;i++){
			outFile3.write(i+"\n");
			outFile3.write(PropertyAry[i].numpixels+"\n");
			outFile3.write((PropertyAry[i].minRow-1)+" "+(PropertyAry[i].minCol-1)+"\n");
			outFile3.write((PropertyAry[i].maxRow-1)+" "+(PropertyAry[i].maxCol-1)+"\n");
			outFile3.write("\n");
		}
	}
}

import java.util.Scanner;

public class Ave3x3 {
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin=0;
	int newMax=0;
	
	int[][] mirrorFrameAry;
	int[][] tempAry;
	int[] neighborAry;
	
	int index;
	
	Ave3x3(int sizeOfRow,int sizeOfCols){
		mirrorFrameAry= new int[sizeOfRow][sizeOfCols];
		tempAry= new int[sizeOfRow][sizeOfCols];
		neighborAry= new int[9];
	}
	
	void loadImage(Scanner x){	
		int input;
		
		for(int i=1;i<=numRows;i++){
			for(int j=1; j<=numCols;j++){
				input=x.nextInt();
				mirrorFrameAry[i][j]=input;
			}
		}
	}
	
	void mirrorFramed(){
		for(int j=1;j<=numCols;j++){
			mirrorFrameAry[0][j]=mirrorFrameAry[1][j];
		}
		
		for(int i=0;i<=numRows;i++){
			mirrorFrameAry[i][0]=mirrorFrameAry[i][1];
			mirrorFrameAry[i][numCols+1]=mirrorFrameAry[i][numCols];
		}
	}
	
	int loadNeighbors(int i, int j){
		
		index=0;
		int sum=0;
		for(int r=i-1;r<=i+1;r++){
			for(int c=j-1;c<=j+1;c++){
					
				neighborAry[index]=mirrorFrameAry[r][c];
					
				sum+=neighborAry[index];
				index++;

						
			}
		}
		int average=sum/index;
		return average;
	}
	
	void Avg(int i, int j, int average){

		tempAry[i][j]=average;
		if(newMin==0&&newMax==0){
			newMin=average;
			newMax=average;
		}
		else{
			if(average<newMin){
				newMin=average;
			}
			else if(average>newMax){
				newMax=average;
			}
		}
	}
	
}

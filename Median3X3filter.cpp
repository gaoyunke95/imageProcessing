
#include <iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

class Median3X3{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int newMin=0;
    int newMax=0;
   
    int** mirrorFrameAry;
    int** tempAry;
    int* neighborAry;
    
    int index;
    
    Median3X3(int sizeOfRow,int sizeOfCols){
       
        mirrorFrameAry= new int* [sizeOfRow];
        for(int i=0;i<sizeOfRow;i++){
            mirrorFrameAry[i]= new int[sizeOfCols];
        }
        for(int i=0;i<sizeOfRow;i++){
            for(int j=0;j<sizeOfCols;j++){
                mirrorFrameAry[i][j]=0;
            }
        }
        
     
        tempAry= new int* [sizeOfRow];
        for(int i=0;i<sizeOfRow;i++){
            tempAry[i]= new int[sizeOfCols];
        }
        for(int i=0;i<sizeOfRow;i++){
            for(int j=0;j<sizeOfCols;j++){
                tempAry[i][j]=0;
            }
        }
     
        neighborAry= new int[9];
    }
    
    void loadImage(ifstream &inFile){
        int input;
        
        for(int i=1;i<=numRows;i++){
            for(int j=1; j<=numCols;j++){
                inFile>>input;
             
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
        int valueOfMedian=0;
        int size=sizeof(neighborAry);
        for(int r=i-1;r<=i+1;r++){
            for(int c=j-1;c<=j+1;c++){
                
                neighborAry[index]=mirrorFrameAry[r][c];
    
                index++;
            }
        }
      
        for(int i=0;i<9;i++){
            int smallest= neighborAry[i];
            int smallIndex=i;
            
            for(int j=i;j<9;j++){
                if(neighborAry[j]<smallest){
                    smallest=neighborAry[j];
                    smallIndex=j;
                }
                
            }
            swap(neighborAry[i],neighborAry[smallIndex]);
        }
        
        int indexOfMedian=9/2;
        valueOfMedian=neighborAry[indexOfMedian];
        return valueOfMedian;
    }
    
    void MedianFilter(int i, int j, int medianValue){
        
        tempAry[i][j]=medianValue;
        if(newMin==0&&newMax==0){
            newMin=medianValue;
            newMax=medianValue;
        }
        else{
            if(medianValue<newMin){
                newMin=medianValue;
            }
            else if(medianValue>newMax){
                newMax=medianValue;
 
            }
        }
    }
    

};





int main(int argc, const char * argv[]) {
    ifstream inFile;
   	ofstream outFile;
    
    inFile.open(argv[1]);
    outFile.open(argv[2]);
    
    if(!inFile.is_open()){
        cout<<"file not found";
    }
    
    
    int numRows;
    int numCols;
    int minVal;
    int maxVal;

    inFile>>numRows;
    inFile>>numCols;
    inFile>>minVal;
    inFile>>maxVal;
    
    
    int sizeOfRow= numRows+2;
    int sizeOfCols=numCols+2;
   
    
    Median3X3 a=Median3X3(sizeOfRow, sizeOfCols);
  
    a.numRows=numRows;
    a.numRows=numRows;
    a.numCols=numCols;
    a.minVal=minVal;
    a.maxVal=maxVal;
    a.loadImage(inFile);
    
    a.mirrorFramed();
    
    
	int medianValue=0;
    
    for(int i=1; i<=numRows;i++){
        for(int j=1;j<=numCols;j++){
            medianValue=a.loadNeighbors(i, j);
            a.MedianFilter(i, j, medianValue);    
        }
    }
   
    outFile<<numRows<<" "<<numCols<<" "<<a.newMin<<" "<<a.newMax<<endl;
   
    for(int i=1;i<=numRows;i++){
        for(int j=1;j<=numCols;j++){
            outFile<<a.tempAry[i][j]<<" ";
        }   
        outFile<<endl;
    }

    inFile.close();
  	outFile.close();
    return 0;
}

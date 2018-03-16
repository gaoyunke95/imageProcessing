
#include <iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

class DistanceTF{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int newMin;
    int newMax;
    
    int** zeroFrameAry;
    int** tempAry;
    int* neighborAry;
    
    int index;
    
    DistanceTF(int numRow,int numCol, int minVal, int maxVal){
        this->numRows=numRow;
        this->numCols=numCol;
        this->minVal=minVal;
        this->maxVal=maxVal;
        zeroFrameAry= new int* [numRows+2];
        for(int i=0;i<numRows+2;i++){
            zeroFrameAry[i]= new int[numCols+2];
        }

        neighborAry= new int[5];
    }
    
    void loadImage(ifstream &inFile){
        int input;
        
        for(int i=1;i<=numRows;i++){
            for(int j=1; j<=numCols;j++){
                inFile>>input;
                
                zeroFrameAry[i][j]=input;
            }
        }
    }
    
    void zeroFramed(){
        for(int i=0;i<numRows+2;i++){
            for(int j=0;j<numCols+2;j++){
                zeroFrameAry[i][j]=0;
            }
        }
        
    }
    
    void loadNeighborsForP1(int i, int j){
        
        index=0;
        
        int r=i-1;
        for(int c=j-1;c<=j+1;c++){
            neighborAry[index]=zeroFrameAry[r][c];
            index++;
        }
        
        neighborAry[index]=zeroFrameAry[i][j-1];
        index++;
    }
    
    void loadNeighborsForP2(int i, int j){
        
        index=0;
        
        int r=i;
        for(int c=j;c<=j+1;c++){
            neighborAry[index]=zeroFrameAry[r][c];
            index++;
        }
        
        r=i+1;
        for(int c=j-1;c<=j+1;c++){
            neighborAry[index]=zeroFrameAry[r][c];
            
            index++;
        }
        
        
    }
    
    int findMin(int maxindex){
        int min=100000;
        for(int i=0;i<maxindex;i++){
            if(neighborAry[i]<min){
                min=neighborAry[i];
            }
        }
        return min;
    }
    
    void updateMinMAX(int i, int j){
        if(zeroFrameAry[i][j]<newMin){
            newMin=zeroFrameAry[i][j];
        }
        if(zeroFrameAry[i][j]>newMax){
            newMax=zeroFrameAry[i][j];
        }
    }
    void DistancePass_1(){
        newMin=10000;
        newMax=0;
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                if(zeroFrameAry[i][j]>0){
                    loadNeighborsForP1(i,j);
                    int min=findMin(index);
                    
                    zeroFrameAry[i][j]=min+1;
                }
                updateMinMAX(i, j);
                
            }
        }
    }
    
    void DistancePass_2(){
        newMin=10000;
        newMax=0;
        for(int i=numRows;i>1;i--){
            for(int j=numCols;j>1;j--){
                if(zeroFrameAry[i][j]>0){
                    loadNeighborsForP2(i,j);
                    int min=findMin(5);
                    if(zeroFrameAry[i][j]==min){
                        ;
                    }
                    else{
                        zeroFrameAry[i][j]=min+1;
                        
                    }
                }
                
                updateMinMAX(i, j);
            }
        }
    }
    
    void prettyPrint(ofstream &outFile2){
        outFile2<<numRows<<" "<<numCols<<" "<<newMin<<" "<<newMax<<endl;
        for(int i=0;i<numRows+2;i++){
            for(int j=0;j<numCols+2;j++){
                if(zeroFrameAry[i][j]==0){
                    outFile2<<"   ";
                }
                else if(zeroFrameAry[i][j]<10){
                    outFile2<<zeroFrameAry[i][j]<<"  ";
                }
                else{
                    outFile2<<zeroFrameAry[i][j]<<" ";
                }
            }
            outFile2<<endl;
        }
        
        outFile2<<endl;
    }
    
    void printToFile(ofstream &outFile1){
        outFile1<<numRows<<" "<<numCols<<" "<<newMin<<" "<<newMax<<endl;
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                outFile1<<zeroFrameAry[i][j]<<" ";
            }
            outFile1<<endl;
        }
    }
};





int main(int argc, const char * argv[]) {
    ifstream inFile;
    ofstream outFile1;
    ofstream outFile2;
    
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    
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
    
    DistanceTF *a=new DistanceTF(numRows,numCols,minVal,maxVal);
    
    a->zeroFramed();
    a->loadImage(inFile);
    
    a->DistancePass_1();
    outFile2<<"pass#1"<<endl;
    a->prettyPrint(outFile2);

    a->DistancePass_2();
    outFile2<<"pass#2"<<endl;
    a->prettyPrint(outFile2);

    a->printToFile(outFile1);
    

    
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}


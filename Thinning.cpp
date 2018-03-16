
#include <iostream>
#include<cstdlib>
#include<fstream>

using namespace std;
class ThinningSkeleton{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    bool changeflag=true;
    int cycleCount;
    int** firstAry;
    int** secondAry;
    int* NeighborsAry;
    
    ThinningSkeleton(int row, int col, int min, int max){
        firstAry= new int*[row+2];
        for(int i=0; i<row+2;i++){
            firstAry[i]= new int[col+2];
        }
       
        secondAry= new int*[row+2];
        for(int j=0;j<row+2;j++){
            secondAry[j]=new int[col+2];
        }
        
        NeighborsAry=new int[9];
        numRows=row;
        numCols=col;
        minVal=min;
        maxVal=max;
        
    }
    
    void zeroFramed(int**Ary){
        for(int i=0;i<numRows+2;i++){
            for(int j=0;j<numCols+2;j++){
                Ary[i][j]=0;
            }
        }
    }
    
    void loadImage(ifstream &inFile){
        int input;
        
        for(int i=1;i<=numRows;i++){
            for(int j=1; j<=numCols;j++){
                inFile>>input;
                firstAry[i][j]=input;
                secondAry[i][j]=input;
            }
        }
    }
    void copyAry(){
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                firstAry[i][j]=secondAry[i][j];
            }
        }
    }
    
    void DoThinning(int i,int j){
       
        bool CheckNFlag=CheckNeighbors(i,j);
        bool CheckCCFlag=CheckCC(i,j);
        if(CheckNFlag==true&&CheckCCFlag==true){
            secondAry[i][j]=0;
            changeflag=true;
        }
        
    }

    bool CheckNeighbors(int i, int j){
        int count=0;

        for(int r=i-1;r<=i+1;r++){
            for(int c=j-1;c<=j+1;c++){
                
                if(firstAry[r][c]>0){
                	count++;
                }
                
            }
        }
        if(count>=5){
            return true;
        }
        return false;
    }
    
	bool CheckCC(int i,int j){
        if(firstAry[i-1][j-1]==1){
            if(firstAry[i-1][j]==0&&firstAry[i][j-1]==0){
                return false;
            }
        }
        if(firstAry[i-1][j+1]==1){
            if(firstAry[i-1][j]==0&&firstAry[i][j+1]==0){
                return false;
            }
        }
        if(firstAry[i+1][j-1]==1){
            if(firstAry[i][j-1]==0&&firstAry[i+1][j]==0){
                return false;
            }
        }
        if(firstAry[i+1][j+1]==1){
            if(firstAry[i+1][j]==0&&firstAry[i][j+1]==0){
                return false;
            }
        }
        
       if(firstAry[i-1][j]==0&&firstAry[i+1][j]==0){
            return false;
        }
       if(firstAry[i][j-1]==0&&firstAry[i][j+1]==0){
            return false;
        }

        return true;
        
    }

    void NorthThinning(){
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                if(firstAry[i][j]>0&&firstAry[i-1][j]==0){
                    DoThinning(i,j);
                }
            }
        }
    }
    void SouthThinning(){
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                if(firstAry[i][j]>0&&firstAry[i+1][j]==0){
                    DoThinning(i,j);
                }
            }
        }
    }
    void EastThinning(){
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                if(firstAry[i][j]>0&&firstAry[i][j+1]==0){
                    DoThinning(i,j);
                }
            }
        }
    }
    void WestThinning(){
        for(int i=1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                if(firstAry[i][j]>0&&firstAry[i][j-1]==0){
                    DoThinning(i,j);
                }
            }
        }
    }
    
    void prettyPrint(int **Ary,ofstream &outFile){
        for(int i =0;i<=numRows+1;i++){
            for(int j=0;j<=numCols+1;j++){
                if(Ary[i][j]>=1){
                    outFile<<Ary[i][j]<<" ";
                }
                else
                    outFile<<"  ";
            }
            outFile<<endl;
        }
    }
    
    void FinalPrint(int **Ary,ofstream &outFile){
        for(int i =1;i<=numRows;i++){
            for(int j=1;j<=numCols;j++){
                if(Ary[i][j]>=1){
                    outFile<<Ary[i][j]<<" ";
                }
                else
                    outFile<<"0 ";
            }
            outFile<<endl;
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
    
    ThinningSkeleton *a= new ThinningSkeleton(numRows,numCols,minVal,maxVal);
    a->zeroFramed(a->firstAry);
    a->zeroFramed(a->secondAry);
    a->loadImage(inFile);

    int cycleCount=0;
   
   	while(a->changeflag){
   		
    	if(cycleCount%2==0){
			outFile2<<"CycleCount:"<<cycleCount<<endl;
          	a->prettyPrint(a->firstAry,outFile2);
      	}
        a->changeflag=false;
        cycleCount++;
        
		a->NorthThinning();
        a->copyAry();
        
        a->SouthThinning();
        a->copyAry();
        
		a->WestThinning();
        a->copyAry();
        
		a->EastThinning();
       	a->copyAry();
        
        
        
    }
    
    outFile2<<"FinalCycleCount:"<<cycleCount<<endl;
    a->prettyPrint(a->firstAry,outFile2);
    outFile1<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<endl;
    a->FinalPrint(a->firstAry,outFile1);
    
	inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

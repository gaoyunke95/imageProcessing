#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
//threshold project1.3
using namespace std;

int main(int argc, char *argv[]){
    ifstream inFile;
    ofstream outFile;
    stringstream outFileName;
    
    
    inFile.open(argv[1]);

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

    int thrValue;
    
    cout<<"enter your tresholdValue:4 or 5 or 6 or 7"<<endl;
    cin>>thrValue;

    
	string fileName=argv[1];
    size_t pos=fileName.find('.');
    int posOfp= static_cast<int>(pos);
    outFileName<<fileName.substr(0,posOfp)<<"_thr_"<<thrValue<<".txt";
    
   
    outFile.open(outFileName.str());
    int pixel_val;
	
	minVal=0;
	maxVal=1;
	outFile<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<endl;
	
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numCols;j++){
            inFile>>pixel_val;
            if(pixel_val>=thrValue)
                outFile<<"1 ";
            else
                outFile<<"0 ";
        }
        outFile<<endl;
    }

    
    inFile.close();
    outFile.close();
}



#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
using namespace std;
//pretty print project1.2

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
    
    
    int pixel_val;
   	string fileName=argv[1];
    size_t pos=fileName.find('.');
    int posOfp= static_cast<int>(pos);
    outFileName<<fileName.substr(0,posOfp)<<"_pp.txt";
   
    outFile.open(outFileName.str());
    
	
	
	outFile<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<endl;
    
    for(int i=0;i<numRows;i++){
        for(int j=0;j<numCols;j++){
            inFile>>pixel_val;
            if(pixel_val>0)
                outFile<<pixel_val<<" ";
            else
                outFile<<"  ";
        }
        outFile<<endl;
    }

    
    inFile.close();
    outFile.close();
}



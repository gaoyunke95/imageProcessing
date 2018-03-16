
public class Histogram {
	int[] hist;
	Histogram(int size){
		hist=new int[size];
		for(int i=0;i<size;i++){
			hist[i]=0;
		}
	}
	void computeHistogram(int input){
		hist[input]++;
	}
}

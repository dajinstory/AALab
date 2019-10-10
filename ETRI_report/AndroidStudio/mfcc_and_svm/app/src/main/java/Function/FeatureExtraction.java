package Function;
import android.util.Log;

import Feature.MFCC;

public class FeatureExtraction {
    public FeatureExtraction(){

    }
    public double[] process(short[] signal){
        MFCC mfcc = new MFCC();
        double[][] MFCC = mfcc.process(signal);//13-d mfcc

        double[] mean = mfcc.getMeanFeature();
        for(int i=0;i<12;i++){
            Log.e("Log", "index = " + i + " and " + mean[i]+ " printcheck");
        }
        return mean;
    }
}

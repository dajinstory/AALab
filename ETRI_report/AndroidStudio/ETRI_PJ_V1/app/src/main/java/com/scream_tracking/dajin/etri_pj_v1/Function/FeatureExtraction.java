package com.scream_tracking.dajin.etri_pj_v1.Function;
import android.util.Log;

import com.scream_tracking.dajin.etri_pj_v1.Feature.MFCC;

public class FeatureExtraction {
    public FeatureExtraction(){

    }
    public double[] process(short[] signal){
        MFCC mfcc = new MFCC();
        double[][] MFCC = mfcc.process(signal);//13-d mfcc

        double[] mean = mfcc.getMeanFeature();
        System.out.println("mean data is like these");
        for(int i=0;i<12;i++){
            System.out.print(mean[i] + " ");
        }
        System.out.println();
        return mean;
    }
}

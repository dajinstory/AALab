package com.example.my.scream_tracking;

import android.Manifest;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import Function.*;

public class MainActivity extends AppCompatActivity {


    short[] audiodata= new short[100000];
    int idx=0;

    void filereader() throws Exception{
        int tmp=0;
        short data = 0;
        char ch;
        File file = new File("./Models/data/input/txt/input1.txt");

        FileReader fr = null;
        Log.e("Log", "kill me kill me kill me up");
        if(!file.exists()){
            Log.e("Log", "tlqkftlqkf me kill me kill me up");

        }
        fr = new FileReader(file);
        Log.e("Log", "tried...");


        tmp = fr.read();
        while(tmp != -1) {
            ch = (char) tmp;
            if (tmp == ' ') {
                audiodata[idx] = data;
                Log.e("Log", "idx and num is " + idx + " and " + data);
                idx++;
                data=0;
            }
            else{
                data*=10;
                data+=ch-'0';
            }
            tmp=fr.read();
        }
        audiodata[idx]=data;
        idx++;
        fr.close();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
/*
        FeatureExtraction getMFCC = new FeatureExtraction();
        svm_predict predict = new svm_predict();
        svm_train train = new svm_train();

        try {
            this.filereader();
        } catch(Exception e){
            e.printStackTrace();
        }
        Log.e("Log", "idx size is " + idx);
        double[] meandata = getMFCC.process(audiodata);
*/
/*        for(int i=0;i<12;i++){
            System.out.println("meandata = " + meandata[i]);
        }
        try {
            predict.process("data/feature/stream_data.txt");
        } catch (IOException e){
            System.err.print("predicting calling is failed\n");
            System.exit(1);
        }
        System.exit(0);
        */
    }
}

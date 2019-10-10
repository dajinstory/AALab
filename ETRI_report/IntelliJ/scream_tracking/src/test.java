import java.io.*;
//import java.io.File;
//import java.io.FileWriter;
//import java.io.IOException;

public class test {
    public static void main(String[] args) {
        System.out.println("running");

        FeatureExtraction getMFCC = new FeatureExtraction();
        svm_train train = new svm_train();
        svm_predict predict = new svm_predict();

        //get mfcc data
        System.out.println("\n\n--------------------------------------\ngetting mfcc data...\n");
        String path;
        double meanData[];
        //pathname is the location to store the mel-frequency data of  audio files.
        File textFile = new File("test_data.txt");
        FileWriter writer = null;
        try{
            writer = new FileWriter(textFile, false);
            //in this case, 5 means the total number of input wav files.
            for(int i=1;i<=5;i++) {
                path = String.format("data/input/test/input%d.wav", i);
                System.out.println(path);
                meanData = getMFCC.process(path);
                //judge indicates whether it is screaming sound or not. if scream 1, else 0
                int judge = 1;
                writer.write(Integer.toString(judge));
                writer.write(" ");
                for (int j = 0; j < 12; j++) {
                    writer.write(Integer.toString(j));
                    writer.write(':');
                    writer.write(Integer.toString((int) (meanData[j] * 100 / 1)));
                    writer.write(" ");
                }
                writer.write("\r\n");
            }
            writer.close();
        }catch(IOException e){
            e.printStackTrace();
        }finally{
            try{
                if(writer!=null)writer.close();
            }catch(IOException e){
                e.printStackTrace();
            }
        }


        //training
        System.out.println("\n\n--------------------------------------\ntraining...\n");
        try {
            //input the filename to training svm model
            train.process("scream_data.txt");
        } catch(IOException e){
            System.err.print("training calling is failed\n");
            System.exit(1);
        }

        //predicting
        System.out.println("\n\n---------------------------------\npredicting...\n");
        try {
            //input the filename which is the test sample to perform a predictive test on the learned model
            predict.process("test_data.txt");
        } catch (IOException e){
            System.err.print("predicting calling is failed\n");
            System.exit(1);
        }

    }
}

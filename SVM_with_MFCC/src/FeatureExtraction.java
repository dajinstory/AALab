import Feature.MFCC;
import SignalProcess.WaveIO;

public class FeatureExtraction {
    public FeatureExtraction(){

    }
    public static void main(String[] args){
          WaveIO waveIO1 = new WaveIO();
          short[] signals1 = waveIO1.readWave("data/input/office1.wav");

          MFCC mfcc = new MFCC();
          double[][] MFCC = mfcc.process(signals1);//13-d mfcc

          double[] mean = mfcc.getMeanFeature();
          for(int i=0;i<12;i++){
              System.out.println(mean[i] + " ");
          }
    }
    public double[] process(String path){
        WaveIO waveIO1 = new WaveIO();
        short[] signals1 = waveIO1.readWave(path);

        MFCC mfcc = new MFCC();
        double[][] MFCC = mfcc.process(signals1);//13-d mfcc

        double[] mean = mfcc.getMeanFeature();
        for(int i=0;i<12;i++){
            System.out.println(mean[i] + " ");
        }
        return mean;
    }
}

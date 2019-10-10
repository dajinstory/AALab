package com.scream_tracking.dajin.etri_pj_v1.Function;
import android.util.Log;

import com.scream_tracking.dajin.etri_pj_v1.libsvm.*;
import java.io.*;
import java.util.*;

public class svm_predict {
	private static svm_print_interface svm_print_null = new svm_print_interface()
	{
		public void print(String s) {}
	};

	private static svm_print_interface svm_print_stdout = new svm_print_interface()
	{
		public void print(String s)
		{
			System.out.print(s);
		}
	};

	private static svm_print_interface svm_print_string = svm_print_stdout;

	static void info(String s)
	{
		svm_print_string.print(s);
	}

	private static double atof(String s)
	{
		return Double.valueOf(s).doubleValue();
	}

	private static int atoi(String s)
	{
		return Integer.parseInt(s);
	}

	private static void predict(double[] meandata, svm_model model, int predict_probability) throws IOException
	{
		int correct = 0;
		int total = 0;
		double error = 0;
		double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;

		int svm_type=svm.svm_get_svm_type(model);
		int nr_class=svm.svm_get_nr_class(model);
		double[] prob_estimates=null;

		if(predict_probability == 1)
		{
			if(svm_type == svm_parameter.EPSILON_SVR ||
			   svm_type == svm_parameter.NU_SVR)
			{
				svm_predict.info("Prob. model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma="+svm.svm_get_svr_probability(model)+"\n");
			}
			else
			{
				int[] labels=new int[nr_class];
				svm.svm_get_labels(model,labels);
				prob_estimates = new double[nr_class];
				/*
				output.writeBytes("labels");
				for(int j=0;j<nr_class;j++)
					output.writeBytes(" "+labels[j]);
				output.writeBytes("\n");
				*/
			}
		}

			/*
			String line = input.readLine();
			if(line == null) break;

			StringTokenizer st = new StringTokenizer(line," \t\n\r\f:");

			double target = atof(st.nextToken());
			int m = st.countTokens()/2;
			*/
			svm_node[] x = new svm_node[meandata.length];
			for(int j=0;j<meandata.length;j++)
			{
				x[j] = new svm_node();
				x[j].index = j;
				x[j].value = meandata[j];
				//Log.e("Log_mfcc_data", x[j].index+ " " + x[j].value);

			}

			double v;
			if (predict_probability==1 && (svm_type==svm_parameter.C_SVC || svm_type==svm_parameter.NU_SVC))
			{
				v = svm.svm_predict_probability(model,x,prob_estimates);
				System.out.println("nonononononononono");
				Log.e("Log_prediction", "nonononono");

				/*
				output.writeBytes(v+" ");
				for(int j=0;j<nr_class;j++)
					output.writeBytes(prob_estimates[j]+" ");
				output.writeBytes("\n");
				*/
			}
			else
			{
				v = svm.svm_predict(model,x);
				Log.e("Log_prediction", "predicting~~~~~~~~~~");
				//output.writeBytes(v+"\n");
			}
			v = svm.svm_predict(model,x);
            Log.e("Log_prediction", "prediction is = " + v);

			System.out.println("prediction result is = " + v);
			/*
			if(v == target)
				++correct;
			error += (v-target)*(v-target);
			sumv += v;
			sumy += target;
			sumvv += v*v;
			sumyy += target*target;
			sumvy += v*target;
			++total;
			*/
		}
		/*
		if(svm_type == svm_parameter.EPSILON_SVR ||
		   svm_type == svm_parameter.NU_SVR)
		{
			svm_predict.info("Mean squared error = "+error/total+" (regression)\n");
			svm_predict.info("Squared correlation coefficient = "+
				 ((total*sumvy-sumv*sumy)*(total*sumvy-sumv*sumy))/
				 ((total*sumvv-sumv*sumv)*(total*sumyy-sumy*sumy))+
				 " (regression)\n");
		}
		else
			svm_predict.info("Accuracy = "+(double)correct/total*100+
				 "% ("+correct+"/"+total+") (classification)\n");
		*/

	private static void exit_with_help()
	{
		System.err.print("usage: svm_predict [options] test_file model_file output_file\n"
		+"options:\n"
		+"-b probability_estimates: whether to predict probability estimates, 0 or 1 (default 0); one-class SVM not supported yet\n"
		+"-q : quiet mode (no outputs)\n");
		System.exit(1);
	}

	public static void main(String argv[]) throws IOException
	{

		int i, predict_probability=0;
        	svm_print_string = svm_print_stdout;

		// parse options
		//argv->test
		String [] test = {"test.txt", "test.txt.model", "test.txt.out"};
		for(i=0;i<test.length;i++)
		{
			if(test[i].charAt(0) != '-') break;
			++i;
			switch(test[i-1].charAt(1))
			{
				case 'b':
					predict_probability = atoi(test[i]);
					break;
				case 'q':
					svm_print_string = svm_print_null;
					i--;
					break;
				default:
					System.err.print("Unknown option: " + test[i-1] + "\n");
					exit_with_help();
			}
		}
		if(i>=test.length-2)
			exit_with_help();
		try
		{
			BufferedReader input = new BufferedReader(new FileReader(test[i]));
			DataOutputStream output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(test[i+2])));
//			svm_model model = svm.svm_load_model(test[i+1]);
/*			if (model == null)
			{
				System.err.print("can't open model file "+test[i+1]+"\n");
				System.exit(1);
			}
			if(predict_probability == 1)
			{
				if(svm.svm_check_probability_model(model)==0)
				{
					System.err.print("Model does not support probabiliy estimates\n");
					System.exit(1);
				}
			}
			else
			{
				if(svm.svm_check_probability_model(model)!=0)
				{
					svm_predict.info("Model supports probability estimates, but disabled in prediction.\n");
				}
			}
			predict(input,output,model,predict_probability);
			input.close();
			output.close();
*/		}
		catch(FileNotFoundException e)
		{
			exit_with_help();
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			exit_with_help();
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	public svm_predict(){

	}

	public static void process(double[] meandata, svm_model model) throws IOException
	{

		int i, predict_probability=0;
		svm_print_string = svm_print_stdout;

		predict(meandata,model,predict_probability);

		/*
		try
		{
			BufferedReader input = new BufferedReader(new FileReader(test[0]));
			DataOutputStream output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(test[2])));
			svm_model model = svm.svm_load_model(test[1]);
			if (model == null)
			{
				System.err.print("can't open model file "+test[1]+"\n");
				System.exit(1);
			}
			if(predict_probability == 1)
			{
				if(svm.svm_check_probability_model(model)==0)
				{
					System.err.print("Model does not support probabiliy estimates\n");
					System.exit(1);
				}
			}
			else
			{
				if(svm.svm_check_probability_model(model)!=0)
				{
					svm_predict.info("Model supports probability estimates, but disabled in prediction.\n");
				}
			}
			predict(input,output,model,predict_probability);
			input.close();
			output.close();
		}
		catch(FileNotFoundException e)
		{
			exit_with_help();
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			exit_with_help();
		}
		*/
	}
}

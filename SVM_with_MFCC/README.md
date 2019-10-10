```
─ project
  ├ data/input                    # input audio data samples
  │	├ scream 					# audio data for trainning
  │	└ test 						# audio data for predicting
  ├ model                    				# well trained data
  ├ src    						# codes
  │ ├ Feature 						# MFCC Library
  │ ├ libsvm						# svm machine library
  │ ├ org 						# apache common library for calculate
  │ ├ SignalProcess 					# library for read audio and wave I/O
  │ ├ Tool 						# library for calculate
  │ ├ FeatureExtraction.java 	# MFCC code
  │ ├ svm_predict.java 					# svm predicting code
  │ ├ svm_scale.java
  │ ├ svm_toy.java
  │ ├ svm_train.java 					# svm training code
  │ └ test.java 					# main code
  ├ scream_data.txt					# accumulated mfcc data
  ├ scream_data.txt.model 				# svm model trainned by scream_data.txt
  └ scream_data.txt.out 				# result of predicting program
```
```
src/test.java가 main 함수 입니다.

test.java에 크게 3가지 기능이 구현되어 있습니다.
(1) mel-frequency data 추출 알고리즘
	18번째 줄에 주석으로 설명이 되어 있듯, "test_data.txt"에 앞으로 입력할 오디오 파일의 mfcc정보들이 입력됩니다.
	입력되는 오디오 파일은 23번째 줄에 주석처리 되어있듯, for문의 적힌 5대신 다른 수를 넣으면, mfcc정보를 추출할 오디오파일의 개수를 늘릴 수 있습니다.
	오디오파일은 scream_tracking/data/input/test 폴더 내부에, input(정수).wav 형태일 때 작동하도록 작성했습니다.
	각 오디오파일별로 judge 정보는 수동으로 해주셔야 합니다. 28번째 줄에 주석으로 설명되어 있습니다.

(2) svm model training 알고리즘
	52번째 줄부터 진행됩니다.
	55번째 줄 주석에 설명되어 있듯, train.process("scream_data.txt")로 동작합니다.
	scream_data.txt는 training 시킬 mel-frequency정보가 저장된 파일입니다.

	(1)의 함수를 거쳐 추출된 mel-frequency 정보들이 저장된 txt파일을 통해 training 시키는 과정입니다.
	되도록, training 시키는 txt파일의 이름은 scream_data.txt로 해주세요. 내부 함수에서 scream_data.txt로 동작하도록 설계되어있습니다.
	training 완료된 모델은 scream_tracking폴더 내부에 scream_data.txt.model로 파일이 만들어집니다.

(3) svm model 기반 비명판단 테스트
	62번째 줄부터 진행됩니다.
	테스트를 거칠 파일의 이름을 65번째 줄 주석에 따라 작성해주세요.

사용하지 않을 부분에 대해서는 주석을 치신 다음 실행하시면 됩니다.
```

***IntelliJ나 Eclipse를 통해 실행할 경우, 툴 내부에서, package나 import하는 부분에서 빨간줄이 쳐지는 경우가 있습니다. 프로그램 내부에 문제가 있기보다, 툴이 잡아내지 못하는 경우입니다. 무시하고 실행하시면 됩니다.

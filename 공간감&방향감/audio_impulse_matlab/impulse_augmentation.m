clc
clear all

%init standard variables
endianness = 'l';
fs = 44100;
datatype = 'int16';
%read background audio
%fid_R = fopen(filename,'r',endianness);
%Signal = fread(fid_R,'int16');
%fclose(fid_R);
%[Signal, aa] = audioread('강의실_1411.wav');
name1 = 'reverberation_room_';
name2 = 'lecture_room_';
name3 = 'concert_hall_';
name4 = 'semi-anechoic_room_';
dir1 = 'D:\ETRI_database\4-2. impulse 적용\reverberation';
dir2 = 'D:\ETRI_database\4-2. impulse 적용\lecture';
dir3 = 'D:\ETRI_database\4-2. impulse 적용\concert';
dir4 = 'D:\ETRI_database\4-2. impulse 적용\semi-anechoic';
for idx=1:4
    if idx==1
        name=name1;
        dirN=dir1;
    end
    if idx==2
        name=name2;
        dirN=dir2;
    end
    if idx==3
        name=name3;
        dirN=dir3;
    end
    if idx==4
        name=name4;
        dirN=dir4;
    end
    cd(pwd);
    cd('C:\Users\my\Documents\MATLAB');
    
    filename=strcat(name,'.wav');
    display(filename);
    Signal = audioread(filename);
    info = audioinfo(filename);
    display(info);
    
    %go to db directory 
    cd(pwd);
    cd('D:\ETRI_database\3. 3초로 통일&소리세기augmentation\전체');% 웨이브가 있는 디렉토리
    list = dir ('*.wav');
    for i = 1 : length(list)
        if mod(i-1,5)+1>=4 
            continue;
        end
        
        cd(pwd);
        cd('D:\ETRI_database\3. 3초로 통일&소리세기augmentation\전체');% 웨이브가 있는 디렉토리
        
        filename=list(i).name;
        disp(filename);
        data = audioread(filename);
        for j = 1:2
            data2(:,j) = conv(Signal(:,j), data(:,j)); %여기서 컨볼루션ww
            data3(:,j)=data2(1:132300,j);
        end
        
        cd(pwd);
        cd(dirN);% 저장될 디렉토리
        s1=list(i).name;
        s2=s1(1:end-4);
        write_name=strcat(name,s2,'.wav'); % need to change for every file
        audiowrite(write_name,data3,fs,'BitsPerSample',16); % outputfile is normalized in apmlitude
        clear data3
        clear data2
        clear data
    end
    clear Signal
end
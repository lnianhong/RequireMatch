clc;clear;
data_max = 10;
data_min = 0;
data_numA = 5;
data_numB = 6;
str = 'S';
while 1
    dataA = randi([data_min data_max],data_numA,1);
    dataB = randi([data_min data_max],data_numB,1);
    if sum(dataA)>sum(dataB)
        deta = sum(dataA)-sum(dataB);
        index = (dataB==0);
        dataB(index) = floor(deta./sum(index));
        dataB(1) = dataB(1)+ sum(dataA)-sum(dataB);
    end
    
    if sum(dataA)<sum(dataB)
        deta = sum(dataB)-sum(dataA);
        index = (dataA==0);
        dataB(index) = floor(deta./sum(index));
        dataA(1) = dataA(1)+ sum(dataB)-sum(dataA);
    end
    if sum(dataA)~= sum(dataB)
        error('The data is error');
    end
    if (max(dataA)<= data_max) && (max(dataB) <= data_max)
        disp('Finished!');
        break;
    end
end
receiver = [reshape(1:data_numA,[],1),dataA];
transimiter = [reshape(1:data_numB,[],1),dataB];
file_nameA = ['receiver_',str,'.csv'];
file_nameB = ['transimiter_',str,'.csv'];
csvwrite(file_nameA,receiver);
csvwrite(file_nameB,transimiter);
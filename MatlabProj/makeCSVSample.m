clc;clear;
data_max = 5000;
data_min = 1;
data_numA = 10000;
data_numB = 11000;
str = 'L';
while 1
    dataA = randi([data_min data_max],data_numA,1);
    dataB = randi([data_min data_max],data_numB,1);
    if sum(dataA)>sum(dataB)
        deta = sum(dataA)-sum(dataB);
        index = (dataB==data_min);
        dataB(index) = floor(deta./sum(index));
        dataB(1) = dataB(1)+ sum(dataA)-sum(dataB);
    end
    
    if sum(dataA)<sum(dataB)
        deta = sum(dataB)-sum(dataA);
        index = (dataA==data_min);
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
file_nameA = ['../VSProj/RequireMatch/data/receiver_',str,'.csv'];
file_nameB = ['../VSProj/RequireMatch/data/transimitter_',str,'.csv'];
dlmwrite(file_nameA,receiver,'precision',16);
dlmwrite(file_nameB,transimiter,'precision',16);
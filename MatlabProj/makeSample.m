clc;clear;
data_max = 1000;
data_min = 0;
data_num = 500000;
while 1
    dataA = randi([data_min data_max],data_num,1);
    dataB = randi([data_min data_max],data_num,1);
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
file_name = ['randsample_',num2str(data_max),'_',num2str(data_num),'.mat'];
save(file_name,'dataA','dataB');
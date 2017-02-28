clc;clear;
data_max = 1000;
data_min = 0;
data_num = 500000;
file_name = ['randsample_',num2str(data_max),'_',num2str(data_num),'.mat'];
load(file_name);




if sum(dataA)~= sum(dataB)
    error('The data is error');
end


excTime = 0;
while 1
    dataA = sort(dataA);
    dataB = sort(dataB);
    [C,ia,ib] = intersect(dataA,dataB);
    if sum(ia) ==0
        break;
    end
    dataA(ia) = 0;
    dataB(ib) = 0;
    excTime = excTime+sum(C>0);
    dataA = dataA(dataA~=0);
    dataB = dataB(dataB~=0);
end
while sum(dataA>0)
    dataA = sort(dataA);
    dataB = sort(dataB);
    if dataA(end)>= dataB(end)
        dataA(end) = dataA(end)-dataB(end);
        dataB(end)=0;
    else %dataA(end)< dataB(end)
        dataB(end) = dataB(end)-dataA(end);
        dataA(end) = 0;
    end
    dataA = dataA(dataA~=0);
    dataB = dataB(dataB~=0);
    excTime = excTime+1;
end

% num = 2*N*N
% excTime/num
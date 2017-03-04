clc;clear;
clc;clear;
data_receive = csvread('receiver0228.csv',1,0);
data_tran = csvread('transmitter0228.csv',1,0);
dataT = data_tran(:,2);
dataR = data_receive(:,2);
if sum(dataT)~= sum(dataR)
    error('The data is error');
end
excTime = 0;


while (sum(dataT>0) && sum(dataR>0)) 
    [C,ia,ib] = intersect(dataT,dataR);
    dataT(ia) = 0;
    dataR(ib) = 0;
    excTime = excTime+sum(C>0);
    if sum(dataT)==0 || sum(dataR)==0 
        break;
    end
    dataT = sort(dataT);
    dataR = sort(dataR);
    if dataT(end)>= dataR(end)
        dataT(end) = dataT(end)-dataR(end);
        dataR(end)=0;
    else %dataA(end)< dataB(end)
        dataR(end) = dataR(end)-dataT(end);
        dataT(end) = 0;
    end
    dataT = dataT(dataT~=0);
    dataR = dataR(dataR~=0);
    excTime = excTime+1;
end

% clc;clear;
% N  = 22;
% data = magic(2*N);
% dataA = reshape(data(1:N,:),[],1);
% dataB = reshape(data(N+1:2*N,:),[],1);
% dataA = dataA(dataA~=0);
% dataB = dataB(dataB~=0);

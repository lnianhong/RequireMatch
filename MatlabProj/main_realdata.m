clc;clear;
clc;clear;
data_receive = csvread('receiver.csv',1,0);
data_tran = csvread('transmitter.csv',1,0);
dataA = data_tran(:,2);
dataB = data_receive(:,2);
% if sum(dataA)~= sum(dataB)
%     error('The data is error');
% end
excTime = 0;


while (sum(dataA>0) && sum(dataB>0)) 
    [C,ia,ib] = intersect(dataA,dataB);
    dataA(ia) = 0;
    dataB(ib) = 0;
    excTime = excTime+sum(C>0);
    if sum(dataA)==0 || sum(dataB)==0 
        break;
    end
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

% clc;clear;
% N  = 22;
% data = magic(2*N);
% dataA = reshape(data(1:N,:),[],1);
% dataB = reshape(data(N+1:2*N,:),[],1);
% dataA = dataA(dataA~=0);
% dataB = dataB(dataB~=0);

clc;clear;
% data_max = 1000;
% data_min = 0;
% data_num = 50000;
% file_name = ['randsample_',num2str(data_max),'_',num2str(data_num),'.mat'];
% load(file_name);
% if sum(dataA)~= sum(dataB)
%     error('The data is error');
% end
excTime = 0;

dataA = [ 8 7 5 1];
dataB = [6 4 4 4 3];

while sum(dataA>0)
    [C,ia,ib] = intersect(dataA,dataB);
    dataA(ia) = 0;
    dataB(ib) = 0;
    excTime = excTime+sum(C>0);
    if sum(dataA)==0
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

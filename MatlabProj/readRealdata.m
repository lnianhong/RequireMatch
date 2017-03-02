clc;clear;
data_receive = csvread('receiver0228.csv',1,0);
data_tran = csvread('transmitter0228.csv',1,0);

dataT = data_tran(:,2);
dataR = data_receive(:,2);
indexT = length(dataT);
indexR = length(dataR);

if sum(dataR)> sum(dataT)
    [ tmp,indexR ] = balanceData( dataR,dataT );
    dataR = tmp;
else
    if sum(dataT)> sum(dataR)
        [ tmp,indexT ] = balanceData( dataT,dataR );
        dataT = tmp;
    end
end
csvwrite('receiver0228part.csv',[data_receive(1:indexR,1),dataR]);
csvwrite('transmitter0228part.csv',[data_tran(1:indexT,1),dataT]);




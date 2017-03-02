clc;clear;
data_receive = csvread('receiver0228.csv',1,0);
data_tran = csvread('transmitter0228.csv',1,0);

dataT = data_tran(:,2);
dataR = data_receive(:,2);
if sum(dataR)> sum(dataT)
    [ tmp,index ] = balanceData( dataR,dataT );
    dataR = tmp;
else
    if sum(dataT)> sum(dataR)
        [ tmp,index ] = balanceData( dataT,dataR );
        dataT = tmp;
    end
end




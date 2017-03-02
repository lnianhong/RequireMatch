clc;clear;
data_receive = csvread('receiver0228.csv',1,0);
data_tran = csvread('transmitter0228.csv',1,0);
dataA = data_tran(:,2);
dataB = data_receive(1:314980,2);
if sum(dataA)~= sum(dataB)
    error('The data is error');
end

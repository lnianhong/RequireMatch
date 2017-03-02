function [ tmp,index ] = balanceData( dataL,dataS )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
S = 0;
index = 0;

while S<sum(dataS)
    index = index +1;
    S = S+dataL(index);
end
% S >=sum(dataT)
tmp  = dataL(1:index);
tmp(index) = tmp(index)-(S-sum(dataS));

end


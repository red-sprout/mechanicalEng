clear all; clc;

A=magic(7);
B=zeros(7);
for row=1:1:7
    for col=1:1:7
        B(row,col)=A(row,col)+row+col;
    end
end
B
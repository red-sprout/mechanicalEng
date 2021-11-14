clear all; clc;

q_0=10^5;   k=50;
L=0.03;     T_0=20;
M=30;       dx=L/M;
x=linspace(1,M,M)*dx;
T=(q_0/(2*k))*(2*L.*x-x.^2)+T_0;

for i=1:1:M
    fprintf("T_%d=%f\n",i,T(i))
end

plot(x,T)
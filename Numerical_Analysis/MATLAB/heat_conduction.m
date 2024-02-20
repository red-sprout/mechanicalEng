clear all; clc;

q_0=10^5;   k=50;
L=0.03;     T_0=20;
M=30;       dx=L/M;
e_max=0.0005;   e=1;

A=zeros(M);
b=zeros(M,1)-(dx^2)*q_0/k;
b(1)=b(1)-T_0;
T=zeros(M,1)+T_0;
for i=1:1:M
    if i==1
        A(i,i)=-2;  A(i,i+1)=1;
    elseif i==M
        A(i,i-1)=2; A(i,i)=-2;
    else
        A(i,i-1)=1; A(i,i)=-2;  A(i,i+1)=1;
    end
end
A_=A-eye(M).*A;
x=linspace(1,M,M)'*dx;

l=0;    T_old=zeros(M,1);   T_=zeros(M,1);

fprintf("Iteration=0 \t")
for i=1:1:M
    fprintf("T_%d=%f,\t",i,T(i))
end
fprintf("\n")

while 1
    hold on;
    if mod(l,100)==0
        plot(x,T)
    end
    if e<e_max
        break
    end
    l=l+1;
    T_old=T;
    fprintf("Iteration=%d \t",l)
    for i=1:1:M
        T_(i)=(1/A(i,i)).*(b(i)-A_(i,:)*T);
        fprintf("T_%d=%f,\t",i,T_(i))
    end
    
    T=T_;
    e=sum(abs(T-T_old));
    fprintf("\n")
end
clear all;clc;

k=40;       alpha=3*(10^-5);    h=500;
T_0=200;    T_inf=100;          t=0;
%아래 dx와 dt의 값을 수렴/발산 조건에 따라 바꿔준다.
dx=0.04;    dt=40/3;            m=4;    n=100;
Fo=alpha*dt/(dx^2);
T=zeros(n,1)+200;
x=zeros(n,1);
T_=T;

fprintf("iter=0  \t")
for idx=1:1:m
    fprintf("x=%.2fm -> %.1f\t",(idx-1)*dx,T(idx))
    x(idx)=(idx-1)*dx;
end
hold on;
fprintf("\tt=%f\n",t)
plot(x(1:m),T(1:m));

for i=1:1:100
    fprintf("iter=%d  \t",i)
    for idx=1:1:m
        if idx==1
            T_(idx)=Fo*(2*T(idx+1)+2*dx*h*T_inf/k)+(1-2*Fo*(1+(dx*h/k)))*T(idx);
            fprintf("x=%.2fm -> %.1f\t",(idx-1)*dx,T_(idx))
        else
            T_(idx)=Fo*(T(idx-1)+T(idx+1))+(1-2*Fo)*T(idx);
            fprintf("x=%.2fm -> %.1f\t",(idx-1)*dx,T_(idx))
        end
    end
    T=T_;
    t=t+dt;
    hold on;
    fprintf("\tt=%f\n",t)
    plot(x(1:m),T(1:m));
end
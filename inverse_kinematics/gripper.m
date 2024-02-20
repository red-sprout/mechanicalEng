clear all; clc;

RotZ=@(theta) [cos(theta) -sin(theta) 0 0;sin(theta) cos(theta) 0 0;0 0 1 0;0 0 0 1];
T=@(x,y,z) [1 0 0 x;0 1 0 y;0 0 1 z;0 0 0 1];
spring_x=0.06;
l=1;

theta0=atan(0.5);
theta=theta0;
alpha=1;     t=0;    dt=0.01;
while 1
    cla;
    if theta<=0
        theta=0;
    end
    T_0_1=RotZ(pi-theta)*T(0.04,0,0);
    T_1_2=RotZ(0)*T(0.04,0.02,0);
    T_0_3=RotZ(-pi/2-theta)*T(0.02,0,0);
    T_0_2=T_0_1*T_1_2;

    y_0=[1 0 0 0;0 1 0 0;0 0 1 0;0 0 0 1];
    y_0_1=T_0_1*y_0;
    y_0_2=T_0_2*y_0;
    y_0_3=T_0_3*y_0;

    originX = [y_0_2(1,4),y_0_1(1,4),y_0(1,4),y_0_3(1,4)];
    originY = [y_0_2(2,4),y_0_1(2,4),y_0(2,4),y_0_3(2,4)];
    originY_ = [-0.04-y_0_2(2,4),-0.04-y_0_1(2,4),-0.04-y_0(2,4),-0.04-y_0_3(2,4)];
    spring = [originX(3),spring_x];
    string = [originX(4),l];
    
    hold on;
    plot(originX,originY,"LineWidth",5)
    plot(originX,originY_,"LineWidth",5)
    plot(spring,[originY(3),originY(3)],"k");
    plot(spring,[originY_(3),originY_(3)],"k");
    plot(string,[originY(4),originY(4)],"k");
    plot(string,[originY_(4),originY_(4)],"k")
    axis equal
    axis ([-0.1 0.1 -0.1 0.1])
    if theta==0
        break;
    end
    t=t+dt;
    theta=theta0-alpha*t^2;
    pause(0.01)
end

m=0.011;    c=100;  k=200;  F0=20;  f=F0/4;
syms x(t)
Dx=diff(x,t);
Dx2=diff(x,t,2);
ode=m*Dx2+c*Dx+k*x==F0-f;
cond1=x(0)==0;
cond2=Dx(0)==0;
cond=[cond1,cond2];
xSol(t)=dsolve(ode,cond);

t_=0;    dt=0.01;
x_old=0; x_=1;
while 1
    cla;
    dx=(x_-x_old);
    err=abs(spring_x-x_);
    if err<=0.00001
        dx=0;
    end
    x_old=xSol(t_);
    if t_==0
        originX = originX+x_old;
    else
        originX = originX+dx;
    end
    spring = [originX(3),spring_x];
    string = [originX(4),l];

    hold on;
    plot(originX,originY,"LineWidth",5)
    plot(originX,originY_,"LineWidth",5)
    plot(spring,[originY(3),originY(3)],"k");
    plot(spring,[originY_(3),originY_(3)],"k");
    plot(string,[originY(4),originY(4)],"k");
    plot(string,[originY_(4),originY_(4)],"k")
    axis equal
    axis ([-0.1 0.1 -0.1 0.1])
    if dx==0
        break;
    end
    t_=t_+dt;
    x_=xSol(t_);
    pause(0.01)
end

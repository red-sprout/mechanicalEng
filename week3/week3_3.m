clear all; clc;

a1=15;              a2=15;
theta1=45*pi/180;   theta2=-30*pi/180;

T_a1=[1 0 0 a1;0 1 0 0;0 0 1 0;0 0 0 1];
T_a2=[1 0 0 a2;0 1 0 0;0 0 1 0;0 0 0 1];
R1=[cos(theta1) -sin(theta1) 0 0;sin(theta1) cos(theta1) 0 0;0 0 1 0;0 0 0 1];
R2=[cos(theta2) -sin(theta2) 0 0;sin(theta2) cos(theta2) 0 0;0 0 1 0;0 0 0 1];

T_0_1=R1*T_a1;
T_1_2=R2*T_a2;
T_0_2=T_0_1*T_1_2;

x=[0 T_0_1(1,4) T_0_2(1,4)];
y=[0 T_0_1(2,4) T_0_2(2,4)];

plot(x,y,'LineWidth',2);
axis([-4 29 -4 29]);
axis square;
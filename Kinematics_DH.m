theta1 = 45*pi/180;
theta2 = -30*pi/180;

a1=15;
a2=15;

RotZ=@(theta) [cos(theta) -sin(theta) 0 0;sin(theta) cos(theta) 0 0;0 0 1 0;0 0 0 1];
T=@(x,y,z) [1 0 0 x;0 1 0 y;0 0 1 z;0 0 0 1];

T_0_1=RotZ(theta1)*T(a1,0,0);
T_1_2=RotZ(theta2)*T(a2,0,0);
T_total=T_0_1*T_1_2;

y_0=[1 0 0 0;0 1 0 0;0 0 1 0;0 0 0 1];
y_0_1=T_0_1*y_0;
y_0_2=T_total*y_0;

originX = [y_0(1,4),y_0_1(1,4),y_0_2(1,4)];
originY = [y_0(2,4),y_0_1(2,4),y_0_2(2,4)];

plot(originX,originY,'LineWidth',2);
axis([min([originX, originY])-4, max([originX, originY])+4, min([originX, originY])-4, max([originX, originY])+4])
axis square

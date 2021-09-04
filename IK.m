clear all; clc;
l1=input('Enter the size of link 1: ');
l2=input('Enter the size of link 2: ');
x_initial=input('Enter the x_cord: ');
y_initial=input('Enter the y_cord: ');

v=VideoWriter('IK.avi');    % 비디오 입력
open(v);
for t=0:0.02:8
    axis([-5 5 -5 5])
    axis square;
    
    cla;
    
    if t<=2
        x=x_initial+t;
        y=y_initial;
    elseif t<=4
        x=x_initial+2;
        y=y_initial+(t-2);
    elseif t<=6
        x=x_initial+2-(t-4);
        y=y_initial+2;
    else
        x=x_initial;
        y=y_initial+2-(t-6);
    end
    
    theta1=atan2(y,x)-acos((x^2+y^2+l1^2-l2^2)/(2*l1*(x^2+y^2)^0.5));
    x1=0;                   y1=0;
    x2=x1+l1*cos(theta1);   y2=y1+l1*sin(theta1);
    x3=x;                   y3=y;
    
    L1x=[x1 x2];            L1y=[y1 y2];
    L2x=[x2 x3];            L2y=[y2 y3];
    L3x=[x_initial x_initial+2];    L3y=[y_initial y_initial];
    L4x=[x_initial+2 x_initial+2];  L4y=[y_initial y_initial+2];
    L5x=[x_initial+2 x_initial];    L5y=[y_initial+2 y_initial+2];
    L6x=[x_initial x_initial];      L6y=[y_initial+2 y_initial];
    

    line(L3x,L3y,'color','black')
    line(L4x,L4y,'color','black')
    line(L5x,L5y,'color','black')
    line(L6x,L6y,'color','black')    
    line(L1x,L1y,'color','blue','LineWidth',2)
    line(L2x,L2y,'color','red','LineWidth',2)
    hold on;
    
    plot(x1,y1,'o','MarkerFaceColor','black','MarkerSize',10)
    plot(x2,y2,'o','MarkerFaceColor','black','MarkerSize',10)
    plot(x3,y3,'o','MarkerFaceColor','black','MarkerSize',10)
    
    pause(0.01);
    
    F=getframe(gcf);
    writeVideo(v,F);
end
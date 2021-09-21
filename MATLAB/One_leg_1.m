clear all; clc;
L = 2;
theta = 0;
H = 4;
theta_d = asin(H/(2*L));
dt = 0.01;
i=0;

Kp = 0.1;
Ki = 0.1;
Kd = 0.001;
integral = 0;
lastError = 0;
result=zeros();
t_ = 0:dt:2;

for t = t_
    axis([-2 3 0 5])
    axis square
    
    cla;
    i=i+1;
    
    error = theta_d-theta;
    pControl = Kp * error;
    integral = integral + error * dt;
    iControl = Ki * integral;
    dControl = Kd * (error-lastError)/dt;

    lastError = error;
    pidControl = pControl + iControl + dControl;
    
    theta = theta + pidControl * error;
    fprintf("%d\n",2*L*sin(theta));
    result(i)=theta;
    
    x1 = 0;                 y1 = 0;
    x2 = L*cos(theta);      y2 = L*sin(theta);
    x3 = 0;                 y3 = 2*L*sin(theta);
    
    L1x=[x1 x2];            L1y=[y1 y2];
    L2x=[x2 x3];            L2y=[y2 y3];
    
    line(L1x,L1y,'color','blue','LineWidth',2)
    line(L2x,L2y,'color','red','LineWidth',2)
    hold on;
    plot(x2,y2,'o','MarkerFaceColor','black','MarkerSize',10)
    
    pause(0.01)
end

cla;
axis([0,2,0,5])
plot(t_,result);
hold on;
fplot(asin(H/(2*L)));
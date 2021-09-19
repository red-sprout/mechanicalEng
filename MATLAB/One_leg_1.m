clear all; clc;
L = 2;
theta = 0;
H = 3;
theta_d = asin(3/(2*L));
dt = 0.1;
i=0;

Kp = 1.5;
Ki = 0;
Kd = 0;
integral = 0;
preAngle = theta;
result=zeros();
t_ = 0:dt:2;

for t = t_
    i=i+1;
    error = theta_d-theta;
    pControl = Kp * error;
    integral = integral + error * dt;
    iControl = Ki * integral;
    dAngle = theta - preAngle;
    dControl = -Kd * (dAngle / dt);

    preAngle = theta;
    pidControl = pControl + iControl + dControl;
    
    theta = pidControl * error * exp(-t);
    fprintf("%d\n",theta);
    result(i)=theta;
end
plot(t_,result);
hold on;
fplot(asin(3/(2*L)));
clear all;clc;close all;
L = 2;
theta = 0;
H = 3;
theta_d = asin(3/(2*L));
dt = 0.01;
i=0;
t = 0:dt:2; 
u = ones(1,201);

kp = 150; 
ki = 3; 
kd = 30; 
C = tf([kd kp ki],[1 0]); 
G = tf([1],[1 5 3]); 
Gc = feedback(G*C,1);
y = lsim(Gc,u,t); 
plot(t,y) 
xlabel('time[sec]') 
axis([0 1 0 1.1])
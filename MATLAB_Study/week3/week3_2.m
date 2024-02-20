clear all; clc;

w=linspace(-10,10,2000);
s=complex(0,w);
T_1=10; T_2=5;
G=(1+s.*T_2)./(1+s.*T_1);

plot(G,'bo-');
axis([0.1 1.4 -0.5 0.5]);
axis equal;
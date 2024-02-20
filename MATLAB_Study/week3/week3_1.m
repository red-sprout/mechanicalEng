clear all; clc;

x=linspace(-5,5,100);
g=1./(1+exp(-x));
plot(x,g,'ro');
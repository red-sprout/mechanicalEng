%week5_1.m
clear all; clc;
z=[-1,0,2];
g=@(z) 1/(1+exp(-z));
fprintf("%f %f %f\n",g(z(1)),g(z(2)),g(z(3)))
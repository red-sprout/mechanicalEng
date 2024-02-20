clear all; clc;
x_l=-5; x_u=5;
e=1;    n=1;
x_r_old=x_l;

while e>=0.005
    f_l=x_l^3+2*x_l^2+3*x_l+4;
    f_u=x_u^3+2*x_u^2+3*x_u+4;
    x_r=x_u-f_u*(x_l-x_u)/(f_l-f_u);

    f_r=x_r^3+2*x_r^2+3*x_r+4;

    if f_l*f_r<0
        x_u=x_r;
    else
        x_l=x_r;
    end
    
    hold on;
    plot(n,x_r,'ro')
    e=abs((x_r-x_r_old)/x_r);
    x_r_old=x_r;
    
    n=n+1;
end
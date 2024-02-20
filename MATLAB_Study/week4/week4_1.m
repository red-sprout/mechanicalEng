clear all; clc;

year=2021;
if ((mod(year,4)==0) && (mod(year,100)~=0)) || mod(year,400)==0
    fprintf("윤년입니다.\n");
else
    fprintf("윤년이 아닙니다.\n");
end
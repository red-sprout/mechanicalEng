clear all; clc;
v=1;
a=4; l1=4; l2=6;

for t=0.01:0.01:1.5
    cla;
    theta=atan((l1-a/2)/(v*t)); 
    oa=[-v*t 0];
    ab=[0 a/2];
    bc=[v*t (l1-a/2)];
    cd=[l2*sin(theta) -l2*cos(theta)];

    ob=oa+ab;
    oc=ob+bc;
    od=oc+cd;
    oe=oc+[-l1*cos(theta) -l1*sin(theta)];
    of=oa+[-6 0];

    L1x=[oa(1) ob(1)];  L1y=[oa(2) ob(2)];
    L2x=[oe(1) oc(1)];  L2y=[oe(2) oc(2)];
    L3x=[oc(1) od(1)];  L3y=[oc(2) od(2)];

    L4x=[oa(1) ob(1)];  L4y=[-oa(2) -ob(2)];
    L5x=[oe(1) oc(1)];  L5y=[-oe(2) -oc(2)];
    L6x=[oc(1) od(1)];  L6y=[-oc(2) -od(2)];
    L7x=[oa(1) of(1)];  L7y=[oa(2) of(2)];

    line(L1x,L1y,'color','red','LineWidth',2);
    line(L2x,L2y,'color','blue','LineWidth',2);
    line(L3x,L3y,'color','blue','LineWidth',2);

    line(L4x,L4y,'color','red','LineWidth',2);
    line(L5x,L5y,'color','blue','LineWidth',2);
    line(L6x,L6y,'color','blue','LineWidth',2);
    line(L7x,L7y,'color','red','LineWidth',2);

    axis([-8 8 -8 8])
    axis square
    hold on
    plot(oc(1),oc(2),'.','MarkerEdgeColor','black','MarkerFaceColor','black','MarkerSize',30);
    plot(oc(1),-oc(2),'.','MarkerEdgeColor','black','MarkerFaceColor','black','MarkerSize',30);
    pause(0.01)
    
end
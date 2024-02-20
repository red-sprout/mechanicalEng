clc; clear all;

% 링크 길이
a=0.065;        b=0.19;
c=0.16;         r=0.0475;       % r : 실린더, 피스톤 반지름
h=0.21;         l=0.3;          % h : 실린더 높이
                                % l : 밑면에서 크랭크 중심 사이 거리
t=0;            step=0.05;
Vol_min=100;    Vol_max=0;      % Vol : 행정 부피
t_min=0;        t_max=0;        % 행정 부피가 최소, 최대일 때의 시간

t_=input('작동 시간을 입력해주세요.[s]: ');
omega2_initial=input('각속도를 입력해주세요.[rad/s]: ');
omega2=omega2_initial;
alpha2=input('각가속도를 입력해주세요.[rad/s^2]: ');
TH2_initial=pi/2;           % 90도에서 운동시작
i=0;

fprintf('\n 1: 위치, 선속도, 선가속도 2: 각도, 각속도, 각가속도\n')
CASE=input('무엇을 보시겠습니까?: ');

while(CASE ~=1 && CASE ~=2)
    fprintf('잘못입력하였습니다. 다시 입력해주세요.\n')
    CASE=input('무엇을 보시겠습니까?: ');
end

% data set initial
time=zeros();
data_d=zeros();
data_f=zeros();    
data_TH3=zeros();
data_TH4=zeros();
data_omega3=zeros();
data_omega4=zeros();
data_alpha3=zeros();
data_alpha4=zeros();
data_d_velocity=zeros();
data_f_velocity=zeros();
data_d_accel=zeros();
data_f_accel=zeros();
det=zeros();

v=VideoWriter('Stirling_Engine_MATLAB.avi');    % 비디오 입력
open(v);
clf;    % 기존 figure 창 지우기

while(1)
    i=i+1;
    
    if t>t_
        break;
    end
    
    % 실제 작동현황을 보여줌
    subplot(2,2,1);
    title('Stirling Engine')
    axis([-0.2 0.4 -0.2 0.4])
    xlabel('x(m)');
    ylabel('y(m)');
    grid on;
            
    cla;

    % loop input
    TH2=TH2_initial+omega2_initial*t+0.5*alpha2*t^2;
    omega2=omega2_initial+alpha2*t;
    
    %% Theta 3,4
    TH3=2*pi-acos(a*cos(TH2)/b);    % 이론 계산으로 구한 값은 예각인데, 실제로 구한 각은
                                    % 그림에서 보듯 180도가 넘는다. 즉, 2pi-theta 꼴이다.
    TH4=pi-asin(a*sin(TH2)/c);      % 이론 걔산으로 구한 값은 예각인데, 실제로 구한 각은
                                    % 그림에서 보듯 둔각이다. 즉, pi-theta 꼴이다.
                                    % 각각의 각에 대해 sin, cos에 대입시 부호는 달라질 수 있지만, 크기는 같다.
    
    %% Distance
    d=a*sin(TH2)-b*sin(TH3);
    f=a*cos(TH2)-c*cos(TH4);
    
    %% Angular Velocity
    omega3=(a/b)*(sin(TH2)/sin(TH3))*omega2;
    omega4=(a/c)*(cos(TH2)/cos(TH4))*omega2;
    
    %% Velocity
    d_vel=a*omega2*cos(TH2)-b*omega3*cos(TH3);
    f_vel=-a*omega2*sin(TH2)+c*omega4*sin(TH4);
    
    %% Angular Acceleration
    alpha3=(a*alpha2*sin(TH2)+a*omega2^2*cos(TH2)-b*omega3^2*sin(TH3))/(b*sin(TH3));
    alpha4=(a*alpha2*cos(TH2)-a*omega2^2*sin(TH2)+c*omega4^2*sin(TH4))/(c*cos(TH4));
    
    %% Acceleration
    d_accel=a*alpha2*cos(TH2)-a*omega2^2*sin(TH2)-b*alpha3*cos(TH3)+b*omega3^2*sin(TH3);
    f_accel=-a*alpha2*sin(TH2)-a*omega2^2*cos(TH2)+c*alpha4*sin(TH4)+c*omega4^2*cos(TH4);
    
    %% Coordinate of the points
    x1=0;               y1=0;
    x2=x1+a*cos(TH2);   y2=y1+a*sin(TH2);
    x3=x1;              y3=y1+d;
    x4=x1+f;            y4=y1;
    x5=x1;              y5=y1+l;
    x6=x1+l;            y6=y1;
    
    %% Link by two points
    L1x=[x1 x2];        L1y=[y1 y2];
    L2x=[x2 x3];        L2y=[y2 y3];
    L3x=[x2 x4];        L3y=[y2 y4];
    
    %% Crank, Cylinder
    L4x=[x3-r x3+r];    L4y=[y3 y3];        % 피스톤1
    L5x=[x4 x4];        L5y=[y4-r y4+r];    % 피스톤2
    L6x=[x5-r x5+r];    L6y=[y5 y5];        % 실린더1 밑면
    L7x=[x6 x6];        L7y=[y6+r y6-r];    % 실린더2 밑면
    L8x=[x5-r x5-r];    L8y=[y5-h y5];      % 실린더1 외벽
    L9x=[x5+r x5+r];    L9y=[y5-h y5];      % 실린더1 외벽
    L10x=[x6-h x6];     L10y=[y6-r y6-r];   % 실린더2 외벽
    L11x=[x6-h x6];     L11y=[y6+r y6+r];   % 실린더2 외벽
    
    %% Drawing of links, crank, cylinder
    line(L1x,L1y,'color','green','LineWidth',2)
    line(L2x,L2y,'color','red','LineWidth',2)
    line(L3x,L3y,'color','blue','LineWidth',2)
    
    line(L4x,L4y,'color','red','LineWidth',3)
    line(L5x,L5y,'color','blue','LineWidth',3)
    line(L6x,L6y,'color','black')
    line(L7x,L7y,'color','black')
    line(L8x,L8y,'color','black')
    line(L9x,L9y,'color','black')
    line(L10x,L10y,'color','black')
    line(L11x,L11y,'color','black')
    
    %% Data save
    
    data_d(i)=y3;
    data_f(i)=x4;
    data_TH3(i)=TH3;
    data_TH4(i)=TH4;
    data_omega3(i)=omega3;
    data_omega4(i)=omega4;
    data_alpha3(i)=alpha3;
    data_alpha4(i)=alpha4;
    data_d_velocity(i)=d_vel;
    data_f_velocity(i)=f_vel;
    data_d_accel(i)=d_accel;
    data_f_accel(i)=f_accel;
    
    time(i)=t;
    t=t+step;
    
    switch CASE
        case 1
            % 위치 해석
            subplot(2,2,2);
            plotresult(t_,time,data_d,data_f,...
                'time[s]','distance[m]')
    
            % 속도 해석
            subplot(2,2,3);
            plotresult(t_,time,data_d_velocity,data_f_velocity,...
                'time[s]','velocity[m/s]')

            % 가속도 해석
            subplot(2,2,4);
            plotresult(t_,time,data_d_accel,data_f_accel,...
                'time[s]','acceleration[m/s^2]')
            
        case 2
            % 각 해석
            subplot(2,2,2);
            plotresult(t_,time,data_TH3,data_TH4,...
                'time[s]','theta[rad]')
    
            % 각속도 해석
            subplot(2,2,3);
            plotresult(t_,time,data_omega3,data_omega4,...
                'time[s]','angular velocity[rad/s]')
    
            % 각가속도 해석
            subplot(2,2,4);
            plotresult(t_,time,data_alpha3,data_alpha4,...
                'time[s]','angular acceleration[rad/s^2]')

        otherwise
            break;
    end
    
    V=pi*(r^2)*((0.3-d)+(0.3-f));
    
    if Vol_min>V
        Vol_min=V;
        t_min=t;
    end
    
    if Vol_max<V
        Vol_max=V;
        t_max=t;
    end

    % 링크 길이가 일정한지 확인하는 과정, 모두 O가 나와야함.
    if abs((x1-x2)^2+(y1-y2)^2-a^2)<0.01
        det(1,i)='O';
    else
        det(1,i)='X';
    end
    if abs((x2-x3)^2+(y2-y3)^2-b^2)<0.01
        det(2,i)='O';
    else
        det(2,i)='X';
    end
    if abs((x2-x4)^2+(y2-y4)^2-c^2)<0.01 
        det(3,i)='O';
    else
        det(3,i)='X';
    end
    
    F=getframe(gcf);
    writeVideo(v,F);
end

close(v);

%엑셀로 각 Data 출력
DATA=[time' data_d' data_f' data_TH3' data_TH4'...
    data_omega3' data_omega4' data_alpha3' data_alpha4'...
    data_d_velocity' data_f_velocity' data_d_accel' data_f_accel'];

xlswrite('Stirling_Engine_data',DATA,'A2:M20000')
parameter={'t' 'd' 'f' 'TH3' 'TH4' 'Omega3' 'Omega4'...
    'Alpha3' 'Alpha4' 'd_velocity' 'f_velocity'...
    'd_accel' 'f_accel'};
xlswrite('Stirling_Engine_data',parameter)

char(det)
fprintf('t가 %f[s]일 때 최소 행정 부피 : %f[m^3]\n',t_min,Vol_min)
fprintf('t가 %f[s]일 때 최대 행정 부피 : %f[m^3]\n',t_max,Vol_max)
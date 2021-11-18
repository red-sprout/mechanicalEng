function plt()
    x=linspace(-5,5,100);
    y=-0.5*(x-2).^2+2;
    for i=1:1:100
        if x(i)>=2
            y(i)=2;
        end
    end
    plot(x,y)
end
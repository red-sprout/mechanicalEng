function result=ReLU(x)
    result=relu(x);
    graph(result);
end
function result=relu(x)
    if x<0
        result=0;
    else
        result=x;
    end
end
function graph(result)
    x=linspace(-5,5,100);
    y=zeros(1,100);
    for i=1:1:100
        y(i)=relu(x(i));
    end
    hold on;
    plot(x,y,'r')
    axis equal
    f=relu(result);
    plot(result,f,'ro')
end
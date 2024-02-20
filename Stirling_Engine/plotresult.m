function plotresult(t_,time,data1,data2,x_axis,y_axis)
    axis([0 t_ -inf inf])
    hold on;
    plot(time(:),data1(:),'r');
    plot(time(:),data2(:),'b');
    xlabel(x_axis);
    ylabel(y_axis);
    grid on;
end
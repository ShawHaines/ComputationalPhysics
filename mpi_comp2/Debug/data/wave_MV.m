clear;
interval=0.1;
data=zeros(800,2);
for i=0:10:700
    for j=0:1:7
        file=sprintf('emp_%03d_%d.txt',i,j);
        da=load(file);
        data(1+j*100:(j+1)*100,:)=da;
    end
    plot(data(:,1),data(:,2),'r','linewidth',1.5);grid on;
    set(gca,'fontsize',15);
    xlim([1 800]);ylim([0 1.5]);
    xlabel('i');ylabel('emp');
    str=sprintf('n=%03d',i);
    text(330,1.35,str,'color',[1,1,1],'fontsize',20,'backgroundcolor',[0 0 0]);
    for k=0:1:7
        str1=sprintf('R%d',k); text(100*k+25,1.1,str1,'fontsize',18);
    end
    % xlim([1 800]);ylim([0 1.5]);
    pause(interval);
end
load('resultats.txt');
[N,p]=size(resultats);
N_steps=3002;
temps = linspace(1,N_steps+1,N_steps+1);
Nb_particules = N/N_steps;
global dynamique_x; global dynamique_y; global dynamique_z;

dynamique_x=zeros(Nb_particules,N_steps);
dynamique_y=zeros(Nb_particules,N_steps);
dynamique_z=zeros(Nb_particules,N_steps);
for i=1:Nb_particules
    for j=1:N_steps
        dynamique_x(i,j+1)= resultats(i+(j-1)*Nb_particules,1);
        dynamique_y(i,j+1)= resultats(i+(j-1)*Nb_particules,2);
        dynamique_z(i,j+1)= resultats(i+(j-1)*Nb_particules,3);
    end
end



%%
xmax= max(abs(dynamique_x(1,:)));
ymax=max(abs(dynamique_y(1,:)));
for i=1:Nb_particules
    if xmax< max(abs(dynamique_x(i,:)))
        xmax = max(abs(dynamique_x(i,:)));
    end
    if ymax< max(abs(dynamique_x(i,:)))
        ymax = max(abs(dynamique_y(i,:)));
    end
end

for j=2:N_steps+1
    for i=1:N_part
       plot(dynamique_x(i,j),dynamique_y(i,j),'k.','MarkerSize',10);
       xlim([-xmax*0.05 xmax*0.05])
       ylim([-ymax*0.05 ymax*0.05])
       hold on;
    end 
    drawnow;  hold off; 
    pause(0.1);
end

load('resultats.txt');
[N,p]=size(resultats);
N_steps=302;
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
fprintf('Done\n');


%%
xmax= max(abs(dynamique_x(1,:)));
ymax=max(abs(dynamique_y(1,:)));
for i=1:Nb_particules
    if xmax< max(abs(dynamique_x(i,:)))
        xmax = max(abs(dynamique_x(i,:)));
    end
    if ymax< max(abs(dynamique_x(i,:)))
        ymax = max(abs(dynamique_y(i,:)))+1;
    end
end

for j=2:N_steps+1
    for i=1:Nb_particules
       plot(dynamique_x(i,j),dynamique_y(i,j),'k.','MarkerSize',10);
       
       xlim([-2*1e16; 2*1e16])
       ylim([-2*1e16; 2*1e16])
       hold on;
    end
    drawnow;  hold off; 
    pause(0.1);
end

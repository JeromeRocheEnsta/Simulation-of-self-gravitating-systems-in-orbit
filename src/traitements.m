%%
load('resultats.txt'); 
[N,p]=size(resultats);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% N_steps correspond au nombre d'it?rations + 2 %%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


N_steps=602;
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
for j=2:N_steps
    for i=1:Nb_particules
       plot(dynamique_x(i,j),dynamique_y(i,j),'k.','MarkerSize',10);
       
       
       %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       %%% Adapter la fen?tre de visualisation pour coller avec votre
       %%% syst?me
       %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       
       
       xlim([-2*1e2; 2*1e2])
       ylim([-2*1e2; 2*1e2])
       hold on;
    end
    drawnow;  
    hold off; 
    j
    pause(0.1);
end

fprintf('Done_2\n');


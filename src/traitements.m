%%
resultats = load('Plummer_0.5circ_500_6000.txt');
[N,p]=size(resultats);
%load('energie.txt');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% N_steps correspond au nombre d'it?rations + 2 %%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


N_steps=6002;
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%% Evolution de l'energie mecanique %%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
temps =1:N_steps;
plot(temps,energie);
xlabel('Iteration')
ylabel('Energie')
pause(10)

%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%Affichage et conception d'une video%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
vidfile = VideoWriter('3body.mp4','MPEG-4');
open(vidfile);
for j=2:N_steps+1
    if mod(j,20)==0 
        for i=1:Nb_particules
            plot(dynamique_x(i,j),dynamique_y(i,j),'k.','MarkerSize',10);
             %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
             %%% Adapter la fen?tre de visualisation pour coller avec votre
            %%% syst?me
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            xlim([-4E4; 4E4])
            ylim([-4E4; 4E4])
            hold on;
        end
        drawnow;  hold off;
        F = getframe(gcf);
        writeVideo(vidfile, F);
        pause(0.01);
    end
end
close(vidfile)


fprintf('Done_2\n');


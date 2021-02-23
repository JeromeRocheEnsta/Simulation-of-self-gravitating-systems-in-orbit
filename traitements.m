load('resultats.txt');
[N,p]=size(resultats);
N_steps=300002;
Nb_particules = N/N_steps;
dynamique_x=zeros(Nb_particules,N_steps);
dynamique_y=zeros(Nb_particules,N_steps);
dynamique_z=zeros(Nb_particules,N_steps);
for i=1:Nb_particules
    hold on
    for j=1:N_steps
        dynamique_x(i,j+1)= resultats(i+(j-1)*Nb_particules,1);
        dynamique_y(i,j+1)= resultats(i+(j-1)*Nb_particules,2);
        dynamique_z(i,j+1)= resultats(i+(j-1)*Nb_particules,3);
    end
    plot(dynamique_x(i,:),dynamique_y(i,:));
end

hold off


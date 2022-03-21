fileID = fopen('affiche_config_non_padding.txt','r');

fgetl(fileID);

formatSpec = '%f %f';

size_point = [1 2];

START = fscanf(fileID,formatSpec,size_point);

END =  fscanf(fileID,formatSpec,size_point);

figure;
hold on;


while(~feof(fileID))
    fgetl(fileID);
    fgetl(fileID);
    ligne_obst = fscanf(fileID,'%c %d',[1 2]);
    sizeA = [2 ligne_obst(1,2)];
     A = fscanf(fileID,formatSpec,sizeA);
     
    ob = polyshape(A(1,:),A(2,:));
    plot(ob);
end

fclose(fileID);

fileID = fopen('graphe.txt','r');
formatSpec = '%f';
size = [1 1];
nb_arcs = fscanf(fileID,formatSpec,size);

formatSpec_point = '%f %f';
formatSpec_length = '%f';
size = [2 2];

liste_arcs = zeros(2,2,nb_arcs);
liste_length_arcs = zeros(1,nb_arcs);

for i = 1:nb_arcs
    liste_arcs(:,:,i) = fscanf(fileID,formatSpec_point,size);
    liste_length_arcs(1,i) = fscanf(fileID,formatSpec_length,[1 1]);
end

fclose(fileID);

fileID = fopen('path.txt','r');

nb_sommets_chemin = fscanf(fileID,formatSpec,[1 1]);

path = fscanf(fileID,formatSpec_point,[2 nb_sommets_chemin]);

fclose(fileID);


scatter(START(1),START(2),'red');

scatter(END(1),END(2),'red');

for i = 1:nb_arcs
     if liste_length_arcs(1,i) ~= -1
         plot(  liste_arcs(1,:,i) ,   liste_arcs(2,:,i) ); 
     end
end


figure;
hold on;

fileID = fopen('affiche_config_non_padding.txt','r');

fgetl(fileID);

formatSpec = '%f %f';

size_point = [1 2];

START = fscanf(fileID,formatSpec,size_point);

END =  fscanf(fileID,formatSpec,size_point);


while(~feof(fileID))
    fgetl(fileID);
    fgetl(fileID);
    ligne_obst = fscanf(fileID,'%c %d',[1 2]);
    sizeA = [2 ligne_obst(1,2)];
     A = fscanf(fileID,formatSpec,sizeA);
     
    ob = polyshape(A(1,:),A(2,:));
    plot(ob);
end

fclose(fileID);

plot(path(1,:),path(2,:),'green');

scatter(START(1),START(2),'red');

scatter(END(1),END(2),'red');
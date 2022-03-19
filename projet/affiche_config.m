%%pkg load matgeom;

fileID = fopen('obstacles4.txt','r');
formatSpec = '%f %f';
sizeA = [2 6];
sizeB = [2 3];
%%sizeC = [2 4];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID,formatSpec,sizeB);
%%C = fscanf(fileID,formatSpec,sizeC);
fclose(fileID);

fileID = fopen('start_end_padding.txt','r');
START = fscanf(fileID,formatSpec,[2 1]);
ENDING = fscanf(fileID,formatSpec,[2 1]);
fclose(fileID);

fileID = fopen('graphe_padding.txt','r');
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

fileID = fopen('path_padding.txt','r');

nb_sommets_chemin = fscanf(fileID,formatSpec,[1 1]);

path = fscanf(fileID,formatSpec_point,[2 nb_sommets_chemin]);

fclose(fileID);


figure; 
hold on;
scatter(START(1),START(2),'red');

ob1 = polyshape(A(1,:),A(2,:));
plot(ob1);
ob2 = polyshape(B(1,:),B(2,:));
plot(ob2);
%ob3 = polyshape(C(1,:),C(2,:));
%plot(ob3);

scatter(ENDING(1),ENDING(2),'red');

for i = 1:nb_arcs
     if liste_length_arcs(1,i) ~= -1
         plot(  liste_arcs(1,:,i) ,   liste_arcs(2,:,i) ); 
     end
end

figure;
hold on;
scatter(START(1),START(2),'red');

ob1 = polyshape(A(1,:),A(2,:));
plot(ob1);
ob2 = polyshape(B(1,:),B(2,:));
plot(ob2);
%ob3 = polyshape(C(1,:),C(2,:));
%plot(ob3);

scatter(ENDING(1),ENDING(2),'red');

plot(path(1,:),path(2,:),'green');

centers = path';

m = length(centers);
radii = ones(m,1)*0.5;

viscircles(centers,radii,'LineWidth',0.1);

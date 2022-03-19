fileID = fopen('obstacles3.txt','r');
formatSpec = '%f %f';
sizeA = [2 5];

A = fscanf(fileID,formatSpec,sizeA);

fclose(fileID);

fileID = fopen('padding.txt','r');
formatSpec = '%f ';

nb_sommets = fscanf(fileID,formatSpec,[1 1]);

formatSpec = '%f %f';
size = [2 nb_sommets];

B = fscanf(fileID,formatSpec,size);

fclose(fileID);

figure; 
hold on;

ob1 = polyshape(A(1,:),A(2,:));
plot(ob1);

ob2 = polyshape(B(1,:),B(2,:));
plot(ob2);

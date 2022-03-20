%pkg load matgeom
figure();
hold on;
fid = fopen("obs2.txt");
formatSpec = '%f %f';
fgetl(fid);
START = fgetl(fid);
START = cell2mat(textscan(START,"%f %f"));
tline = fgetl(fid);
ENDING = cell2mat(textscan(tline,"%f %f"));
drawPoint([START;ENDING],'g','lineWidth',3)
xlim([min(START(1,1),ENDING(1,1))-5 max(START(1,1),ENDING(1,1))+5])
ylim([min(START(1,2),ENDING(1,2))-5,max(START(1,2),ENDING(1,2))+5])
i=0;
while ischar(tline)
    #disp(tline)
    tline = fgetl(fid);
    if length(tline) >= 1 
      if(tline(1) == "%")
        continue
      endif
      if(tline(1) == "/")
        sizeA = [2 textscan(tline,'%s %d'){1,2}];
        A = fscanf(fid,formatSpec,sizeA);
        
        % If using matlab
        %a = polyshape(A(1,:)',A(2,:)','r', 'lineWidth', 2)
        %plot(a)

        % If using Octave
        %drawPolygon(A(1,:)',A(2,:)','r', 'lineWidth', 2);
        i+=1;
      endif
    endif
endwhile
fclose(fid)

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
%plot(liste_arcs(1,:,:),liste_arcs(2,:,:),'b')
fileID = fopen('path.txt','r');

nb_sommets_chemin = fscanf(fileID,formatSpec,[1 1]);

path = fscanf(fileID,formatSpec_point,[2 nb_sommets_chemin]);

fclose(fileID);

plot(path(1,:),path(2,:),'b');
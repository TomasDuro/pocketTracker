function addGTdata(fileName,imageName,cX,cY,W,H)
%Saves groundTruth data in a file

fileID = fopen(fileName,'a');
fprintf(fileID,'%s,%d,%d,%d,%d\n',imageName,cX,cY,W,H);
fclose(fileID);

end
function [X,Y] = positiveSamples(fileGroundTruth)
%code to generate positive training samples

Data = importdata(fileGroundTruth,',');
[Npositives,~] = size(Data.data);

for i = 1:Npositives
    squarePos = Data.data(i,:);
    image = double(imread(char(Data.rowheaders(i)),'png'))/255.0;
    tempImage = image(squarePos(2)-1:squarePos(2)-1+squarePos(4)+1,squarePos(1)-1:squarePos(1)-1+squarePos(3)+1);
    tempX = hogClean(tempImage);
    X(i,:) = hogBlock(tempX);
end

[nSamples,~] = size(X);
Y = ones(nSamples,1);

end
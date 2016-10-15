function [features] = hogClean(image)
%calculate hog cells

[imageHeight,imageWidth] = size(image);

cellSide = 2;
nBins = 9;

cellControl = 0;
for y = 2:cellSide:imageHeight-2
    for x = 2:cellSide:imageWidth-2
        features(1+cellControl*nBins:9+cellControl*nBins) = calculateCell(image,x,y,cellSide,nBins);
        cellControl = cellControl + 1;
    end
end

end
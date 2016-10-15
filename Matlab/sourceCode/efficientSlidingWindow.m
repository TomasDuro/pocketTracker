function [X,pixelH,pixelW] = efficientSlidingWindow(image,windowWidth,windowHeight)
%efficient sliding window implementation

[imageHeight,imageWidth] = size(image);
fullImageFeatures = hogClean(image);

cellSide = 2;
nBins = 9;

imageXcells = (imageWidth-2)/cellSide;

windowControl = 0;
for y = 2:cellSide:imageHeight-windowHeight     %controls the line
    for x = 2:cellSide:imageWidth-windowWidth   %controls the column
        windowControl = windowControl + 1;
        
        counter = 0;
        for iy = 1:cellSide:28
            for ix = 1:cellSide:24
                tempX(1+counter*nBins:9+counter*nBins) = ...
                    fullImageFeatures(((y-2+iy-2+1)/2)*nBins*imageXcells+((x-2+ix-2+1)/2)*nBins+1:...
                    ((y-2+iy-2+1)/2)*nBins*imageXcells+((x-2+ix-2+1)/2)*nBins+9);
                counter = counter+1;
            end
        end
        
        tempX = hogBlock(tempX);
        
        X(windowControl,:) = tempX;
        pixelH(windowControl) = y;
        pixelW(windowControl) = x;
    end
end

end
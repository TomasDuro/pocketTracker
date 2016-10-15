function [X,pixelH,pixelW] = slidingWindow(image,windowWidth,windowHeight)
%sliding window implementation

[imageHeight,imageWidth] = size(image);

windowControl = 0;
for y = 2:2:imageHeight-windowHeight     %controls the line
    for x = 2:2:imageWidth-windowWidth   %controls the column
        windowControl = windowControl + 1;
        tempImage = image(y-1:y-1+windowHeight+1,x-1:x-1+windowWidth+1);
        
        tempX = hogClean(tempImage);
        %tempX = hogBlock(tempX);
        
        X(windowControl,:) = tempX;
        pixelH(windowControl) = y;
        pixelW(windowControl) = x;
    end
end

end
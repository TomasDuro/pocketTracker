function tempBin = calculateCell(image,xinImage,yinImage,cellSide,nBins)
%code to calculate the histogram of a cell

tempGrad = zeros(cellSide*cellSide*2,1);
tempBin = zeros(nBins,1);

for y=0:cellSide-1
    for x=0:cellSide-1
        tempGrad(1+x*2+y*4) = image(yinImage+y,xinImage+x+1) - image(yinImage+y,xinImage+x-1);%x
        tempGrad(2+x*2+y*4) = image(yinImage+y+1,xinImage+x) - image(yinImage+y-1,xinImage+x);%y
    end
end

for i=0:cellSide*cellSide-1
    
    binStep = 180 / nBins;
    binHalfStep = binStep / 2;
    angle = atan2(tempGrad(i*2+2),tempGrad(i*2+1));
    angleDeg = angle*180/pi;
    vote = norm([tempGrad(i*2+2) tempGrad(i*2+1)],2);
    
    if angleDeg < 0
        angleDeg = angleDeg + 180;
    end
    
    for j=0:nBins-1
        if angleDeg < binStep*j + binHalfStep
            nextBin = binStep*j + binHalfStep;
            prevBin = binStep*(j-1) + binHalfStep;
            
            if j < nBins - 1
                tempBin(j+1) = tempBin(j+1) + vote*(angleDeg - prevBin)/binStep;
                if prevBin < 0
                    tempBin(nBins - 1 + 1) = tempBin(nBins - 1 + 1) + vote*(nextBin - angleDeg)/binStep;
                    break;
                end
                tempBin(j - 1 + 1) = tempBin(j - 1 + 1) + vote*(nextBin - angleDeg)/binStep;
                break
            end
            tempBin(1) = tempBin(1) + vote*(angleDeg - 170)/binStep;
            tempBin(nBins - 1 + 1) = tempBin(nBins - 1 + 1) + vote*(190 - angleDeg)/binStep;
            break
        end
    end
end

end
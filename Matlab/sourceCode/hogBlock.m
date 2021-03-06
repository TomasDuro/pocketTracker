function blockFeatures = hogBlock(cellFeatures)
%code to calculate hog blocks

templateYcells = 14;
templateXcells = 12;

nBins = 9;

blockSide = 1;
overlapStep = 0;

counter = 0;

%1 by 1
if blockSide == 1
    blockFeatures = cellFeatures;
end

%2 by 2
if blockSide == 2
    for yi=1:overlapStep:templateYcells - blockSide + 1
        for xi=1:overlapStep:templateXcells - blockSide + 1
            blockFeatures(1+counter*nBins:1+counter*nBins+nBins-1) = ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi-1)*nBins+1:(yi-1)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi)*nBins+1:(yi-1)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi-1)*nBins+1:(yi)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi)*nBins+1:(yi)*templateXcells*nBins+(xi)*nBins+9);
            counter = counter + 1;
        end
    end
end

%3 by 3
if blockSide == 3
    for yi=1:overlapStep:templateYcells - blockSide + 1
        for xi=1:overlapStep:templateXcells - blockSide + 1
            blockFeatures(1+counter*nBins:1+counter*nBins+nBins-1) = ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi-1)*nBins+1:(yi-1)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi)*nBins+1:(yi-1)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi+1)*nBins+1:(yi-1)*templateXcells*nBins+(xi+1)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi-1)*nBins+1:(yi)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi)*nBins+1:(yi)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi+1)*nBins+1:(yi)*templateXcells*nBins+(xi+1)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi-1)*nBins+1:(yi+1)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi)*nBins+1:(yi+1)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi+1)*nBins+1:(yi+1)*templateXcells*nBins+(xi+1)*nBins+9);
            counter = counter + 1;
        end
    end
end

%4 by 4
if blockSide == 4
    for yi=1:overlapStep:templateYcells - blockSide + 1
        for xi=1:overlapStep:templateXcells - blockSide + 1
            blockFeatures(1+counter*nBins:1+counter*nBins+nBins-1) = ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi-1)*nBins+1:(yi-1)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi)*nBins+1:(yi-1)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi+1)*nBins+1:(yi-1)*templateXcells*nBins+(xi+1)*nBins+9) + ...
                cellFeatures((yi-1)*templateXcells*nBins+(xi+2)*nBins+1:(yi-1)*templateXcells*nBins+(xi+2)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi-1)*nBins+1:(yi)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi)*nBins+1:(yi)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi+1)*nBins+1:(yi)*templateXcells*nBins+(xi+1)*nBins+9) + ...
                cellFeatures((yi)*templateXcells*nBins+(xi+2)*nBins+1:(yi)*templateXcells*nBins+(xi+2)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi-1)*nBins+1:(yi+1)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi)*nBins+1:(yi+1)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi+1)*nBins+1:(yi+1)*templateXcells*nBins+(xi+1)*nBins+9) + ...
                cellFeatures((yi+1)*templateXcells*nBins+(xi+2)*nBins+1:(yi+1)*templateXcells*nBins+(xi+2)*nBins+9) + ...
                cellFeatures((yi+2)*templateXcells*nBins+(xi-1)*nBins+1:(yi+2)*templateXcells*nBins+(xi-1)*nBins+9) + ...
                cellFeatures((yi+2)*templateXcells*nBins+(xi)*nBins+1:(yi+2)*templateXcells*nBins+(xi)*nBins+9) + ...
                cellFeatures((yi+2)*templateXcells*nBins+(xi+1)*nBins+1:(yi+2)*templateXcells*nBins+(xi+1)*nBins+9) + ...
                cellFeatures((yi+2)*templateXcells*nBins+(xi+2)*nBins+1:(yi+2)*templateXcells*nBins+(xi+2)*nBins+9);
            counter = counter + 1;
        end
    end
end

end
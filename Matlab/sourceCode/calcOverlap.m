function overlap = calcOverlap(square1,square2)
%code to calculate the overlap between two rectangles

overlapArea = calcOverlapArea(square1,square2);
unionArea = calcUnionArea(square1,square2);
overlap = overlapArea/unionArea;

end
function overlapArea = calcOverlapArea(square1,square2)
%code to calculate the overlap area between two rectangles

wOverlap = max(0,min(square1(1)+square1(3),square2(1)+square2(3)) - max(square1(1),square2(1)));
hOverlap = max(0,min(square1(2)+square1(4),square2(2)+square2(4)) - max(square1(2),square2(2)));
overlapArea = wOverlap*hOverlap;

end
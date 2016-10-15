function unionArea = calcUnionArea(square1,square2)
%code to calculate the union area of two rectangles

unionArea = square1(3)*square1(4) + square2(3)*square2(4) - calcOverlapArea(square1,square2);

end
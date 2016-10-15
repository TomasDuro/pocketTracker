function [cornerX,cornerY,width,height] = initboxTsize(frame,H,W)
%code to initialize the parameters of a bounding box

[C,R,~] = impixel(frame);
close all;

% width = abs(C(2,1)-C(1,1));
% height = abs(R(2,1)-R(1,1));
width = W;
height = H;

cornerX = min(C);
cornerY = min(R);

end
function [X,Y] = negativeSamples(fileBackGround,targetNsamples)
%code to generate negative training samples

windowWidth = 24;
windowHeight = 28;

image = double(imread(char(fileBackGround),'png'))/255.0;

[X,~,~] = efficientSlidingWindow(image,windowWidth,windowHeight);

[nSamples,~] = size(X);
sampleControl = round(nSamples/targetNsamples);
X = X(1:sampleControl:end,:);

[nSamples,~] = size(X);
Y = -1*ones(nSamples,1);

end
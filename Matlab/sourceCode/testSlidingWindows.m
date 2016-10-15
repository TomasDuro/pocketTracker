%test sliding window vs efficient slidingwindow

image = imread('image.png');

windowWidth = 24;
windowHeight = 28;

[X,pixelH,pixelW] = slidingWindow(image,windowWidth,windowHeight);
[Xe,pixelHe,pixelWe] = efficientSlidingWindow(image,windowWidth,windowHeight);
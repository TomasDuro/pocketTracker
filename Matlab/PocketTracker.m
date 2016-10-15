function PocketTracker()
%pocketTracker main file

%FOLDERS
addpath('sourceCode');
addpath('groundTruth');

%FILES
fileGroundTruth ='testingDataSetFINAL';

%PARAMETERS
templateW = 24;
templateH = 28;
frameWidth = 128;
frameHeight = 96;
cellSide = 2;
nBins = 9;
nFails = 0;

OTP = 0;

%IMPORT DATA
%images to test with
Data = importdata(fileGroundTruth,',');
%treined detector
load('Results/FINAL/FINALB0O0L1000');

[nImages,~] = size(Data.data);
overlaps = zeros(nImages,1);

for i = 1:nImages
    
    image = double(imread(char(Data.rowheaders(i)),'png'))/255.0;
    gtSquare = Data.data(i,:); 
    
    [X,pixelH,pixelW] = efficientSlidingWindow(image,templateW,templateH);
    
    [M,~] = size(X);
    X = [ones(M,1) X];
    
%     %LINEAR SVM
%     [label,score] = predict(SVMModel,X);
%     [scoreMax,I] = max(score(:,2));
%     fprintf('Detection: label = %d with %f as score\n',label(I),scoreMax);
%     detSquare = [pixelW(I),pixelH(I),templateW,templateH];
    
    %LOGISTIC REGRESSION
    score = X * theta;
    [scoreMax,I] = max(score);
    fprintf('Detection: %f as score\n',scoreMax);
    detSquare = [pixelW(I),pixelH(I),templateW,templateH];    
    
    image = drawbox(image,pixelW(I),pixelH(I),templateW,templateH);
    imshow(image);
    
    %Evaluation Calculations
    overlaps(i) = calcOverlap(gtSquare,detSquare);
    
    if overlaps(i) < 0.5
        nFails = nFails + 1;
    else
        OTP = OTP + overlaps(i);
    end
    
    fprintf('Progress: %d/%d\n',i,nImages);
end

%Evaluation Results
OTP = OTP/(nImages-nFails);
ATA = mean(overlaps);
nFails;

close all;
return;
end
    
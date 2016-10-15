function PocketTrainer()
%code to train the parameters of the detector

%FOLDERS
addpath('sourceCode');

%FILES
fileGroundTruth ='groundTruth/trainingDataSetFINAL';
fileBackGround = {'imageSequences/imagesCyberZoo/imageLeft40';...
    'imageSequences/imagesCyberZoo/imageLeft509';...
    'imageSequences/imagesCyberZoo/imageLeft698';...
    'imageSequences/imagesCyberZoo/imageLeft852';...
    'imageSequences/imagesCyberZoo/imageLeft1010';...
    'imageSequences/imagesFinalTrainB/imageRight296';...
    'imageSequences/imagesFinalTrainB/imageRight351';...
    'imageSequences/imagesFinalTrainB/imageRight1061'};

fileSaveXyTheta = 'Results/name.mat';
%PARAMETROS
nNegative = 600;

[Xtrain,Ytrain] = sampler(fileGroundTruth,fileBackGround,nNegative);

size(Xtrain)

% SVMModel = fitcsvm(Xtrain,Ytrain,'KernelFunction','linear','Standardize',true,'ClassNames',[-1,1]);
% save(fileSaveXyTheta,'Xtrain','Ytrain','SVMModel');

theta = trainLogist(Xtrain,Ytrain);
save(fileSaveXyTheta,'Xtrain','Ytrain','theta');

end
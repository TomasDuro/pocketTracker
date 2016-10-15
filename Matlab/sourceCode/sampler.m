function [Xtrain,Ytrain] = sampler(fileGroundTruth,fileBackGround,nNegative)
%code to generate the final dataset then used for training

[nBacks,~] = size(fileBackGround);

[Xtrain,Ytrain] = positiveSamples(fileGroundTruth);

for i = 1:nBacks
    [X,Y] = negativeSamples(fileBackGround{i},nNegative/nBacks);
    Xtrain = [Xtrain;X];
    Ytrain = [Ytrain;Y];
end

[nSamples,~] = size(Xtrain);
Xtrain = [ones(nSamples,1) Xtrain];

end
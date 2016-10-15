%code used to anotate the samples which were then used for training

addpath('SourceCode');

TemplateW = 24; %pixel size
TemplateH = 28; %pixel size

SequencesPath = 'imageSequences/';
Sequence = 'imagesFinalTrainB';
ImagesPath = strcat(SequencesPath,Sequence);
ImagesPath = strcat(ImagesPath,'/');

GroundTruthPath = 'groundTruth/final/';
Angle = 'orientation';

for i=1329:1377
    
    good = 0;
    
    ImageName = strcat('imageRight',num2str(i),'.png');
    FRAME = imread(strcat(ImagesPath,ImageName));
    %FRAME = imrotate(FRAME,180);
    
    TEMPFrame = FRAME;
    
    while good == 0
        [cornerX,cornerY,width,height] = initboxTsize(TEMPFrame,TemplateH,TemplateW);
        %[cornerX,cornerY,width,height] = initboxAdaptative(TEMPFrame);
        TEMPFrame = drawbox(FRAME,cornerX,cornerY,width,height);
        imshow(TEMPFrame);
        % 1 for good, 0 for bad
        i
        good = input('Is the box good enough?');
        close all;
    end    
    if good == 2
        continue
    end
    if good == 3
        break
    end
    
    addGTdata(strcat(GroundTruthPath,Angle),strcat(ImagesPath,ImageName),cornerX,cornerY,width,height);
    
end
disp('No more images');
return;

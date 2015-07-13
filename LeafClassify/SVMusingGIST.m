%SVM with RBF kernel using the Gist Features 
clear all;clc;

load GistFeature;
[m, n] = size(GistFeatures);
%GistFeatures size is 140(sample number) * 512
label = [ones(120, 1); zeros(20,1)];

model = svmtrain(label, GistFeatures, '-s 0 -t 2 -c 1.2 -g 2.8');

%------------------------------------------------------------------
%after we trained the model, we test it
testdatalabel = [ones(20, 1); zeros(16,1)];
testdata = zeros(36, 512);
%read the positive training set first
fidin = fopen('./TrainingSet/Trainning/train_list.txt');
cnt = 1;
while ~feof(fidin)
    tline = fgetl(fidin);
    
    % Load image
    img = imread(tline);

    % Parameters:
    clear param gist;
    param.imageSize = [400 300]; % it works also with non-square images
    param.orientationsPerScale = [8 8 8 8];
    param.numberBlocks = 4;
    param.fc_prefilt = 4;

    % Computing gist requires 1) prefilter image, 2) filter image and collect
    % output energies
    [gist, param] = LMgist(img, '', param);
    testdata(cnt, :) = gist;
    cnt = cnt + 1
end
fclose(fidin);

[predictlabel,accuracy, c_v] = svmpredict(testdatalabel,double(testdata),model);

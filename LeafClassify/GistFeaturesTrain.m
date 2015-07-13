%calculate the GIST features of the image by using the LEAR of the
%implementation
clear all; clc;

poistive_num = 120;
negative_num = 20;
GistFeatures = zeros(poistive_num + negative_num, 512);%512 is the size of GIST per image

%read the positive training set first
fidin = fopen('./TrainingSet/Positive/train_list.txt');
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
    GistFeatures(cnt, :) = gist;
    cnt = cnt + 1
end
fclose(fidin);

%read the negative training set first
fidin = fopen('./TrainingSet/Negative/train_list.txt');

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
    GistFeatures(cnt, :) = gist;
    cnt = cnt + 1
end
fclose(fidin);

%save GistFeatures
save GistFeature GistFeatures;

clear;
close all;
%总共有120个训练样本，全部变成300 ×400的大小
for i = 1 : 120
    filename = sprintf('%s%d%s', 'pos (', i, ').jpg');
    img = imread(filename);
    [width, length, depth] = size(img); %600 * 800
    img_rotate = img;
    if width > length %需要旋转 
        img_rotate = imrotate(img, 90);
    end
    img_resize = imresize(img_rotate, [300, 400]);
    imwrite(img_resize, filename);
end



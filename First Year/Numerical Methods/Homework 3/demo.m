
%Demo-ul dureaza aproximativ 240 de secunde, obtinandu-se 12 de imagini

%% ROTATII

x=pi/4;
t=[cos(x) -sin(x); sin(x) cos(x)];

img_out=inverse_mapping('flapping_duck.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_duck_45.png');

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_45.png');


x=pi;
t=[cos(x) -sin(x); sin(x) cos(x)];

img_out=inverse_mapping('flapping_duck.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_duck_180.png');

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_180.png');


x=3*pi/4;
t=[cos(x) -sin(x); sin(x) cos(x)];

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_135.png');


x=5*pi/4;
t=[cos(x) -sin(x); sin(x) cos(x)];

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_225.png');


x=7*pi/4;
t=[cos(x) -sin(x); sin(x) cos(x)];

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_315.png');


%% SCALARI

t=[0.4 0;0 0.4];

img_out=inverse_mapping('flapping_duck.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_duck_0.4.png');

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_0.4.png');

t=[2 0; 0 2];

img_out=inverse_mapping('flapping_bird.png',t);
imwrite(mat2gray(img_out),'inverse_mapping_bird_2.png');

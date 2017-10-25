close all;
clear

disp('Opening File');

video_file = 'D:\Exp\HEVCtupian\ClassD-416x240\BasketballPass_416x240_50.yuv';
% data_path = 'D:\Exp\data\Raw';
% 
% data_folder = dir(data_path);
test = regexp(video_file,'\','split');
test2 = regexp(test{1,5},'_','split');
test3 = regexp(test2{1,2},'x','split');
video_name = test2{1,1};
row = str2double(test3{1,1});
col = str2double(test3{1,2});

% for data_i = 3:28
%     data_folder(data_i).name
%     test = regexp(data_folder(data_i).name,'.txt','split');
%     data_name = test{1,1};
%     if strcmp(data_name,video_name)
%         break
%     end
%     if data_i == 28
%         disp('can not find the data file!');
%         quit;
%     end
% end

%data_file = ['D:\Exp\data\Raw\',data_folder(data_i).name];

videobase = fopen(video_file,'r');
%database = fopen(data_file,'r');

% size_block = 2; % 方块大小
Y = zeros(row,col);
U = zeros(row/2,col/2);
V = zeros(row/2,col/2);
UU = zeros(row,col);
VV = zeros(row,col);
R = zeros(row,col);
G = zeros(row,col);
B = zeros(row,col);
video = struct('cdata',repmat(uint8(0),720,1280,3),'colormap',zeros(1,1000));

% disp('Importing Data');
% i = 1;
% frame_temp = zeros(750,1);
% frame_count = zeros(750,1);
% data = repmat(struct('x',0.0,'y',0.0),[750,300]);

% while ~feof(database)
%     [line] = textscan(fgetl(database),'%d %f %f\n');
%     if frame_temp(line{1,1}) ~= 1
%         frame_temp(line{1,1}) = 1;
%         frame_count(line{1,1}) = 1;
%     end
%     data(line{1,1},frame_count(line{1,1})).x = round(line{1,2}/3840*row);
%     data(line{1,1},frame_count(line{1,1})).y = round(line{1,3}/2160*col);
%     frame_count(line{1,1}) = frame_count(line{1,1}) + 1;
% end

disp('Processing Video');
% writeObj = VideoWriter(['D:\Exp\DataProcess\avi\',num2str(row),'-',num2str(col),'-',video_name,'.avi']);
% open(writeObj);
for frame = 1:750
    frame %#ok<*NOPTS>
    
    try
        [Y(:,:),count] = fread(videobase,[row,col]);
        [U(:,:),count1] = fread(videobase,[row/2,col/2]);
        [V(:,:),count2] = fread(videobase,[row/2,col/2]);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%上面三行用于处理8bit视频，下面三行用于处理16bit视频
%         [Y(:,:),count] = fread(videobase,[row,col],'uint16');
%         [U(:,:),count1] = fread(videobase,[row/2,col/2],'uint16');
%         [V(:,:),count2] = fread(videobase,[row/2,col/2],'uint16');
    catch 
        break
    end
    
    UU(1:2:row-1,1:2:col-1) = U(:,:);
    UU(1:2:row-1,2:2:col) = U(:,:);
    UU(2:2:row,1:2:col-1) = U(:,:);
    UU(2:2:row,2:2:col) = U(:,:);
    
    VV(1:2:row-1,1:2:col-1) = V(:,:);
    VV(1:2:row-1,2:2:col) = V(:,:);
    VV(2:2:row,1:2:col-1) = V(:,:);
    VV(2:2:row,2:2:col) = V(:,:);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%处理8bit视频时，注释下面三行
%     Y = Y/1023*255;
%     UU = UU/1023*255;
%     VV = VV/1023*255;
    
    R = Y + 1.140 * (VV-128);
    G = Y - 0.395 * (UU-128) - 0.581 *(VV-128);
    B = Y + 2.032 *(UU-128);
    
    for i = 1:row
        for j = 1:col
            if R(i,j) < 0
                R(i,j) = 0;
            end
            if R(i,j) > 255
                R(i,j) = 255;
            end
            if G(i,j) < 0
                G(i,j) = 0;
            end
            if G(i,j) > 255
                G(i,j) = 255;
            end
            if B(i,j) < 0
                B(i,j) = 0;
            end
            if B(i,j) > 255
                B(i,j) = 255;
            end
        end
    end
    R = R/255;
    G = G/255;
    B = B/255;

%     for j = 1:300
%         if data(frame,j).x && data(frame,j).y
%             min_list = [size_block ,data(frame,j).x-1 ,data(frame,j).y-1 ,row-data(frame,j).x-1 ,col-data(frame,j).y-1];
%             [size_temp,size_num] = min(min_list);
%             R(data(frame,j).x-size_temp:data(frame,j).x+size_temp ,data(frame,j).y-size_temp:data(frame,j).y+size_temp) = 0;
%             G(data(frame,j).x-size_temp:data(frame,j).x+size_temp ,data(frame,j).y-size_temp:data(frame,j).y+size_temp) = 0;
%             B(data(frame,j).x-size_temp:data(frame,j).x+size_temp ,data(frame,j).y-size_temp:data(frame,j).y+size_temp) = 0;
%         end
%     end

    film(:,:,1) = R(:,:)';
    film(:,:,2) = G(:,:)';
    film(:,:,3) = B(:,:)';
    film = im2double(film);
%     for j=1:3
%         if data(frame,j).x ~= 0
%             text(data(frame,j).x,data(frame,j).y,'*','FontSize',20);
%         end
%     end
%     figure, imshow(film);
    imwrite(film,['frame',num2str(frame),'.jpg']);
%     film_resize = imresize(film,[1080 1980],'bilinear');
%     video(frame) = im2frame(film_resize);
%     writeVideo(writeObj,film);
%     video(frame) = im2frame(film);
end
% scrsz = get(0,'ScreenSize');
% set(gcf,'Position',scrsz);
% close(writeObj);
% movie(video,1,30)
disp('Program Finished');
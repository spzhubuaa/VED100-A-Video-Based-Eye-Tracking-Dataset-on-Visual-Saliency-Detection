%以日为单位提取数据

close all;
clear

folder_name = 'D:\Exp\data\backup\3.28';
file_name = dir(folder_name);
folder_count = 2;

while 1
    folder_count = folder_count + 1;
    disp(folder_count-2);
    video_file = dir([folder_name,'\',file_name(folder_count).name,'\video\*.txt']);
    tracker_file = dir([folder_name,'\',file_name(folder_count).name,'\tracker\*.txt']);
    try
        video_file(1).name;
    catch
        break
    end

    parfor count = 1:26
        video_path = [video_file(count).folder,'\',video_file(count).name];
        tracker_path = [tracker_file(count).folder,'\',tracker_file(count).name];
        
        file_video = fopen(video_path,'r');
        video_name = textscan(fgetl(file_video),'video name: %s\n');
        video_index = textscan(fgetl(file_video),'video index: %d\n');
        window_xmin = textscan(fgetl(file_video),'window xmin: %d\n');
        window_ymin = textscan(fgetl(file_video),'window ymin: %d\n');
        i = 1;
        frame_begin = zeros(1,750);
        frame_end = zeros(1,750);
        while 1
            [date_temp] = textscan(file_video,'frame %d begin: %f-%f-%f %f:%f:%f\n');
            try
                frame_begin(i) = datenum(date_temp{1,2},date_temp{1,3},date_temp{1,4},date_temp{1,5},date_temp{1,6},date_temp{1,7});
            catch
                break
            end
            [date_temp] = textscan(file_video,'frame %d end: %f-%f-%f %f:%f:%f\n');
            frame_end(i) = datenum(date_temp{1,2},date_temp{1,3},date_temp{1,4},date_temp{1,5},date_temp{1,6},date_temp{1,7});
            
            i=i+1;
        end
        
        frame_count = i;
        
        file_eye = fopen(tracker_path,'r');
        
        j = 1;
        i = 1;
        eye_data = repmat(struct('time',0.0,'x',0.0,'y',0.0,'frame',0),[1,3000]);
        while ~feof(file_eye)
            try
                eye_json = fgetl(file_eye);
                [eye_json_data] = loadjson(eye_json);
                [date_temp] = textscan(eye_json_data.timestamp,'%f-%f-%f %f:%f:%f');
            catch
                break;
            end
            eye_data(j).time = datenum(date_temp{1,1},date_temp{1,2},date_temp{1,3},date_temp{1,4},date_temp{1,5},date_temp{1,6});
            eye_data(j).x = eye_json_data.rawx;%%%%%%%%%%%%%数据分为raw和avg
            eye_data(j).y = eye_json_data.rawy;
            while i <= frame_count
                if eye_data(j).time<= frame_begin(1)
                    eye_data(j).frame = -1;
                    break
                elseif ( eye_data(j).time > frame_begin(i) && eye_data(j).time <= frame_end(i) )
                    eye_data(j).frame = i;
                    break
                elseif (eye_data(j).time <= frame_begin(i) && eye_data(j).time > frame_end(i-1))
                    eye_data(j).frame = -1;
                    break
                else
                    i = i+1;
                end
            end
            j=j+1;
        end
        fclose(file_video);
        fclose(file_eye);
        
        save_name = [char(video_name{1,1}),'_',int2str(count),'.txt'];
        fid = fopen(save_name,'at');
        i = 1;
        while 1
            try
                if (eye_data(i).x > 3960 || eye_data(i).y > 2160)
                    eye_data(i).frame = -2;
                end
                if (eye_data(i).x <= 0 || eye_data(i).y <= 0)
                    eye_data(i).frame = -2;
                end
                if (eye_data(i).frame) > 0
                    fprintf(fid,'%g ',eye_data(i).frame);
                    fprintf(fid,'%g ',eye_data(i).x);
                    fprintf(fid,'%g\n',eye_data(i).y);
                    %     fprintf(fid,'%s\n',eye_data{1,i}.timestamp);
                end
                i=i+1;
            catch
                break
            end
        end
        fclose(fid);
        
        %     choose_ = input('continue or not?  1/0');
        %     if choose_ == 0
        %         break;
        %     end
    end
end

disp('Program Finished!');

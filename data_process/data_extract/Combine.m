%合并每天生成的数据

close all
clear

folder_name = 'D:\Exp\data\backup';
datamode = 'Avg';
file_name = dir(folder_name);
name_temp = cell(26,10);

for folder_count = 3:20
    try
    txt_file = dir([folder_name,'\',file_name(folder_count).name,'\',datamode,'\*.txt']);
    catch
        break;
    end
    for j = 1:26
        fid = fopen([folder_name,'\',file_name(folder_count).name,'\',datamode,'\',txt_file(j).name]);
        data(folder_count-2,j).data = importdata([folder_name,'\',file_name(folder_count).name,'\',datamode,'\',txt_file(j).name]);
        fclose(fid);
        rename = regexp(txt_file(j).name,'_','split');
        txt_file(j).name = [rename{1,1},'.txt'];
    end
end

for j = 1:26
    fid = fopen(['D:\Exp\data\','\',datamode,'\',txt_file(j).name],'at');
    for i = 1:folder_count-3
        x = 1;
        while 1
            try
                fprintf(fid,'%g ',data(i,j).data(x,1));
                fprintf(fid,'%g ',data(i,j).data(x,2));
                fprintf(fid,'%g\n',data(i,j).data(x,3));
                x = x+1;
            catch
                break;
            end
        end
    end
    fclose(fid);
end
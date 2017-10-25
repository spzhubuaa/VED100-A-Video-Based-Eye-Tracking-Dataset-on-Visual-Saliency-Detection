import functools
import os
import re

max_buffer_size = 10

screen_width = 1280
screen_height = 720

data_path = '/Users/apple/Desktop/data'
backup_data_path = './example'

video_root_dir = '''/Volumes/zhangxiwen/HEVCtupian'''

video_list = []
pattern_class_dir = re.compile(r'''.*Class(\w)-.+''')
pattern_video_name = re.compile(r'''(\w+)_(\d+)x(\d+)_(\d+)(_(\d+)bit|).*.yuv''')
for fpathe, dirs, fs in os.walk(video_root_dir):
    class_result = pattern_class_dir.search(fpathe)
    if class_result:
        class_name = class_result.group(1)
        for a_filename in fs:
            result = pattern_video_name.search(a_filename)

            if result:
                w = int(result.group(2))
                h = int(result.group(3))
                fps = int(result.group(4))
                filepath = os.path.join(fpathe, a_filename)
                file_size = os.path.getsize(filepath)
                total_frames = file_size * 2 / 3 / w / h / 10 * 10
                total_time = total_frames / fps

                if result.group(5) == '':
                    bit_depth = 8
                else:
                    bit_depth = int(result.group(5)[1:3])
                    total_time /= 2
                    total_frames /= 2

                video_info = {
                    'name': result.group(1),
                    'filename': a_filename,
                    'filepath': filepath,
                    'width': w,
                    'height': h,
                    'fps': fps,
                    'bit_depth': int(bit_depth),
                    'class': class_name,
                    'total_frames': total_frames,
                    'total_time': total_time,
                    'shape': (h, w)
                }
                video_list.append(video_info)

video_list.sort(key=lambda x: x['class'], reverse=True)










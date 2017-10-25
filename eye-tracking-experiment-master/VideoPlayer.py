import numpy as np
from datetime import datetime
import config
from config import screen_height as H
from config import screen_width as W
from collections import deque
import os
from PIL import Image
from numpy import uint8
from numpy import fromfile
from numpy import zeros, repeat
import cv2
import logging


class VideoPlayer():
    def __init__(self, userID = '0000'):
        self.frames = deque()
        self.video_list = config.video_list
        self.video_sum = len(self.video_list)
        self.set_userID(userID)
        self.window_name = 'show'
        self.img_prepare = np.zeros((H, W))
        cv2.putText(self.img_prepare,
                    'Nice done!  Please wait for a moment . . .',
                    (400, 800),
                    cv2.FONT_HERSHEY_PLAIN,
                    2,
                    100,
                    2)
        self.img_attention = np.ones((H, W)) * 100
        cv2.putText(self.img_attention,
                    'Please pay attention to your eye position',
                    (400, 800),
                    cv2.FONT_HERSHEY_PLAIN,
                    3,
                    0,
                    3)

    def set_userID(self, userID):
        self.user_id = userID
        logging.info('set user ID to: ' + userID)
        self._update_log_path()

    def _update_log_path(self):
        self.log_path = os.path.join(config.data_path, self.user_id, 'video')
        logging.info('update log path to: ' + self.log_path)
        self.backup_log_path = os.path.join(config.backup_data_path, self.user_id, 'video_backup')
        logging.info('update backup log path to: ' + self.backup_log_path)
        if not os.path.isdir(self.log_path):
            os.makedirs(self.log_path)
        if not os.path.isdir(self.backup_log_path):
            os.makedirs(self.backup_log_path)



    def show_prepare(self, wait_ms=0):
        cv2.imshow(self.window_name, self.img_prepare)
        cv2.moveWindow(self.window_name, 0, 0)
        cv2.waitKey(wait_ms)
        pass

    def show_attention(self):
        cv2.imshow(self.window_name, self.img_attention)
        cv2.moveWindow(self.window_name, 0, 0)
        cv2.waitKey(0)

    def play_i(self, i):
        logging.info('play video %d ' % i)
        self.show_prepare(1)
        logf_filename = os.path.join(self.log_path, 'video_{}_{}.txt'.format(i, datetime.now().strftime('%m-%d-%H-%M-%S')))
        with open(logf_filename, 'w') as logf:
            logging.info('play detail is written to ' + logf_filename)
            a_video_info = self.video_list[i]
            logf.write('video name: ' + a_video_info['name'] + '\n')
            logf.write('video index: {}'.format(i) + '\n')
            pl = YUVideo(a_video_info['filepath'], a_video_info['shape'], bit_depth=a_video_info['bit_depth'])
            pl.open()
            frames = []
            logging.info('start to load the video')
            for frame in pl.get_frames():
                frame = cv2.resize(frame, (W, H))
                frames.append(frame)
            logging.info('the video has been loaded')

            wait_time = 900 / a_video_info['fps']
            # window_x = (W - a_video_info['width']) / 2
            # window_y = (H - a_video_info['height']) / 2
            window_x = 0
            window_y = 0
            logf.write('window xmin: {}'.format(window_x) + '\n')
            logf.write('window ymin: {}'.format(window_y) + '\n')
            # print wait_time
            for i, frame in enumerate(frames):
                # frame = cv2.resize(frame, (1600, 900))
                logf.write('frame {} begin: '.format(i) + datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f') + '\n')
                cv2.imshow(self.window_name, frame)
                cv2.moveWindow(self.window_name, window_x, window_y)
                cv2.waitKey(15)
                logf.write('frame {} end: '.format(i) + datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f') + '\n')


    def playall(self):
        for i in range(self.video_sum):
            self.play_i(i)

    def stop(self):
        cv2.destroyAllWindows()

    def load_yuv(self, file_path, width, height, frame_rate, bit_depth=8):
        pass


class YUVideo(object):

    def __init__(self, videoFile, videoSize, bit_depth=8):
        self.vf = videoFile
        self.bit_depth = bit_depth
        self.width = videoSize[0]
        self.height = videoSize[1]
        self.blkSize = self.width * self.height * 3 / 2
        if bit_depth > 8:
            self.blkSize *= 2
        # print videoFile
        # print os.path.isfile(videoFile)
        fileSize = os.path.getsize(videoFile)
        self.frmCount = fileSize / self.blkSize

    def open(self):
        self.fp = open(self.vf, 'rb')

    def close(self):
        self.fp.close()

    def getYuvFrm(self, frmnum):
        halfWidth = self.width // 2
        halfHeight = self.height // 2
        self.fp.seek(self.blkSize * frmnum, 0)

        if self.bit_depth > 8:
            y = fromfile(self.fp, np.uint16, self.width * self.height).reshape(self.width, self.height)
            u = fromfile(self.fp, np.uint16, halfWidth * halfHeight).reshape(halfWidth, halfHeight)
            v = fromfile(self.fp, np.uint16, halfWidth * halfHeight).reshape(halfWidth, halfHeight)
            to8bit = lambda x: (x / 4).astype(np.uint8)
            y = to8bit(y)
            u = to8bit(u)
            v = to8bit(v)
        else:
            y = fromfile(self.fp, uint8, self.width * self.height).reshape(self.width, self.height)
            u = fromfile(self.fp, uint8, halfWidth * halfHeight).reshape(halfWidth, halfHeight)
            v = fromfile(self.fp, uint8, halfWidth * halfHeight).reshape(halfWidth, halfHeight)
        return (y, u, v)

    def yuv2rgb(self, y, u, v):
        u = repeat(u, 2, 0)
        u = repeat(u, 2, 1)
        v = repeat(v, 2, 0)
        v = repeat(v, 2, 1)
        yuv = np.array((y, u, v)).transpose(1, 2, 0)
        rgb = cv2.cvtColor(yuv, cv2.COLOR_YCrCb2BGR)
        return rgb

    def getFrm(self, frmnum):
        if frmnum >= self.frmCount:
            frmnum = self.frmCount -1
            print 'the last frame'
        if frmnum < 0:
            frmnum = 0
            print 'the first frame'

        (y, u, v) = self.getYuvFrm(frmnum)
        rgb = self.yuv2rgb(y, u, v)

        return rgb

    def get_frames(self):
        for i in range(self.frmCount):
            (y, u, v) = self.getYuvFrm(i)
            rgb = self.yuv2rgb(y, v, u)
            yield rgb

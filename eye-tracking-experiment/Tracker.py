import pytribe
import os
import config
from datetime import datetime
import threading
import logging
import time
import json
from enum import Enum
class Status(Enum):
    uninit = 0
    ready = 1
    listening = 2
    closing = 3
    starting = 4


class Tracker(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.status = Status.uninit
        self.log_path = os.path.join(config.data_path, 'tracker')
        if not os.path.isdir(self.log_path):
            os.makedirs(self.log_path)
        self.eyetribe_log_filename = os.path.join(self.log_path, 'EyeTribe' + datetime.now().strftime('_%m-%d_%H-%M-%S'))
        self.tracker = pytribe.EyeTribe(logfilename=self.eyetribe_log_filename)

        self.is_waiting = True
        self.thread_stop = False
        self.status = ''
        self.set_userID('0000')
        self.video_index = 0
        self.status = Status.ready
        self.frame_sum = 0
        self.frame_failed = 0
        self.tracker_ok = True
        pass

    def set_userID(self, userID):
        self.user_id = userID
        logging.info('set user ID to: ' + userID)
        self._update_log_path()

    def start_track_video_i(self, index):
        self.video_index = index
        logging.info('start to track video %d' % index)
        cnt = 0
        while self.status != Status.ready:
            time.sleep(0.01)
            cnt += 1
            if cnt % 10 == 0:
                logging.info('waiting Tracker to be ready for %d seconds' % (float(cnt)/100))
        self.frame_sum = 0
        self.frame_failed = 0
        self.status = Status.starting

    def stop_current_track(self):
        self.status = Status.closing
        logging.info('stop to track video %d' % self.video_index)
        return self.frame_sum, self.frame_failed

    def _update_log_path(self):
        self.log_path = os.path.join(config.data_path, self.user_id, 'tracker')
        logging.info('update log path to: ' + self.log_path)
        self.backup_log_path = os.path.join(config.backup_data_path, self.user_id, 'tracker_backup')
        logging.info('update backup log path to: ' + self.backup_log_path)
        if not os.path.isdir(self.log_path):
            os.makedirs(self.log_path)
        if not os.path.isdir(self.backup_log_path):
            os.makedirs(self.backup_log_path)

    def run(self):
        logging.info('Tracker start running...')
        logf_filename = 'Error'
        while not self.thread_stop:
            if self.status == Status.ready or self.status == Status.uninit:
                pass
            elif self.status == Status.listening:
                frame_info = self.tracker._tracker.get_frame()
                state = frame_info['state']
                if self.is_tracker_fail(state) or self.is_tracker_lost(state):
                    self.tracker_ok = False
                    self.frame_failed += 1
                else:
                    self.tracker_ok = True
                self.frame_sum += 1
                json.dump(frame_info, f)
            elif self.status == Status.closing:
                f.close()
                logging.info('frame sum: {}, failed sum: {}'.format(self.frame_sum, self.frame_failed))
                logging.info('close file: ' + logf_filename)
                self.status = Status.ready
            elif self.status == Status.starting:
                logf_filename = os.path.join(self.log_path,
                                             'video_{}_{}.txt'.format(self.video_index,
                                                                      datetime.now().strftime('%m-%d-%H-%M-%S')))
                f = open(logf_filename, 'a')
                logging.info('open file: ' + logf_filename)
                self.status = Status.listening
            time.sleep(0.01)

    def waiting(self):
        return self.is_waiting

    def stop(self):
        logging.info("thread stop")
        self.thread_stop = True

    def is_tracker_fail(self, state):
        STATE_TRACKING_GAZE = 0x1
        STATE_TRACKING_EYES = 0x2
        STATE_TRACKING_PRESENCE = 0x4
        STATE_TRACKING_FAIL = 0x8
        STATE_TRACKING_LOST = 0x10
        return state & STATE_TRACKING_FAIL > 0

    def is_tracker_lost(self, state):
        STATE_TRACKING_LOST = 0x10
        return state & STATE_TRACKING_LOST > 0

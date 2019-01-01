from VideoPlayer import VideoPlayer
from Tracker import Tracker
import logging
from datetime import datetime
import time

class Experiment():
    def __init__(self):
        logging.info('Init Experiment...')
        self.player = VideoPlayer()
        self.tracker = Tracker()
        self.tracker.start()
        pass

    def start_from_i(self, index, name, is_male, age):
        get_gender = lambda b: 'male' if b else 'female'
        userID = str(name) + get_gender(is_male) + str(age) + datetime.now().strftime('_%m%d%H%M%S')
        self.player.set_userID(userID)
        self.tracker.set_userID(userID)
        for i in range(index, self.player.video_sum):
            self.tracker.start_track_video_i(i)
            time.sleep(0.5)
            self.player.play_i(i)
            frame_sum, frame_failed = self.tracker.stop_current_track()
            if float(frame_failed) / frame_sum > 0.1:
                self.player.show_attention()
        self.player.stop()

    def start(self, name, is_male=True, age=22):
        self.start_from_i(0, name, is_male, age)

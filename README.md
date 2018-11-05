# VED100：A Video-Based Eye-Tracking Dataset on Visual Saliency Detection

</br>
This is the code and dataset in our paper
</br>
This reponsitory consists mainly the following several sections.

## Section.1 Data
</br>
This folder contains two different version of our dataset.

1. Raw is the original visual fixation data
2. Avg is the averaged visual fixation data

Note: in our paper, all evaluations are done with Avg data
## Section.2 Data_Process
</br>
This folder contains the necessary code for users to extract data and visualize them.

1. data_extract contains code to extract data from .txt files in Section.1 which are written in Matlab.
2. Heatmap contains code to visualize fixation data(ground truth) in videos which is written with OpenCV in visual studio

## Section.3 Eye-Tracking-Experiment-Master
</br>
This folder contains the code for our experiment in order to collect visual fixation data via eyetracker. The codes are witten with python and the eyetracker is EyeTribe.

## Complementary Information 
</br>
- We have put the video sequence in 


  [Google Drive](https://drive.google.com/drive/folders/0B4Gid1KDSHisZVR3dUFvejdKOXc?usp=sharing/ "Google Drive")


You can download all videos in this website in the folder of "avi".
</br>
- If you need all the experiment original data, the folder "data_backup" contains all the data according to the experiment date. The file is the original text file created by eyetracker api.
</br>
- Also, we have put our visualized result in the folder "heatmap_video", you can find the input video frames and output result video frames there.
</br>

## If you have any other questions, please feel free to send a email to us to ask. My email is <fan.zhang@berkeley.edu>





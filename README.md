# ORB-SLAM3

## Development Environment

- OS : Ubuntu 18.04
- Gcc : 7.5.0
- OpenCV : 4.4.0
- Eigen : 3.3.4
- OpenSSL : 1.1.1
- ROS : Melodic


## Run Dockerfile
* 본인 Local에 git clone 한 뒤, 
```bash
  docker build --no-cache --progress=tty --force-rm -f base.dockerfile -t orb:slam3 . # 예시, 뒤의 image 이름은 수정 필요
```

* Dataset 저장을 위한 docker volume 활용
    1. docker create volume [이름]
    2. HOST OS가 windows라면
        1. \\wsl$\docker-desktop-data\version-pack-data\community\docker\volumes 경로의 각 volume에 데이터 저장
    3. HOST OS가 Linux라면
        1. /var/lib/docker/volumes 경로의 각 volume에 데이터 저장
* 실행 가능한 docker container run
    
    ```bash
    docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix \ # visualization 관련
    -v dataset:/slam/ORB_SLAM3/DataSets/EuRoC/MH01 \ # EuRoC 데이터 볼륨
    -v KITTI:/slam/ORB_SLAM3/DataSets/KITTI \    # KITTI 데이터 볼륨
    -e DISPLAY=unix$DISPLAY \     # HOST에서 DISPLAY할 수 있도록 설정
    --net=host \         # host 연결 관련
    --name visual orb3:test    # container 이름, image 이름
    ```
    
    복사용 : docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -v dataset:/slam/ORB_SLAM3/DataSets/EuRoC/MH01 -v KITTI:/slam/ORB_SLAM3/DataSets/KITTI -e DISPLAY=unix$DISPLAY --net=host --name visual orb3:test

    
* docker attach [컨테이터 이름]
    - 실행 환경 : MobaXterm
    - 추가 설치 프로그램 : XLaunch


* 기존의 build.sh파일을 build_thirdparty.sh, build.sh 파일 두개로 분리하였습니다. 
* base.dockerfile 실행시 build_thidrparty.sh만 실행되어 빌드되고(DBow2, OpenSSL, g2o, Sophus, vocabulary 압축 해제),
* 이후 build.sh을 실행하면 전체 build가 진행됩니다.

```bash
./build.sh
```
### ORB_SLAM 3 실행 방법

- 각 데이터 셋 마다 요구하는 매개변수 값이 상이함
    
    KITTI : [mono_kitti] [path_to_vocabulary] [path_to_settings] [path_to_sequence]
    
    ex1) ./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/KITTI00-02.yaml ../DataSets/KITTI/00/
    
    EuRoc : [mono_inertial_euroc] [path_to_vocabulary] [path_to_settings] [path_to_sequence_folder_1] [path_to_times_file_1]
    
    ex2) ./Monocular/mono_euroc ../Vocabulary/ORBvoc.txt ./Monocular/EuRoC.yaml ../DataSets/EuRoC/MH01/ ./Monocular/EuRoC_TimeStamps/MH01.txt

### Extra. Map 저장, 저장된 Map 파일 Pangolin으로 실행하는 방법
* 영상이 끝나면 ./kitti.ply 저장 (파일명 변경가능)
* 해당 파일을 Pangolin으로 실행하는 명령어

```
./plotPointCloud file_name
# example : ./plotPointCloud kitti.ply
```


### 이 Github는 https://github.com/UZ-SLAMLab/ORB_SLAM3의 내용을 기반으로 작성하였습니다.
-----------------------------------

### V1.0, December 22th, 2021
**Authors:** Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, [José M. M. Montiel](http://webdiis.unizar.es/~josemari/), [Juan D. Tardos](http://webdiis.unizar.es/~jdtardos/).

The [Changelog](https://github.com/UZ-SLAMLab/ORB_SLAM3/blob/master/Changelog.md) describes the features of each version.

ORB-SLAM3 is the first real-time SLAM library able to perform **Visual, Visual-Inertial and Multi-Map SLAM** with **monocular, stereo and RGB-D** cameras, using **pin-hole and fisheye** lens models. In all sensor configurations, ORB-SLAM3 is as robust as the best systems available in the literature, and significantly more accurate. 

We provide examples to run ORB-SLAM3 in the [EuRoC dataset](http://projects.asl.ethz.ch/datasets/doku.php?id=kmavvisualinertialdatasets) using stereo or monocular, with or without IMU, and in the [TUM-VI dataset](https://vision.in.tum.de/data/datasets/visual-inertial-dataset) using fisheye stereo or monocular, with or without IMU. Videos of some example executions can be found at [ORB-SLAM3 channel](https://www.youtube.com/channel/UCXVt-kXG6T95Z4tVaYlU80Q).

This software is based on [ORB-SLAM2](https://github.com/raulmur/ORB_SLAM2) developed by [Raul Mur-Artal](http://webdiis.unizar.es/~raulmur/), [Juan D. Tardos](http://webdiis.unizar.es/~jdtardos/), [J. M. M. Montiel](http://webdiis.unizar.es/~josemari/) and [Dorian Galvez-Lopez](http://doriangalvez.com/) ([DBoW2](https://github.com/dorian3d/DBoW2)).

<a href="https://youtu.be/HyLNq-98LRo" target="_blank"><img src="https://img.youtube.com/vi/HyLNq-98LRo/0.jpg" 
alt="ORB-SLAM3" width="240" height="180" border="10" /></a>

### Related Publications:

[ORB-SLAM3] Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M. M. Montiel and Juan D. Tardós, **ORB-SLAM3: An Accurate Open-Source Library for Visual, Visual-Inertial and Multi-Map SLAM**, *IEEE Transactions on Robotics 37(6):1874-1890, Dec. 2021*. **[PDF](https://arxiv.org/abs/2007.11898)**.

[IMU-Initialization] Carlos Campos, J. M. M. Montiel and Juan D. Tardós, **Inertial-Only Optimization for Visual-Inertial Initialization**, *ICRA 2020*. **[PDF](https://arxiv.org/pdf/2003.05766.pdf)**

[ORBSLAM-Atlas] Richard Elvira, J. M. M. Montiel and Juan D. Tardós, **ORBSLAM-Atlas: a robust and accurate multi-map system**, *IROS 2019*. **[PDF](https://arxiv.org/pdf/1908.11585.pdf)**.

[ORBSLAM-VI] Raúl Mur-Artal, and Juan D. Tardós, **Visual-inertial monocular SLAM with map reuse**, IEEE Robotics and Automation Letters, vol. 2 no. 2, pp. 796-803, 2017. **[PDF](https://arxiv.org/pdf/1610.05949.pdf)**. 

[Stereo and RGB-D] Raúl Mur-Artal and Juan D. Tardós. **ORB-SLAM2: an Open-Source SLAM System for Monocular, Stereo and RGB-D Cameras**. *IEEE Transactions on Robotics,* vol. 33, no. 5, pp. 1255-1262, 2017. **[PDF](https://arxiv.org/pdf/1610.06475.pdf)**.

[Monocular] Raúl Mur-Artal, José M. M. Montiel and Juan D. Tardós. **ORB-SLAM: A Versatile and Accurate Monocular SLAM System**. *IEEE Transactions on Robotics,* vol. 31, no. 5, pp. 1147-1163, 2015. (**2015 IEEE Transactions on Robotics Best Paper Award**). **[PDF](https://arxiv.org/pdf/1502.00956.pdf)**.

[DBoW2 Place Recognition] Dorian Gálvez-López and Juan D. Tardós. **Bags of Binary Words for Fast Place Recognition in Image Sequences**. *IEEE Transactions on Robotics,* vol. 28, no. 5, pp. 1188-1197, 2012. **[PDF](http://doriangalvez.com/php/dl.php?dlp=GalvezTRO12.pdf)**

# 1. License

ORB-SLAM3 is released under [GPLv3 license](https://github.com/UZ-SLAMLab/ORB_SLAM3/LICENSE). For a list of all code/library dependencies (and associated licenses), please see [Dependencies.md](https://github.com/UZ-SLAMLab/ORB_SLAM3/blob/master/Dependencies.md).

For a closed-source version of ORB-SLAM3 for commercial purposes, please contact the authors: orbslam (at) unizar (dot) es.

If you use ORB-SLAM3 in an academic work, please cite:
  
    @article{ORBSLAM3_TRO,
      title={{ORB-SLAM3}: An Accurate Open-Source Library for Visual, Visual-Inertial 
               and Multi-Map {SLAM}},
      author={Campos, Carlos AND Elvira, Richard AND G\´omez, Juan J. AND Montiel, 
              Jos\'e M. M. AND Tard\'os, Juan D.},
      journal={IEEE Transactions on Robotics}, 
      volume={37},
      number={6},
      pages={1874-1890},
      year={2021}
     }

# 2. Prerequisites
We have tested the library in **Ubuntu 16.04** and **18.04**, but it should be easy to compile in other platforms. A powerful computer (e.g. i7) will ensure real-time performance and provide more stable and accurate results.

## C++11 or C++0x Compiler
We use the new thread and chrono functionalities of C++11.

## Pangolin
We use [Pangolin](https://github.com/stevenlovegrove/Pangolin) for visualization and user interface. Dowload and install instructions can be found at: https://github.com/stevenlovegrove/Pangolin.

## OpenCV
We use [OpenCV](http://opencv.org) to manipulate images and features. Dowload and install instructions can be found at: http://opencv.org. **Required at leat 3.0. Tested with OpenCV 3.2.0 and 4.4.0**.

## Eigen3
Required by g2o (see below). Download and install instructions can be found at: http://eigen.tuxfamily.org. **Required at least 3.1.0**.

## DBoW2 and g2o (Included in Thirdparty folder)
We use modified versions of the [DBoW2](https://github.com/dorian3d/DBoW2) library to perform place recognition and [g2o](https://github.com/RainerKuemmerle/g2o) library to perform non-linear optimizations. Both modified libraries (which are BSD) are included in the *Thirdparty* folder.

## Python
Required to calculate the alignment of the trajectory with the ground truth. **Required Numpy module**.

* (win) http://www.python.org/downloads/windows
* (deb) `sudo apt install libpython2.7-dev`
* (mac) preinstalled with osx


# 3. Building ORB-SLAM3 library and examples

Clone the repository:
```
git clone https://github.com/UZ-SLAMLab/ORB_SLAM3.git ORB_SLAM3
```

We provide a script `build.sh` to build the *Thirdparty* libraries and *ORB-SLAM3*. Please make sure you have installed all required dependencies (see section 2). Execute:
```
cd ORB_SLAM3
chmod +x build.sh
./build.sh
```

This will create **libORB_SLAM3.so**  at *lib* folder and the executables in *Examples* folder.

# 4. Running ORB-SLAM3 with your camera

Directory `Examples` contains several demo programs and calibration files to run ORB-SLAM3 in all sensor configurations with Intel Realsense cameras T265 and D435i. The steps needed to use your own camera are: 

1. Calibrate your camera following `Calibration_Tutorial.pdf` and write your calibration file `your_camera.yaml`

2. Modify one of the provided demos to suit your specific camera model, and build it

3. Connect the camera to your computer using USB3 or the appropriate interface

4. Run ORB-SLAM3. For example, for our D435i camera, we would execute:

```
./Examples/Stereo-Inertial/stereo_inertial_realsense_D435i Vocabulary/ORBvoc.txt ./Examples/Stereo-Inertial/RealSense_D435i.yaml
```


## Evaluation
EuRoC provides ground truth for each sequence in the IMU body reference. As pure visual executions report trajectories centered in the left camera, we provide in the "evaluation" folder the transformation of the ground truth to the left camera reference. Visual-inertial trajectories use the ground truth from the dataset.

Execute the following script to process sequences and compute the RMS ATE:
```
./euroc_eval_examples
```


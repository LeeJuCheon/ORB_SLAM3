FROM orbslam:origin

ARG DEBIAN_FRONTEND=noninteractive


RUN cd slam && cd ORB_SLAM3 && chmod +x build.sh && \
    ./build.sh


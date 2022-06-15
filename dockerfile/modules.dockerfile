FROM orbslam:origin

ARG BRANCH=main
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN useradd -m user && yes password | passwd user

RUN cd slam && cd ORB_SLAM3 && \
git remote update && \
git fetch --all && \
git checkout ${BRANCH} && \
git pull && \
git branch 
# mkdir build_debug && cd build_debug && \
# cmake -DCMAKE_BUILD_TYPE=Debug -GNinja .. && ninja


RUN cd slam && cd ORB_SLAM3 && chmod +x build.sh && \
    ./build.sh


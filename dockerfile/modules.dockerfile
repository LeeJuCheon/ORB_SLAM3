FROM orb3:base

ARG BRANCH=development
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN useradd -m user && yes password | passwd user

RUN echo "== Start Release build == " && \
cd slam && cd ORB_SLAM3 && \
git remote update && \
git fetch --all && \
git checkout ${BRANCH} && \
git pull && \
git branch && \
git branch && \
mkdir build && \
cd build && \
cmake .. -DCMAKE_BUILD_TYPE=Release && \
make -j2


RUN echo "== Start Debug build == " && \
cd slam && cd ORB_SLAM3 && \
git remote update && \
git fetch --all && \
git checkout ${BRANCH} && \
git pull && \
git branch && \
cd build && \
cmake .. -DCMAKE_BUILD_TYPE=Debug && \
make -j2



# FROM orbslam:origin

# ARG BRANCH=main
# ARG DEBIAN_FRONTEND=noninteractive

# RUN apt-get update -y && apt-get upgrade -y

# RUN useradd -m user && yes password | passwd user

# RUN cd slam && cd ORB_SLAM3 && \
# git remote update && \
# git fetch --all && \
# git checkout ${BRANCH} && \
# git pull && \
# git branch 
# # mkdir build_debug && cd build_debug && \
# # cmake -DCMAKE_BUILD_TYPE=Debug -GNinja .. && ninja


# RUN cd slam && cd ORB_SLAM3 && chmod +x build.sh && \
#     ./build.sh

FROM orbslam:origin

ARG BRANCH=development
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN useradd -m user && yes password | passwd user

RUN echo "== Start Debug build == " && \
cd slam && cd ORB_SLAM3 && \
git remote update && \
git fetch --all && \
git checkout ${BRANCH} && \
git pull && \
git branch && \
mkdir build && \
cd build && \
cmake .. -DCMAKE_BUILD_TYPE=Debug && \
make -j2


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
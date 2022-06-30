#include <pangolin/pangolin.h>
#include "Eigen/Core"
#include <Eigen/Geometry>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

int points_number_ = 0;
Eigen::Matrix<float, 3, 1> * getPointsDataFromFile(std::string file_name);
void drawPointsCloud(Eigen::Matrix<float, 3, 1> *points_data);
void readFile(std::string file_name);

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Please check usage ==> ./plotPointCloud file_name" << std::endl;
        exit(1);
    }
    std::string file_name = argv[1];

    Eigen::Matrix<float, 3, 1> * points_data = getPointsDataFromFile(file_name);
    drawPointsCloud(points_data);
    return 0;
}


Eigen::Matrix<float, 3, 1> * getPointsDataFromFile(std::string file_name) {
    int points_number = 0;
    std::ifstream readFile;
    readFile.open(file_name);
    if (!readFile.is_open()) {
        std::cerr << file_name << "can not be opened!" << std::endl;
        exit(0);
    }

    std::string word;
    getline(readFile, word);
    if (word.compare("ply") == 0) {
        while(!readFile.eof()) {
            readFile >> word;
            if (word.compare("element") == 0) {
                readFile >> word;
                if (word.compare("vertex") == 0) {
                    readFile >> word;
                    points_number = stoi(word);
                }
            }
            if (word.compare("end_header") == 0) {
                break;
            }
        }
    }
    const size_t points_size = points_number;
    int cnt = 0;
    Eigen::Matrix<float, 3, 1> *points_data = new Eigen::Matrix<float, 3, 1>[points_size * 3];
    while(!readFile.eof() && cnt != points_number) {
        float x, y, z;
        readFile >> x >> y >> z;
        // std::cout << cnt << " x " << x << " y " << y << " z " << z << std::endl;
        points_data[cnt][0] = x;
        points_data[cnt][1] = y;
        points_data[cnt][2] = z;
        cnt++;
    }
    readFile.close();
    if (points_number == cnt) {
        std::cout << "finish read, the row count is " << cnt << std::endl;
        points_number_ = points_number;
        return points_data;
    }

    return nullptr;
}

void drawPointsCloud(Eigen::Matrix<float, 3, 1> *points_data) {
    if (points_number_ == 0) {
        std::cerr << "The point size is zero. Please check the file contents or format." << std::endl;
        exit(1);
    }
    const size_t points_size = points_number_;
    pangolin::CreateWindowAndBind("Point Cloud Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    // glColorPointer(4, GL_FLOAT, 0, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
        pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0));

    pangolin::View &d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
                                .SetHandler(new pangolin::Handler3D(s_cam));

    pangolin::GlBuffer glxyzBuffer;
    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
        glColor3f(0.0, 0.0, 0.0);
        glxyzBuffer.Reinitialise(pangolin::GlArrayBuffer, points_size, GL_FLOAT, 3, GL_STATIC_DRAW);
        glxyzBuffer.Upload(points_data, 3*sizeof(float)*points_size);
    
        glPointSize(1);
        glxyzBuffer.Bind();
        glVertexPointer(glxyzBuffer.count_per_element, glxyzBuffer.datatype, 0, 0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, points_size);
        glDisableClientState(GL_VERTEX_ARRAY);
        glxyzBuffer.Unbind();

        pangolin::RenderVbo(glxyzBuffer, GL_POINTS);
        pangolin::FinishFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // sleep 5 ms
    }
    
}
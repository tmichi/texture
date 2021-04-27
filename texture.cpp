#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
int init_texture(const std::string texture_file) {
        cv::Mat image = cv::imread(texture_file);
        if (image.empty()){
                return 0;
        }
        const int TEXW = image.size().width;
        const int TEXH = image.size().height;
        std::vector<GLubyte> bits(TEXH * TEXW * 3, 0x00);
        GLuint texName;
        for (int i = 0; i < TEXH; i++) {
                for (int j = 0; j < TEXW; j++) {
                        cv::Vec3b pixel = image.at<cv::Vec3b>(TEXH - 1 - i, j); //上下逆
                        bits[(i * TEXW + j) * 3 + 0] = (GLubyte) pixel[2];
                        bits[(i * TEXW + j) * 3 + 1] = (GLubyte) pixel[1];
                        bits[(i * TEXW + j) * 3 + 2] = (GLubyte) pixel[0];
                }
        }
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXW, TEXH, 0, GL_RGB, GL_UNSIGNED_BYTE, &bits[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        return texName;
}

int main(void) {
        GLFWwindow *window;
        if (!glfwInit()) {
                return -1;
        }
        window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
        if (!window) {
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);
        GLuint texName = init_texture("../texture.png");
        if (texName == 0 ) {
                std::cerr<<"texture not found"<<std::endl;
        }
        glEnable(GL_DEPTH_TEST);

        while (!glfwWindowShouldClose(window)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glBindTexture(GL_TEXTURE_2D, texName);
                glBegin(GL_POLYGON);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(-0.9f, -0.9f);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(-0.9f, 0.9f);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(0.9f, 0.9f);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(0.9f, -0.9f);
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);

                glfwSwapBuffers(window);
                glfwPollEvents();
        }
        glfwTerminate();
        return 0;
}



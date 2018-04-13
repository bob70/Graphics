#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include "Utility.h"
#include "Math/Vector.h"

class Shader: public NonCopyable {
public:
    Shader(GLuint eShaderType, const std::string &strFileData);
    ~Shader() { glDeleteShader(mShader); }
    auto get() const noexcept { return mShader; }
private:
    GLuint mShader;
};

class Program: public NonCopyable {
public:
    Program() = default;
    ~Program() { glDeleteProgram(mProgram); }
    void link(const std::vector<Shader*>& shaderList);
    auto get() const noexcept { return mProgram; }
    void use() {
        glUseProgram(mProgram);
    }
    auto getUniformLoc(const char* name) {
        return glGetUniformLocation(mProgram, name);
    }
private:
    GLuint mProgram;
};

class Texture {
public:
    Texture() { glGenTextures(1, &mTexture); }
    ~Texture() { glDeleteTextures(1, &mTexture); }
private:
    GLuint mTexture;
};

class RenderBuffer {
public:
    RenderBuffer() { glGenRenderbuffers(1, &mRenderBuffer); }
    ~RenderBuffer() { glDeleteRenderbuffers(1, &mRenderBuffer); }
    void setStorage(GLuint fmt, Vec2i size) {
        glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, fmt, size.x, size.y);
    }
    auto get() const noexcept { return mRenderBuffer; }
private:
    GLuint mRenderBuffer;
};

class FrameBuffer {
public:
    FrameBuffer() { glGenFramebuffers(1, &mFrameBuffer); }
    ~FrameBuffer() { glDeleteFramebuffers(1, &mFrameBuffer); }
    auto get() const noexcept { return mFrameBuffer; }
    void use(GLuint target){ glBindFramebuffer(target, mFrameBuffer); }
private:
    GLuint mFrameBuffer;
};

class DataBuffer {
public:
    DataBuffer() { glGenBuffers(1, &mBuffer); }
    ~DataBuffer() { glDeleteBuffers(1, &mBuffer); }
    auto get() const noexcept { return mBuffer; }
    void use(GLuint target){ glBindBuffer(target, mBuffer); }
private:
    GLuint mBuffer;
};

#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

#include <cassert>

OpenGLFrameBuffer::OpenGLFrameBuffer()
    : m_BufferID(0), m_TextureID(0),m_RBO(0), m_Width(1), m_Height(1), m_Multisample(0),
    m_Samples(2)
{
}

OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height, bool multisample)
    : m_BufferID(0), m_TextureID(0), m_RBO(0), m_Width(width), m_Height(height),
    m_Multisample(multisample), m_Samples(2)
{   
    Invalidate();
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
    glDeleteFramebuffers(1, &m_BufferID);
    glDeleteTextures(1, &m_TextureID);
    glDeleteRenderbuffers(1, &m_RBO);
}

uint32_t OpenGLFrameBuffer::GetBufferID()
{
    return m_BufferID;
}

uint32_t OpenGLFrameBuffer::GetTextureID()
{
    return m_TextureID;
}

void OpenGLFrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
    glViewport(0, 0, m_Width, m_Height);
}

void OpenGLFrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::Resize(int32_t width, int32_t height)
{
    m_Width = width;
    m_Height = height;

    Invalidate();
}

void OpenGLFrameBuffer::BlitFrom(const std::shared_ptr<FrameBuffer>& source)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, source->GetBufferID());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_BufferID);
    glBlitFramebuffer(0, 0, source->GetWidth(), source->GetHeight(), 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

uint32_t OpenGLFrameBuffer::GetWidth()
{
    return m_Width;
}

uint32_t OpenGLFrameBuffer::GetHeight()
{
    return m_Height;
}

void OpenGLFrameBuffer::SetSamples(uint8_t samples)
{
    m_Samples = samples;
}

void OpenGLFrameBuffer::Invalidate()
{
    // delete existing buffer
    if (m_BufferID)
    {
        glDeleteFramebuffers(1, &m_BufferID);
        glDeleteTextures(1, &m_TextureID);
        glDeleteRenderbuffers(1, &m_RBO);
    }

    // create buffer
    glGenFramebuffers(1, &m_BufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

    if (m_Multisample)
    {
        // texture attachment
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_TextureID);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Samples, GL_RGBA, m_Width, m_Height, GL_TRUE);

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_TextureID, 0);

        // depth stencil buffer attachment
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_Samples, GL_DEPTH24_STENCIL8, m_Width, m_Height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        // chek status
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "Failed to create FrameBuffer");

        // unbind frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else
    {
        // texture attachment
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

        // depth stencil buffer attachment
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        // chek status
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "Failed to create FrameBuffer");

        // unbind frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}

#include "gl_fbo.h"
#include <iostream>

#define USE_DEPTH_TEXTURE 1

void GLFBO::open(int w, int h) {
    m_w = w;
    m_h = h;

	glGenFramebuffers(1, &m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// create color0 texture
	glGenTextures(1, &m_tex_color0);
	glBindTexture(GL_TEXTURE_2D, m_tex_color0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// create depth texture
#if USE_DEPTH_TEXTURE
	glGenTextures(1, &m_tex_depth);
	glBindTexture(GL_TEXTURE_2D, m_tex_depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_w, m_h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);
#else
	glGenRenderbuffers(1, &m_tex_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_tex_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_w, m_h);
#endif

	// attach textures to a framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex_color0, 0);
#if USE_DEPTH_TEXTURE
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_tex_depth, 0);
#else
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_tex_depth);
#endif

	// default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::cout << "fbo:m_id: " << m_id << std::endl;
    std::cout << "fbo:m_tex_color0: " << m_tex_color0 << std::endl;
    std::cout << "fbo:m_tex_depth: " << m_tex_depth << std::endl;
}

void GLFBO::close() {
    if (m_id == 0) return;

	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// detach textures
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
#if USE_DEPTH_TEXTURE
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
#else
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
#endif
	glDeleteTextures(1, &m_tex_color0);
	glDeleteTextures(1, &m_tex_depth);
	glDeleteFramebuffers(1, &m_id);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFBO::bind() {
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void GLFBO::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
}

void GLFBO::check() {
	switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		case GL_FRAMEBUFFER_COMPLETE:
            std::cout << "fbo: good" << std::endl;
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cout << "fbo: unsupported" << std::endl;
			break;
		default:
            std::cout << "fbo: bad" << std::endl;
			break;
	}
}


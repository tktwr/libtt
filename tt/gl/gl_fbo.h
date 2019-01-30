#ifndef gl_fbo_h
#define gl_fbo_h

#include "gl.h"

class GLFBO {
public:
	GLFBO() {}

	void open(int w, int h);
	void close();

	void bind();
	void unbind();

    GLuint getColorTexId() const { return m_tex_color0; }
    GLuint getDepthTexId() const { return m_tex_depth; }

	static void check();

private:
	int m_viewport[4] = {0, 0, 0, 0};
	int m_w = 0;
	int m_h = 0;
	GLuint m_id = 0;
	GLuint m_tex_color0 = 0;
	GLuint m_tex_depth = 0;
};

#endif  // gl_fbo_h


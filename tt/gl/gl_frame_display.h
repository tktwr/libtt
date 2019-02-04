#ifndef gl_frame_display_h
#define gl_frame_display_h

#include "gl_frame.h"
#include "gl_texture.h"

class GLFrameDisplay : public GLFrame {
public:
    void init();
    void draw();

    void setImage(const tt::Image4uc& image);
    const tt::Vec2i& getImageSize() const { return m_image_size; }

    GLuint getTexId() const { return m_tex.id(); }

    void setScale(float f) { m_scale = f; }
    float getScale() const { return m_scale; }

    void setFit(bool b) { m_fit = b; }
    bool getFit() const { return m_fit; }

private:
    GLTexture2D m_tex;
    tt::Vec2i m_image_size = {0, 0};

    float m_scale = 1.0f;
    bool m_fit = true;
};

#endif  // gl_frame_display_h


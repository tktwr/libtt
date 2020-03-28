#pragma once

#include <vector>
#include <string>
#include <tt/util/type.h>
#include <tt/util/time.h>

class AppBase {
public:
    enum Key {
        KEY_SPACE            = 32,
        KEY_APOSTROPHE       = 39,  /* ' */
        KEY_COMMA            = 44,  /* , */
        KEY_MINUS            = 45,  /* - */
        KEY_PERIOD           = 46,  /* . */
        KEY_SLASH            = 47,  /* / */
        KEY_0 = 48,
        KEY_1 = 49,
        KEY_2 = 50,
        KEY_3 = 51,
        KEY_4 = 52,
        KEY_5 = 53,
        KEY_6 = 54,
        KEY_7 = 55,
        KEY_8 = 56,
        KEY_9 = 57,
        KEY_SEMICOLON        = 59,  /* ; */
        KEY_EQUAL            = 61,  /* = */
        KEY_A = 65,
        KEY_B = 66,
        KEY_C = 67,
        KEY_D = 68,
        KEY_E = 69,
        KEY_F = 70,
        KEY_G = 71,
        KEY_H = 72,
        KEY_I = 73,
        KEY_J = 74,
        KEY_K = 75,
        KEY_L = 76,
        KEY_M = 77,
        KEY_N = 78,
        KEY_O = 79,
        KEY_P = 80,
        KEY_Q = 81,
        KEY_R = 82,
        KEY_S = 83,
        KEY_T = 84,
        KEY_U = 85,
        KEY_V = 86,
        KEY_W = 87,
        KEY_X = 88,
        KEY_Y = 89,
        KEY_Z = 90,
        KEY_ESCAPE           = 256,
        KEY_ENTER            = 257,
        KEY_TAB              = 258,
        KEY_BACKSPACE        = 259,
        KEY_INSERT           = 260,
        KEY_DELETE           = 261,
        KEY_RIGHT            = 262,
        KEY_LEFT             = 263,
        KEY_DOWN             = 264,
        KEY_UP               = 265,
    };

    AppBase() {}
    virtual ~AppBase() {}

    virtual void Init() {
        if (!m_init) return;
        m_tm_init.start();
        init();
        m_tm_init.end();
        m_init = false;
    }
    virtual void Draw() {
        if (m_init) Init();
        m_tm_draw.start();
        draw();
        m_tm_draw.end();
    }

    virtual void init() {}
    virtual void draw() {}

    virtual void setScreenSize(int width, int height) { m_screen_size = {width, height}; }
    //virtual tt::Vec2i getScreenSize() const { return m_screen_size; }
    int getWidth() const { return m_screen_size[0]; }
    int getHeight() const { return m_screen_size[1]; }

    virtual void dropFiles(const std::vector<std::string>& fnames) {}
    virtual bool command(const std::string& line) { return false; }

    // for pc
    virtual void keyDown(int key) {}
    virtual void keyUp(int key) {}
    virtual void keyRepeat(int key) {}

    // for android
    virtual void touchDown(float x, float y) {}
    virtual void touchUp(float x, float y) {}
    virtual void touchMove(float dx, float dy) {}

    void needInit(bool b) { m_init = b; }

    void  setTime(float msec) { m_time = msec; }
    float getTime() const { return m_time; }

    float getInitTime() const { return m_tm_init.getElapsedMSec(); }
    float getDrawTime() const { return m_tm_draw.getElapsedMSec(); }

protected:
    bool m_init = true;
    tt::Vec2i m_screen_size = {400, 800};
    tt::Color4f m_clear_color = {0.2f, 0.2f, 0.2f, 1.0f};

    float m_time = 0.0f;
    tt::Time m_tm_init;
    tt::Time m_tm_draw;
};


#pragma once

#include <tt/util/time.h>
#include <vector>
#include <string>

class AppBase {
public:
    enum Key {
        KEY_SPACE = 32,
        KEY_ESCAPE = 256,
        KEY_ENTER = 257,
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

    virtual void setScreenSize(int width, int height) {
        m_screen_size[0] = width;
        m_screen_size[1] = height;
    }
    virtual void dropFiles(const std::vector<std::string>& fnames) {}

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

    float getInitTime()    const { return m_tm_init.getElapsedMSec(); }
    float getResizeTime()  const { return m_tm_resize.getElapsedMSec(); }
    float getDrawTime()    const { return m_tm_draw.getElapsedMSec(); }

protected:
    bool m_init = true;
    int m_screen_size[2] = {400, 800};

    float m_time = 0.0f;
    tt::Time m_tm_init;
    tt::Time m_tm_resize;
    tt::Time m_tm_draw;
};


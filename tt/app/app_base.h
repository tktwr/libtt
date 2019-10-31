#pragma once

class AppBase {
public:
    enum Key {
        KEY_SPACE = 32,
        KEY_ESCAPE = 256,
        KEY_ENTER = 257,
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

    virtual void init() {}
    virtual void resize(int width, int height) {}
    virtual void draw() {}

    // for pc
    virtual void keyDown(int key) {}
    virtual void keyUp(int key) {}
    virtual void keyRepeat(int key) {}

    // for android
    virtual void touchDown(float x, float y) {}
    virtual void touchUp(float x, float y) {}
    virtual void touchMove(float dx, float dy) {}
};


#pragma once

class AppBase {
public:
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


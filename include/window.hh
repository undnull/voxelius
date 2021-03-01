/*
 * window.hh
 * Created: 2021-01-16, 15:37:44.
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef WINDOW_HH
#define WINDOW_HH 1

struct GLFWwindow;

class WindowBase {
public:
    WindowBase(int width, int height, const char *title, bool fullscreen);
    virtual ~WindowBase();

    void setVSyncEnabled(bool b);

    bool isOpen() const;
    void close();

    void endFrame();

    void getSize(int &width, int &height);

    GLFWwindow *getWindow() const;

    virtual void onKey(int key, int scancode, int action, int mods);
    virtual void onChar(unsigned int unicode);
    virtual void onMouseButton(int button, int action, int mods);
    virtual void onCursorPos(float x, float y);

private:
    GLFWwindow *window;
};

#endif

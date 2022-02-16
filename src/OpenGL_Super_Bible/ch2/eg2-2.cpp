#include <sb6.h>
#include <math.h>

class simpleclear_app : public sb6::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Simple Clear";

        sb6::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void render(double currentTime)
    {
        const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, color);
    }
};

DECLARE_MAIN(simpleclear_app);
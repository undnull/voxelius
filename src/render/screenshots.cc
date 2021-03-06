/*
 * screenshots.cc
 * Created: 2021-03-06, 23:32:13.
 * Copyright (C) 2021, Kirill GPRB.
 */
#include <util/format.hh>
#include <util/fs.hh>
#include <util/logger.hh>

#include <glad/glad.h>
#include <stb_image_write.h>
#include <time.h>

namespace render
{
static const fs::path SCREENSHOTS_DIR = "screenshots";

// I was writing this with chronic sleep deprivation so
// please leave this code alone if it works fine
void takeScreenshot()
{
    fs::create_directories(SCREENSHOTS_DIR);

    char filename[64] = { 0 };
    time_t cur_time = time(nullptr);
    strftime(filename, sizeof(filename), "Screenshot %Y-%m-%d %H-%M-%S.jpg", localtime(&cur_time));

    const fs::path path = SCREENSHOTS_DIR / filename;

    int xywh[4];
    glGetIntegerv(GL_VIEWPORT, xywh);

    GLubyte *pixels = new GLubyte[static_cast<size_t>(xywh[2]) * static_cast<size_t>(xywh[3]) * 4];

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glReadPixels(xywh[0], xywh[1], xywh[2], xywh[3], GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    stbi_flip_vertically_on_write(1);
    stbi_write_jpg(path.string().c_str(), xywh[2], xywh[3], 4, pixels, 100);

    delete[] pixels;
}
} // namespace render

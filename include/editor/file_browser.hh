/*
 * file_browser.hh
 * Created: 2021-03-06, 13:03:40.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/fs.hh>
#include <imgui.h>

namespace editor
{
class FileBrowserDialog final {
private:
    struct fs_entry final {
        fs::path path;
        std::string print;
        bool is_directory;
        bool selected;
    };

public:
    FileBrowserDialog(const std::string &title, const char *filter);

    void close();
    bool draw(const ImGuiIO &io, bool show);

    const fs::path &getPath() const;

private:
    void updateEntries(bool reset);

    std::string title;
    bool visible;

    fs::path cwd;
    fs::path selected;
    std::string selected_str;

    bool has_enumerated;
    std::vector<fs_entry> entries;

    std::string filter;
    bool has_filter;
};

inline const fs::path &FileBrowserDialog::getPath() const
{
    return selected;
}
} // namespace editor
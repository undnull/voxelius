/*
 * file_browser.hh
 * Created: 2021-03-06, 13:03:40.
 * Copyright (C) 2021, Kirill GPRB.
 */
#pragma once
#include <util/fs.hh>
#include <util/imgui.hh>

namespace ui
{
class FileBrowserDialog {
private:
    struct fs_entry {
        fs::path path;
        std::string print;
        bool is_directory;
        bool selected;
    };

public:
    FileBrowserDialog(const std::string &title);

    void setFilter(const std::string &filter);
    void clearFilter();

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
} // namespace ui

/*
 * cmdline.hh
 * Created: 2021-01-30, 14:49:00
 * Copyright (C) 2021, Kirill GPRB.
 */
#ifndef VOXELIUS_CMDLINE_HH
#define VOXELIUS_CMDLINE_HH 1

namespace cmdline
{
void init(int argc, char **argv);

bool has_option(const char *opt);
bool has_argument(const char *opt);

const char *get_argument(const char *opt);
} // namespace cmdline

#endif

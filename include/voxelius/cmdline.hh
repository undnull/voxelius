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
bool hasOption(const char *opt);
bool hasArgument(const char *opt);
const char *getArgument(const char *opt);
} // namespace cmdline

#endif

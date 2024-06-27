#pragma once

namespace color {
    constexpr const char *reset = "\033[0m";

    namespace basic {
        constexpr const char *black = "\033[30m";
        constexpr const char *red = "\033[31m";
        constexpr const char *green = "\033[32m";
        constexpr const char *yellow = "\033[33m";
        constexpr const char *blue = "\033[34m";
        constexpr const char *magenta = "\033[35m";
        constexpr const char *cyan = "\033[36m";
        constexpr const char *white = "\033[37m";
    }// namespace basic

    namespace bright {
        constexpr const char *black = "\033[90m";
        constexpr const char *red = "\033[91m";
        constexpr const char *green = "\033[92m";
        constexpr const char *yellow = "\033[93m";
        constexpr const char *blue = "\033[94m";
        constexpr const char *magenta = "\033[95m";
        constexpr const char *cyan = "\033[96m";
        constexpr const char *white = "\033[97m";
    }// namespace bright
}// namespace color

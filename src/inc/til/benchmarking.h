// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

namespace til // Terminal Implementation Library. Also: "Today I Learned"
{
    #include <chrono>

    template <typename F>
    class ScopeTimer
    {
    public:
        ScopeTimer(F&& f) :
            _func{ f }
        {
            _start = std::chrono::steady_clock::now();
        }

        ~ScopeTimer()
        {
            auto end = std::chrono::steady_clock::now();
            auto diff = end - _start;
            _func(_start, diff);
        }

    private:
        F _func;
        std::chrono::steady_clock::time_point _start;
    };

    // This would be nice to have, but all kinds of things include this library
    // and they don't always link with fmt so compilation gets blocked
    auto ScopeTimerLogName(const char* name) -> decltype(auto)
    {
        return ScopeTimer([name](auto start, auto diff) {
            auto str = fmt::format("{}, start: {} elapsed: {}us\n", name, start.time_since_epoch().count(), std::chrono::duration_cast<std::chrono::microseconds>(diff).count());
            OutputDebugStringA(str.c_str());
        });
    }
    
}


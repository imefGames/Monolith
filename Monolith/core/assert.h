#pragma once

namespace Monolith
{
    namespace Report
    {
        void Assert(bool condition, const char* message);
        void Error(bool condition, const char* message);
        void Warning(bool condition, const char* message);
    }
}
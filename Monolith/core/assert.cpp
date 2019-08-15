#include <precomp.h>
#include <core/assert.h>

#include <Windows.h>

namespace Monolith
{
    namespace Report
    {
        namespace ReportInternal
        {
            void Notify(const char* messagetype, const char* message)
            {
                OutputDebugStringA("[");
                OutputDebugStringA(messagetype);
                OutputDebugStringA("] ");
                OutputDebugStringA(message);
                OutputDebugStringA("\n");
            }
        }

        void Assert(bool condition, const char* message)
        {
            if (!condition)
            {
                ReportInternal::Notify("ASSERT", message);
                DebugBreak();
                abort();
            }
        }

        void Error(bool condition, const char* message)
        {
            if (!condition)
            {
                ReportInternal::Notify("ERROR", message);
            }
        }

        void Warning(bool condition, const char* message)
        {
            if (!condition)
            {
                ReportInternal::Notify("WARNING", message);
            }
        }
    }
}
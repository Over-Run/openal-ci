
#include "config.h"

#include "dbus_wrap.h"

#if HAVE_DYNLOAD

#include <mutex>
#include <type_traits>

#include "logging.h"


void PrepareDBus()
{
    const char *libname{"libdbus-1.so.3"};

    dbus_handle = LoadLib(libname);
    if(!dbus_handle)
    {
        WARN("Failed to load {}", libname);
        return;
    }

    auto load_func = [](auto &f, const char *name) -> void
    {
        /* NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast) */
        f = reinterpret_cast<std::remove_reference_t<decltype(f)>>(GetSymbol(dbus_handle, name));
    };
#define LOAD_FUNC(x) do {                         \
    load_func(p##x, #x);                          \
    if(!p##x)                                     \
    {                                             \
        WARN("Failed to load function {}", #x);   \
        CloseLib(dbus_handle);                    \
        dbus_handle = nullptr;                    \
        return;                                   \
    }                                             \
} while(0);

    DBUS_FUNCTIONS(LOAD_FUNC)

#undef LOAD_FUNC
}
#endif

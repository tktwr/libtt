#include "path.h"
#include <windows.h>
#include <shlobj.h>

namespace tt { namespace win {

tstring f_get_home_dir()
{
    TCHAR path[_MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, path);
    return tstring(path) + _T('\\');
}

tstring f_get_local_appdata_dir()
{
    TCHAR path[_MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path);
    return tstring(path) + _T('\\');
}

tstring f_get_desktop_dir()
{
    TCHAR path[_MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, path);
    return tstring(path) + _T('\\');
}

tstring f_get_exe_dir()
{
    TCHAR path[_MAX_PATH];
    GetModuleFileName(NULL, path, _MAX_PATH);

    TCHAR drive[_MAX_DRIVE];
    TCHAR dir  [_MAX_DIR];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext  [_MAX_EXT];
    _tsplitpath_s(
        path,
        drive, _MAX_DRIVE,
        dir,   _MAX_DIR,
        fname, _MAX_FNAME,
        ext,   _MAX_EXT
        );
    return tstring(drive) + tstring(dir);
}

tstring f_get_current_dir()
{
    TCHAR path[_MAX_PATH];
    GetCurrentDirectory(_MAX_PATH, path);
    return tstring(path) + _T('\\');
}

} }


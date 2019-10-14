#pragma once

#include <string>
#include <tchar.h>

typedef std::basic_string<TCHAR> tstring;

namespace tt {
namespace win {

tstring f_get_home_dir();
tstring f_get_local_appdata_dir();
tstring f_get_desktop_dir();
tstring f_get_exe_dir();
tstring f_get_current_dir();

}
}


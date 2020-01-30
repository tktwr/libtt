#include <stdio.h>
#include <stdlib.h>     // getenv
#ifndef WIN32
#include <pwd.h>        // getpwnam
#include <sys/types.h>  // getpwnam
#endif // !WIN32
#include <algorithm>    // count
#include "filename.h"

namespace tt {

std::string filename_expand_homedir(std::string path);
std::string filename_expand_env(std::string path);
std::string filename_erase_redundant_slash(std::string path);
std::string filename_expand_path(std::string path);
std::string::size_type filename_find_fname(const std::string& path);
std::string::size_type filename_find_ext(const std::string& path);

std::string getenv_s(const char* varname) {
    char *pValue;
    size_t len;
    errno_t err = _dupenv_s(&pValue, &len, varname);
    if (err) return std::string();
    std::string str(pValue);
    free(pValue);
    return str;
}

// expand '~', "~usr_name"
std::string filename_expand_homedir(std::string path) {
	if (path[0] == '~') {
		if (path.size() == 1 || path[1] == '/') {
			// expand '~'
#ifdef WIN32
			path.replace(0, 1, getenv_s("USERPROFILE"));
#else
			path.replace(0, 1, getenv("HOME"));
#endif
		} else {
			// expand "~usr_name"
#ifndef WIN32
			std::string::size_type i = path.find('/');
			const std::string& usr_name = path.substr(1, i-1);
			struct passwd* pw = getpwnam(usr_name.c_str());
			if (pw) path.replace(0, i, pw->pw_dir);
#endif // !WIN32
		}
	}

	return path;
}

// expand ${...}
std::string filename_expand_env(std::string path) {
	std::string::size_type i1, i2;

	while (1) {
		i1 = path.find("${"); if (i1 == std::string::npos) break;
		i2 = path.find("}");  if (i2 == std::string::npos) break;

		const std::string& s = path.substr(i1+2, i2-i1-2);
#ifdef WIN32
        const std::string& envstr = getenv_s(s.c_str());
		const char* env = envstr.c_str();
#else
		const char* env = getenv(s.c_str());
#endif
		if (env) path.replace(i1, i2-i1+1, env);
		else     path.replace(i1, i2-i1+1, "");
	}

	return path;
}

std::string filename_erase_redundant_slash(std::string path) {
	std::string::size_type i;

	while (1) {
		i = path.find("//");
		if (i == std::string::npos) break;

		path.erase(i, 1);
	}

	return path;
}

std::string filename_expand_path(std::string path) {
	path = filename_expand_homedir(path);
	path = filename_expand_env(path);
	path = filename_erase_redundant_slash(path);
	return path;
}

std::string::size_type filename_find_fname(const std::string& path) {
	std::string::size_type i = path.rfind('/');
	if (i == std::string::npos)
		return 0;
	else
		return i+1;
}

std::string::size_type filename_find_ext(const std::string& path) {
	std::string::size_type i = path.rfind('.');
	if (i != std::string::npos) {
		const std::string& s = path.substr(i);
		if (s == ".Z" || s == ".gz" || s == ".bz2") {
			std::string::size_type i2 = path.rfind('.', i-1);
			if (i2 != std::string::npos) i = i2;
		}
	}
	return i;
}

//=========================================================================
// class FileName
//=========================================================================

void FileName::path(const std::string& path) {
	m_orig      = path;
	m_path      = filename_expand_path(path);
	m_idx_fname = filename_find_fname(m_path);
	m_idx_ext   = filename_find_ext(m_path);
}

std::string FileName::dirname() const {
	return m_path.substr(0, m_idx_fname);
}

std::string FileName::fname() const {
	return m_path.substr(m_idx_fname);
}

std::string FileName::name() const {
	return m_path.substr(m_idx_fname, m_idx_ext - m_idx_fname);
}

std::string FileName::ext() const {
	if (m_idx_ext == std::string::npos) return "";
	return m_path.substr(m_idx_ext);
}

std::string FileName::prefix(int n) const {
	std::string::size_type i1 = 0;
	std::string::size_type i2 = m_idx_fname;
	while (n >= 0) {
		i1 = i2;
		i2 = m_path.find('.', i1);
		if (i2 == std::string::npos) return "";
		++i2;
		--n;
	}
	return m_path.substr(i1, i2-i1);
}

std::string FileName::suffix(int n) const {
	std::string::size_type i1 = 0;
	std::string::size_type i2 = std::string::npos;
	while (n >= 0) {
		i1 = i2;
		i2 = m_path.rfind('.', i1);
		if (i2 == std::string::npos) return "";
		--i2;
		--n;
	}
	return m_path.substr(i2+1, i1-i2);
}

bool FileName::isAbsPath() const {
	return (m_path[0] == '/');
}

std::istream& operator >>(std::istream& is, FileName& fname) {
	std::string s;
	is >> s;
	fname.path(s);
	return is;
}

std::ostream& operator <<(std::ostream& os, const FileName& fname) {
	os << fname.path();
	return os;
}

//=========================================================================
// class FrameName
//=========================================================================

FrameName::FrameName(const std::string& fname)
: FileName(fname) {
}

std::string FrameName::path(int nr) const {
	return dirname() + name(nr) + ext();
}

std::string FrameName::fname(int nr) const {
	return name(nr) + ext();
}

std::string FrameName::name(int nr) const {
	char buf[256];
    std::string orgname = FileName::name();
	sprintf_s(buf, 256, orgname.c_str(), nr);
	return std::string(buf);
}

}

#ifndef tt_filename_h
#define tt_filename_h

#include <string>
#include <iostream>

namespace tt {

class FileName {
public:
    FileName() {}
    FileName(const char* _path) { path(_path); }
    FileName(const std::string& _path) { path(_path); }

    void path(const std::string& path);

    operator const char*()        const { return m_path.c_str(); }
    const char* c_str()           const { return m_path.c_str(); }
    std::string str()             const { return m_path; }

    // path()  == dirname() + fname()
    // fname() == name() + ext()
    std::string orig()            const { return m_orig; }
    std::string path()            const { return m_path; }
    std::string dirname()         const;
    std::string fname()           const;
    std::string name()            const;
    std::string ext()             const;
    std::string prefix(int n = 0) const;
    std::string suffix(int n = 0) const;

    bool isAbsPath() const;

    bool matchExt(const std::string& str) {
        return str.find(ext()) != std::string::npos ? true : false;
    }

private:
    std::string m_orig, m_path;
    std::string::size_type m_idx_fname, m_idx_ext;
};

std::istream& operator >>(std::istream& is, FileName& fname);
std::ostream& operator <<(std::ostream& os, const FileName& fname);

//=========================================================================
// class FrameName
//
// EXAMPLE:
//   FrameName frname("frame.%04d.ppm");
//=========================================================================

class FrameName : public FileName {
public:
    FrameName(const std::string& fname);

    std::string path (int nr) const;
    std::string fname(int nr) const;
    std::string name (int nr) const;
};

}

#endif  // tt_filename_h


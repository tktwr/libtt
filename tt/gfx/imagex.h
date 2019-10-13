#ifndef imagex_h
#define imagex_h

#include <string>
#include <tt/gfx/image.h>
#include <tt/util/filename.h>

namespace tt {

class ImageX {
public:
    enum DataType {
        I_8UC1 = 0,
        I_8UC2,
        I_8UC3,
        I_8UC4,
        I_16UC1,
        I_16UC2,
        I_16UC3,
        I_16UC4,
        I_32FC1,
        I_32FC2,
        I_32FC3,
        I_32FC4,
        I_NONE
    };

    ImageX() {
        create("i4uc", 1, 1);
    }
    ~ImageX() {
        destroy();
    }

    int w() const { return m_image->w(); }
    int h() const { return m_image->h(); }

    std::size_t size() const { return m_image->size(); }
    std::size_t sizeOfDataType() const { return m_image->sizeOfDataType(); }

    void resize(int w, int h) { return m_image->resize(w, h); }
    void alloc(int w, int h) { return m_image->alloc(w, h); }
    void clear() { return m_image->clear(); }
    bool empty() const { return m_image->empty(); }

    const void* void_ptr() const { return m_image->void_ptr(); }
          void* void_ptr()       { return m_image->void_ptr(); }

    ImageBaseConstPtr getImageBaseConstPtr() const { return m_image; }
    ImageBasePtr      getImageBasePtr()            { return m_image; }

    void create(const std::string& type, int w, int h);
    void load(const std::string& fname);
    void save(const std::string& fname) const;

    std::string getType() const { return m_type; }
    std::string getFileName() const { return m_fname; }

private:
    std::string getExt(const tt::FileName& fname) const;
    std::string getType(const std::string& ext) const;
    bool isType(const std::string& ext) const;

    void destroy() {
        if (m_image) {
            m_image = nullptr;
            m_type = "";
            m_fname = "";
        }
    }
    void load_bin(const std::string& fname);
    void save_bin(const std::string& fname) const;

    ImageBasePtr m_image = nullptr;
    std::string m_type;
    std::string m_fname;
};

inline tt::Image1ucPtr toImage1ucPtr(tt::ImageX& img) { return std::dynamic_pointer_cast<tt::Image1uc>(img.getImageBasePtr()); }
inline tt::Image1usPtr toImage1usPtr(tt::ImageX& img) { return std::dynamic_pointer_cast<tt::Image1us>(img.getImageBasePtr()); }
inline tt::Image3ucPtr toImage3ucPtr(tt::ImageX& img) { return std::dynamic_pointer_cast<tt::Image3uc>(img.getImageBasePtr()); }
inline tt::Image4ucPtr toImage4ucPtr(tt::ImageX& img) { return std::dynamic_pointer_cast<tt::Image4uc>(img.getImageBasePtr()); }

inline tt::Image1ucConstPtr toImage1ucConstPtr(const tt::ImageX& img) { return std::dynamic_pointer_cast<const tt::Image1uc>(img.getImageBaseConstPtr()); }
inline tt::Image1usConstPtr toImage1usConstPtr(const tt::ImageX& img) { return std::dynamic_pointer_cast<const tt::Image1us>(img.getImageBaseConstPtr()); }
inline tt::Image3ucConstPtr toImage3ucConstPtr(const tt::ImageX& img) { return std::dynamic_pointer_cast<const tt::Image3uc>(img.getImageBaseConstPtr()); }
inline tt::Image4ucConstPtr toImage4ucConstPtr(const tt::ImageX& img) { return std::dynamic_pointer_cast<const tt::Image4uc>(img.getImageBaseConstPtr()); }

inline tt::Image1uc& toImage1ucRef(tt::ImageX& img) { return dynamic_cast<tt::Image1uc&>(*(img.getImageBasePtr())); }
inline tt::Image1us& toImage1usRef(tt::ImageX& img) { return dynamic_cast<tt::Image1us&>(*(img.getImageBasePtr())); }
inline tt::Image3uc& toImage3ucRef(tt::ImageX& img) { return dynamic_cast<tt::Image3uc&>(*(img.getImageBasePtr())); }
inline tt::Image4uc& toImage4ucRef(tt::ImageX& img) { return dynamic_cast<tt::Image4uc&>(*(img.getImageBasePtr())); }

}  // namespace tt

#endif  // imagex_h


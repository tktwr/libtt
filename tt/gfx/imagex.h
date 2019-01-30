#ifndef imagex_h
#define imagex_h

#include <string>
#include <tt/gfx/image.h>
#include <tt/util/filename.h>

namespace tt {

class ImageX {
public:
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

    const ImageBase* getImageBase() const { return m_image; }
          ImageBase* getImageBase()       { return m_image; }

    std::string getType(const tt::FileName& fname) const;
    std::string getType(int cv_type) const;
    bool isType(const std::string& type) const;
    void create(const std::string& type, int w, int h);
    void load(const std::string& fname);
    void save(const std::string& fname) const;

private:
    void destroy() {
        if (m_image) {
            delete m_image;
            m_image = 0;
        }
    }
    void load_bin(const std::string& fname);
    void save_bin(const std::string& fname) const;
    void load_mat(const std::string& fname);
    void save_mat(const std::string& fname) const;

    ImageBase* m_image = 0;
    std::string m_type;
};

inline tt::Image1uc* toImage1ucPtr(tt::ImageX& img) { return dynamic_cast<tt::Image1uc*>(img.getImageBase()); }
inline tt::Image1us* toImage1usPtr(tt::ImageX& img) { return dynamic_cast<tt::Image1us*>(img.getImageBase()); }
inline tt::Image3uc* toImage3ucPtr(tt::ImageX& img) { return dynamic_cast<tt::Image3uc*>(img.getImageBase()); }
inline tt::Image4uc* toImage4ucPtr(tt::ImageX& img) { return dynamic_cast<tt::Image4uc*>(img.getImageBase()); }

inline tt::Image1uc& toImage1ucRef(tt::ImageX& img) { return dynamic_cast<tt::Image1uc&>(*(img.getImageBase())); }
inline tt::Image1us& toImage1usRef(tt::ImageX& img) { return dynamic_cast<tt::Image1us&>(*(img.getImageBase())); }
inline tt::Image3uc& toImage3ucRef(tt::ImageX& img) { return dynamic_cast<tt::Image3uc&>(*(img.getImageBase())); }
inline tt::Image4uc& toImage4ucRef(tt::ImageX& img) { return dynamic_cast<tt::Image4uc&>(*(img.getImageBase())); }

}  // namespace tt

#endif  // imagex_h


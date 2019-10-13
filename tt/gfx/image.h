#ifndef tt_image_h
#define tt_image_h

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <memory>
#include <string.h>
#include <tt/util/array.h>
#include <tt/util/type.h>

namespace tt {

class ImageBase {
public:
    virtual ~ImageBase() {}

    virtual int w() const = 0;
    virtual int h() const = 0;

    virtual std::size_t size() const = 0;
    virtual std::size_t sizeOfDataType() const = 0;

    virtual void resize(int w, int h) = 0;
    virtual void alloc(int w, int h) = 0;
    virtual void clear() = 0;
    virtual bool empty() const = 0;

    virtual const void* void_ptr() const = 0;
    virtual       void* void_ptr()       = 0;
};

template<class T>
class Image : public ImageBase {
public:
    Image() : m_w(0), m_h(0) {}
    Image(int w, int h) { resize(w, h); }

    void resize(int w, int h) {
        m_w = w;
        m_h = h;
        m_data.resize(w * h);
    }
    void alloc(int w, int h) {
        m_w = w;
        m_h = h;
        m_data.alloc(w * h);
    }

    void clear() {
        m_w = 0;
        m_h = 0;
        m_data.clear();
    }
    void fill(const T& v = T()) { m_data.fill(v); }

    bool empty() const { return m_data.empty(); }

    std::size_t size() const { return m_data.size(); }
    std::size_t sizeOfDataType() const { return m_data.sizeOfDataType(); }

    int w() const { return m_w; }
    int h() const { return m_h; }

    const T* data() const { return m_data.data(); }
          T* data()       { return m_data.data(); }

    const void* void_ptr() const { return m_data.data(); }
          void* void_ptr()       { return m_data.data(); }

    T    getValue(int x, int y) const { return m_data[y * m_w + x]; }
    void setValue(int x, int y, const T& val) { m_data[y * m_w + x] = val; }

    void foreach(const std::function<void(T&, int, int)>& func, int nth = -1) {
        if (nth == 0) {
            foreach_nothread(func);
            return;
        }
        if (nth == -1) {
            nth = std::thread::hardware_concurrency();
        }
        std::vector<std::thread> th;
        std::atomic<int> i(0);
        for (int t=0; t<nth; t++) {
            th.push_back(std::thread([&]() {
                int y = 0;
                while ((y = i++) < m_h) {
                    for (int x=0; x<m_w; x++) {
                        T& val = m_data[y * m_w + x];
                        func(val, x, y);
                    }
                }
            }));
        }
        for (auto& t : th) {
            t.join();
        }
    }

private:
    void foreach_nothread(const std::function<void(T&, int, int)>& func) {
        for (int y = 0; y < m_h; y++) {
            for (int x = 0; x < m_w; x++) {
                T& val = m_data[y * m_w + x];
                func(val, x, y);
            }
        }
    }

    int m_w, m_h;
    Array<T> m_data;
};

template<class T>
void f_image_print(Image<T>& image) {
    image.foreach([&](T& val, int x, int y) {
        std::cout << val << " ";
        if (x == image.w() - 1) std::cout << std::endl;
    }, 0);
    std::cout << std::flush;
}

template<class T>
void f_image_same_size(const Image<T>& img0, const Image<T>& img1) {
    return (img0.w() == img1.w()) && (img0.h() == img1.h());
}

template<class T>
void f_image_copy(Image<T>& dst, const Image<T>& src) {
    dst.alloc(src.w(), src.h());
    memcpy(dst.data(), src.data(), src.size() * src.sizeOfDataType());
}

using Image1uc = Image<Color1uc>;
using Image1us = Image<Color1us>;
using Image1f  = Image<Color1f>;

using Image2uc = Image<Color2uc>;
using Image2us = Image<Color2us>;
using Image2f  = Image<Color2f>;

using Image3uc = Image<Color3uc>;
using Image3us = Image<Color3us>;
using Image3f  = Image<Color3f>;

using Image4uc = Image<Color4uc>;
using Image4us = Image<Color4us>;
using Image4f  = Image<Color4f>;

using ImageBasePtr      = std::shared_ptr<ImageBase>;
using ImageBaseConstPtr = std::shared_ptr<const ImageBase>;

using Image1ucPtr       = std::shared_ptr<Image1uc>;
using Image1ucConstPtr  = std::shared_ptr<const Image1uc>;
using Image1usPtr       = std::shared_ptr<Image1us>;
using Image1usConstPtr  = std::shared_ptr<const Image1us>;
using Image1fPtr        = std::shared_ptr<Image1f>;
using Image1fConstPtr   = std::shared_ptr<const Image1f>;

using Image2ucPtr       = std::shared_ptr<Image2uc>;
using Image2ucConstPtr  = std::shared_ptr<const Image2uc>;
using Image2usPtr       = std::shared_ptr<Image2us>;
using Image2usConstPtr  = std::shared_ptr<const Image2us>;
using Image2fPtr        = std::shared_ptr<Image2f>;
using Image2fConstPtr   = std::shared_ptr<const Image2f>;

using Image3ucPtr       = std::shared_ptr<Image3uc>;
using Image3ucConstPtr  = std::shared_ptr<const Image3uc>;
using Image3usPtr       = std::shared_ptr<Image3us>;
using Image3usConstPtr  = std::shared_ptr<const Image3us>;
using Image3fPtr        = std::shared_ptr<Image3f>;
using Image3fConstPtr   = std::shared_ptr<const Image3f>;

using Image4ucPtr       = std::shared_ptr<Image4uc>;
using Image4ucConstPtr  = std::shared_ptr<const Image4uc>;
using Image4usPtr       = std::shared_ptr<Image4us>;
using Image4usConstPtr  = std::shared_ptr<const Image4us>;
using Image4fPtr        = std::shared_ptr<Image4f>;
using Image4fConstPtr   = std::shared_ptr<const Image4f>;

}  // namespace tt

#endif  // tt_image_h


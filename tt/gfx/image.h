#ifndef tt_image_h
#define tt_image_h

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
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

typedef Image<Color1uc> Image1uc;
typedef Image<Color1us> Image1us;
typedef Image<Color1f>  Image1f;

typedef Image<Color2uc> Image2uc;
typedef Image<Color2us> Image2us;
typedef Image<Color2f>  Image2f;

typedef Image<Color3uc> Image3uc;
typedef Image<Color3us> Image3us;
typedef Image<Color3f>  Image3f;

typedef Image<Color4uc> Image4uc;
typedef Image<Color4us> Image4us;
typedef Image<Color4f>  Image4f;

}  // namespace tt

#endif  // tt_image_h


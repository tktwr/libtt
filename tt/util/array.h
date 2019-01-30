#ifndef tt_array_h
#define tt_array_h

namespace tt {

template<class T>
class Array {
public:
    typedef T data_type;

    Array() : m_data_char(0), m_data(0), m_size(0) {}
    Array(std::size_t size) : m_data_char(0), m_data(0), m_size(0) { resize(size); }
    virtual ~Array() { destroy(); }

    void resize(std::size_t size) {
        if (m_size == size) return;

        destroy();
        if (size > 0) {
            m_data_char = 0;
            m_data = new T[size];
            m_size = size;
        }
    }

    void alloc(std::size_t size) {
        if (m_size == size) return;

        destroy();
        if (size > 0) {
            m_data_char = new char[size * sizeof(data_type)];
            m_data = reinterpret_cast<T*>(m_data_char);
            m_size = size;
        }
    }

    void clear() { destroy(); }
    void fill(const T& v = T()) { for (std::size_t i=0; i<m_size; i++) m_data[i] = v; }

    bool empty() const { return m_size == 0; }

    std::size_t size() const { return m_size; }
    std::size_t sizeOfDataType() const { return sizeof(data_type); }

    const T* data() const { return m_data; }
          T* data()       { return m_data; }

    const T& operator[](std::size_t i) const { return m_data[i]; }
          T& operator[](std::size_t i)       { return m_data[i]; }

private:
    void destroy() {
        if (m_data_char) {
            delete [] m_data_char;
            m_data_char = 0;
            m_data = 0;
        }
        if (m_data) {
            delete [] m_data;
            m_data_char = 0;
            m_data = 0;
        }
        m_size = 0;
    }

    char* m_data_char;
    T* m_data;
    std::size_t m_size;
};

}

#endif  // tt_array_h


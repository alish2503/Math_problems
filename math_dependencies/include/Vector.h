#include <memory>

template<bool B, typename U, typename V>
struct conditional {
    using type = V;
};
template<typename U, typename V>
struct conditional<true, U, V> {
    using type = U;
};

template<bool B, typename U, typename V>
using conditional_t = typename conditional<B, U, V>::type;

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using alloc_traits = std::allocator_traits<Allocator>;

private:
    Allocator alloc_;
    size_type size_;
    size_type capacity_;
    T* data_;

public:
    template <bool IsConst>
        struct common_iterator {
            conditional_t<IsConst, const T*, T*>  ptr;

            common_iterator(T *p = nullptr) : ptr(p) {}

            common_iterator& operator++() { 
                ++ptr; 
                return *this; 
            }
            common_iterator operator++(int) { 
                common_iterator tmp = *this;
                ++ptr; 
                return tmp; 
            }
            conditional_t<IsConst, const T&, T&> operator*() { return *ptr; }

            bool operator==(const common_iterator& other) const { return ptr == other.ptr; }
            bool operator!=(const common_iterator& other) const { return ptr != other.ptr; }
        };
private:
    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;
public:
    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }
    const_iterator begin() const { return const_iterator(data_); }
    const_iterator end() const { return const_iterator(data_ + size_); }

    Vector() : size_(0), capacity_(0), data_(nullptr) {}
    Vector(size_t count, const T& value = T(), const Allocator& alloc = Allocator())
        : alloc_(alloc), size_(count), capacity_(count) {
        data_ = alloc_traits::allocate(alloc_, capacity_);
        std::uninitialized_fill_n(data_, size_, value);
    }
    Vector(const Vector& other)
        : alloc_(alloc_traits::select_on_container_copy_construction(other.alloc_)),
          size_(other.size_), capacity_(other.capacity_) {
        data_ = alloc_traits::allocate(alloc_, capacity_);
        std::uninitialized_copy(other.data_, other.data_ + size_, data_);
    }

    Vector(Vector&& other) noexcept
        : alloc_(std::move(other.alloc_)),
          size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            clear();
            alloc_traits::deallocate(alloc_, data_, capacity_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            alloc_ = alloc_traits::select_on_container_copy_construction(other.alloc_);
            data_ = alloc_traits::allocate(alloc_, capacity_);
            std::uninitialized_copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            alloc_traits::deallocate(alloc_, data_, capacity_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = other.data_;
            alloc_ = std::move(other.alloc_);
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }
    ~Vector() {
        clear();
        if (data_) {
            alloc_traits::deallocate(alloc_, data_, capacity_);
        }
    }
    reference front() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    const_reference front() const {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    reference back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }

    const_reference back() const {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }
    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity_) return;

        T* new_data = alloc_traits::allocate(alloc_, new_capacity);

        for (size_type i = 0; i < size_; ++i) {
            alloc_traits::construct(alloc_, new_data + i, std::move_if_noexcept(data_[i]));
        }

        clear();
        if (data_) {
            alloc_traits::deallocate(alloc_, data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }
    void resize(size_type new_size, const T& value = T()) {
        if (new_size > size_) {
            if (new_size > capacity_) reserve(new_size);
            std::uninitialized_fill(data_ + size_, data_ + new_size, value);
        } else if (new_size < size_) {
            for (size_type i = new_size; i < size_; ++i) {
                alloc_traits::destroy(alloc_, data_ + i);
            }
        }

        size_ = new_size;
    }

    template<typename U>
    void push_back(U&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        alloc_traits::construct(alloc_, data_ + size_, std::forward<U>(value));
        ++size_;
    }
    size_type size() const { return size_; }
    size_type capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    reference operator[](size_type i) { return data_[i]; }
    const_reference operator[](size_type i) const { return data_[i]; }

private:
    void clear() {
        for (size_type i = 0; i < size_; ++i) {
            alloc_traits::destroy(alloc_, data_ + i);
        }
    }
};

using dv = Vector<double>;

#include <iostream>
#include <stdexcept>
#include <iomanip>

class VectorUShort {
private:
    unsigned short* data;
    size_t num;
    int State;
    static int objectCount;

public:
    // конструктори
    VectorUShort() : num(1), State(0) {
        try {
            data = new unsigned short[1]{0};
        } catch (...) {
            State = 1;
            data = nullptr;
        }
        ++objectCount;
    }

    VectorUShort(size_t n) : num(n), State(0) {
        try {
            data = new unsigned short[n]{0};
        } catch (...) {
            State = 1;
            data = nullptr;
        }
        ++objectCount;
    }

    VectorUShort(size_t n, unsigned short value) : num(n), State(0) {
        try {
            data = new unsigned short[n];
            for (size_t i = 0; i < n; ++i)
                data[i] = value;
        } catch (...) {
            State = 1;
            data = nullptr;
        }
        ++objectCount;
    }

    // конструктор копіювання
    VectorUShort(const VectorUShort& other) : num(other.num), State(other.State) {
        data = new unsigned short[num];
        for (size_t i = 0; i < num; ++i)
            data[i] = other.data[i];
        ++objectCount;
    }

    // деструктор
    ~VectorUShort() {
        delete[] data;
        --objectCount;
    }

    // геттер кількості об'єктів
    static int getObjectCount() {
        return objectCount;
    }

    // оператор присвоєння
    VectorUShort& operator=(const VectorUShort& other) {
        if (this != &other) {
            delete[] data;
            num = other.num;
            State = other.State;
            data = new unsigned short[num];
            for (size_t i = 0; i < num; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Індексація
    unsigned short& operator[](size_t index) {
        if (index >= num) {
            State = 2;
            return data[num - 1];
        }
        return data[index];
    }

    // виклик функції ()
    unsigned short operator() (size_t index) const {
        if (index >= num) return data[num - 1];
        return data[index];
    }

    // унарні ++/-- (префікс і постфікс)
    VectorUShort& operator++() {
        for (size_t i = 0; i < num; ++i) ++data[i];
        return *this;
    }
    VectorUShort operator++(int) {
        VectorUShort tmp(*this);
        ++(*this);
        return tmp;
    }
    VectorUShort& operator--() {
        for (size_t i = 0; i < num; ++i) --data[i];
        return *this;
    }
    VectorUShort operator--(int) {
        VectorUShort tmp(*this);
        --(*this);
        return tmp;
    }

    // унарні логічні побітові та арифметичні
    bool operator!() const {
        return num == 0;
    }

    VectorUShort operator~() const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = ~data[i];
        return res;
    }

    VectorUShort operator-() const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = static_cast<unsigned short>(-data[i]);
        return res;
    }

    // арифметичні бінарні
    VectorUShort operator+(const VectorUShort& other) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] + other.data[i];
        return res;
    }

    VectorUShort operator-(const VectorUShort& other) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] - other.data[i];
        return res;
    }

    VectorUShort operator*(unsigned short val) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] * val;
        return res;
    }

    VectorUShort operator/(unsigned short val) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] / val;
        return res;
    }

    VectorUShort operator%(unsigned short val) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] % val;
        return res;
    }

    // Побітові бінарні
    VectorUShort operator|(const VectorUShort& other) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] | other.data[i];
        return res;
    }

    VectorUShort operator^(const VectorUShort& other) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] ^ other.data[i];
        return res;
    }

    VectorUShort operator&(const VectorUShort& other) const {
        VectorUShort res(num);
        for (size_t i = 0; i < num; ++i)
            res.data[i] = data[i] & other.data[i];
        return res;
    }

    // Оператори порівняння
    bool operator==(const VectorUShort& other) const {
        if (num != other.num) return false;
        for (size_t i = 0; i < num; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorUShort& other) const {
        return !(*this == other);
    }

    bool operator>(const VectorUShort& other) const {
        for (size_t i = 0; i < num; ++i)
            if (data[i] <= other.data[i]) return false;
        return true;
    }

    bool operator<(const VectorUShort& other) const {
        for (size_t i = 0; i < num; ++i)
            if (data[i] >= other.data[i]) return false;
        return true;
    }

    bool operator>=(const VectorUShort& other) const {
        return !(*this < other);
    }

    bool operator<=(const VectorUShort& other) const {
        return !(*this > other);
    }

    // Побітові зсуви (друзі)
    friend std::istream& operator>>(std::istream& in, VectorUShort& v) {
        for (size_t i = 0; i < v.num; ++i)
            in >> v.data[i];
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const VectorUShort& v) {
        for (size_t i = 0; i < v.num; ++i)
            out << v.data[i] << " ";
        return out;
    }

    // Присвоєння операцією
    VectorUShort& operator+=(const VectorUShort& other) {
        for (size_t i = 0; i < num; ++i)
            data[i] += other.data[i];
        return *this;
    }

    VectorUShort& operator-=(const VectorUShort& other) {
        for (size_t i = 0; i < num; ++i)
            data[i] -= other.data[i];
        return *this;
    }

    VectorUShort& operator*=(unsigned short val) {
        for (size_t i = 0; i < num; ++i)
            data[i] *= val;
        return *this;
    }

    VectorUShort& operator/=(unsigned short val) {
        for (size_t i = 0; i < num; ++i)
            data[i] /= val;
        return *this;
    }

    VectorUShort& operator%=(unsigned short val) {
        for (size_t i = 0; i < num; ++i)
            data[i] %= val;
        return *this;
    }

    VectorUShort& operator|=(const VectorUShort& other) {
        for (size_t i = 0; i < num; ++i)
            data[i] |= other.data[i];
        return *this;
    }

    VectorUShort& operator^=(const VectorUShort& other) {
        for (size_t i = 0; i < num; ++i)
            data[i] ^= other.data[i];
        return *this;
    }

    VectorUShort& operator&=(const VectorUShort& other) {
        for (size_t i = 0; i < num; ++i)
            data[i] &= other.data[i];
        return *this;
    }

    // доступ в State
    int getState() const { return State; }

    // повернення кількості елементів
    size_t size() const { return num; }
};

// лічильник об'єктів
int VectorUShort::objectCount = 0;

// тестування
int main() {
    VectorUShort v1(5, 10), v2(5, 3);
    VectorUShort v3 = v1 + v2;
    std::cout << "v3: " << v3 << std::endl;

    v3 *= 2;
    std::cout << "v3 * 2: " << v3 << std::endl;

    ++v3;
    std::cout << "++v3: " << v3 << std::endl;

    std::cout << "Number of VectorUShort objects: " << VectorUShort::getObjectCount() << std::endl;

    return 0;
}

#ifndef STDEXTENSION_H
#define STDEXTENSION_H
#include <functional>

namespace std {
template <typename T>
struct hash<std::reference_wrapper<T>> {
    size_t operator()(const std::reference_wrapper<T>& ref) const {
        return std::hash<T*>()(&ref.get()); // Хешируем указатель на объект
    }
};

template <typename T>
struct ReferenceWrapperEqual {
    bool operator()(const std::reference_wrapper<T>& lhs,
                    const std::reference_wrapper<T>& rhs) const {
        return &lhs.get() == &rhs.get(); // Сравниваем адреса объектов
    }
};
}

#endif // STDEXTENSION_H

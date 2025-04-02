#ifndef STDEXTENSION_H
#define STDEXTENSION_H
#include <functional>

//accessed and modified from https://stackoverflow.com/questions/29379019/why-is-stdhash-not-specialised-for-stdreference-wrapper
namespace std {
template <typename T>
struct hash<std::reference_wrapper<T>> {
    size_t operator()(const std::reference_wrapper<T>& ref) const {
        return std::hash<T*>()(&ref.get());
    }
};

template <typename T>
struct ReferenceWrapperEqual {
    bool operator()(const std::reference_wrapper<T>& lhs,
                    const std::reference_wrapper<T>& rhs) const {
        return &lhs.get() == &rhs.get();
    }
};
}

#endif // STDEXTENSION_H

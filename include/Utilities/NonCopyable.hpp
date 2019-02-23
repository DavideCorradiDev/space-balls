#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

namespace mnk {

class NonCopyable {
public:
    NonCopyable() {}
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

}

#endif // NONCOPYABLE_HPP

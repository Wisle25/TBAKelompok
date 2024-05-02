#pragma once

#include <functional>
#include <stdexcept>

template<typename... Args>
class Delegate;

template<typename R, typename... Args>
class Delegate<R(Args...)> {
private:
    struct BaseDelegate {
        virtual R Invoke(Args...) = 0;
    };

    template<typename T>
    struct MemberDelegate : public BaseDelegate {
        T* obj;
        R(T::*func)(Args...);

        MemberDelegate(T* obj, R(T::*func)(Args...)) : obj(obj), func(func) {}

        R Invoke(Args... args) override {
            return (obj->*func)(args...);
        }
    };

    struct StaticDelegate : public BaseDelegate {
        using FuncPtr = R(*)(Args...);
        FuncPtr func;

        StaticDelegate(FuncPtr func) : func(func) {}

        R Invoke(Args... args) override {
            return (*func)(args...);
        }
    };

    BaseDelegate* delegate = nullptr;

public:
    template<typename T>
    void Bind(T* obj, R(T::*func)(Args...)) {
        delegate = new MemberDelegate<T>(obj, func);
    }

    void Bind(R(*func)(Args...)) {
        delegate = new StaticDelegate(func);
    }

    R Execute(Args... args) {
        if (delegate) {
            return delegate->Invoke(args...);
        }
        throw std::bad_function_call();
    }

    const bool IsBinded() const
    {
        return dynamic_cast<BaseDelegate*>(delegate) != nullptr;
    }

    ~Delegate() {
        delete delegate;
    }
};
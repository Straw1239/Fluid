#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED

template <int First, int Last>
struct static_for
{
    template <typename Fn>
    inline void operator()(Fn const& fn) const
    {
        if (First < Last)
        {
            fn(First);
            static_for<First+1, Last>()(fn);
        }
    }
};

template <int N>
struct static_for<N, N>
{
    template <typename Fn>
    inline void operator()(Fn const& fn) const
    { }
};


#endif // UTIL_HPP_INCLUDED

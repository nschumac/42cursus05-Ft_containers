#ifndef CHOOSE_HPP
# define CHOOSE_HPP

namespace ft
{

    template <bool isConst, typename first, typename second>
    struct choose;

    template <typename first, typename second>
    struct choose<true, first, second>
    {
        typedef first type;
    };

    template <typename first, typename second>
    struct choose<false, first, second>
    {
        typedef second type;
    };


}

#endif

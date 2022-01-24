#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{

    template <bool B>
    struct enable_if;

    template <>
    struct enable_if<true> { typedef int type; };

    template <class T>
    struct is_integral { static bool const value = false; };

    template <>
    struct is_integral <bool> { static bool const value = true; };

    template <>
    struct is_integral <char> { static bool const value = true; };
	
    template <>
    struct is_integral <unsigned char> { static bool const value = true; };

    template <>
    struct is_integral <wchar_t> { static bool const value = true; };

    template <>
    struct is_integral <short> { static bool const value = true; };

    template <>
    struct is_integral <unsigned short> { static bool const value = true; };

    template <>
    struct is_integral <int> { static bool const value = true; };

    template <>
    struct is_integral <unsigned int> { static bool const value = true; };

    template <>
    struct is_integral <long> { static bool const value = true; };
	
    template <>
    struct is_integral <unsigned long> { static bool const value = true; };

    template <>
    struct is_integral <long long> { static bool const value = true; };
	
    template <>
    struct is_integral <unsigned long long> { static bool const value = true; };


}

#endif

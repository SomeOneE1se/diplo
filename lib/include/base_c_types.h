#ifndef BASE_C_TYPES_H
#define BASE_C_TYPES_H

enum E_OPER
{
    SUCCESS = 0,
    FAILURE = 1
};

enum E_FLAG
{
    FALSE = 0,
    TRUE  = 1
};

typedef enum E_OPER       TOper;
typedef enum E_FLAG       TFlag;

typedef char              TChar;
typedef short             TShort;
typedef int               TInt;
typedef long int          TLong;
typedef float             TFloat;
typedef double            TDouble;

typedef unsigned char     TUChar;
typedef signed char       TSChar;
typedef unsigned short    TUShort;
typedef signed short      TSShort;
typedef unsigned int      TUInt;
typedef signed int        TSInt;
typedef unsigned long int TULong;
typedef signed long int   TSLong;

enum
{
    X,
    Y,
    Z
};
enum
{
    P,
    R,
    K
};

#endif  // BASE_C_TYPES_H

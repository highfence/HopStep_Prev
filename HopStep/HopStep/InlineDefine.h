#pragma once

#define WorkingOnLib 0

#if WorkingOnLib
    #define InternalProperty inline
#else
    #define InternalProperty 
#endif
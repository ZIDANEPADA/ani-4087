#pragma once

#ifdef TEST_HPP



class calculatrice{
    public:
        int add(int a, int b);
        int sub(int a, int b);
        int mul(int a, int b);
};
#else

class calculatrice{
};

#endif 
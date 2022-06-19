#include <iostream>
#include <vector>
#include <map>

int main(int argc, char ** argv)
{
    std::vector<int> x = {1,2,3,4,5,6};
    for(auto & y : x)
    {
        std::cout << y << std::endl;
    }
    return 0;
}

#include "../include/monotonous_subarray.hpp"

std::pair<size_t, size_t> find_max_monotonous_subarray(const std::vector<int>& numbers) {
    
    int startUp = 0;
    int startDown = 0;
    int maxUp_ind = 0;
    int maxDown_ind = 0;

    auto size = numbers.size();

    int maxCountUp = 0;
    int maxCountDown = 0;

    if(numbers.empty() ) {
        return {0,0};
    }
    /*
    [2, 7, 5, 3] -> [1, 3]
    [1, 1] -> [1, 1] // or [0, 0]
    */
    for(int i = 1; i < size; ++i) {
        if( numbers[i] - numbers[i - 1 ] > 0 ) { // up
            startDown = i;
            if(i - startUp > maxCountUp) {
                maxCountUp = i - startUp;
                maxUp_ind = i;
            }
        } else if ( numbers[i] - numbers[i - 1 ] < 0 ) { // down
            startUp = i;
            if(i - startDown > maxCountDown) {
                maxCountDown = i - startDown;
                maxDown_ind = i;
            } else {
                startUp = i;
                startDown = i;
            }
        }
    }
    return maxCountUp > maxCountDown ? 
        std::make_pair<size_t, size_t>( startUp  , startUp + maxCountUp  ) : 
        std::make_pair<size_t, size_t>(startDown , startDown + maxCountDown );
}   
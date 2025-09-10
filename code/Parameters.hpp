#pragma once

struct Parameters {
    // score increase per necessary access
    size_t f_a;
    // score increase per used KiB (started/rounded up)
    size_t f_s;
    // name of the data/query pair used for evaluation
    std::string filename;

    Parameters(char* arg1, char* arg2, char* arg3) : 
        f_a(atoi(arg1)), f_s(atoi(arg2)), filename(arg3){}
};
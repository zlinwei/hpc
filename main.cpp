#include <iostream>
#include <openacc.h>
#include <omp.h>

int main() {
    std::cout << acc_get_device_num(acc_device_host) << std::endl;
    std::cout << omp_get_max_threads() << std::endl;

#pragma omp parallel
    {
        std::cout << "Hello, World! " << omp_get_thread_num() << std::endl;
    };
    return 0;
}
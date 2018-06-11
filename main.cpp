#include <iostream>
#include <openacc.h>
#include <omp.h>
#include <mpi.h>

#include <cstdio>

int main() {
    std::cout << "acc device num: " << acc_get_device_num(acc_device_host) << std::endl;
    std::cout << "omp max threads: " << omp_get_max_threads() << std::endl;


#pragma omp parallel
    {
        std::cout << omp_get_thread_num();
    };
    std::cout << std::endl;

    int a[10] = {0};

#pragma acc parallel loop
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
        printf("%d", i);
    }

    std::cout << std::endl;
#pragma omp parallel for
    for (int j = 0; j < 10; ++j) {
        std::cout << a[j];
    }
    std::cout << std::endl;

    return 0;
}
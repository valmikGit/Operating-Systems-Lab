#include <stdio.h>
#include <sys/resource.h>

void print_resource_limit(int resource) {
    struct rlimit rlim;
    if (getrlimit(resource, &rlim) == 0) {
        printf("Resource %d limit:\n", resource);
        printf("  Soft limit: %ld\n", rlim.rlim_cur);
        printf("  Hard limit: %ld\n", rlim.rlim_max);
    } else {
        perror("getrlimit");
    }
}

int main() {
    printf("Printing system resource limits:\n");
    print_resource_limit(RLIMIT_CPU);       // CPU time limit
    print_resource_limit(RLIMIT_FSIZE);     // File size limit
    print_resource_limit(RLIMIT_DATA);      // Data segment size limit
    print_resource_limit(RLIMIT_STACK);     // Stack size limit
    print_resource_limit(RLIMIT_CORE);      // Core file size limit
    print_resource_limit(RLIMIT_RSS);       // Resident set size limit
    print_resource_limit(RLIMIT_NOFILE);    // Number of open files limit
    // Add more resource limits as needed

    return 0;
}

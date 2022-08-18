#define __CL_ENABLE_EXCEPTIONS
// #define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>
#include <iostream>
#include <vector>

int main()
{
    // Get all platforms (vendor specific implementation, e.g. Nvidia, Intel, AMD)
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Throw error if there is none
    if (platforms.size() == 0)
    {
        std::cout << "No OpenCL platforms found." << std::endl;
        exit(1);
    }

    std::cout << "Platforms:" << std::endl;
    for (auto platform : platforms)
    {
        std::cout << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
    }
    std::cout << std::endl;

    // Select the first in the array of platforms
    cl::Platform platform = platforms.front();

    // Get all devices using selected platform
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    // Throw error if there is none
    if (devices.size() == 0)
    {
        std::cout << "No devices found." << std::endl;
        exit(1);
    }

    std::cout << "Devices:" << std::endl;
    for (auto device : devices)
    {
        std::cout << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    }
    std::cout << std::endl;

    cl::Device device = devices.front();
    // std::cout << "Device vendor: " << device.getInfo<CL_DEVICE_VENDOR>() << std::endl;
    // std::cout << "Device version: " << device.getInfo<CL_DEVICE_VERSION>() << std::endl;
}
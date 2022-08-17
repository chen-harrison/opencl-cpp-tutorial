#include "opencl_helper.h"

cl::Program createProgram(const std::string& file)
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    cl::Platform platform = platforms.front();

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    cl::Device device = devices.front();

    // Load text from .cl file and move to string
    std::ifstream file_stream(file);
    std::string   src(std::istreambuf_iterator<char>(file_stream),
                    (std::istreambuf_iterator<char>()));

    // vector<std::pair<const char*, size_type> >, each element is input text (and its size)
    cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

    // Context: environment in which kernels execute
    // Includes one or multiple devices, device memory, one or multiple command-queues
    cl::Context context(device);

    // Program: encapsulates context, program sources (from .cl files), target devices and build
    // options
    cl::Program program(context, sources);

    auto err = program.build("-cl-std=CL1.2");

    return program;
}
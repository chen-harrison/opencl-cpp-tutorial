/****************************************************************************
 * HOST PROGRAM
 * 1. Define the platform ... platform = devices+context+queues
 * 2. Create and Build the program (dynamic library for kernels)
 * 3. Setup memory objects
 * 4. Define the kernel (attach arguments to kernel function)
 * 5. Submit commands ... transfer memory objects and execute kernels
 ****************************************************************************/

#include "opencl_helper.h"

int main()
{
    cl::Program             program = createProgram("hello_world.cl");
    cl::Context             context = program.getInfo<CL_PROGRAM_CONTEXT>();
    std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::Device&             device  = devices.front();

    char buf[16];
    // For flags, device performing calc can only write (it's receiving garbage) but we want host to
    // read what is returned
    cl::Buffer mem_buf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
    cl::Kernel kernel(program, "helloWorld");
    kernel.setArg(0, mem_buf);

    cl::CommandQueue queue(context, device);
    // Execute
    queue.enqueueTask(kernel);
    // Read global memory (mem_buf) into memory on host side (buf);
    queue.enqueueReadBuffer(mem_buf, CL_TRUE, 0, sizeof(buf), buf);

    std::cout << buf;
}
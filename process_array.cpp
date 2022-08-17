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
    cl::Program             program = createProgram("process_array.cl");
    cl::Context             context = program.getInfo<CL_PROGRAM_CONTEXT>();
    std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::Device&             device  = devices.front();

    std::vector<int> vec(1024);
    std::fill(vec.begin(), vec.end(), 1);

    cl::Buffer in_buf(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
                      sizeof(int) * vec.size(), vec.data());
    cl::Buffer out_buf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                       sizeof(int) * vec.size());
    cl::Kernel kernel(program, "processArray");
    kernel.setArg(0, in_buf);
    kernel.setArg(1, out_buf);

    cl::CommandQueue queue(context, device);
    queue.enqueueFillBuffer(in_buf, 3, sizeof(int) * 10, sizeof(int) * (vec.size() - 10));
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec.size()));
    queue.enqueueReadBuffer(out_buf, CL_FALSE, 0, sizeof(int) * vec.size(), vec.data());

    cl::finish();

    std::cout << vec.at(20) << std::endl;
}
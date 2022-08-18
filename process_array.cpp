#include "opencl_helper.h"

int main()
{
    cl::Program             program = createProgram("process_array.cl");
    cl::Context             context = program.getInfo<CL_PROGRAM_CONTEXT>();
    std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::Device&             device  = devices.front();

    std::vector<int> vec(1024);
    std::fill(vec.begin(), vec.end(), 1);

    // input: kernel should only read, host shouldn't read/write, passing vec in via copy
    // (instead of pin, etc.)
    cl::Buffer in_buf(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
                      sizeof(int) * vec.size(), vec.data());
    cl::Buffer out_buf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                       sizeof(int) * vec.size());
    cl::Kernel kernel(program, "processArray");
    kernel.setArg(0, in_buf);
    kernel.setArg(1, out_buf);

    cl::CommandQueue queue(context, device);
    // another way to fill buffer, e.g. fill with 3 starting at idx 10
    queue.enqueueFillBuffer(in_buf, 3, sizeof(int) * 10, sizeof(int) * (vec.size() - 10));
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec.size()));
    queue.enqueueReadBuffer(out_buf, CL_FALSE, 0, sizeof(int) * vec.size(), vec.data());

    cl::finish();

    for (int i = 0; i < 20; i++)
    {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
}
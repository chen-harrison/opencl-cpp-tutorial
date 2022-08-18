#include "opencl_helper.h"

#include <array>

int main()
{
    cl::Program             program = createProgram("process_array.cl");
    cl::Context             context = program.getInfo<CL_PROGRAM_CONTEXT>();
    std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::Device&             device  = devices.front();

    // int arr[3][2]
    const int                                       num_rows = 3;
    const int                                       num_cols = 2;
    const int                                       count    = num_rows * num_cols;
    std::array<std::array<int, num_cols>, num_rows> arr      = {{{1, 1}, {2, 2}, {3, 3}}};

    cl::Buffer buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                   sizeof(int) * count, arr.data());
    cl::Kernel kernel(program, "processMultidim");
    kernel.setArg(0, buf);

    cl::CommandQueue queue(context, device);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(num_rows, num_cols));
    queue.enqueueReadBuffer(buf, CL_TRUE, 0, sizeof(int) * count, arr.data());

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
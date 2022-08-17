#ifndef OPENCL_HELPER_H
#define OPENCL_HELPER_H

#define __CL_ENABLE_EXCEPTIONS
#include "opencl_helper.h"

#include <CL/cl.hpp>
#include <fstream>
#include <iostream>
#include <vector>

cl::Program createProgram(const std::string& file);

#endif // OPENCL_HELPER_H
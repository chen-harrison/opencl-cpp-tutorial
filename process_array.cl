__kernel void processArray(__global int* data, __global int* out_data)
{
    out_data[get_global_id(0)] = data[get_global_id(0)] * 2;
}
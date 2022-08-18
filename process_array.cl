__kernel void processArray(__global int* data, __global int* out_data)
{
    out_data[get_global_id(0)] = data[get_global_id(0)] * 2;
}

__kernel void processMultidim(__global int* data)
{
    size_t id = get_global_id(0) * get_global_size(1) + get_global_id(1);
    data[id] = data[id] * 2;
}
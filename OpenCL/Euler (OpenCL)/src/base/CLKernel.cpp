#include <iostream> // cout, endl
#include <sys/stat.h> // file stat for file size in kernel
#include <cstdarg> // varargs for kernel
#include <cstdio> // fopen, fread
#include <fstream> // ifstream

#include "CLKernel.h"
#include "config.h"

CLKernel::CLKernel(int s)
{
   localsize = s;
   released = false;
}

void CLKernel::error(int errno, std::string msg)
{
	std::cout << "ERROR::: (" << errno << ") " << msg << std::endl;
	switch (errno)
	{
		case CL_DEVICE_NOT_FOUND:
			std::cout << "CL_DEVICE_NOT_FOUND";
			break;
		case CL_DEVICE_NOT_AVAILABLE:
			std::cout << "CL_DEVICE_NOT_AVAILABLE";
			break;
		case CL_COMPILER_NOT_AVAILABLE:
			std::cout << "CL_COMPILER_NOT_AVAILABLE";
			break;
		case CL_MEM_OBJECT_ALLOCATION_FAILURE:
			std::cout << "CL_MEM_OBJECT_ALLOCATION_FAILURE";
			break;
		case CL_OUT_OF_RESOURCES:
			std::cout << "CL_OUT_OF_RESOURCES";
			break;
		case CL_OUT_OF_HOST_MEMORY:
			std::cout << "CL_OUT_OF_HOST_MEMORY";
			break;
		case CL_PROFILING_INFO_NOT_AVAILABLE:
			std::cout << "CL_PROFILING_INFO_NOT_AVAILABLE";
			break;
		case CL_MEM_COPY_OVERLAP:
			std::cout << "CL_MEM_COPY_OVERLAP";
			break;
		case CL_IMAGE_FORMAT_MISMATCH:
			std::cout << "CL_IMAGE_FORMAT_MISMATCH";
			break;
		case CL_IMAGE_FORMAT_NOT_SUPPORTED:
			std::cout << "CL_IMAGE_FORMAT_NOT_SUPPORTED";
			break;
		case CL_BUILD_PROGRAM_FAILURE:
			std::cout << "CL_BUILD_PROGRAM_FAILURE";
			break;
		case CL_MAP_FAILURE:
			std::cout << "CL_MAP_FAILURE";
			break;
		case CL_MISALIGNED_SUB_BUFFER_OFFSET:
			std::cout << "CL_MISALIGNED_SUB_BUFFER_OFFSET";
			break;
		case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
			std::cout << "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
			break;
		case CL_INVALID_VALUE:
			std::cout << "CL_INVALID_VALUE";
			break;
		case CL_INVALID_DEVICE_TYPE:
			std::cout << "CL_INVALID_DEVICE_TYPE";
			break;
		case CL_INVALID_PLATFORM:
			std::cout << "CL_INVALID_PLATFORM";
			break;
		case CL_INVALID_DEVICE:
			std::cout << "CL_INVALID_DEVICE";
			break;
		case CL_INVALID_CONTEXT:
			std::cout << "CL_INVALID_CONTEXT";
			break;
		case CL_INVALID_QUEUE_PROPERTIES:
			std::cout << "CL_INVALID_QUEUE_PROPERTIES";
			break;
		case CL_INVALID_COMMAND_QUEUE:
			std::cout << "CL_INVALID_COMMAND_QUEUE";
			break;
		case CL_INVALID_HOST_PTR:
			std::cout << "CL_INVALID_HOST_PTR";
			break;
		case CL_INVALID_MEM_OBJECT:
			std::cout << "CL_INVALID_MEM_OBJECT";
			break;
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
			std::cout << "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
			break;
		case CL_INVALID_IMAGE_SIZE:
			std::cout << "CL_INVALID_IMAGE_SIZE";
			break;
		case CL_INVALID_SAMPLER:
			std::cout << "CL_INVALID_SAMPLER";
			break;
		case CL_INVALID_BINARY:
			std::cout << "CL_INVALID_BINARY";
			break;
		case CL_INVALID_BUILD_OPTIONS:
			std::cout << "CL_INVALID_BUILD_OPTIONS";
			break;
		case CL_INVALID_PROGRAM:
			std::cout << "CL_INVALID_PROGRAM";
			break;
		case CL_INVALID_PROGRAM_EXECUTABLE:
			std::cout << "CL_INVALID_PROGRAM_EXECUTABLE";
			break;
		case CL_INVALID_KERNEL_NAME:
			std::cout << "CL_INVALID_KERNEL_NAME";
			break;
		case CL_INVALID_KERNEL_DEFINITION:
			std::cout << "CL_INVALID_KERNEL_DEFINITION";
			break;
		case CL_INVALID_KERNEL:
			std::cout << "CL_INVALID_KERNEL";
			break;
		case CL_INVALID_ARG_INDEX:
			std::cout << "CL_INVALID_ARG_INDEX";
			break;
		case CL_INVALID_ARG_VALUE:
			std::cout << "CL_INVALID_ARG_VALUE";
			break;
		case CL_INVALID_ARG_SIZE:
			std::cout << "CL_INVALID_ARG_SIZE";
			break;
		case CL_INVALID_KERNEL_ARGS:
			std::cout << "CL_INVALID_KERNEL_ARGS";
			break;
		case CL_INVALID_WORK_DIMENSION:
			std::cout << "CL_INVALID_WORK_DIMENSION";
			break;
		case CL_INVALID_WORK_GROUP_SIZE:
			std::cout << "CL_INVALID_WORK_GROUP_SIZE";
			break;
		case CL_INVALID_WORK_ITEM_SIZE:
			std::cout << "CL_INVALID_WORK_ITEM_SIZE";
			break;
		case CL_INVALID_GLOBAL_OFFSET:
			std::cout << "CL_INVALID_GLOBAL_OFFSET";
			break;
		case CL_INVALID_EVENT_WAIT_LIST:
			std::cout << "CL_INVALID_EVENT_WAIT_LIST";
			break;
		case CL_INVALID_EVENT:
			std::cout << "CL_INVALID_EVENT";
			break;
		case CL_INVALID_OPERATION:
			std::cout << "CL_INVALID_OPERATION";
			break;
		case CL_INVALID_GL_OBJECT:
			std::cout << "CL_INVALID_GL_OBJECT";
			break;
		case CL_INVALID_BUFFER_SIZE:
			std::cout << "CL_INVALID_BUFFER_SIZE";
			break;
		case CL_INVALID_MIP_LEVEL:
			std::cout << "CL_INVALID_MIP_LEVEL";
			break;
		case CL_INVALID_GLOBAL_WORK_SIZE:
			std::cout << "CL_INVALID_GLOBAL_WORK_SIZE";
			break;
		case CL_INVALID_PROPERTY:
			std::cout << "CL_INVALID_PROPERTY";
			break;
		default:
			std::cout << "Unknown ERROR";
			break;
	}
	std::cout << std::endl;
}

bool CLKernel::init(const char* file, const char* kernelFunction)
{
   setCLFile(file);
   if (!init())
      return false;
   if (!setupOpenCLKernel(kernelFunction))
      return false;
   return true;
}

bool CLKernel::discover()
{
   int errno;
   released = false;

	cl_uint available;
   // check the platform
	errno = clGetPlatformIDs(0, NULL, &available);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Failed to find any OpenCL platform.");
      return false;
   }
	cl_platform_id* my_platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * available);
   errno = clGetPlatformIDs(available, my_platforms, &available);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Failed to find an OpenCL platform.");
      return false;
   }

	for (cl_uint ii = 0; ii < available; ii++)
	{
      std::cout << "Platform number " << ii << std::endl;
		// get the devices
      cl_uint dev_available;
		errno = clGetDeviceIDs(my_platforms[ii], CL_DEVICE_TYPE_ALL, 0, NULL, &dev_available);
      if (errno != CL_SUCCESS)
      {
         error(errno,"Failed to query OpenCL platform");
         continue;
      }
      cl_device_id* my_devices = (cl_device_id*)malloc(sizeof(cl_device_id)*dev_available);
		errno = clGetDeviceIDs(my_platforms[ii], CL_DEVICE_TYPE_ALL, dev_available, my_devices, NULL);
      if (errno != CL_SUCCESS)
      {
         if (errno == CL_INVALID_PLATFORM)
            error(errno,"Invalid Platform");
         else if (errno == CL_INVALID_VALUE)
            error(errno,"Invalid Value");
         else if (errno == CL_DEVICE_NOT_FOUND)
            error(errno,"Device Not Found");
         else if (errno == CL_INVALID_DEVICE_TYPE)
            error(errno,"Invalid Device Type");
         error(errno,"Failed to query get platform devices");
         continue;
      }
      for (cl_uint jj = 0; jj < dev_available; jj++)
      {
         device_id = my_devices[jj];
         char buffer[10240];
         cl_uint buf_uint;
         cl_ulong buf_ulong;
         std::cout << "Device number " << jj << std::endl;
         errno = clGetDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(buffer),
               buffer, NULL);
         if (errno == CL_SUCCESS)
         {
            std::cout << "   Name: " << buffer << std::endl;
         }
         errno = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, 
               sizeof(buf_uint), &buf_uint, NULL);
         if (errno == CL_SUCCESS)
         {
            std::cout << "   Max Compute Units: " << buf_uint << std::endl;
         }
         errno = clGetDeviceInfo(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, 
               sizeof(buf_uint), &buf_uint, NULL);
         if (errno == CL_SUCCESS)
         {
            std::cout << "   Max Clock Frequency (MHz): " << buf_uint << std::endl;
         }
         errno = clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, 
               sizeof(buf_ulong), &buf_ulong, NULL);
         if (errno == CL_SUCCESS)
         {
            std::cout << "   Global Memory Size (MB): " << (buf_ulong / 1024.0 / 1024.0) << std::endl;
         }
         errno = clGetDeviceInfo(device_id, CL_DEVICE_LOCAL_MEM_SIZE,
					sizeof(buf_ulong), &buf_ulong, NULL);
			if (errno == CL_SUCCESS)
			{
				std::cout << "   Local Memory Size (kB): " << (buf_ulong / 1024.0) << std::endl;
			}
			errno = clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
					sizeof(buf_uint), &buf_uint, NULL);
			if (errno == CL_SUCCESS)
			{
				std::cout << "   Local Workgroup Dimensions: " << buf_uint << std::endl;
			}
			size_t buf_st_arr[buf_uint];
			errno = clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
					sizeof(size_t)*buf_uint, &buf_st_arr, NULL);
			if (errno == CL_SUCCESS)
			{
				std::cout << "   Local Workgroup Sizes:";
				for (cl_uint ii = 0; ii < buf_uint; ii++)
				{
					std::cout << " " << buf_st_arr[ii];
				}
				std::cout << std::endl;
			}
      }
	}
   return true;
}


bool CLKernel::init()
{
   int errno;
   released = false;

	cl_uint available;
   // check the platform
	errno = clGetPlatformIDs(0, NULL, &available);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Failed to find any OpenCL platform.");
      return false;
   }
	cl_platform_id* my_platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * available);
   errno = clGetPlatformIDs(available, my_platforms, &available);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Failed to find an OpenCL platform.");
      return false;
   }

	for (cl_uint ii = 0; ii < available; ii++)
	{
		// get the devices, looking for GPUs
		int devType = atoi(Config::Instance().getValue("devicetype").c_str());
		errno = clGetDeviceIDs(my_platforms[ii], devType, 1, &device_id, NULL);
		if (errno == CL_SUCCESS)
			break; // we found one!
	}
	if (errno != CL_SUCCESS)
	{
		if (errno == CL_INVALID_PLATFORM)
			error(errno,"Invalid Platform");
		else if (errno == CL_INVALID_VALUE)
			error(errno,"Invalid Value");
		else if (errno == CL_DEVICE_NOT_FOUND)
			error(errno,"Device Not Found");
		else if (errno == CL_INVALID_DEVICE_TYPE)
			error(errno,"Invalid Device Type");
		return false;
	}

   // create a compute context
   if(!(context = clCreateContext(0,1,&device_id,NULL,NULL,&errno)))
   {
      error(errno,"Failed to create a compute context.");
      return false;
   }

   if (!(queue = clCreateCommandQueue(context,device_id,0,&errno)))
   {
      error(errno,"Failed to create a command queue.");
      return false;
   }

   return true;
}

bool CLKernel::setupOpenCLKernel(const char* kernelFunction)
{
	// Check that a filename was given
   if (cl_filename[0] == 0)
   {
      error(0,"No CL Kernel file specified.");
      return false;
   }

   // Check if the file exists
   std::ifstream file(cl_filename);
   if (!file)
   {
      error(1,cl_filename + std::string(" doesn't exist"));
      return false;
   }

	// fread the file into source
   struct stat statbuf;
   FILE* fh;
   char* source;

   fh = fopen(cl_filename, "r");
   if (fh == 0)
   {
      error(0,std::string("Could not open file") + cl_filename);
      return false;
   }

   stat(cl_filename, &statbuf);
   source = (char*) malloc(statbuf.st_size + 1);
   size_t result = fread(source, statbuf.st_size, 1, fh);
   if (result != 1)
   {
   	error(0,std::string("Failed to read compute program.") + cl_filename);
   }
   source[statbuf.st_size] = '\0';

   if (!source)
   {
      error(0,std::string("Failed to load compute program from file.") + cl_filename);
      return false;
   }

   return setupOpenCLKernelWithSource(source, kernelFunction);
}

bool CLKernel::setupOpenCLKernelWithSource(const char* source, const char* kernelFunction)
{
	int errno;

   // create the compute program from the source buffer
   if (!(program = clCreateProgramWithSource(context,1, (const char**) & source,
               NULL, &errno)))
   {
      error(errno,"Failed to create compute program.");
      return false;
   }

   errno = clBuildProgram(program,0,NULL,NULL,NULL,NULL);
   if (errno != CL_SUCCESS)
   {
      size_t len;
      char buffer[2048];
      error(errno,"Failed to build program executable.");
      clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
            sizeof(buffer), buffer, &len);
      std::cout << buffer << std::endl;
      return false;
   }

   // create the compute kernel in the program we wish to run
   kernel = clCreateKernel(program, kernelFunction, &errno);
   if (!kernel || errno != CL_SUCCESS)
   {
      error(errno,"Failed to create compute kernel.");
      return false;
   }

   return true;
}

bool CLKernel::setupOpenCLKernelArgs(int argno, ...)
{
   va_list arguments;
   
   va_start(arguments, argno);
   for (int ii = 0; ii < argno; ii++)
   {
      int size = va_arg(arguments, int);
      const void* object = va_arg(arguments, void*);

      int errno = clSetKernelArg(kernel,ii,size,object);
      if (errno != CL_SUCCESS)
      {
         error(errno,"Failed to set kernel arguments for arg " + to_string(ii) + ":" + to_string(size));
         return false;
      }
   }
   va_end(arguments);
   return true;
}

bool CLKernel::launchKernel(long numKernels, int workgroupSize)
{
   size_t globalsize = numKernels;
   size_t worksize = workgroupSize;

   if (numKernels % localsize != 0)
   {
      error(0,"Number of threads must be a multiple of localsize.");
      return false;
   }

   // launch kernel
   int errno = worksize == 0 ?
   		clEnqueueNDRangeKernel(queue,kernel,1,NULL,&globalsize,
   					NULL,0,NULL,NULL) :
         clEnqueueNDRangeKernel(queue,kernel,1,NULL,&globalsize,
                  &worksize,0,NULL,NULL);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Kernel problem.");
      return false;
   }

   return true;
}

void CLKernel::releaseKernel()
{
   // otherwise we get a seg fault
   if (released)
      return;
   clReleaseProgram(program);
   clReleaseKernel(kernel);
   clReleaseCommandQueue(queue);
   clReleaseContext(context);
   released = true;
}

void CLKernel::waitForQueue()
{
   clFinish(queue);
}

bool CLKernel::createReadOnlyMemory(int size, cl_mem* mem)
{
   *mem = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, NULL);
   if (!(*mem))
   {
      error(0,"Failed to allocate device memory.");
      return false;
   }

   return true;
}

bool CLKernel::createReadWriteMemory(int size, cl_mem* mem)
{
   *mem = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, NULL);
   if (!(*mem))
   {
      error(0,"Failed to allocate device memory.");
      return false;
   }

   return true;
}

bool CLKernel::createWriteOnlyMemory(int size, cl_mem* mem)
{
   *mem = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, NULL);
   if (!(*mem))
   {
      error(0,"Failed to allocate device memory.");
      return false;
   }

   return true;
}

bool CLKernel::transferGPUObjectToCPU(int size, cl_mem* gpuObject, void* cpuObject)
{
	int errno = clEnqueueReadBuffer(queue, *gpuObject, CL_TRUE, 0,
            size, cpuObject, 0, NULL, NULL);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Failed to read output array.");
      return false;
   }
   return true;
}

bool CLKernel::transferCPUObjectToGPU(int size, cl_mem* gpuObject, void* cpuObject)
{
   int errno = clEnqueueWriteBuffer(queue, *gpuObject, CL_TRUE, 0,
         size, cpuObject, 0, NULL, NULL);
   if (errno != CL_SUCCESS)
   {
      error(errno,"Failed to write source array.");
      return false;
   }
   return true;
}
   
CLKernel::~CLKernel()
{
   releaseKernel();
}

#ifndef CLKERNEL_H
#define CLKERNEL_H

#include <CL/cl.h>
#include <CL/opencl.h>
#include <iostream>
#include <string>
#include <sstream>

class CLKernel
{
   private:
      int localsize;                  // size multiple for threading
      cl_device_id      device_id;    // compute device id
      cl_context        context;      // compute context
      cl_command_queue  queue;        // compute command queue
      cl_program        program;      // compute program
      cl_kernel         kernel;       // compute kernel
      const char*       cl_filename;  // filename containing the kernel

      bool released;
      void error(int,std::string);



		template <typename T>
		std::string to_string(T value)
		{
			std::ostringstream os;
			os << value;
			return os.str();
		}

   public:
      CLKernel(int);
      // set the filename
      void setCLFile(const char* filename) 
            { cl_filename = filename; }
      // create the platform, devices_id, context, and queue
      bool init();
      // find and print available devices and platforms
      bool discover();
      // creates the program
      bool setupOpenCLKernel(const char*);
      // creates the program out of source data
      bool setupOpenCLKernelWithSource(const char*, const char*);
      // does setCLFile, init, and setupOpenCLKernel
      bool init(const char*, const char*);
      // supplies the arguments to the program in format:
      // #args,arg1 size,&arg1,arg2 size,&arg2 ...etc. In this case
      // first argument would be 2
      bool setupOpenCLKernelArgs(int, ...); 
      // launch this number of kernels
      bool launchKernel(long,int = 0);

      // blocking wait for kernels to finish
      void waitForQueue();
      // clean up (delete also cleans)
      void releaseKernel();

      bool createReadOnlyMemory(int, cl_mem*);  // depends on context
      bool createReadWriteMemory(int, cl_mem*); // depends on context
      bool createWriteOnlyMemory(int, cl_mem*); // depends on context
      bool transferGPUObjectToCPU(int, cl_mem*, void*);
      bool transferCPUObjectToGPU(int, cl_mem*, void*);

      ~CLKernel();

};

#endif

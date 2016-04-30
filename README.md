# NCTU EE 2016 Spring Computer Organization Final Project
This program will blur and sharpen three images under directory "Images" respectively and save the results in directory "Output".

Your job is to improve the cache perfromance on the riscv-isa-simulator, spike, through software and hardware (modify the simulator) appraoches.

## Introduction
Image bluring/unsharping are two of the most important techniques in digital image processing used often in daily life to remove noise and enhance image quality. They are basically doing 2D-convolution with a low-pass/high-pass filter onto an image. Please check the following links to obtain more information: [convolution](https://en.wikipedia.org/wiki/Convolution), [bluring](http://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm) and [unsharping](http://homepages.inf.ed.ac.uk/rbf/HIPR2/unsharp.htm).
There are many opportunities to improve the performance of doing the 2D-convolution through software and hardware approaches. In this project, we aim on the L1 cache performance on riscv architecture with the riscv isa simulator - spike. You are asked to finished the job by both of the software and hardware approaches.

## Environment Setup
To get the simulator - spike and the compiler for riscv architecture, you have to download the source code of riscv-tools from our lab's repository and compile it by yourself. Use following commands to get the code and finish the installation by following the guides on the repository page - [riscv-tools](https://github.com/nctu-pcslab/riscv-tools)
> $ git clone https://github.com/nctu-pcslab/riscv-tools.git

Note: You have to install at least riscv-fesvr, riscv-gnu-toolchain, riscv-isa-sim and riscv-pk to complete the jobs in this project.

## Compile the given program from source code
Once you get the needed tools, you can use the belowing commands to compile our source code. It will generate the binary of our main program - bns-riscv and the testing program - checker. Then, use spike to run our program and test it right after the execution.

	$ make 
	$ make run

You may want to test the program first on your host machine. Similarly, you can use these commands to do it.
	
	$ make host
	$ make run-host

## Tasks requirements
### Task 1
### Task 2

## Grading Policy

## Acknowledgments

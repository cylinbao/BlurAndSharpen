# NCTU EE 2016 Spring Computer Organization Final Project
This program will blur and sharpen three images under directory "Images" respectively and save the results in directory "Output".

Your job is to improve the cache perfromance on the riscv-isa-simulator, spike, through software and hardware (modify the simulator) appraoches.

## Introduction
Image bluring/unsharping are two of the most important techniques in digital image processing used often in daily life to remove noise and enhance image quality. They are basically doing 2D-convolution with a low-pass/high-pass filter onto an image. Please check the following links to obtain more information: [convolution](https://en.wikipedia.org/wiki/Convolution), [bluring](http://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm) and [unsharping](http://homepages.inf.ed.ac.uk/rbf/HIPR2/unsharp.htm).
There are many opportunities to improve the performance of doing the 2D-convolution through software and hardware approaches. In this project, we aim on the L1 cache performance on riscv architecture with the riscv isa simulator - spike. You are asked to finished the job by both of the software and hardware approaches.

## Environment Setup
To get the simulator - spike and the compiler for riscv architecture, you have to download the source code of riscv-tools from our lab's repository and compile it by yourself. Use following commands to get the code and finish the installation by refering the guides on the repository page - [riscv-tools](https://github.com/nctu-pcslab/riscv-tools)
	
	$ git clone https://github.com/nctu-pcslab/riscv-tools.git

Note: You have to install at least riscv-fesvr, riscv-gnu-toolchain, riscv-isa-sim and riscv-pk to complete the jobs in this project.

## Compile the given program from source code
Once you get the needed tools, you can use the belowing commands to compile our source code. It will generate the binary of our main program - bns-riscv and the testing program - checker. Then, use spike to run our program and test it right after the execution.

	$ make 
	$ make run

You may want to test the program first on your host machine. Similarly, you can use these commands to do it.
	
	$ make host
	$ make run-host

## Task requirements
### Task 1 - Software approach (Due date: 5/31 23:59)
TA has provided the reference code. In the program, it will get three input images, apply two different filters respectively  and generate 6 (2X3) outputs stored under "Output" directory. You can read previous descriptoin to know how to use this reference code. But due to the limited programming skills of TA. The reference program looks like has extremely poor cache performance. Please use your solid computer organization knowledge and ultimate coding techniques to rewrite the program and make it work better. 
Note: Task 1.1 plus task 1.2 will be responsible for the total points in the complteness part (40% in total. Please check the grading policy)
#### 1.1 Modify the given blur-and-sharp program to gain better performance(bns.c) (25%)
* Try to understand what is image bluring and sharpening, what is 2D-convolution and what does the reference code do first.
* Use what you have learned in the course and modify the program.
* Calculate the total cache accessing time for L1 $I and $D (instruction-cache & data-cache) by following formula. (For the hit_time, please refer to the file "CacheAccessTime.pdf" to get the right value for your cache setting. For the penalty, we assume the backside of L1 is connected to a DRAM and it takes 100ns to access that DRAM) Put the results in your report.

		total_cache_access_time = access_count * (hit_time + miss_rate * miss_penalty)
	
* You must have performance enhancement (less total_cache_access_time) to get points. If your result is equal or worse than the reference code, you will get zero point on this part.
* You must pass the testing by executing the ckecker. If you pass the ckecking, you will get the message "Congratulations! You have passed the checking.". On the other hand, you will get the message "Sorry, your results are wrong!".
* Do not modify the checker program.

#### 1.2 Find out the optimal L1 cache configuration (15%)
* You can use the option "--ic" and "--dc" to configure the cache of spike. The parameters for each option would be "sets:associativity:linesize". If you multiple all the numbers together, you will get the cache size. For example, if you set "--ic=32:1:64 --dc=64:1:64", you will get a 2KB(32X1X64) instruction-cache and 4KB(64X1X64) data-cache. In the real case, you may type belowing command to run the simulation.

		$ spike --ic=64:1:64 --dc=32:1:64 pk bns-riscv

* Find out the best configuratoin which can bring you the fastest cache accessing time.
* The size limit of the L1 $I and $D is 4KB respective. Do not use cache size larger than 4KB.
* You are recommanded to write a shell script to help you to find out the best parameters automatically.
* Write the cache configuration in the corresponding place in the Makefile and let TA can use "make run" to reproduce your result.

#### 1.3 Bonus: Add the L2 cache (up to 5%)
spike also supports L2 cache simulation by plusing "--l2" in the options. You can do some experiments and modify your code and the cache configuration to reach the best cache performance with the fastest cache access time.
* The limit of the L2 cache size is 8KB.
* Modify the cache-access-time formula to calculate the new total cache access time and compare the results.
* Put the configuration at the corresponding location in Makefile and make TA can use "make run-l2" to rerun your program.
* Create a directory called "bonus" to store all the needed files for this task.
* Discuss the impacts in your report.

### Task 2 - Hardware approach (Due date: 6/14 23:59)
As what you have learned in the class, the behaviors of the cache can incluence the performance dramatically. So it's possible to improve it through modify the reactions of the cache on the read/write accesses. For spike, the riscv isa simulator, the related files of the cache simulation are cachesim.cc and cachesim.h. (You can find those files under the directory "/path/to/riscv-isa-sim/riscv") You can customize the cache behavior by modifying these two file. You can redesign the replacement policy or add a prefetching mechanism onto the cache simulation to gain better cache performance.
Note: Task 2.1 plus task 2.2 will be responsible for the total points in the complteness part (40% in total. Please check the grading policy)
#### 2.1 Modify the simulation of L1 cache in spike for the reference program to obtain better performance (30%)
* You are restricted to only modify the two files, cachesim.h and cachesim.cc.
* Do not modify the part to calculate cache access count and the miss count.
* You must have performance enhancement (less total_cache_access_time) to get points. If your result is equal or worse than the reference code, you will get zero point on this part.
* Write a shell script named "task2_1.sh" containing your cache configuration to show TA how to run your modified simulator. For example, the content of your "task2_1.sh" could be

		spike --ic=32:2:64 --dc=64:1:64 pk bns-riscv

* Create a directory named "task2_1" to store the files: cachesim.h, cachesim.cc and task2_1.sh.
* The size limit of the L1 $I and $D is 4KB respective. Do not use cache size larger than 4KB.
* Recalculate the total cache access time for the origin program within the modified simulator. Put the results in your report.
* Your results must still pass the checking of the checker.

#### 2.2 Modify the simulation of L1 cache in spike for the modified program your have done in the taks1 to obtain better performance (10%)
* The same constraints as task 2.1.
* Write a shell script called "task2_2.sh" to indicate how to run your modified spike with corresponding cache configuratoin.
* Create a directory named "task2_2" to save the files: cachesim.h, cachesim.cc and task2_2.sh.
* Recalculate the total cache access time for the origin program within the modified simulator. Put the results in your report.
#### 2.3 Bonus: Add the L2 cache (up to 10%)
* Now consider the L2 cache and redesign your cache policy.
* The limit of the L2 cache size is 8KB.
* Write a shell script called "bonus.sh" to indicate how to run your modified spike with corresponding cache configuratoin.
* Create a directory named "bonus" to store the files: cachesim.h, cachesim.cc and bonus.sh.
* Modify the cache-access-time formula to calculate the new total cache access time and compare the results.
* Discuss the impact in your report.

## Grading policy (The same for the two tasks)
Upload all the asked files to E3 in right format before the deadline. TA will write a testing script to grade your project automatically. So if you don't follow the naming policy, you will have extraordinary high probability to get no point. Who doesn't submit on time will only get 70% of the total points. If you don't upload till 3 days after the due date, you will just get zero point. Otherwise, the grade will be evaluated by the below items:
* Must followed rules
	* Name your report as "Report_task#_studentID.pdf". For example, if it's task1 and your ID is 0605040, then set your report as "Report_task1_0605040.pdf".
	* Put the needed source codes under a directory called "code_studentID".
	* Pack your report and source code into a file named "Task#_studentID.zip" in zip format. Then upload it to E3.
* Completeness 40%
	* You must finish the necessary tasks and follow the requirements to get the points in this part.
* Report 40%
Your report should include the following parts
	* The descriptions of all the modifications you have made and explain the reasons why you do this. (30% at most)
	* The descriptions and explainations of all the results you can get from the tasks. (30% at most)
	* Discussions. This part can be: What phenomenons you have found in the project? What extra works you did in the project? How did you solve the errors(if any) when you built up the execution environment? and so on. You are free to add other topics related to this project. Please write meaningful discussions as more as possible to gain higher score in this part (30% at most)
	* Feedback. Is the project fun? Is the project too difficult or too easy? Which part you have spent the most time? Please let TA know what you feel to make us able to create better project and make TA have chance to applogize if it is designed too badly. (10% at most)
* Performance Rank 20%
	* We will sort your total cache access time. The best one can get all points and the worst one will get 1 point in this part for each task. 
	* We will not compare your results in the bonus parts.

## Acknowledgments
This project is heavily inspired by the lab2 of the course 2015 Spring CS152 at UC Berkeley. It's made possible through the hard works of Andrew Waterman, Yunsup Lee, David Patterson and Krste Asanovi ́c who developed the RISC-V ISA and the made the complete toolchain.

## Notes
If you get any problem when you read this document or work on the project, feel free to ask google or email TA about your issue. Hope you will have a great time on this project. Thanks!

TA: Chien-Yu Lin
Email: myislin@gmail.com

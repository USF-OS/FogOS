# FogOS

![FogOS](docs/fogos.gif)

$U/_hash\:
	The hash function is a makefile UPROG command that uses the Secure Hash Alorithm 1 library (sha1.c and sha1.h) to create a hash string based on the contents of the test file. A similar algorithm is used in the md5sum command. Inside user/hash.c, we utilize the Secure Hash Algorithm 1 library functions to hash the contents of a test file located in the root directory of the FogOS. This function is used to identify if changes were made in files or if files are corrupted.

How to run the code:
	In the root directory of FogOS, run 'make qemu'. After the code compiles, enter the command /hash. You will see the hash output of the file you are testing on qemu.

Testing:
	Keep track of the hash in the qemu output. Make any change to the file that is passed as a parameter in the hash.c file. After making changes, even simply adding an extra character to the file, re-run the hash function for the same test file on qemu. The hash string for the same file will be completely different from the initial hash because it detected that the contents of the test file have changed.

Makefile:
-	Added UPROG command $U/_hash\
-	Added $U/sha1.o to the ULIB section
-	Included the test file in the fs.img section

User space:
-	sha1.h and sha1.c libraries
-	hash.c file calls the library functions

Test file:
-	Located in root directory of FogOS, currently named 'input.txt'

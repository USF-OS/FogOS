CKSUM Command

* Usage: cksum file_name1 file_name2 etc.

* Tests: cksumtest 

* Performs a cyclical redundancy check on the file argument
  and prints the calculated value, the size of the file, and
  the file name to the console

* CRC algorithm used is based on POSIX CR32 specification

* Uses polynomial 0x04C11DB7

* Uses full-byte table-lookup method
	* Table is defined in crctable.h

* Files:
	* New:
		* user/cksum.c
		* user/cksum_test.c
		* user/crctable.h
	* Modified:
		* user/ulib.c
		* user/user.h


Issue with setting the proper FD - possibly
	

	URL --> https://devblog.microsoft.com/oldnewthing/20221102-00/?p=107343

	FD_SET - used to place sockets into a set for various purposes

		fd is non blocking
				Blocking: not return until there is activity
			
				non-blocking: Ssystem calls will reitn immediatly if nothing is pending



		#0  0x00005555556a89a9 in set_if_selectable (f=0x7fffd5ad33c0, fdsp=0x7fffd5ad19c0, n=0x7fffd5ad192c) at /home/half/unicon/src/runtime/fxposix.ri:2301
	2301	   FD_SET(fd, fdsp);

	#1  0x00005555556a972e in Zselect (r_nargs=1, r_args=0x7fffd5ad33b0) at /home/half/unicon/src/runtime/fxposix.ri:2458
	2458			  if ((rv = set_if_selectable(files+k, &fds, &n)))

	#2  0x00005555555de65c in interp_0 (fsig=0, cargp=0x0) at /home/half/unicon/src/runtime/interp.r:1308
	1308			  signal = (*bfunc)(nargs,rargp);

	#3  0x0000555555616e15 in new_context (fsig=0, cargp=0x0) at /home/half/unicon/src/runtime/rcoexpr.r:513
	513	      interp(fsig, cargp);

	#4  0x0000555555617df6 in nctramp (arg=0x7fffd5ad3010) at /home/half/unicon/src/runtime/rcoexpr.r:749
	749	   new_context(0, 0);			/* call new_context; will not return */

	#5  0x00007ffff7518b43 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
	442	./nptl/pthread_create.c: No such file or directory.

	#6  0x00007ffff75aaa00 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
	81	../sysdeps/unix/sysv/linux/x86_64/clone3.S: No such file or directory.


	
		* fd_set == the set that has been set. 
			FD_SET (fd f, fd_set fdst)
				    |		---------------------------
				     ----?---?----------?---?--		   |	
							       V	   V
			int set_if_selectable (struct descrip *f, fd_set *fdsp, int *n);
							|			      |
	------------------------------------------------|------------------------------
	V						










int set_if_selectable(struct descrip *f, fd_set *fdsp, int *n)
{
   int fd, status;

	*Initialization



   if (is:file(*f)) {
      status = BlkD(*f,File)->status;
	

	* if f is a file we are going to get the status of the file by getting the file BLKD(f, FILE) and getting(-->)the status
	
		now we have status if file

#if UNIX
      if (status & Fs_Buff) return 1048;
      BlkLoc(*f)->File.status |= Fs_Unbuf;
#endif                                  /* UNIX */




		00000000000000000
		00000000000000000 --> Bunch of non relevant code
		00000000000000000




#endif                                  /* PseudoPty && MSWindows */
      if ((fd = get_fd(*f, Fs_Read|Fs_Socket|Fs_Messaging)) < 0) {
        	|
	       /
	      /
             /
            |
	    V
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000int get_fd(struct descrip file, unsigned int errmask)
{			|			|
			|			|						
-------------------------			|
|						|
V						|
Normal File Descriptor   			|
-------------------------------------------------
|
V
Opinion: 
	Unsigned means that it can only be positive with a range much bigger than signed
	This is because an or statement will not produce a negative bit (there are no negative bits)
	

int status;

   status = BlkD(file,File)->status;

		* Lets check the status of the file
	
	
   /* Check it's opened for reading, or it's a window */
   if ((status & Fs_Directory)
#ifdef Dbm
       || (status & Fs_Dbm)
#endif
       )
     return -1; --> file is -1

 !!!!!!!!!!!!!IMPORTANT!!!!!!!!!!
	A FILE WILL NOT BE OPENED IF THE DESCRIPTOR IS -1

#ifdef Graphics
   if (status & Fs_Window) {
     if (!(status & Fs_Read)) {
        return -1;

		REFER TO IMPORTANT SECTION

        }
#ifdef XWindows
     return XConnectionNumber(BlkD(file,File)->fd.wb->
                              window->display->display);
#else                                   /* XWindows */
     return -1;
	REFER TO IMPORTANT SECTION


#endif                                  /* XWindows */
     }
#endif                                  /* Graphics */



#ifdef PseudoPty
   if (status & Fs_Pty) {
#if NT
      return -1;
	
     REFER TO IMPORTANT SECTION

#else                                   /* NT */
 










int master_fd, slave_fd;             /* master, slave pty file descriptor */
						     ^			
----------------------------------------------	     |
|Couldnt find much more info on it other than|>>>----
----------------------------------------------
^
|
---------------------------------------------------------
							|
							|
	lets get the the file location in the block then from the fd.pt we will get the master_fd
	^						|
	|						|
	|						|
  return BlkD(file,File)->fd.pt->master_fd;--------------
#endif                      |            /* NT */
			    |
-----------------------------
|
V
Whats fd.pt?
	|
	|
	-----> struct ptstruct *pt;
			|
-------------------------
|
V
000000000000000000000000000000000000000000000000000000000000000000000000000
#ifdef PseudoPty
struct ptstruct {
#if NT
   HANDLE master_read, master_write;
   HANDLE slave_pid;
#else                                   /* WIN32 */
   int master_fd, slave_fd;             /* master, slave pty file descriptor */
   pid_t slave_pid;                     /* process id of slave  */
#endif                                  /* WIN32 */
     
   char slave_filename[256];/* pty slave filename associated with master pty */
   char slave_command[256]; /* name of executable associated with slave */
};
00000000000000000000000000000000000000000000000000000000000000000000000000

      }
#endif                                  /* PseudoPty */

   if (errmask && !(status & errmask))
      return -2;
   else

#if NT
#define fileno _fileno
#endif                                  /* NT */


------
|     |       
|     > HERE
|	     
|     if (status & Fs_Socket)
|        return BlkD(file,File)->fd.fd;
|
|
|
|		!!!!!!!Posible Change!!!!!!!!
|	     ---------------------------------------------
------------|if (status & Fs_Socket)			  |
	    |		return BLKD(file, FILE)->fd.sslfd |
	    |						  |
	    |	NOTE: Figure out how the fd is set--------|---							
	     ---------------------------------------------   |
							     |
-------------------------------------------------------------
|
V
Inside fsys.r
	-> inside open function--
			        |
---------------------------------
|
V
00000000000000000000000000000000000000000000000000
if(status && Fs_Encrypt)
                {
                        ssl = SSL_new(ctx);
                        SSL_set_fd(ssl, fd);    
                                
                }
00000000000000000000000000000000000000000000000000

CHANGE:

	1.) inside open function create new SSL context
		------>	ssl_new(ctx);
	2.) store ssl Context
		------> f.ssl = ssl;
	3.) SSL is now stored and we can create a new context in side get_fd
		if (status & Fs_Encrypt)
		{
			return SSL_set_fd(BLKD(file, f)->fd.ssl, fd)
		}
	






      else if (status & Fs_Messaging)
         return tp_fileno(BlkD(file,File)->fd.mf->tp);
      else
         return fileno(BlkD(file,File)->fd.fp);
}
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	     ^
	     |
	      \
	       \
		get_fd(normal f for our file descripor, ???????)
							   |
		--------------------------------------------
		|
		V
		fs_Read OR Fs_Socket OR Fs_Messaging
		errmask?
		 |
------------------
V
0000000000000000000000000000000000000
0 if (errmask && !(status & errmask)) 0
0       return -2;		      0
0    else                             0
0000000000000000000000000000000000000
|
 ->Checks to see if the status contains the error mask???
	|
	 -> Returns a negative number so that means it is some type of method used for error checking
		-> status and errmask if then not and if it is bitwise and return the the read file is not open and ready for reading.
					^
					|
					|
					|- 212, "attempt to read file not open for reading"
					|
					|
         if (fd == -2)		      	|
            return 212;------------------
         


	else
           return 174;
         }
      }
   else
      return 105;

   if (*n < fd + 1)
      *n = fd + 1;
   printf("before fail");
   printf("1.) FD: %d and FDSP: %d\n", fd, fdsp);
   FD_SET(fd, fdsp);
   printf("2.) FD: %d and FDSP: %d\n", fd, fdsp);
   return 0;

	

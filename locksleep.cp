#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#ifdef OS_NT

#include <windows.h>
#include <io.h>

#define LOCK_UN 8
#define LOCK_SH 1
#define LOCK_EX 2

#define sleep(s) Sleep(s * 1000)

#else

#include <unistd.h>
#include <sys/file.h>

#endif

#ifndef NONAMESPACE

#include <iostream>
using namespace std;

#else

#include <iostream.h>

#endif

int lockFile( int fd, int flag )
{

# ifdef OS_NT

	HANDLE h = (HANDLE)_get_osfhandle( fd );
	OVERLAPPED ol;

	ol.Internal = 0;
	ol.InternalHigh = 0;
	ol.Offset = 0xFFFFFFFF;
	ol.OffsetHigh = 0xFFFFFFFF;
	ol.hEvent = 0;

	switch( flag )
	{
	case LOCK_UN: return !UnlockFileEx( h, 0, 1, 0, &ol );
	case LOCK_SH: return !LockFileEx( h, 0, 0, 1, 0, &ol );
	case LOCK_EX: return !LockFileEx( h, LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &ol );
	}

	return -1;

# else

	switch( flag )
	{
	case LOCK_UN:
	case LOCK_SH:
	case LOCK_EX:
	    return flock( fd, flag );
	}

	return -1;

# endif /* OS_NT */

}

int main( int argc, char **argv );
int main( int argc, char **argv )
{
	int fd;

	if( argc < 3 )
	{
	    cout << "Usage: " << argv[0] << " <file> <lock-type> <seconds>\n";
	    return EINVAL;
	}

	if( ( fd = open( argv[1], O_RDONLY ) ) == -1 )
	{
	    cout << "Couldn't open " << argv[1] << "!\n";
	    return errno;
	}

	if( lockFile( fd, atoi( argv[2] ) ) == -1 )
	{
	    cout << "Couldn't lock with lock type " << argv[2] << "!\n";
	    return EIO;
	}

	sleep( atoi( argv[3] ) );

	lockFile( fd, LOCK_UN );

	close( fd );

	return 0;
}

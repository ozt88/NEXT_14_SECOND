// FileIO.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>

#define STRING_LEN 100

BOOL FileWrite( LPCWSTR fileName );
BOOL FileRead( LPCWSTR hFile );
BOOL PrintFileTime( LPCWSTR fileName );
BOOL PrintFileSize( LPCWSTR fileName );
BOOL PrintFileInfo( LPCWSTR fileName );
BOOL ShowAttributes( DWORD attrib );
BOOL ShowFileTime( FILETIME ft );
BOOL ShowPath( LPCWSTR fileName );
BOOL TestSetPointer( LPCWSTR fileName );
BOOL TestDirectory();
BOOL ShowDir();

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR fileName[] = TEXT( "data.txt" );
// 	FileWrite( fileName );
// 	FileRead( fileName );
// 	PrintFileInfo( fileName );
// 	ShowPath( fileName );
// 	TestSetPointer( fileName );
// 	//TestDirectory();
	ShowDir();

	return 0;
}

BOOL FileWrite(LPCWSTR fileName)
{
	HANDLE hFile = CreateFile(
		fileName ,				//파일 이름
		GENERIC_WRITE ,			//접근 형식 R/W
		FILE_SHARE_WRITE ,		//공유 방식 공유 안함, 읽기공유, 쓰기 공유
		NULL ,					//보안 속성 NULL
		CREATE_ALWAYS ,			//생성 방식 항상 뉴, 같은 이름 있으면 안 뉴,
								//기존 파일 쓰고 없으면 뉴, 기존 파일 쓰고 없으면 에러
								//기존 파일 내용 지우고 오픈, 없으면 에러
		FILE_ATTRIBUTE_NORMAL ,	//파일의 특성 정보 FILE_ATTRIBUTE_NORMAL
		NULL					//기존 템플릿 호출 NULL
		);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "FILE OPEN FAULT!\n" ) );
		return FALSE;
	}
	DWORD numOfByteWritten = 0;
	TCHAR fileData[] = TEXT( "1234567890" );
	BOOL bWriteResult = true;
	bWriteResult = WriteFile(
		hFile ,					//Read랑 똑같음
		fileData ,
		sizeof( fileData ) ,
		&numOfByteWritten ,
		NULL
		);

	_tprintf_s( TEXT( "Written Data Size : %u \n" ) , numOfByteWritten );
	
	CloseHandle( hFile );
	return bWriteResult;
}

BOOL FileRead( LPCWSTR fileName )
{
	HANDLE hFile = CreateFile(
		fileName ,				//파일 이름
		GENERIC_READ ,			//접근 형식 R/W
		FILE_SHARE_READ ,		//공유 방식 공유 안함, 읽기공유, 쓰기 공유
		NULL ,					//보안 속성 NULL
		OPEN_EXISTING ,			//생성 방식 항상 뉴, 같은 이름 있으면 안 뉴,
								//기존 파일 쓰고 없으면 뉴, 기존 파일 쓰고 없으면 에러
								//기존 파일 내용 지우고 오픈, 없으면 에러
		FILE_ATTRIBUTE_NORMAL ,	//파일의 특성 정보 FILE_ATTRIBUTE_NORMAL
		NULL					//기존 템플릿 호출 NULL
		);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "FILE OPEN FAULT!\n" ) );
		return FALSE;
	}

	DWORD numOfByteToRead = 0;
	TCHAR fileData[STRING_LEN];
	BOOL bReadResult = true;
	bReadResult = ReadFile(
	 	hFile,					//읽을 파일 핸들
	 	fileData,				//버퍼
	 	sizeof(fileData),		//읽고자하는 데이터의 크기
	 	&numOfByteToRead,		//저장된 데이터 크기를 얻는 변수의 주소
	 	NULL					//나중에 설명;
		);
	fileData[numOfByteToRead / sizeof( TCHAR )] = '\0';

	_tprintf_s( _T( "READ DATA SIZE: %d \n" ) , numOfByteToRead );
	_tprintf_s( _T( "READ DATA STR: %s \n" ) , fileData );
	
	CloseHandle( hFile );
	return bReadResult;
}

BOOL PrintFileTime( LPCWSTR fileName )
{
	TCHAR fileCreateTimeInfo[STRING_LEN];
	TCHAR fileAccessTimeInfo[STRING_LEN];
	TCHAR fileWriteTimeInfo[STRING_LEN];

	FILETIME ftCreate , ftAccess , ftWrite;

	SYSTEMTIME stCreateUTC , stCreateLocal;
	SYSTEMTIME stAccessUTC , stAccessLocal;
	SYSTEMTIME stWriteUTC , stWriteLocal;

	HANDLE hFile = CreateFile(
		fileName ,				//파일 이름
		GENERIC_READ ,			//접근 형식 R/W
		NULL ,					//공유 방식 공유 안함, 읽기공유, 쓰기 공유
		NULL ,					//보안 속성 NULL
		OPEN_EXISTING ,			//생성 방식 항상 뉴, 같은 이름 있으면 안 뉴,
								//기존 파일 쓰고 없으면 뉴, 기존 파일 쓰고 없으면 에러
								//기존 파일 내용 지우고 오픈, 없으면 에러
		FILE_ATTRIBUTE_NORMAL ,	//파일의 특성 정보 FILE_ATTRIBUTE_NORMAL
		NULL					//기존 템플릿 호출 NULL
		);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s(_T("File Open Fault!\n")); 
		return FALSE;
	}

	if( !GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite) )
	{
		_tprintf_s( _T( "GetFileTime Function call Fault!\n" ) );
		return FALSE;
	}

	FileTimeToSystemTime( &ftCreate , &stCreateUTC );
	SystemTimeToTzSpecificLocalTime( NULL , &stCreateUTC , &stCreateLocal );

	FileTimeToSystemTime( &ftAccess , &stAccessUTC );
	SystemTimeToTzSpecificLocalTime( NULL , &stAccessUTC , &stAccessLocal );
	
	FileTimeToSystemTime( &ftWrite , &stWriteUTC );
	SystemTimeToTzSpecificLocalTime( NULL , &stWriteUTC , &stWriteLocal );

	_stprintf_s( fileCreateTimeInfo , _T( "%02d/%02d/%d\t%02d:%02d" ) ,
				 stCreateLocal.wMonth , stCreateLocal.wDay ,
				 stCreateLocal.wYear , stCreateLocal.wHour ,
				 stCreateLocal.wMinute );

	_stprintf_s( fileAccessTimeInfo , _T( "%02d/%02d/%d\t%02d:%02d" ) ,
				 stAccessLocal.wMonth , stAccessLocal.wDay ,
				 stAccessLocal.wYear , stAccessLocal.wHour ,
				 stAccessLocal.wMinute );

	_stprintf_s( fileWriteTimeInfo , _T( "%02d/%02d/%d\t%02d:%02d" ) ,
				 stWriteLocal.wMonth , stWriteLocal.wDay ,
				 stWriteLocal.wYear , stWriteLocal.wHour ,
				 stWriteLocal.wMinute );

	_tprintf_s( _T( "File Created time : %s \n" ) , fileCreateTimeInfo );
	_tprintf_s( _T( "File Accessed time : %s \n" ) , fileAccessTimeInfo );
	_tprintf_s( _T( "File Written time : %s \n" ) , fileWriteTimeInfo );

	CloseHandle( hFile );
	return TRUE;
}


BOOL PrintFileSize( LPCWSTR fileName )
{
	HANDLE hFile = CreateFile( fileName , 
							   GENERIC_READ , 
							   NULL ,
							   NULL , 
							   OPEN_EXISTING ,
							   FILE_ATTRIBUTE_NORMAL , 
							   NULL );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "Create File Fault!\n" ) );
		return FALSE;
	}

	DWORD high4ByteFileSize = 0;
	DWORD low4ByteFileSize = GetFileSize( hFile , &high4ByteFileSize );

	_tprintf_s( _T( "High 4Byte File Size: %u Byte\n" ) , high4ByteFileSize );
	_tprintf_s( _T( "Low 4Byte File Size: %u Byte\n" ) , low4ByteFileSize );

	LARGE_INTEGER fileSize;
	GetFileSizeEx( hFile , &fileSize );
	_tprintf_s( _T( "Total File Size: %u Byte\n" ) , fileSize.QuadPart );
	
	CloseHandle( hFile );
	return TRUE;
}

BOOL PrintFileInfo( LPCWSTR fileName )
{
	BY_HANDLE_FILE_INFORMATION fileInfo;
	HANDLE hFile = CreateFile( fileName , 
							   GENERIC_READ ,
							   NULL , 
							   NULL ,
							   OPEN_EXISTING , 
							   FILE_ATTRIBUTE_NORMAL , 
							   NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "Create File Fault!\n" ) );
		return FALSE;
	}

	GetFileInformationByHandle( hFile , &fileInfo );

	_tprintf_s( _T( "File Size : %u\n" ) , fileInfo.nFileSizeLow );

	ShowAttributes( fileInfo.dwFileAttributes );

	_tprintf_s( _T( "File Create Time :"));
	ShowFileTime( fileInfo.ftCreationTime );
	_tprintf_s( _T( "File Access Time :" ) );
	ShowFileTime( fileInfo.ftLastAccessTime );
	_tprintf_s( _T( "File Write Time :" ) );
	ShowFileTime( fileInfo.ftLastWriteTime );

	CloseHandle( hFile );
	return TRUE;
}

BOOL ShowFileTime( FILETIME ft )
{
	TCHAR fileTimeInfo[STRING_LEN] = { 0 , };
	SYSTEMTIME stUTC , stLocal;
	FileTimeToSystemTime( &ft , &stUTC );
	SystemTimeToTzSpecificLocalTime( NULL , &stUTC , &stLocal );

	_stprintf_s( fileTimeInfo , _T( "%02d/%02d/%d\t%02d:%02d" ) ,
				 stLocal.wMonth , stLocal.wDay ,
				 stLocal.wYear , stLocal.wHour ,
				 stLocal.wMinute );
	_tprintf_s( _T("%s\n") , fileTimeInfo );
	return TRUE;
}

BOOL ShowAttributes( DWORD attrib )
{
	TCHAR attribStr[STRING_LEN] = { 0 , };
	if( attrib & FILE_ATTRIBUTE_NORMAL )
	{
		_stprintf_s( attribStr , _T( "%s | %s" ) ,
					 attribStr , _T( "NORMAL" ) );
	}
	else
	{
		if( attrib & FILE_ATTRIBUTE_READONLY )
		{
			_stprintf_s( attribStr , _T( "%s | %s" ) ,
						 attribStr , _T( "READ ONLY" ) );
		}
		if( attrib & FILE_ATTRIBUTE_HIDDEN )
		{
			_stprintf_s( attribStr , _T( "%s | %s" ) ,
						 attribStr , _T( "HIDDEN" ) );
		}
	}
	_tprintf_s( _T( "%s \n" ) , attribStr );
	return TRUE;
}

BOOL ShowPath( LPCWSTR fileName )
{
	TCHAR fileFullPath[MAX_PATH] = { 0 , };
	LPTSTR filePtr;

	GetFullPathName( fileName , MAX_PATH , fileFullPath , &filePtr );
	_tprintf_s( _T( "%s\n" ) , fileFullPath );
	_tprintf_s( _T( "%s\n" ) , filePtr );

	return TRUE;
}


BOOL TestSetPointer( LPCWSTR fileName )
{
	TCHAR readBuffer[STRING_LEN] = { 0 , };
	DWORD numOfByte = 0;
	DWORD dwPtr = 0;
	HANDLE hFile = CreateFile( fileName , GENERIC_READ , NULL , NULL ,
							   OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
	ReadFile( hFile , readBuffer , sizeof( readBuffer ) , &numOfByte , NULL );
	_tprintf_s( _T( "%s\n" ) , readBuffer );

	dwPtr = SetFilePointer( hFile , sizeof( TCHAR ) * 4 , NULL , FILE_BEGIN );
	if( dwPtr == INVALID_SET_FILE_POINTER )
	{
		_tprintf_s( _T( "SetFilePointer Error!\n" ) );
		return FALSE;
	}


	ReadFile( hFile , readBuffer , sizeof( readBuffer ) , &numOfByte , NULL );
	_tprintf_s( _T( "%s\n" ) , readBuffer );
	dwPtr = SetFilePointer( hFile , -((LONG)sizeof( TCHAR ) * 4) , NULL , FILE_END );
	if( dwPtr == INVALID_SET_FILE_POINTER )
	{
		_tprintf_s( _T( "SetFilePointer Error!\n" ) );
		return FALSE;
	}

	ReadFile( hFile , readBuffer , sizeof( readBuffer ) , &numOfByte , NULL );
	_tprintf_s( _T( "%s\n" ) , readBuffer );

	CloseHandle( hFile );
	return TRUE;
}

BOOL TestDirectory()
{
	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePathp[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	_tprintf_s( _T( "Insert Name of File to Find :" ) );
	_getts_s(fileName);

	result = SearchPath( NULL , fileName , NULL , MAX_PATH , bufFilePathp , &lpFilePart );
	if( result )
	{
		_tprintf_s( _T( "FilePath: %s \n" ) , bufFilePathp );
		_tprintf_s( _T( "File name only: %s \n" ) , lpFilePart );
	}
	else
	{
		_tprintf_s( _T( "File not Found!\n" ) );
	}

	return TRUE;
}

BOOL ShowDir()
{
	TCHAR dirPath[MAX_PATH];
	GetCurrentDirectory( MAX_PATH , dirPath);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	_tcsncat_s( dirPath , _T( "\\*" ) , 3 );
	hFind = FindFirstFile( dirPath , &FindFileData );
	if( hFind == INVALID_HANDLE_VALUE )
	{
		_tprintf_s( _T( "Invalid File Handle\n" ) );
		return FALSE;
	}
	else
	{
		_tprintf_s( _T( "%s\n" ) , FindFileData.cFileName );
		while( FindNextFile( hFind , &FindFileData ) )
		{
			_tprintf_s( _T( "%s\n" ) , FindFileData.cFileName );
		}
	}
	FindClose( hFind );
	return TRUE;
}
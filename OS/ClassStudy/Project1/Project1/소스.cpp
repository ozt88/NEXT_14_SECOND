#include<stdio.h>
//ackerMannRe 재귀로 애커만 함수
//ackerMannIt 반복문으로 애커만함수
int ackerMannIt( int m , int n );
int ackerMannRe( int m , int n );
int main( void )
{
	int m , n;
	printf( "input m:" );
	scanf_s( "%d" , &m );
	printf( "input n:" );
	scanf_s( "%d" , &n );

	printf( "Reculsive AckerMan(%d, %d) = %d\n" , m , n , ackerMannRe( m , n ) );
	printf( "Iterative AckerMan(%d, %d) = %d\n" , m , n , ackerMannIt( m , n ) );
	getchar();
	getchar();

	return 0;
}

int ackerMannRe( int m , int n )
{

	if( m == 0 )
	{
		return n + 1;
	}
	else if( n == 0 )
	{
		return ackerMannRe( m - 1 , 1 );
	}
	else
	{
		return ackerMannRe( m - 1 , ackerMannRe( m , n - 1 ) );
	}

}

//arr을 에커만 테이블로 만들어서 
int ackerMannIt( int m , int n )
{
	int k = n;
	int arr[7][10000] = { 0 , };
	for( int i = 0; i <= m; i++ )
	{
		for( int j = 0; j <= k; j++ )
		{
			if( arr[i][j] == 0 )
			{
				if( i == 0 )
				{
					arr[i][j] = j + 1;
				}
				else if( j == 0 )
				{
					if( arr[i - 1][1] != 0 )
					{
						arr[i][j] = arr[i - 1][1];
					}
					else
					{
						printf( "Bug 1\n" ); return -1;
					}
				}
				else
				{
					if( arr[i - 1][arr[i][j - 1]] != 0 )
					{
						arr[i][j] = arr[i - 1][arr[i][j - 1]];
					}
					else
					{
						k = arr[i][j - 1];
						i--;
					}
				}
			}
		}
	}
	return arr[m][n];

}
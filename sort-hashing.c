/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);//초기화시키는 int형 함수 initialize
int freeArray(int *a);//배열에 할당된 메모리 해제하는 int형 함수 freeArray
void printArray(int *a);//배열을 출력하는 void형 printArray 함수

int selectionSort(int *a);//선택정렬  int형 selectionSort함수
int insertionSort(int *a);//삽입정렬 int형 insertion함수
int bubbleSort(int *a);//버블정렬 int형 bubbleSort 함수
int shellSort(int *a);//셀 정렬 int형 shellSort함수
/* recursive function으로 구현 */
int quickSort(int *a, int n);//퀵 정렬함수 int형 quickSort함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);//

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;//char형 command 변수 선언
	int *array = NULL;//int형 포인터 array NULL로 초기화
	int *hashtable = NULL;//int형 포인터 hashtable NULL로 초기화
	int key = -1;//int형 변수 key -1로 초기화
	int index = -1;//int형 변수 index -1로 초기화

	srand(time(NULL));//난수 생성

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
        printf("-----------[----- [Kimdongwoo] [2020039058] -----]--------------\n");
        printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z'://z 대소문자 입력 받았을 때
			initialize(&array);//nitialize 함수 호출하여 array 초기화
			break;
		case 'q': case 'Q'://q 대소문자 입력받았을 때
			freeArray(array);//freeArray 함수 호출하여 array에 할당된 메모리 해제
			break;
		case 's': case 'S'://s 대소문자 입력받았을 때
			selectionSort(array);//selectionSort함수 호출하여 array 선택정렬
			break;
		case 'i': case 'I'://i 대소문자 입력받았을 때
			insertionSort(array);//insertionSort 함수 호출하여 array 삽입정렬
			break;
		case 'b': case 'B'://b 대소문자 입력받았을 때
			bubbleSort(array);//bubbleSort 함수 호출하여 array 버블정렬
			break;
		case 'l': case 'L'://l 대소문자 입력받았을 때
			shellSort(array);//shellsort함수 호출하여 array 셀정렬
			break;
		case 'k': case 'K'://k 대소문자 입력받았을 때
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);//printArray함수 호출하여 array 출력
			quickSort(array, MAX_ARRAY_SIZE);//quickSort 함수 호출하여 array 퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);//printArray함수 호출하여 퀵정렬 후 array 출력

			break;

		case 'h': case 'H'://h 대소문자 입력받았을 때
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);//printArray 함수 호출하여 array 출력
			hashing(array, &hashtable);//hashing 함수 호출하여 array 해싱한 후, hashtable에 저장
			printArray(hashtable);//printArray함수 호출하여 hashtable 출력
			break;

		case 'e': case 'E'://e 대소문자 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력받은 값 key에 할당
			printArray(hashtable);//printArray함수로 hashtable 출력
			index = search(hashtable, key);//search로 탐색한 주소 index에 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);//탐색한 결과 출력
			break;

		case 'p': case 'P'://p 대소문자 입력받았을 때
			printArray(array);//printArray함수로 array 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q 입력받았기 전까지 반복

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;//포인터 temp NULL로 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//temp에 MAX_ARRAY_SIZE만큼 동적메모리 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;//temp에 a가 가르키는 값 할당

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//배열의 크기만큼 반복
		temp[i] = rand() % MAX_ARRAY_SIZE;//temp[i]에 랜덤값 저장

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)//배열 a가 NULL이 아니라면
		free(a);//a에 할당된 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {//a가 NULL이라면
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);//a에 저장된 값 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min;//int형 변수 min 선언
	int minindex;//int형 변수 minidex 선언
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//선택정렬 전 배열 a 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//배열 a의 크기만큼 반복
	{
		minindex = i;//minindex에 i값 할당
		min = a[i];//min에 a[i] 할당
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)//배열 a의 크기만큼 반복
		{
			if (min > a[j])//min이 a[j]보다 크다면
			{
				min = a[j];//min에 a[j]값 할당
				minindex = j;//minindex에 j 값 할당
			}
		}
		a[minindex] = a[i];//a[minindex]에 a[i] 저장
		a[i] = min;//a[i]에 min값 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//선택정렬 후 a 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;//int형 변수 i,j,t 선언

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//삽입 전 a 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//t에 a[i] 저장
		j = i;//j에 i 저장
		while (a[j-1] > t && j > 0)//a[j-1]가 t보다 크다 and  j가 0보다 클 동안
		{
			a[j] = a[j-1];//a[j]에 a[j-1] 할당
			j--;
		}
		a[j] = t;//a[j]에 t 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//삽입 정렬 후 a 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;//int형 변수 i,j,t 선언

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//버블 정렬 전 a 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])//a[j-1]이 a[j]보다 크다면
			{
				t = a[j-1];//t에 a[j-1] 저장
				a[j-1] = a[j];//a[j-1]에 a[j] 저장
				a[j] = t;//a[j]에 t 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//버블정렬 후 배열 a 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;//int형 변수 i,j,k,h,v 선언

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//셀 정렬 전 a 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//h를 원소개수의 1/2로 사용 h가 1이 될때까지 반복
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//단계 안에서 비교하는 반복문
			{
				v = a[j];//v에 a[j] 저장
				k = j;//k에 j 할당
				while (k > h-1 && a[k-h] > v)//k가 h-1보다 크다 and a[k-h]가 v보다 클 동안
				{
					a[k] = a[k-h];//a[k]에 a[k-h] 저장
					k -= h;//k에 k-h저장
				}
				a[k] = v;//a[k]에 v 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//셀 정렬한 수 a 배열 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;//int형 v,t 선언
	int i, j;//int형 i,j 선언

	if (n > 1)//n이 1보다 크다면
	{
		v = a[n-1];//v에 a[n-1] 저장
		i = -1;//i -1로 초기화
		j = n - 1;//j에 n-1 저장

		while(1)
		{
			while(a[++i] < v);//왼쪽 부분 집합이 피봇보다 작을 동안
			while(a[--j] > v);//오른쪽 부분 집합 피봇보다 클 동안 

			if (i >= j) break;//i가 j보다 크거나 같다면 break
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		//a[i]와 a[n-1]값 교환
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);//왼쪽 부분집합 퀵정렬
		quickSort(a+i+1, n-i-1);//오른쪽 부분집합 퀵정렬
	}


	return 0;
}

int hashCode(int key) {
	return key % MAX_HASH_TABLE_SIZE;//key로 hashtable크기로 나눈 나머지 값 출력
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;//포인터 hashtable을 NULL로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//hashtable에 정수 크기만큼 MAX_ARRAY_SIZE만큼 메모리 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1  */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;//hashtable[i]에 -1로 초기화

	int key = -1;//int형 변수 key -1로 초기화
	int hashcode = -1;//int형 변수 hashcode -1로 초기화
	int index = -1;//int형 변수 index -1로 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//배열의 크기만큼 반복
	{
		key = a[i];//key에 a[i] 저장
		hashcode = hashCode(key);//생성한 hashtable을 hashCode에 저장

		if (hashtable[hashcode] == -1)//hashtable[hashcode]가 -1이라면
		{
			hashtable[hashcode] = key;//hashtable[hashcode]에 입력받은 key 저장
		} else 	{

			index = hashcode;//index에 hashcode 저장

			while(hashtable[index] != -1)//hashtable[index]가 -1이 아닐 동안
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//index에 증가된 index로 hashtable 크기로 나눈 나머지 값 저장
			}
			hashtable[index] = key;//hashtable[index]에 key값 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);//index에 생성한 hasdtable 저장

	if(ht[index] == key)//ht[index]이 key와 같다면
		return index;//index 리턴

	while(ht[++index] != key)//ht[증가한 index]가 key가 아닐 경우
	{
		index = index % MAX_HASH_TABLE_SIZE;//index에 index를 배열크기와 나눈 값 할당
	}
	return index;//index 리턴
}




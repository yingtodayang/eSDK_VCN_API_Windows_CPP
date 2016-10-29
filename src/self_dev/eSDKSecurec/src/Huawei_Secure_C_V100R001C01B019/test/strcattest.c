/******************************************************************************

Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.

******************************************************************************
File Name     :
Version       :
Author        :
Created       : 2010/9/1
Last Modified :
Description   :
Function List :

History       :
1.Date        : 2010/9/1
Author      :
Modification: Created file

******************************************************************************/


#include "securec.h"
#include "unittest.h"
#include "testutil.h"

#include <assert.h>
#include <string.h>

#define LEN   ( 128 )


typedef unsigned int uint32_t;
typedef int int32_t;

void test_strcat_s(void)
{
	errno_t rc;
	int32_t  ind;
	int32_t  len1;
	int32_t  len2;
	int32_t  len3;
	char   str1[LEN];
	char   str2[LEN];

#ifdef _DEBUG
	printf("num addr offset = %d\n", (char*)&len1 - (char*)&ind);
	//printf("float addr offset = %d\n", (char*)&fnumber - (char*)&lnumber);
#endif

	rc = strcat_s(NULL, LEN, str2);
	assert(rc == EINVAL);

	/*--------------------------------------------------*/

	rc = strcat_s(str1, LEN, NULL);
	assert((rc & 0x7F) == EINVAL);

	/*--------------------------------------------------*/

	rc = strcat_s(str1, 0, str2);
	assert( rc == ERANGE);

	/*--------------------------------------------------*/

	rc = strcat_s(str1, (SECUREC_STRING_MAX_LEN + 1), str2);
	assert(rc == ERANGE);

	/*--------------------------------------------------*/

	strcpy(str1, "aaaaaaaaaa");
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 1, str2);
	assert((rc & 0x7F) == EINVAL);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	strcpy(str1, "aaaaaaaaaa");
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 2, str2);
	assert((rc & 0x7F) == EINVAL);
	assert(rc  == EINVAL_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	strcpy(&str1[0], "aaaaaaaaaa");
	strcpy(&str2[0], "keep it simple");

	len1 = strlen(str1);
	len2 = strlen(str2);

	rc = strcat_s(str1, 50, str2);
	assert(rc == EOK);

	len3 = strlen(str1);
	assert(len3 == (len1 + len2));

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 1, str2);

	assert(rc == ERANGE_AND_RESET);
	assert((rc &0x7F) == ERANGE);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 2, str2);
	assert(rc == ERANGE_AND_RESET);
	assert((rc &0x7F) == ERANGE);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	str1[0] = '\0';
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 20, str2);

	assert(rc == EOK);
	ind = strcmp(str1, str2);
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	str2[0] = '\0';

	rc = strcat_s(str1, LEN, str2);

	assert(rc == EOK);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, LEN, str2);

	assert(rc == EOK);

	ind = strcmp(str1, str2);
	assert(ind == 0);

	/*--------------------------------------------------*/

	strcpy(str1, "qqweqq");
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, LEN, str2);

	assert(rc == EOK);

	ind = strcmp(str1, "qqweqqkeep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	strcpy(str1, "1234");
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 12, str2);
	assert(rc == ERANGE_AND_RESET);

	/*--------------------------------------------------*/

	strcpy(str1, "1234");
	strcpy(str2, "keep it simple");

	rc = strcat_s(str1, 52, str2);
	assert(rc == EOK);

	ind = strcmp(str1, "1234keep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	strcpy(str1, "12345678901234567890");

	rc = strcat_s(str1, 8, &str1[7]);

	assert(rc == EOVERLAP_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	strcpy(str1, "123456789");

	rc = strcat_s(str1, 9, &str1[8]);

	assert(rc == EOVERLAP_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	strcpy(str2, "123");
	strcpy(str1, "keep it simple");

	rc = strcat_s(str2, 31, &str1[0]);

	assert(rc == EOK);

	ind = strcmp(str2, "123keep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/

	strcpy(str2, "1234");
	strcpy(str1, "56789");

	rc = strcat_s(str2, 10, str1);
	assert(rc == EOK);

	ind = strcmp(str2, "123456789");
	assert(ind == 0);

	/*--------------------------------------------------*/
}


void test_strncat_s(void)
{
	errno_t rc;
	int32_t ind;
	char   str1[LEN];
	char   str2[LEN];

	/*--------------------------------------------------*/

	rc = strncat_s(NULL, LEN, str2, LEN);

	assert(rc == EINVAL);

	/*--------------------------------------------------*/

	rc = strncat_s(str1, LEN, NULL, LEN);

	assert(rc == EINVAL_AND_RESET); 

	/*--------------------------------------------------*/

	rc = strncat_s(str1, 0, str2, LEN);

	assert(rc == ERANGE);

	/*--------------------------------------------------*/

	rc = strncat_s(str1, (SECUREC_STRING_MAX_LEN+1), str2, LEN);

	assert(rc == ERANGE);

	/*--------------------------------------------------*/

	rc = strncat_s(str1, (SECUREC_STRING_MAX_LEN), str2, (SECUREC_STRING_MAX_LEN + 1));

	assert(rc == ERANGE_AND_RESET);

	/*--------------------------------------------------*/

	strcpy(str1, "aaaaaaaaaa");
	strcpy(str2, "keep it simple");

	rc = strncat_s(str1, 1, str2, LEN);

	assert(rc == EINVAL_AND_RESET);

	/*--------------------------------------------------*/

	strcpy(str1, "aaaaaaaaaa");
	strcpy(str2, "keep it simple");

	rc = strncat_s(str1, 2, str2, LEN);

	assert(rc == EINVAL_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	strcpy(str1, "a");
	strcpy(str2, "b");

	rc = strncat_s(str1, 2, str2, 1);
	assert(rc == ERANGE_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	strcpy(str1, "a");
	strcpy(str2, "b");

	rc = strncat_s(str1, 3, str2, 1);

	assert(rc == EOK);

	ind = strcmp(str1, "ab");
	assert(ind == 0);

	/*--------------------------------------------------*/

	strcpy(str1, "aaaaaaaaaa");
	strcpy(str2, "keep it simple");

	rc = strncat_s(str1, 50, str2, LEN);
	assert(rc == EOK);

	ind = strcmp(str1, "aaaaaaaaaakeep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/
	/* TR example */

	strcpy(str1, "good");
	strcpy(str2, "bye");

	rc = strncat_s(str1, 100, str2, 100);
	assert( rc == EOK);

	ind = strcmp(str1, "goodbye");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/* TR example */

	strcpy(str1, "hello");

	rc = strncat_s(str1, 6, "", 1);
	assert( rc == EOK);

	ind = strcmp(str1, "hello");
	assert( ind == 0 );

	/*--------------------------------------------------*/
	/* TR example */

	strcpy(str1, "hello");

	rc = strncat_s(str1, 6, "X", 2);
	assert(rc == ERANGE_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/* TR example */

	strcpy(str1, "abc");

	rc = strncat_s(str1, 7, "defghijklmn", 3);
	assert( rc == EOK);

	ind = strcmp(str1, "abcdef");
	assert(ind == 0);

	/*--------------------------------------------------*/
}
void test_wcscat_s(void)
{
	errno_t rc;
	int32_t  ind;
	int32_t  len1;
	int32_t  len2;
	int32_t  len3;
	
	wchar_t   str1[LEN];
	wchar_t   str2[LEN];

	rc = wcscat_s(NULL, LEN, str2);
	assert(rc == EINVAL);

	/*--------------------------------------------------*/

	rc = wcscat_s(str1, LEN, NULL);
	assert(rc == EINVAL_AND_RESET);

	/*--------------------------------------------------*/

	rc = wcscat_s(str1, 0, str2);
	assert( rc == ERANGE);

	/*--------------------------------------------------*/

	rc = wcscat_s(str1, (SECUREC_STRING_MAX_LEN + 1), str2);
	assert(rc == ERANGE);

	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"aaaaaaaaaa");
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcscat_s(str1, 1, str2);
	assert(rc == EINVAL_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	wcscpy_s(str1,LEN, L"aaaaaaaaaa");
	wcscpy_s(str2,LEN, L"keep it simple");

	rc = wcscat_s(str1, 2, str2);
	assert(rc == EINVAL_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	wcscpy_s(&str1[0],LEN, L"aaaaaaaaaa");
	wcscpy_s(&str2[0],LEN, L"keep it simple");

	len1 = wslen(str1);
	len2 = wslen(str2);

	rc = wcscat_s(str1, 50, str2);
	assert(rc == EOK);

	len3 = wslen(str1);
	assert(len3 == (len1 + len2));

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	wcscpy_s(str2,LEN, L"keep it simple");

	rc = wcscat_s(str1, 1, str2);

	assert(rc == ERANGE_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcscat_s(str1, 2, str2);
	assert(rc == ERANGE_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	str1[0] = '\0';
	wcscpy_s(str2,LEN, L"keep it simple");

	rc = wcscat_s(str1, 20, str2);

	assert(rc == EOK);
	ind = my_wcscmp(str1, str2);
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	str2[0] = '\0';

	rc = wcscat_s(str1, LEN, str2);

	assert(rc == EOK);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	str1[0] = '\0';
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcscat_s(str1, LEN, str2);

	assert(rc == EOK);

	ind = my_wcscmp(str1, str2);
	assert(ind == 0);

	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"qqweqq");
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcscat_s(str1, LEN, str2);

	assert(rc == EOK);

	ind = my_wcscmp(str1, L"qqweqqkeep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"1234");
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcscat_s(str1, 12, str2);
	assert(rc == ERANGE_AND_RESET);

	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"1234");
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcscat_s(str1, 52, str2);
	assert(rc == EOK);

	ind = my_wcscmp(str1, L"1234keep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"12345678901234567890");

	rc = wcscat_s(str1, 8, &str1[7]);

	assert(rc == EOVERLAP_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"123456789");

	rc = wcscat_s(str1, 9, &str1[8]);

	assert(rc == EOVERLAP_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	wcscpy_s(str2, LEN, L"123");
	wcscpy_s(str1, LEN, L"keep it simple");

	rc = wcscat_s(str2, 31, &str1[0]);

	assert(rc == EOK);

	ind = my_wcscmp(str2, L"123keep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/

	wcscpy_s(str2, LEN, L"1234");
	wcscpy_s(str1, LEN, L"56789");

	rc = wcscat_s(str2, 10, str1);
	assert(rc == EOK);

	ind = my_wcscmp(str2, L"123456789");
	assert(ind == 0);

	/*--------------------------------------------------*/
}


void test_wcsncat_s(void)
{
	errno_t rc;
	int32_t ind;
	
	wchar_t   str1[LEN];
	wchar_t   str2[LEN];

/*--------------------------------------------------*/

	rc = wcsncat_s(NULL, LEN, str2, LEN);

	assert(rc == EINVAL);

	/*--------------------------------------------------*/

	rc = wcsncat_s(str1, LEN, NULL, LEN);

	assert(rc == EINVAL_AND_RESET); 

	/*--------------------------------------------------*/

	rc = wcsncat_s(str1, 0, str2, LEN);

	assert(rc == ERANGE);

	/*--------------------------------------------------*/

	rc = wcsncat_s(str1, (SECUREC_STRING_MAX_LEN+1), str2, LEN);

	assert(rc == ERANGE);

	/*--------------------------------------------------*/

	rc = wcsncat_s(str1, (SECUREC_STRING_MAX_LEN), str2, (SECUREC_STRING_MAX_LEN + 1));

	assert(rc = ERANGE);

	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN, L"aaaaaaaaaa");
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcsncat_s(str1, 1, str2, LEN);

	assert(rc == EINVAL_AND_RESET);

	/*--------------------------------------------------*/

	wcscpy_s(str1,LEN, L"aaaaaaaaaa");
	wcscpy_s(str2,LEN, L"keep it simple");

	rc = wcsncat_s(str1, 2, str2, LEN);

	assert(rc == EINVAL_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	wcscpy_s(str1,LEN, L"a");
	wcscpy_s(str2, LEN,L"b");

	rc = wcsncat_s(str1, 2, str2, 1);
	assert(rc == ERANGE_AND_RESET);
	assert(str1[0] == '\0');

	/*--------------------------------------------------*/

	wcscpy_s(str1,LEN, L"a");
	wcscpy_s(str2,LEN, L"b");

	rc = wcsncat_s(str1, 3, str2, 1);

	assert(rc == EOK);

	ind = my_wcscmp(str1, L"ab");
	assert(ind == 0);

	/*--------------------------------------------------*/

	wcscpy_s(str1, LEN,L"aaaaaaaaaa");
	wcscpy_s(str2, LEN,L"keep it simple");

	rc = wcsncat_s(str1, 50, str2, LEN);
	assert(rc == EOK);

	ind = my_wcscmp(str1, L"aaaaaaaaaakeep it simple");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/*--------------------------------------------------*/
	/* TR example */

	wcscpy_s(str1,LEN, L"good");
	wcscpy_s(str2,LEN, L"bye");

	rc = wcsncat_s(str1, 100, str2, 100);
	assert( rc == EOK);

	ind = my_wcscmp(str1, L"goodbye");
	assert(ind == 0);

	/*--------------------------------------------------*/
	/* TR example */

	wcscpy_s(str1, LEN,L"hello");

	rc = wcsncat_s(str1, 6, L"", 1);
	assert( rc == EOK);

	ind = my_wcscmp(str1, L"hello");
	assert( ind == 0 );

	/*--------------------------------------------------*/
	/* TR example */

	wcscpy_s(str1,LEN, L"hello");

	rc = wcsncat_s(str1, 6, L"X", 2);
	assert(rc == ERANGE_AND_RESET);

	assert(str1[0] == '\0');

	/*--------------------------------------------------*/
	/* TR example */

	wcscpy_s(str1, LEN, L"abc");

	rc = wcsncat_s(str1, 7, L"defghijklmn", 3);
	assert( rc == EOK);

	ind = my_wcscmp(str1, L"abcdef");
	assert(ind == 0);

	/*--------------------------------------------------*/
}


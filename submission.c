#include<stdio.h>
#include "intal.h"
#include<string.h>
#include<stdlib.h>
// #define INTAL_SIZE 1001

// Removing initial zeroes
static char* removeZeroes(char* intal)
{
    int count = 0;
    int len = strlen(intal);
    for(int i = 0;i<len;++i)
    {
        if(intal[i] == '0')
            ++count;
        else
            break;
        
    }

    if(count == len)
    {
        // free(intal);
        // char* intzero = (char*)calloc(INTAL_SIZE,sizeof(char));
        char* intzero = (char*)calloc(2,sizeof(char));
        intzero[0] = '0';
        intzero[1] = '\0';
        free(intal);
        return intzero;
    }
    if(count == 0)
    {
        return intal;
    }
    else
    {
        int newlen = len - count + 1;
        // char* noz = (char*)calloc(INTAL_SIZE,sizeof(char));
        // printf("remove %d\n",newlen);
        char* noz = (char*)calloc(newlen+1,sizeof(char));
        noz[newlen-1] = '\0';
        for(int i = count;i<len;++i)
        {
            noz[i-count] = intal[i];
        }
        free(intal);
        return noz;
    }
}

char* intal_add(const char* intal1, const char* intal2)
{
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	int res=len1;
	if(len2>len1)
		res=len2;
	char *ret=(char *)malloc(sizeof(char)*(res+2));
	ret[res+1]='\0';
	int i=len1-1;
	int j=len2-1;
	int k=res;
	int carry=0;
	int sum;
	while (i>=0 || j>=0)
	{
		int ele1=0;
		int ele2=0;
		if(i>=0)
			ele1=intal1[i]-48;
		if(j>=0)
			ele2=intal2[j]-48;
		sum=ele1+ele2+carry;
		ret[k]=sum%10+48;
		carry=sum/10;
		i--;j--;k--;
	}
	ret[0]=carry+48;
	return removeZeroes(ret);
}

int intal_compare(const char* intal1, const char* intal2)
{
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    if(len1 == len2)
    {
        int temp1,temp2;
        for(int i = 0;i<len1;++i)
        {
            temp1 = intal1[i] - '0';
            temp2 = intal2[i] - '0';
            if(temp1==temp2)
                continue;
            else if(temp1>temp2)
                return 1;
            else if(temp1<temp2)
                return -1; 
        }
        return 0;
    }
    else if(len1 > len2)
    {
        return 1;
    }
    else
        return -1;
}

char* intal_diff(const char* intal1,const char* intal2)
{
    if(intal_compare(intal1,intal2) == -1)
    {
        const char* temp = intal1;
        intal1 = intal2;
        intal2 = temp;
    }

    int n1 = strlen(intal1);
    int n2 = strlen(intal2);
    char *answer = (char*)calloc((n1+1),sizeof(char));
    // char* answer = (char*)calloc(INTAL_SIZE,sizeof(char));
    int ans_len = n1;
    answer[ans_len--] = '\0';
    int diff = n1-n2;
    int carry = 0;
    for(int i = n2-1;i>=0;i--)
    {
        int sub = (intal1[i+diff] - '0') - (intal2[i] - '0') - carry;

        if(sub<0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        
        answer[ans_len--] = (sub + '0');
    }
    for(int i = diff - 1;i>=0;--i)
    {
        int sub = (intal1[i]-'0')-carry;

        if(sub<0)
        {
            sub = sub+10;
            carry = 1;
        }
        else
            carry = 0;

        answer[ans_len--] = (sub+'0');
        
    }
    return removeZeroes(answer);
}

char* intal_fibonacci(unsigned int n)
{
    if(n == 0)
    {
        // char* intzero = (char*)calloc(INTAL_SIZE,sizeof(char));
        char* intzero = (char*)calloc(2,sizeof(char));
        intzero[0] = '0';
        intzero[1] = '\0';
        return intzero;
    }

    else if(n == 1 || n==2)
    {
        // char* intone = (char*)calloc(INTAL_SIZE,sizeof(char));
        char* intone = (char*)calloc(2,sizeof(char));
        intone[0] = '1';
        intone[1] =  '\0';
        return intone;
    }

    else
    {
        // char* a =  (char*)calloc(INTAL_SIZE,sizeof(char));
        char* a = (char*)calloc(2,sizeof(char));
        a[0] = '0'; a[1] = '\0';
        // char* b =  (char*)calloc(INTAL_SIZE,sizeof(char));
        char* b = (char*)calloc(2,sizeof(char));
        b[0] = '1'; b[1] = '\0';
        char* c;
        // char* tofreeb;
        for(int i = 2;i<n+1;++i)
        {
            // char* tofreec = c;
            c = intal_add(a,b);
            free(a);
            a = b;
            // tofreeb = b;
            b = c;
        }
        free(a);
        return b;
    }
    
}

// // 0 1 1 2 3 5 8 13 21 34 55
char* intal_multiply(const char* intal1,const char* intal2)
{
    // char* intzero = (char*)calloc(INTAL_SIZE,sizeof(char));
    char* intzero = (char*)calloc(2,sizeof(char));
    intzero[0] = '0';
    intzero[1] = '\0';
    
    if(strlen(intal1) == 0 || strlen(intal2) == 0)
        return intzero;
    
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int ans_len = len1+len2;
    int* result = (int*)calloc(ans_len,sizeof(int));

    int i_n1 = 0;
    int i_n2 = 0;

    for(int i = len1-1;i>=0;--i)
    {
        int carry = 0;
        int n1 = intal1[i] - '0';
        i_n2 = 0;
        for(int j = len2-1;j>=0;--j)
        {
            int n2 = intal2[j] - '0';
            int sum = n1*n2 + (int)result[i_n1+i_n2]  + carry;
            carry = sum/10;
            result[i_n1+i_n2] = sum%10;
            i_n2++;
        }
        if(carry>0)
            result[i_n1+i_n2] +=carry;

        i_n1++;
    }
    
    int iter = ans_len-1;
    while(iter>=0 && result[iter] == 0)
        iter--;

    if(iter == -1)
    {
        free(result);
        return intzero;
    }
    free(intzero);
    char* answer = (char*)malloc((iter+2)*sizeof(char));
    // char* answer = (char*)calloc(INTAL_SIZE,sizeof(char));
    answer[iter+1] = '\0';

    int tempiter = iter;
    while(iter >=0)
    {

        answer[tempiter - iter] = result[iter] + '0';
        iter--;
    }
    free(result);
    return answer;
}

char* intal_pow(const char* intal1, unsigned int n)
{
    if(intal_compare(intal1,"0") == 0)
    {
        char * intzero = (char*)calloc(2,sizeof(char));
        intzero[0] = '0';
        intzero[1] = '\0'; 
        return intzero;      
    }
    if(n == 0)
    {
        // char * intone = (char*)calloc(INTAL_SIZE,sizeof(char));
        char * intone = (char*)calloc(2,sizeof(char));
        intone[0] = '1';
        intone[1] = '\0'; 
        return intone;
    }
    char* ans = intal_add(intal1,"0");
    int temp = 2;
    while(temp<=n && temp%2 == 0)
    {
        char* tofree = ans;
        ans = intal_multiply(ans,ans);
        free(tofree);
        temp = temp<<1;
    }
    temp = temp>>1;
    for(int i = temp;i<n;++i)
    {
        char *tofreea = ans;
        ans = intal_multiply(ans,intal1);
        free(tofreea);
    }
    return ans;
}


char* intal_gcd(const char* intal1,const char* intal2)
{
    // char* intzero = (char*)calloc(INTAL_SIZE,sizeof(char));
    char* intzero = (char*)calloc(2,sizeof(char));
    intzero[0] = '0';
    intzero[1] = '\0';
    if(intal_compare(intal1,intzero) == 0 && intal_compare(intal2,intzero) == 0)
        return intzero;
    if(intal_compare(intal1,intzero) == 0)
    {
        free(intzero);
        return intal_add(intal2,"0");
    }
    if(intal_compare(intal2,"0") == 0)
    {
        free(intzero);
        return intal_add(intal1,"0");
    }

    char* a = intal_multiply(intal1,"1");
    char* b = intal_multiply(intal2,"1");
    while(intal_compare(a,b)!=0)
    {
        if(intal_compare(a,intzero) == 0)
        {
            free(intzero);
            free(a);
            return b;
        }
        
        if(intal_compare(b,intzero) == 0)
        {
            free(intzero);
            free(b);
            return a;
        }
        // a>b
        if(intal_compare(a,b) == 1)
        {
            char* tofreea = a;
            a = intal_mod(a,b);
            free(tofreea);
        }
        else
        {
            // a<b
            char* tofreeb = b;
            b = intal_mod(b,a);
            free(tofreeb);
        }
    }
    free(intzero);
    free(b);
    return a;
}

char* intal_factorial(unsigned int n)
{
    // char* intone = (char*)calloc(INTAL_SIZE,sizeof(char));
    char* intone = (char*)calloc(2,sizeof(char));
    intone[0] = '1';
    intone[1] = '\0';
    if(n == 0 || n == 1)
        return intone;

    char* iter = intal_add(intone,intone);
    char* answer = intal_multiply(intone,intone);
    for(int i = 2;i<=n;++i)
    {
        char* tofree1 = answer;
        answer = intal_multiply(answer,iter);
        char* tofree2 = iter;
        iter = intal_add(iter,intone);
        free(tofree1);
        free(tofree2);
    }
    free(iter);
    free(intone);
    return answer;
}

int intal_max(char **arr, int n)
{
    if(n == 1)
        return 0;
    else
    {
        char* max = arr[0];
        int index = 0;
        for(int i = 1;i<n;++i)
        {
            if(intal_compare(arr[i],max) == 1)
            {
                max = arr[i];
                index = i;
            }
        }
        return index;
    }
}

int intal_min(char **arr, int n)
{
    if(n == 1)
        return 0;

    else
    {
        char* min = arr[0];
        int index = 0;
        for(int i = 1;i<n;++i)
        {
            if(intal_compare(arr[i],min) == -1)
            {
                min = arr[i];
                index = i;
            }
        }
        return index;
    }
}

int intal_search(char **arr, int n,const char* key)
{
    int found = -1;
    for(int i = 0;i<n;++i)
    {
        if(intal_compare(key,arr[i]) == 0)
        {
            found = i;
            return found;
        }
    }
    return -1;
}

char* coin_row_problem(char **arr, int n)
{
    // char* prev = (char*)malloc(INTAL_SIZE*sizeof(char));
    char* prev = (char*)calloc(2,sizeof(char));
    prev[0] = '0';
    prev[1] = '\0';
    if(n == 0)
        return prev;

    char* cur = intal_add(arr[0],"0");
    char* next;
    for(int i = 2;i<=n;++i)
    {
        char* temp = intal_add(prev,arr[i-1]);
        int comp = intal_compare(temp,cur);
        if(comp >=0)
        {
            next = temp;
        }
        else
        {
            // printf("else\n");
            free(temp);
            next = intal_add(cur,"0");
        }
        char* tofree = prev;
        prev = cur;
        cur = next;
        free(tofree);
    }
    free(prev);
    return cur;
}

static int min(int a,int b)
{
    if(a<b)
        return a;
    else 
        return b;
}

static char* intal_slice(char *intal,int start,int end)
{
	char* ans=(char*)calloc((end-start+2),sizeof(char));
    // printf("%d\n",end-start+2);
    int index = 0;
    
    for(int i = start; i < min(end,strlen(intal)); ++i)
        ans[index++] = intal[i];
   
    ans[index] = '\0';
    // printf("heyy%s %s\n",ans,intal);
    return ans;    
}

char* intal_mod(const char* intal1, const char* intal2)
{
	char * zero=(char*)calloc(2,sizeof(char));
	zero[0]= '0';
	zero[1]= '\0';
	int len1 = strlen(intal1);
    int len2 = strlen(intal2);
	char *dividend = intal_add(intal1,zero);
	char * frh;
	char * toFree;
    while(intal_compare(dividend,intal2) != -1)
    {
        // getchar();
        
        char * ans=intal_slice(dividend,0,len2);
        // printf("%s\n",ans);
		if(intal_compare(ans,intal2) == -1){
			frh=ans;
			ans=intal_slice(dividend,0, len2 + 1);
			free(frh);
		}
		int ans_length = strlen(ans);
		while(intal_compare(ans,intal2) != -1)
        {
            char *toFree = ans;
            ans = intal_diff(ans,intal2);
            free(toFree);
        }
        if(intal_compare(ans,zero) == 0)
        {	
        	frh=ans;
            ans=intal_slice(dividend,ans_length, len1);
            toFree=dividend;
            dividend=intal_add(ans,zero);
            free(toFree);
            free(frh);
            free(ans);
        }
        else
        {
            char * rem=intal_slice(dividend,ans_length, len1);
            int len1=strlen(ans);
            int len2=strlen(rem);
            int i=0;
            toFree=dividend;
            dividend=(char*)calloc((len1+len2+1),sizeof(char));
            // dividend = (char*)calloc(1001,sizeof(char));

           	while(i<len1)
           	{
           		dividend[i]=ans[i];
           		i++;
           	}
           	int j=0;
           	while(j<len2)
           	{
           		dividend[i+j]=rem[j];
           		j++;
           	}
           	dividend[i+j]='\0';
            free(toFree);
            free(ans);
            free(rem);
        }
        
   	}
    free(zero);
    return removeZeroes(dividend);
}


static void heapify(char** arr,int n,int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l<n && intal_compare(arr[l],arr[largest])==1)
        largest = l;

    if(r<n && intal_compare(arr[r],arr[largest])==1)
        largest = r;

    if(largest!=i)
    {
        char* temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
	    heapify(arr,n,largest);
    }
}


void intal_sort(char **arr, int n)
{
    for(int i=(n/2-1);i>=0;i--)
        heapify(arr,n,i);
   
    for(int i=n-1;i>0;i--)
    {
        char* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr,i,0);
    }
}

int intal_binsearch(char **arr, int n,const char* key)
{
	int start=0;
	int end=n-1;
	int mid=(start+end)/2;
	while(start<=end)
	{
		int k=intal_compare(arr[mid],key);
		if(k==0)
            if(mid>start && intal_compare(arr[mid-1],key) == 0)
                end = mid -1;
            else
    			return mid;

		else if(k==-1)
		{
			start=mid+1;
		}
		else
			end=mid-1;
		mid=(start+end)/2;
	}
	return -1;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    if(k>n)
    {
        char* intzero = (char*)calloc(2,sizeof(char));
        intzero[0] = '0';
        intzero[1] = '\0';
        return intzero;
    }

    if(k > n/2)
        k = n - k;

    char **row = (char **)calloc(k + 1, sizeof(char *));
    for(int i = 0; i < k + 1; ++i)
    {
        // row[i] = (char *)calloc(INTAL_SIZE,sizeof(char));
        row[i] = (char *)calloc(2,sizeof(char));
        strcpy(row[i],"0");
    }
    strcpy(row[0],"1");
    for(int i = 1; i <= n; ++i)
    {
        for(int j = i < k ? i : k; j > 0; --j)
        {
            char *toFree = row[j];
            row[j] = intal_add(row[j],row[j-1]);
            free(toFree);
        }
    }
    char *result = row[k];
    
    for(int i = 0; i < k; ++i)
        free(row[i]);
        
    free(row);
    return result;
}

#include<stdio.h>
#include<string.h>

typedef struct MyStruct
{
	int used;
	struct MyStruct *next[10];
} MyStruct;

int addr_len = 0;
MyStruct addr[100010];

MyStruct *new_MyStruct()
{
	int i;

	for (i = 0; i < 10; i++)
		addr[addr_len].next[i] = NULL;
	addr[addr_len].used = 0;

	return addr + addr_len++;
}
int add_MyStruct(char *n, MyStruct *root)
{
	MyStruct **next;
	int i, n_len;

	// handle exception
	if (root <= 0 || n <= 0) return 0;

	n_len = strlen(n);

	// try add
	i = 0;
	while (i < n_len)
	{
		next = &(root->next[n[i] - '0']);
		if (*next == NULL)
		{
			*next = new_MyStruct();
		}
		else if (i == n_len - 1 || (*next)->used == 1)
		{
			// can't add
			return 0;
		}
		root = *next;
		i++;
	}

	root->used = 1;
	return 1;
}

int main()
{
	MyStruct *phone_book;
	int t, n, consistency;
	char phone_number[11];

	scanf("%d", &t);
	while (t--)
	{
		phone_book = new_MyStruct();
		consistency = 1;
		scanf("%d", &n);
		while (n--)
		{
			scanf("%s", phone_number);
			if (consistency)
				consistency = add_MyStruct(phone_number, phone_book);
		}
		if (consistency) printf("YES\n");
		else printf("NO\n");
		addr_len = 0;
	}
}
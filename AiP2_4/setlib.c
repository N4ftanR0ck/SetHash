#include <stdio.h>
#include "setlib.h"
#include <malloc.h>

int hash(void* elem, int size) {
	int x = *((int*)elem);
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x%size;
}

set* initEmpty()
{
	set* s = (set*)malloc(sizeof(set));
	s->size = 0;
	s->args = NULL;
	return s;
};

set* initArgs(void* elems, int size, char type)
{
	set* s = (set*)malloc(sizeof(set));
	s->size = size * 2;
	s->args = (item*)malloc(sizeof(item) * s->size);
	if (type == 'i')
	{
		for (int i = 0; i < size; i++)
		{
			s = addElem(s, (int*)elems + i, 'i');
		}
	}
	if (type == 'f')
	{
		for (int i = 0; i < size; i++)
		{

			s = addElem(s, (int*)elems + i, 'f');
		}
	}
	if (type == 'c')
	{
		for (int i = 0; i < size; i++)
		{
			s = addElem(s, (int*)elems + i, 'c');
		}
	}

	return s;
};

int getElem(set* s, void* elem)
{
	item* args = s->args;
	int shift = 0;
	int hsh = hash(elem, s->size);
	while (!ifType((args[hsh + shift]).type) && hsh + shift < s->size)
	{
		if (args[hsh + shift].num == *((int*)elem))
			return hsh + shift + 1;
		++shift;
	}
	if (hsh + shift == s->size)
	{
		shift = -hsh;
		while (!ifType((args[hsh + shift]).type) && hsh + shift < hsh)
		{
			if (args[hsh + shift].num == *((int*)elem))
				return hsh + shift + 1;
			shift++;
		}
	}
	return 0;
};

set* addElem(set* s, void* elem, char type)
{
	item* args = s->args;
	int shift = 0;
	if (getElem(s, elem))
		return s;
	int hsh = hash(elem, s->size);
	while (!ifType((args[hsh + shift]).type) && hsh + shift < s->size)
	{
		shift++;
	}
	if (hsh + shift == s->size)
	{
		shift = -hsh;
		while (!ifType((args[hsh + shift]).type) && hsh + shift < hsh)
		{
			shift++;
		}
	}
	
	args[hsh+shift].type = type;
	args[hsh+shift].num = *(int*)elem;
	return s;
};

int ifType(char type)
{
	if (type != 'i' && type != 'c' && type != 'f')
		return 1;
	return 0;
}


set* delElem(set* s, int elem)
{
	int pos = getElem(s, &elem);
	if (pos)
		((s->args)[pos-1]).type = 0;
	return s;
};

void printSet(set* s)
{
	item* args = s->args;
	void* n;
	for (int i = 0; i < s->size; i++)
	{
		/*if (!ifType(args->type))
			continue;*/
		n = &(args->num);
		if (args->type == 'i')
		{
			printf("%d: %d\n", i, *(int*)n);
		}
		if (args->type == 'c')
		{
			printf("%d: %c\n", i, *(char*)n);
		}
		if (args->type == 'f')
		{
			printf("%d: %f\n", i, *(float*)n);
		}
		++args;
	}
};

set* unification(set* s1, set* s2)
{
	set* s = (set*)malloc(sizeof(set)); 
	s->size = (s1->size + s2->size);
	s->args = (item*)malloc(s->size * sizeof(item));
	item* args = s2->args;
	for (int i = 0; i < s2->size; i++)
	{
		if (ifType(args->type))
		{
			++args;
			continue;
		}
		addElem(s, &(args->num), args->type);
		++args;
	}
	args = s1->args;
	for (int i = 0; i < s1->size; i++)
	{
		if (ifType(args->type))
		{
			++args;
			continue;
		}
		addElem(s, &(args->num), args->type);
		++args;
	}
	free(s1->args);
	free(s2->args);
	s1->args = NULL;
	s2->args = NULL;
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return s;
};
set* intersection(set* s1, set* s2)
{
	set* s = (set*)malloc(sizeof(set));
	if (s1->size > s2->size)
		s->size = (s1->size);
	else
		s->size = (s2->size);
	s->args = (item*)malloc(s->size * sizeof(item));
	item* args = s2->args;
	for (int i = 0; i < s2->size; i++)
	{
		if (ifType(args->type))
		{
			++args;
			continue;
		}
		if (getElem(s1, &(args->num)))
			addElem(s, &(args->num), args->type);
		++args;
	}
	free(s1->args);
	free(s2->args);
	s1->args = NULL;
	s2->args = NULL;
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return s;
};

set* symdif(set* s1, set* s2)
{
	set* s = (set*)malloc(sizeof(set)); 
	s->size = (s1->size + s2->size);
	s->args = (item*)malloc(s->size * sizeof(item));
	item* args = s2->args;
	for (int i = 0; i < s2->size; i++)
	{
		if (ifType(args->type))
		{
			++args;
			continue;
		}
		if (!getElem(s1, &(args->num)))
			addElem(s, &(args->num), args->type);
		++args;
	}
	args = s1->args;
	for (int i = 0; i < s1->size; i++)
	{
		if (ifType(args->type))
		{
			++args;
			continue;
		}
		if (!getElem(s2, &(args->num)))
			addElem(s, &(args->num), args->type);
		++args;
	}
	free(s1->args);
	free(s2->args);
	s1->args = NULL;
	s2->args = NULL;
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return s;
};
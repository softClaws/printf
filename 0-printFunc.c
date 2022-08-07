#include "main.h"
/**
 * get_print_func - selects the correct function to perform the operation.
 * @s: argument indentifier
 * @index: index for argument indentifier
 * Return: pointer to a function.
 */
int (*get_print_func(const char *s, int index))(va_list, char *, unsigned int)
{
	print_t pr[] = {
		{"c", print_chr}, {"s", print_str},
		{"%", print_prg}, {"i", print_int},
		{"b", print_bnr}, {"d", print_int},
		{"u", print_unt}, {"o", print_oct},
		{"x", print_hex}, {"X", print_upx},
		{"S", print_usr}, {"p", print_add},
		{"#o", prinnoct}, {"#x", prinnhex},
		{"#X", prinnupx}, {"#i", print_int},
		{"#d", print_int}, {"#u", print_unt},
		{"+i", prinpint}, {"+d", prinpint},
		{"+u", print_unt}, {"+o", print_oct},
		{"+x", print_hex}, {"+X", print_upx},
		{" i", prinsint}, {" d", prinsint},
		{" u", print_unt}, {" o", print_oct},
		{" x", print_hex}, {" X", print_upx},
		{" +i", prinpint}, {" +d", prinpint},
		{"+ i", prinpint}, {"+ d", prinpint},
		{" %", print_prg},
		{NULL, NULL},
	};
	int i = 0, j = 0, first_index;

	first_index = index;
	while (pr[i].type_arg)
	{
		if (s[index] == pr[i].type_arg[j])
		{
			if (pr[i].type_arg[j + 1] != '\0')
				index++, j++;
			else
				break;
		}
		else
		{
			j = 0;
			i++;
			index = first_index;
		}
	}
	return (pr[i].f);
}
/**
 * ev_print_func - returns the amount of identifiers.
 * @s: argument indentifier
 * @index: index of argument identifier.
 * Return: amount of identifiers.
 */
int ev_print_func(const char *s, int index)
{
	print_t pr[] = {
		{"c", print_chr}, {"s", print_str}, {"%", print_prg},
		{"i", print_int}, {"d", print_int}, {"b", print_bnr},
		{"u", print_unt}, {"o", print_oct}, {"x", print_hex},
		{"X", print_upx}, {"S", print_usr}, {"p", print_add},
		{"#o", prinnoct}, {"#x", prinnhex}, {"#X", prinnupx},
		{"#i", print_int}, {"#d", print_int}, {"#u", print_unt},
		{"+i", prinpint}, {"+d", prinpint}, {"+u", print_unt},
		{"+o", print_oct}, {"+x", print_hex}, {"+X", print_upx},
		{" i", prinsint}, {" d", prinsint}, {" u", print_unt},
		{" o", print_oct}, {" x", print_hex}, {" X", print_upx},
		{" +i", prinpint}, {" +d", prinpint},
		{"+ i", prinpint}, {"+ d", prinpint}, {" %", print_prg},
		{NULL, NULL},
	};
	int i = 0, j = 0, first_index;

	first_index = index;
	while (pr[i].type_arg)
	{
		if (s[index] == pr[i].type_arg[j])
		{
			if (pr[i].type_arg[j + 1] != '\0')
				index++, j++;
			else
				break;
		}
		else
		{
			j = 0;
			i++;
			index = first_index;
		}
	}
	return (j);
}

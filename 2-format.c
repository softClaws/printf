#include "main.h"

/**
 * fill_oct_array - writes the character c to stdout
 *
 * @bnr: array where is stored the binary.
 * @oct: array where is stored the octal.
 *
 * Return: binary array
 */
char *fill_oct_array(char *bnr, char *oct)
{
	int op, i, j, ioct, limit;

	oct[11] = '\0';
	for (i = 31, ioct = 10; i >= 0; i--, ioct--)
	{
		if (i > 1)
			limit = 4;
		else
			limit = 2;
		for (op = 0, j = 1; j <= limit; j *= 2, i--)
			op = ((bnr[i] - '0') * j) + op;
		i++;
		oct[ioct] = op + '0';
	}
	return (oct);
}

/**
 * fill_hex_array - writes the character c to stdout
 *
 * @bnr: array where is stored the binary.
 * @hex: array where is stored the hexadecimal.
 * @isupp: integer that determines if the hexadecimal array is
 * in uppercase or lowercase letter.
 * @limit: size of hex
 * Return: binary array
 */
char *fill_hex_array(char *bnr, char *hex, int isupp, int limit)
{
	int op, i, j, toletter;

	hex[limit] = '\0';
	if (isupp)
		toletter = 55;
	else
		toletter = 87;
	for (i = (limit * 4) - 1; i >= 0; i--)
	{
		for (op = 0, j = 1; j <= 8; j *= 2, i--)
			op = ((bnr[i] - '0') * j) + op;
		i++;
		if (op < 10)
			hex[i / 4] = op + 48;
		else
			hex[i / 4] = op + toletter;
	}
	return (hex);
}
/**
 * print_usr - prints a string and values of
 * non-printed chars
 * @arguments: input string
 * @buf: buffer pointer
 * @ibuf: index for buffer pointer
 * Return: number of chars printed
 */
int print_usr(va_list arguments, char *buf, unsigned int ibuf)
{
	unsigned char *str;
	char *hexadecimal, *binary;
	unsigned int i, sum, op;

	str = va_arg(arguments, unsigned char *);
	binary = malloc(sizeof(char) * (32 + 1));
	hexadecimal = malloc(sizeof(char) * (8 + 1));
	for (sum = i = 0; str[i]; i++)
	{
		if (str[i] < 32 || str[i] >= 127)
		{
			ibuf = handl_buf(buf, '\\', ibuf);
			ibuf = handl_buf(buf, 'x', ibuf);
			op = str[i];
			binary = fill_binary_array(binary, op, 0, 32);
			hexadecimal = fill_hex_array(binary, hexadecimal, 1, 8);
			ibuf = handl_buf(buf, hexadecimal[6], ibuf);
			ibuf = handl_buf(buf, hexadecimal[7], ibuf);
			sum += 3;
		}
		else
			ibuf = handl_buf(buf, str[i], ibuf);
	}
	free(binary);
	free(hexadecimal);

	return (i + sum);
}
/**
 * print_add - prints the address of an input variable
 * @arguments: input address.
 * @buf: buffer pointer.
 * @ibuf: index for buffer pointer
 *
 * Return: number of chars printed.
 */
int print_add(va_list arguments, char *buf, unsigned int ibuf)
{
	void *add;
	long int int_input;
	int i, count, first_digit, isnegative;
	char *hexadecimal, *binary;
	char nill[] = "(nil)";

	add = (va_arg(arguments, void *));
	if (add == NULL)
	{
		for (i = 0; nill[i]; i++)
			ibuf = handl_buf(buf, nill[i], ibuf);
		return (5);
	}
	int_input = (intptr_t)add;
	isnegative = 0;
	if (int_input < 0)
	{
		int_input = (int_input * -1) - 1;
		isnegative = 1;
	}
	binary = malloc(sizeof(char) * (64 + 1));
	binary = fill_binary_array(binary, int_input, isnegative, 64);
	hexadecimal = malloc(sizeof(char) * (16 + 1));
	hexadecimal = fill_hex_array(binary, hexadecimal, 0, 16);
	ibuf = handl_buf(buf, '0', ibuf);
	ibuf = handl_buf(buf, 'x', ibuf);
	for (first_digit = i = count = 0; hexadecimal[i]; i++)
	{
		if (hexadecimal[i] != '0' && first_digit == 0)
			first_digit = 1;
		if (first_digit)
		{
			ibuf = handl_buf(buf, hexadecimal[i], ibuf);
			count++;
		}
	}
	free(binary);
	free(hexadecimal);
	return (count + 2);
}
/**
 * prinnoct - print the number in octal begining with zero
 * @arguments: input string
 * @buf: buffer pointer
 * @ibuf: index for buffer pointer
 * Return: number of chars printed
 */
int prinnoct(va_list arguments, char *buf, unsigned int ibuf)
{
	int int_input, i, isnegative, count, first_digit;
	char *octal, *binary;

	int_input = va_arg(arguments, int);
	isnegative = 0;
	if (int_input == 0)
	{
		ibuf = handl_buf(buf, '0', ibuf);
		return (1);
	}
	if (int_input < 0)
	{
		int_input = (int_input * -1) - 1;
		isnegative = 1;
	}
	ibuf = handl_buf(buf, '0', ibuf);
	binary = malloc(sizeof(char) * (32 + 1));
	binary = fill_binary_array(binary, int_input, isnegative, 32);
	octal = malloc(sizeof(char) * (11 + 1));
	octal = fill_oct_array(binary, octal);
	for (first_digit = i = count = 0; octal[i]; i++)
	{
		if (octal[i] != '0' && first_digit == 0)
			first_digit = 1;
		if (first_digit)
		{
			ibuf = handl_buf(buf, octal[i], ibuf);
			count++;
		}
	}
	free(binary);
	free(octal);
	return (count + 1);
}

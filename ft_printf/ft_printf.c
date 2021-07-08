#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <libc.h>

int ft_strlen(char *str)
{
   int i =0;
   while (str[i])
      i++;
   return (i);
}

int ft_putchar_len(char c)
{
   write (1, &c, 1);
   return (1);
}

int ft_putstr_len(char *str)
{
   
   int len = ft_strlen(str);
   write(1, str, len);
   return (len);
}

static int	ft_count(long n) 
{
   int i;
   if (n == 0)
      i = 1;
   else
      i = 0;
   while (n)
   {
      n = n/10;
      i++;
   }
   return (i);
}
static char *ft_itoa(long n)
{
   long tmp;
   int size = ft_count(n);
   char *str;

   if (n < 0)
   {
      size = size +1;
      tmp = -n;
   }
   else
      tmp = n;
   if (!(str = malloc(sizeof(char *) * size + 1)))
      return (NULL);
   str[size] = '\0';
   while (size--)
   {
         str[size] = tmp % 10 + '0';
         tmp = tmp / 10;
   }
   if (n < 0)
      str[0] = '-';
   return (str);
}   

static int  ft_count_x(unsigned int n, int base)
{
   int i;
   if (n == 0)
      i = 1;
   else
      i =0;
   while (n)
   {
      n = n /base;
      i++;
   }
   return (i);
}

static char *ft_itoa_x(unsigned int n, int base)
{
   char *str;

   int size = ft_count_x(n, base);
   str = malloc (sizeof(char *) * size + 1);
   if (!str)
      return (NULL);
   str[size] = '\0';
   while (size--)
   {
      if (n % base <= 9)
         str[size] = n % base + '0';
      else
         str[size] = n % base - 10 + 'a';
      n = n / base;
   }
   return (str);
}
 
 int ft_prec_s(char *s, int prec)
{
   
   int i = 0;
   while (s[i] && i < prec)
   {
      ft_putchar_len(s[i++]);
   }
   return (i);
}
 int  ft_s(char *s, int width, int prec)
{
   int i = 0;
   int len;
 if (!s)
      s = "(null)";
   len = ft_strlen(s);
   if (prec < 0)
   {
      if (width)
         width = width - len;
      while (width-- > 0)
         i += ft_putchar_len(' ');
      i += ft_putstr_len(s);
   }
   else if (prec >= 0)
   {
      if (prec > len)
         prec = len; 
      if (width)
         width = width - prec;
      while (width-- > 0)
         i += ft_putchar_len(' ');
      i += ft_prec_s(s, prec);
   }
   return (i);
}

int ft_x(unsigned int n, int width, int prec)
{
   int i = 0;
   char *str= ft_itoa_x(n, 16);
   int len = ft_strlen(str);
   if (prec < 0)
   {
      if (width)
         width = width - len;
      while (width-- > 0)
         i += ft_putchar_len(' ');
      i += ft_putstr_len(str);
   }
   else if (prec >= 0)
   {
      if (n == 0 && prec == 0)
      {
         while (width-- > 0)
          i += ft_putchar_len(' ');
         return (i);
      }
      if (prec > len)
         width = width - prec;
      else
         width = width - len;
      while (width-- > 0)
         i += ft_putchar_len(' ');
      if (prec > len)
      {
         prec = prec - len;
         while (prec--> 0)
            i += ft_putchar_len('0');
      }
      i += ft_putstr_len(str);
   }
   free(str);
   return (i);
}
 
int ft_d(long n, int width, int prec)
{
   int i = 0;
   long  tmp;
   char *str;
   int len;

   tmp = n;
   if (n < 0)
      n = -n;
   str = ft_itoa(n); 
   len = ft_strlen(str); 
   if (prec < 0)
   {
      if (width)
         width  = width - len;
      if (tmp < 0)
         width--;
      while (width-- > 0)
         i += ft_putchar_len(' ');
      if (tmp < 0)
         i += ft_putchar_len('-');
      i += ft_putstr_len(str);
   }
   else if (prec >= 0)
   {
      if (n == 0 && prec == 0)
      {
         while (width-- > 0)
            i += ft_putchar_len(' ');
         return (i);
      }
      if (prec > len)
         width = width - prec;
      else
         width = width - len;
      if (tmp < 0)
         width = width - 1;
      while (width-- > 0)
         i += ft_putchar_len(' ');
      if (tmp < 0)
         i += ft_putchar_len('-');
      if (prec > len)
      {
         prec = prec - len;
         while (prec-- > 0)
         i += ft_putchar_len('0');
      }
      i += ft_putstr_len(str);
   }
   free(str);
   return (i);

}

int ft_process(const char *format, va_list list)
{
   int i = 0;
   int count = 0;

   while (format[i])
   {
      int prec = -1;
      int width = 0;
      if (format[i] == '%')
      {
         i++;
         while(format[i] >= '0' && format[i] <= '9')
         { 
            width = width * 10 + format[i] - '0';
            i++;
         }
         if (format[i] == '.')
         {
            prec = 0;
            i++;
            while (format[i] >= '0' && format[i] <= '9')
            {
               prec = prec * 10 + format[i] - '0';
               i++;
            }
         }
         if (format[i] == 's')
            count += ft_s(va_arg(list, char *), width, prec);
         else if (format[i] == 'x')
            count += ft_x(va_arg(list, unsigned int), width, prec);
         else if (format[i] == 'd')  
            count += ft_d(va_arg(list, int), width, prec);
      }
      else
         count += ft_putchar_len(format[i]);
      i++;
      
   }
   return (count);
}

int ft_printf(const char *format, ...)
{
   int i = 0;
   va_list list;

   va_start(list, format);
   i = ft_process(format, list);
   va_end(list);
   return (i);
}
int main()
 {
    
    int i = ft_printf("%8.0s\n", "toto");
    printf("%d\n\n", i);
    int j = printf("%8.0s\n", "toto");
    printf("%d\n\n", j);
    ft_printf("%8.2s, %5.1d, %6.2x\n", "toto", 23, 15);
    printf("%8.2s, %5.1d, %6.2x\n", "toto", 23, 15);
    ft_printf("%2.8s\n", "toto");
    printf("%2.8s\n\n", "toto");
    
    // prec值短于字符串里截断 多不变 width(8)前面加空格
    printf("%5.0d\n",0); 
     ft_printf("%5.0d\n",0);


     printf("%5.1d\n",-55); 
     ft_printf("%5.1d\n",-55); 
     printf("%5.10d\n",-55); 
     ft_printf("%5.10d\n",-55); 
     printf("%5d\n",-55); 
     ft_printf("%5d\n",-55); 
     printf("%2d\n",-55); 
     ft_printf("%2d\n",-55); 
    //prec 不截断少了加0(-00042)；width(10)前面加空格  d用itoa
    ft_printf("%6.0x\n", 0);
    printf("%6.0x\n\n", 0);
     ft_printf("%6.8x\n", 223455);
    printf("%6.8x\n", 223455);
     ft_printf("%15.6x\n", 223455);
    printf("%15.6x\n", 223455);

     ft_printf("%6.2x\n", 223455);
    printf("%6.2x\n", 223455);
     ft_printf("%6.10x\n", 223455);
    printf("%6.10x\n", 223455);
     ft_printf("%2.6x\n", 223455);
    printf("%2.6x\n", 223455);

    
   //  //prec 不截断少了加0, width（9）加空格 itoa-x
     return 0;
 }

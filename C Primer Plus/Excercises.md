##  第二章编程练习

1.  编写一个程序，调用一次` printf()`函数.........

     ```c
     #include<stdio.h>
     int main(void)
     {
         printf("Asada Shino\n");
         printf("Asada\nShino\n");
         printf("Asada ");
         printf("Shino");
         getchar();
         return 0;
     }
     ```

2.  编写一个程序，打印你的姓名和地址。

   ```c
   #include<stdio.h>
   int main(void)
   {
       printf("My name is Asada Shino\n");
       printf("My address is NanJing Road ZhaoYang District BeiJing.");
       
       getchar();
       return 0;
   }
   ```

3. 编写一个程序把你的年龄转换....

   ```c
   #include<stdio.h>
   int main(void)
   {
      	int age,day;
       age = 10,day = 365;
       printf("%d",age*day);
   	  
       getchar();
       return 0;
   }
   ```

4.  编写一个程序，生成以下输出.....

   ```c
   #include<stdio.h>
   
   void jolly(void);
   void deny(void);
   
   int main(void)
   {
   	jolly();
       jolly();
       jolly();
       deny();
       
       getchar();
       return 0;
   }
   
   void jolly(void)
   {
       printf("For he's a jolly good fellow\n");
   }
   void deny(void)
   {
       printf("which nobody can deny\n");
   }
   ```

5.  编写一个程序，生成以下.......

   ```c
   #include<stdio.h>
   void br(void)
   {
       printf("Brazil,Russia");
   }
   void ic(void)
   {
       printf("India,China");
   }
   int main(void)
   {
   	br();
       printf(",");
       ic();
       printf("\n");
       ic();
       printf(",\n");
       br();
       return 0;
   }
   ```

6.  编写一个程序，创建一个整型变量toes，并将toes设.....

   ```c
   #include<stdio.h>
   int main(void)
   {
   	int toes;
       toes = 10;
       printf("toes multiplied by 2 is %d.\nsquared = %d",toes*2,toes*toes);
       return 0;
   }
   ```

7.  许多研究表明，微笑益处多多。编写一个....

   ```c
   #include<stdio.h>
   void print_smile(void)
   {
       printf("Smlie!");
   }
   int main(void)
   {
     	print_smile();
       print_smile();
       print_smile();
       printf("\n");
       print_smile();
       print_smile();
       printf("\n");
       print_smile();
   	return 0;   
   }
   ```

8.  在C语言中，函数可以调用另一个函数。编写一个.....

   ```c
   #include<stdio.h>
   void two(void)
   {
       printf("two\n");
   }
   void one_three(void)
   {
       printf("one\n");
       two();
       printf("three\ndone!");
       
   }
   int main(void)
   {
   	printf("starting now\n");
       one_three();
       return 0;
   }
   ```

---

## 3.11编程练习

1. 通过试验（即编写带有此类问题的程序）观察...

   ```c
   #include<stdio.h>
   int main(void)
   {
       signed short overflow = 32767;
       printf("%hd\t%hd\n",overflow,overflow+1);
       //32767 -32768
       float f = 92E100;
       printf("%.2f\n",f);
       //1.#J
       f= 0.1234E-100;
       //0.00
       printf("%.2f");
       return 0;
   }
   ```

2. 编写一个程序，要求提示输入一个ASCII码值（如，66）...

   ```c
   void chapter_three2(void)
   {
       char input;
       int num;
       printf("Please enter ASCLL and i will print it:");
       scanf("%d",&num);
       input = num;
       printf("\nThe character was %c .",input);
   }
   ```

3. 编写一个程序，发出一声警报，然后打印下面的文本：

   ```c
   void chapter_three3(void)
   {
       printf("\bStartled by the sudden sound, Sally shouted,\n\"By the Great Pumpkin, what was that!\"");
   }
   
   ```

4. 编写一个程序，读取一个浮点数，先打印成小数点形式，再....

   ```c
   void chapter_three4(void)
   {
       printf("Enter a floating-point value:");
       float user_input;
       scanf("%f",&user_input);
       printf("fixed-point notaion: %.2f",user_input);
       printf("\nexponential notation: %E",user_input);
       printf("\nP notation: %a",user_input);
   }
   ```

5. 一年大约有3.156×107秒。编写一个程序，提示用户输入年龄，...

   ```c
   void chapter_three5(void)
   {
       unsigned short age;
       printf("Enther your age:");
       scanf("%hu",&age);
       printf("Now age %hu will be rewritten to second.",age);
       printf("It is %.0f",3.156E7*age);
   }
   ```

6. 1个水分子的质量约为3.0×10−23克。1夸脱水大约是950克。...

   ```c
   //float-point overflows
   ```

7. 英寸相当于2.54厘米。编写一个程序，提示...

   ```c
   void chapter_three7(void)
   {
       float inch,centimeter;
       
    	printf("What's your height(inch):");
       scanf("%f",&inch);
       //printf("%f",inch);
       centimeter = inch*2.54;
       printf("Your height is %.2f centimeter",centimeter);
   }
   ```

8. 在美国的体积测量系统中，1品脱等于2杯，1杯等于8盎...

   ```c
   void chapter_three8(void)
   {
       float pint,cup,ounce, soup_ladle,teaspoon;
       printf("How mush cup do you have:");
       scanf("%f",&cup);
       pint = cup/2;
       ounce = cup/8;
       soup_ladle = ounce/2;
       teaspoon = soup_ladle/3;
   
       printf("You have %.2f pint.\nYou have %.2f cup.\nYou have %.2f cunce.\nYou have %.2f Soup Ladle.\nYou have %.2f teaspoon."
       ,pint,cup,ounce,soup_ladle,teaspoon);
   }
   ```

## 4.8编程练习

1. 编写一个程序，提示用户输入名和姓，然后以.......

   ```c
   void chapter_four1(void)
   {
       char name[11],surname[11];
       printf("Please enter your name and surname:");
       scanf("%s",name);
       scanf("%s",surname);
       printf("%s %s",name,surname);
   }
   ```

2. 编写一个程序，提示用户输入名和...

   ```c
   void chapter_four2(void)
   {
       char name [31];
       printf("Please enter your name and surname:");
       scanf("%s",name);
       printf("\"%s\"\n",name);
       printf("\"%20s\"\n",name);
       printf("\"%-20s\"\n",name);
       printf("%*s", strlen(name)+3,name);//string.h should be included.
   }
   ```

3. 编写一个程序，读取一个浮点数，首先以小数点...

   ```c
   void chapter_four3(void)
   {
       double user_input;
       printf("Please enter a floating-point:");
       scanf("%lf",&user_input);
       printf("%.1f\t%.1e\n",user_input,user_input);
       printf("%+.3f\t%.3E",user_input,user_input);
   }
   ```

4. 编写一个程序，提示用户输入身高（单位：英寸）和姓...

   ```c
   void chapter_four4(void)
   {
       const float FEET = 0.83333330f;
       printf("Please enter your height in inches:");
       float height;
       scanf("%f",&height);
       printf("Please enter you name:");
       char name[20];
       scanf("%s",name);
       printf("%s,you are %.3f feet tall",name,height*FEET);
   }
   ```

5. 编写一个程序，提示用户输入以兆位每秒（Mb/s）为单位的下...

   ```c
   void chapter_four5(void)
   {   
       const float CONVERT = 8.f;
       float netword_speed,package_size,downloading_time;
       printf("Enter the download speed in megabits per second:");
       scanf("%f",&netword_speed);
       printf("Enter the size of your package you need download in magebyte:");
       scanf("%f",&package_size);
   
       downloading_time = package_size*CONVERT/netword_speed;
       printf("At %.2f megabits per second, a file of %.2f megabytes.\ndownloads in %.2f seconds",netword_speed,package_size,downloading_time);
   }
   
   ```

6. 编写一个程序，先提示用户输入名，然后提示用户输入姓。在...

   ```c
   void chapter_four6(void)
   {
       char name[11],surname[11];
       unsigned short lenght1,lenght2;
       printf("Enter your name:");
       scanf("%s",name);
       printf("Enter your surname:");
       scanf("%s",surname);
       lenght1 = strlen(name);
       lenght2 = strlen(surname);
       printf("%s %s\n%-*d %-*d",name,surname,lenght1,lenght2,lenght1,lenght2);
   }
   ```

7. 编写一个程序，将一个double类型的变量设...

   ```c
   void chapter_four7(void)
   {
       double d = 1.0/3.0;
       float f = 1.f/3.f;
       printf("double = %.6f\ndouble = %.12f\ndouble = %.16f",d,d,d);
       printf("\nfloat = %.6f\nfloat = %.12f\nfloat = %.16f",f,f,f);
       printf("\n%u",DBL_DIG);
       printf("\n%u",FLT_DIG);
   }
   ```

8. 编写一个程序，提示用户输入旅行的里程....

   ```c
   #include<stdio.h>
   int main(void)
   {
       
       return 
           0;
   }
   ```
   

## 5.11编程练习

1. 编写一个程序，把用分钟表示的...

   ```c
   void chapter_five1(void)
   {
       const int M_PER_HOUR = 60;
       int minutes,left,hour;
       printf("Please enter minutes:");
       scanf("%d",&minutes);
       //printf("%d",minutes);
       while (minutes>=30)
       {
           
           left=minutes%M_PER_HOUR;
           hour = minutes/M_PER_HOUR;
           printf("%dH%dM\n\
   Now enter anther minutes(<=0 to quit)",hour,left);
           scanf("%d",&minutes);
       }
       
   }
   ```

2. 编写一个程序，提示用户输入一.....

   ```c
   void chapter_five2(void)
   {
       int intager,mark;
       printf("Please enter an intager:");
       while (scanf("%d",&intager))
       {
           mark=11;
           while (mark--)
           {
               printf("%d\t",intager);
               ++intager;
               
           }
           printf("\nEnter another intager or enter 'q' to quit\n");
       }
       
   }
   ```

3. 编写一个程序，提示用户输入天数，然...

   ```c
   void chapter_five3(void)
   {
       unsigned int day,week,left;
       printf("Enter the number of day(s):");
       while (scanf("%d",&day))
       {
           week = day/7;
           left=day%7;
           printf("%d days are %d week %d days",day,week,left);
           printf("\nNow enter another number or enter 'q' to quit:");
       }
       
   }
   ```

4. 编写一个程序，提示用户输入一个身高（单位：厘米），并分别以....

   ```c
   void chapter_five4(void)
   {
       const double CM_PER_FEET = 30.48;
       const double CM_PER_INCH = 2.54;
       double height,inches;
       unsigned short feet;
       printf("Enter a height in centimeters:");
       scanf("%lf",&height);
       while (height>0)
       {
           feet = (int)height/CM_PER_FEET;
           inches = (height - feet*CM_PER_FEET)/CM_PER_INCH;
           printf("%.1f cm = %hu feet %.1f inches.\n",height,feet,inches);
           printf("Enter a height in centimeters (<=0 to quit)");
           scanf("%lf",&height);
       }
       printf("bye");
   }
   ```

5. 修改程序addemup.c（程序清单5.13），你可以认....

   ```c
   void chapter_five5(void)
   {
       int user_input,total;
       printf("Enter a number:");
       while (scanf("%d",&user_input))
       {
           total = (1+user_input)*user_input/2;
           printf("The addition result of 1 to %d is %d\n",user_input,total);
           printf("Now enter another number or enter 'q' to quit:");
   
       }
       
       
   }
   ```

6. 修改编程练习5的程序，使其能计算整数的平方....

   ```c
   void chapter_five6(void)
   {
       long long int user_input,total;
       unsigned long long temp1,temp2;
       printf("Enter a number:");
       while (scanf("%lld",&user_input))
       {
           temp1 =user_input+1;
           temp2 =2*user_input+1;
           total = user_input*temp1*temp2/6;
           printf("The squared result of 1 to %lld is %llu\n",user_input,total);
           printf("Now enter another number or enter 'q' to quit:");
   
       }
       
       
   }
   ```

7. 编写一个程序，提示用户输入一个double类型的数，并...

   ```c
   #include<stdio.h>
   
   void squared(const double num)
   {
       printf("%.2f",num*num);
   }
   int main(void)
   {
       double num;
       printf("Enter a number:");
       scanf("%lf",&num);
       squared(num);
       return 0;
   }
   ```

8. 编写一个程序，显示求模运算的结果。把用户输入....

   ```c
   void chapter_five8(void)
   {
       int moduli,integer,calculate;
       printf("This program computes moduli.\n\
   Enter an integer to serve as the second operand:");
       scanf("%d",&moduli);
       printf("Now enter the first operand:");
       scanf("%d",&integer);
       while (integer>=0)
       {
           calculate = integer%moduli;
           printf("%d %%  %d is %d",integer,moduli,calculate);
           printf("\nNnter next number for first operand (<= 0 to quit)");
           scanf("%d",&integer);
       }
       printf("Done");
   }
   ```

9. 编写一个程序，要求用户输入一个华氏温度。程序应

   ```c
   #include<stdio.h>
   
   void temperatures(const double degree_fahrenheit)
   {
       double temperature,degree_kelvin;
       temperature = 5.0/9.0*(degree_fahrenheit-32);
       degree_kelvin = temperature+273.16;
       printf("Temperature = %.2f\tDegree Fahrenheit = %.2f\t Degree Kelvin = %.2f\n"
       ,temperature,degree_fahrenheit,degree_kelvin);
   }
   
   int main(void)
   {   
       double degree_fahrenheit;
       printf("Enter a degree fahrenheit:");
       while (scanf("%lf",&degree_fahrenheit))
       {
           temperatures(degree_fahrenheit);
           printf("Enter next degree fahrenheit:");
       }
   
       return 0;
   }
   ```


## 6.16编程练习

1. 编写一个程序，创建一个包含...

   ```c
   void print_alphabet(void)
   {
       char alphabet[26]="abcdefghijklmnopqrstuvwxyz";
       unsigned int index;
       for(index=0;index<26;++index)
       {
           printf("%c",alphabet[index]);
       }
   }
   ```

2. 使用嵌套循环，按下面的格式打印字符：....

   ```c
   void print_dollar_symbol(void)
   {
       int i,j;
       for (i=1;i<=5;++i)
       {
           for(j=0;j<i;++j)
           {
               printf("%$");
           }
           printf("\n");
       }
   }
   ```

3. 使用嵌套循环，按下面的格式打印字母：

   ```c
   void print_reverse_alphabet(void)
   {
       int external_loop,inner_loop;
       signed char letter;
       for(external_loop=1;external_loop<=6;++external_loop)
       {
           for(letter='F',inner_loop=0;inner_loop<external_loop;++inner_loop,--letter)
           {
               printf("%c",letter);
           }
           printf("\n");
       }
   }
   ```

   


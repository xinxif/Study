## 第二章编程练习

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


### 4.8编程练习

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
       
       return 0;
   }
   ```

   


## 第二章编程练习

1.  

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

2.  

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

3. 

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

4.  

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

5.  

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

6.  

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

7.  

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

8.  

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






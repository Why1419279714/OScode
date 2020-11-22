 #include <stdio.h>

    int cat(int argc, char *argv[])

    {

        FILE *fp = fopen(argv[1], "r");   // 以只读方式打开文件，argv[1]是输入的要显示的文件路径名

        int read_ret;

        if(argc < 2)  //说明没有输入要显示的文件名，只有本程序名argv[0]

        {

            printf("please input source file!\n");

        }

        if(fp == NULL)  //如果打开成功的话就把该文件的信息结构体地址赋给文件指针fp，如果打开不成功的话就将文件指针fp置为无效(NULL)

        {

            printf("open source %s failed!\n", argv[1]);

            return -1;

        }

        while(1)  //成功打开

        {

            read_ret = fgetc(fp);  //单个字符读写

            if(feof(fp))  // feof判断文件结束，若fp已经指向文件末尾，则feof（fp）函数值为“真”，即返回非零值

            {

                printf("read file %s endl\n",argv[1]);
                break;

            }

            fputc(read_ret,stdout);  //把单个字符输出到屏幕

        }

    }

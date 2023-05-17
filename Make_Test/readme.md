[A simple task to use `Make`](https://www.jianshu.com/p/8dc048ae1e11)

Make的规则

```makefile
test(目标文件): prog.o code.o(依赖文件列表)
tab(一个tab来隔开) gcc prog.o code.o -o test(命令)
```

生成MakeFile文件

```makefile
test: prog.o code.o
        gcc prog.o code.o -o test
prog.o: prog.c code.h
        gcc -c prog.c -o prog.o
code.o: code.c code.h
        gcc -c code.c -o code.o
clean:
        rm -f *.o test
```

使用make命令执行Makefile

```shell
make
gcc prog.o code.o -o test
gcc -c code.c -o code.o
gcc prog.o code.o -o test

./test

//清除.o和test文件
make clean
```

### 以下非常感谢[@Eric2i](https://github.com/Eric2i)的MakeFile项目结构

![image-20230516205814774](https://raw.githubusercontent.com/Sweet196/Picgo-images/main/problems/202305162058096.png)

```makefile
CC=g++
CFLAGS=-Wall -std=c++17  -Wno-sign-compare
BINDIR=bin
OBJDIR=obj
SRCDIR=src

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR)/exec: $(OBJDIR)/main.o $(OBJDIR)/grammar.o 
	$(CC) -o $@ $^

test: $(BINDIR)/exec
	$(BINDIR)/exec

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*
```

会常用这一套结构的！
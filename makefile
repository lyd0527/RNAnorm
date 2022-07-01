CC=g++
SRCS=FileOperate.cpp\
        RNAnorm.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=RNAnorm
start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
.cpp.o:
	$(CC) -o $@ -c $< -DMYLINUX

#执行make clean指令
clean:
	rm -rf $(OBJS)


# 建议使用 vim 编辑, TAB键缩进格式和vscode不一样 !!!

# include Makefile.def # 引入文件


# 1. 显示规则
# {目标文件}:{依赖文件}
#    {command}
hello:hello.c
	cat hello.c
	gcc hello.c -o hello

# 2. 伪指令
.PHONY: # 
clean:
	rm -rf hello


objects = main.o foo.o bar.o utils.o 
# objects := $(objects) another.o
objects += another.o

.PHONY: print
print:
	@echo $(objects)


foo = $(bar) 
bar = $(ugh) 
ugh = Huh?
all:
	echo $(foo)

define two-lines
echo foo
echo $(bar)
endef

line:
	@echo $(two-lines)

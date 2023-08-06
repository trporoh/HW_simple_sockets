binfirst := local local_client
binsecond := net net_client

local: $(binfirst) 
net: $(binsecond)

%.o: %.c
	gcc -c $< -o $@ -g

clean:
	rm $(binfirst) $(obj1) $(binsecond) $(obj2)
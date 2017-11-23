CFLAGS = -fPIC -O0 -g
LDLIBS = -ldl

all: main libapp.so

main: main.c app.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

libapp.so: app.c app.h
	$(CC) $(CFLAGS) -shared $(LDFLAGS) -o $@ $< $(LDLIBS)

test: main libapp.so
	./$<

clean:
	$(RM) *.o *.so main

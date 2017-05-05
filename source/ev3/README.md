## How to make and install STATIC library

```
> cd source/ev3/
> make
> make install
```

## How to make and install SHARED library

```
> cd source/ev3/
> make shared
> make shared-install
```

## How to use SHARED library

```
> cd eg/port/
> gcc port.c -lev3dev-c -o port
> ./port
```

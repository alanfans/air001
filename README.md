# air001
由于keil没有linux版本，大佬都是用命令行，我不行，我只会用IDE,所以air001编译采用eclipse

pyocd已经支持了air001，air32的芯片

daplink+pyocd可以正常debug

环境变量参考air001-cmake设置了三个：AIR001_DEV，USE_HAL_DRIVER，ARM_MATH_CM0PLUS

主要是配置头文件相关的库引用
```
"${workspace_loc:/${ProjName}/src}"
"${workspace_loc:/${ProjName}/include}"
"${workspace_loc:/${ProjName}/system/include/cmsis}"
"${workspace_loc:/${ProjName}/system/include/air001-hal}"
"${workspace_loc:/${ProjName}/system/include/air001-hal/Legacy}"
```

hal有些template库和syscall.c，编译报错，我不知道怎么配置排除，所认删除了一些

startup_air001xx.s结尾这个S要大写（外网关于eclipse单片机视频里看到up主这么改的，我不知道原因）且和ld文件放入同一个目录

Eclipse IDE for Embedded C/C++ Developers  used

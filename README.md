# Alpha blending

Program combines one image with transparent backbround and second image.
![alt Cat on the table](https://github.com/XelerT/alpha_blending/blob/main/imgs/cat%26table.png)

### Install and use
```
    $ git clone https://github.com/XelerT/alpha_blending.git
    $ cd alpha_blending
    $ make
```
To run program you need to save way to the front image and the background image. Exist two modes of program, if 3rd argument is 1, performance counter mode turns on, if 0, standart mode turns on.
```
    $ ./alpha_blending.out front_img_way back_img_way 0/1
```

Example:
```
    ./alpha_blending.out imgs/AskhatCat.bmp imgs/Table.bmp 1
```

### Performance
    There are two way to make calculations. Simple, without parallelism and else(calculate 1 pixel per iteration). And avx permormance improvement, using parallelism to calculate 4 pixels in a time. Calculation performance improved almost in 4 time using avx optimisation.

    Performance was checked in performance counter mode for 10 000 iterations.
![alt My time counter](https://github.com/XelerT/alpha_blending/blob/main/imgs/my_time.png)

![alt perf outside](https://github.com/XelerT/alpha_blending/blob/main/imgs/perf.png)

### Credits
     Created by Alex Taranov during 1 year of X courses, Spring 2023



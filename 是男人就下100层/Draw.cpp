#include "Draw.h"
//水平翻转图片
void Draw::flipimage(int x, int y, IMAGE img,DWORD H) {
    int h = img.getheight();
    int w = img.getwidth();//获取原图片宽高
    IMAGE img1(w, h);// 设置一个与原图片相同大小的图片用于存放翻转图片
    DWORD* d1 = GetImageBuffer(&img1);
    DWORD* d = GetImageBuffer(&img);//获取图片缓冲区地址，通过更改缓冲区实现
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            d1[w * j + i] = d[w * j + w - i - 1];
        }
    }//对调水平像素实现翻转（同理可实现垂直翻转）
    putimage(x, y, &img1,H);//打印图片
}
#include "Draw.h"
//ˮƽ��תͼƬ
IMAGE Draw::flipimage(IMAGE img) {
	int h = img.getheight();
	int w = img.getwidth();//��ȡԭͼƬ���
	IMAGE img1(w, h);// ����һ����ԭͼƬ��ͬ��С��ͼƬ���ڴ�ŷ�תͼƬ
	DWORD* d1 = GetImageBuffer(&img1);
	DWORD* d = GetImageBuffer(&img);//��ȡͼƬ��������ַ��ͨ�����Ļ�����ʵ��
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			d1[w * j + i] = d[w * j + w - i - 1];
		}
	}//�Ե�ˮƽ����ʵ�ַ�ת��ͬ���ʵ�ִ�ֱ��ת��
	return img1;
}

#include<reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define LCD_data P0
sbit SDA = P3 ^ 5;
sbit SCL = P3 ^ 4;//24C08控制口设置
sbit LCD_RS = P3 ^ 3; //寄存器选择输入
sbit LCD_RW = P3 ^ 6; //液晶读/写控制
sbit LCD_EN = P3 ^ 7; //液晶使能控制
sbit LCD_PSB = P3 ^ 2; //串/并方式控制
sbit FM = P2 ^ 4;//蜂鸣器控制口
sbit RS = P2 ^ 5;
sbit T_CLK = P2 ^ 0; //实时时钟时钟线引脚 //
sbit T_IO = P2 ^ 1; //实时时钟数据线引脚 //
sbit T_RST = P2 ^ 2; //实时时钟复位线引脚 //
sbit ds = P2 ^ 3;
sbit EN = P2 ^ 6;
sbit ZZ = P2 ^ 7;
sbit FZ = P3 ^ 1;
sbit ACC0 = ACC ^ 0;
sbit ACC7 = ACC ^ 7;
uint temp1, s_temp; //定义整形变量
float f_temp; //定义浮点型变量
uchar num, num1, flag, count, a, b;
uchar unlock_i;//解密标志位
uchar t[4];
uchar t1[4];
void delay_ms(uint z)//长延时
{
	uint x, y;
	for (x = z; x > 0; x--)
	for (y = 110; y > 0; y--);
}
void delay() //短延时，大约5us
{
	;;
}
void reshi()
{
	if (RS == 1)
	{
		unlock_i = 1;
	}
	else
	{
		unlock_i = 0;
	}
}
uchar code mima[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*' };
void lcd_xieping0(uchar x, uchar y, uchar date);
void lcd_xieping(uchar x, uchar y, uchar *str);
//********************************************************
// 开机显示
//********************************************************
void kjxs()
{
	uint i, j;
	lcd_xieping(0, 0, "PLEASE SET CODE");

	delay_ms(4000);

	for (j = 3; j > 0; j--)
	{
		for (i = 0; i < 8; i++)
		{
			lcd_xieping(3, i, "*");
			delay_ms(250);
		}
		lcd_xieping(3, 0, " ");
	}
}
//********************************************************
// 12864显示
//********************************************************
void write_cmd(uchar cmd)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	P0 = cmd;
	delay_ms(5);
	LCD_EN = 1;
	delay_ms(5);
	LCD_EN = 0;
}
void write_dat(uchar dat)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EN = 0;
	P0 = dat;
	delay_ms(5);
	LCD_EN = 1;
	delay_ms(5);
	LCD_EN = 0;
}
void lcd_xieping0(uchar x, uchar y, uchar date)
{
	switch (x)
	{
	case 0: write_cmd(0x80 + y); break;
	case 1: write_cmd(0x90 + y); break;
	case 2: write_cmd(0x88 + y); break;
	case 3: write_cmd(0x98 + y); break;
	}
	write_dat(date);
}
void lcd_xieping(uchar x, uchar y, uchar *str)
{
	switch (x)
	{
	case 0: write_cmd(0x80 + y); break;
	case 1: write_cmd(0x90 + y); break;
	case 2: write_cmd(0x88 + y); break;
	case 3: write_cmd(0x98 + y); break;
	}
	while (*str)
	{
		write_dat(*str);
		str++;
	}
}
void lcd_init()
{
	LCD_PSB = 1; //并口方式
	write_cmd(0x30); //基本指令操作
	delay_ms(5);
	write_cmd(0x0C); //显示开，关光标
	delay_ms(5);
	write_cmd(0x01); //清除LCD的显示内容
	delay_ms(5);
}
//**************************************************************
// 键盘扫描函数
//**************************************************************
uchar keyscan1() //矩阵键盘扫描函数
{
	uchar temp;
	while (!num)
	{
		P1 = 0xfe; //赋值
		temp = P1; //读回数据
		temp = temp & 0xf0; //与运算
		if (temp != 0xf0) //判断
		{
			delay_ms(2); //延时消抖
			temp = P1; //读回数据
			temp = temp & 0xf0;
			if (temp != 0xf0)
			{
				switch (temp) //多分支选择
				{
				case 0x70:num = 1; break; //跳出
				case 0xb0:num = 2; break;
				case 0xd0:num = 3; break;
				case 0xe0:num = 4; break;
				}
				while (temp != 0xf0)
				{
					temp = P1;
					temp = temp & 0xf0;
				}//等待按键释放
			}
		}
		P1 = 0xfd; //赋值
		temp = P1; //读回数据
		temp = temp & 0xf0; //与运算
		if (temp != 0xf0) //判断
		{
			delay_ms(2); //延时消抖
			temp = P1; //读回数据
			temp = temp & 0xf0;
			if (temp != 0xf0)
			{
				switch (temp) //多分支选择
				{
				case 0x70:num = 5; break; //跳出
				case 0xb0:num = 6; break;
				case 0xd0:num = 7; break;
				case 0xe0:num = 8; break;
				}
				while (temp != 0xf0)
				{
					temp = P1;
					temp = temp & 0xf0;
				}//等待按键释放
			}
		}
		P1 = 0xfb; //赋值
		temp = P1; //读回数据
		temp = temp & 0xf0; //与运算
		if (temp != 0xf0) //判断
		{
			delay_ms(2); //延时消抖
			temp = P1; //读回数据
			temp = temp & 0xf0;
			if (temp != 0xf0)
			{
				switch (temp) //多分支选择
				{
				case 0x70:num = 9; break; //跳出
				case 0xb0:num = 10; break;
				case 0xd0:num = 11; break;
				case 0xe0:num = 12; break;
				}
				while (temp != 0xf0)
				{
					temp = P1;
					temp = temp & 0xf0;
				}//等待按键释放
			}
		}
	}
	return(num); //返回值
}
uchar keyscan2()
{
	uchar temp;
	while (!num1)
	{
		P1 = 0xf7; //赋值
		temp = P1; //读回数据
		temp = temp & 0xf0; //与运算
		if (temp != 0xf0) //判断
		{
			delay_ms(2); //延时消抖
			temp = P1; //读回数据
			temp = temp & 0xf0;
			if (temp != 0xf0)
			{
				switch (temp) //多分支选择
				{
				case 0x70:num1 = 1; break; //跳出
				case 0xb0:num1 = 2; break;
				case 0xd0:num1 = 3; break;
				case 0xe0:num1 = 4; break;
				}
				while (temp != 0xf0)
				{
					temp = P1;
					temp = temp & 0xf0;
				}//等待按键释放
			}
		}
	}
	return(num1);
}

//**************************************************************
// EPPROM
//**************************************************************
void start() //启动信号
{
	SDA = 1;
	delay();
	SCL = 1;
	delay();
	SDA = 0;
	delay();
}
void stop() //停止信号
{
	SDA = 0;
	delay();
	SCL = 1;
	delay();
	SDA = 1;
	delay();
}
void respons() //响应信号
{
	uchar i;
	SCL = 1;
	delay();
	while ((SDA == 1) && (i < 250))
		i++;
	SCL = 0;
	delay();
}
void writebyte(uchar date) //写一个字节
{
	uchar i, temp;
	temp = date;
	for (i = 0; i < 8; i++)
	{
		temp = temp << 1;
		SCL = 0;
		delay();
		SDA = CY;
		delay();
		SCL = 1;
		delay();
	}
	SCL = 0;
	delay();
	SDA = 1; //释放总线
	delay();
}
uchar readbyte() //读一个字节
{
	uchar i, k;
	SCL = 0;
	delay();
	SDA = 1;
	for (i = 0; i < 8; i++)
	{
		SCL = 1;
		delay();
		k = (k << 1) | SDA;
		SCL = 0;
		delay();
	}
	delay();
	return(k);
}
void write(uchar add, uchar date) //在一个地址写一个字节
{
	start();
	writebyte(0xa0);
	respons();
	writebyte(add);
	respons();
	writebyte(date);
	respons();
	stop();
}
uchar read(uchar add) //在一个地址读一个字节
{
	start();
	writebyte(0xa0);
	respons();
	writebyte(add);
	respons();
	start();
	writebyte(0xa1);
	respons();
	b = readbyte();
	respons();
	stop();
	return(b);
}



//**************************************************************
// 解密函数
//**************************************************************
void unlock()
{
	uchar in, i;
	if (num == 0)
	{
		lcd_xieping(3, 0, " ");
		for (i = 0; i < 4; i++)
		{
			t1[i] = keyscan1();
			lcd_xieping(3, i, "*");
			num = 0;
		}//输密码
	}
	in = keyscan1();
	if (in == 12)//in-确定键标志位
	{
		in = 0;
		num = 0;
		if ((t1[0] == t[0]) && (t1[1] == t[1]) && (t1[2] == t[2]) && (t1[3] == t[3]))
		{
			flag = 1;//解密成功与否标志位
			//unlock_i=1;
			a = 0;//功能键标志
			lcd_xieping(0, 0, "PLEASE SET CODE ");
			lcd_xieping(2, 0, " INPUT PASSWORD ");

			delay_ms(1500);
			lcd_xieping(1, 0, "PLEASE COME IN");

		}
		else
		{
			flag = 0;
			count++;
			if (count == 3)
			{
				count = 0;
				num = 1;
				lcd_xieping(1, 0, "——————————");

				FM = 0;
				delay_ms(1000);
				FM = 1;
			}
		}
	}
}

  }
  ib = keyscan1();
  if (ib == 12)
  {
	  ib = 0;
	  num = 0;
	  if (t2[0] == t3[0] && t2[1] == t3[1] && t2[2] == t3[2] && t2[3] == t3[3])
	  {
		  t[0] = t3[0];
		  t[1] = t3[1];
		  t[2] = t3[2];
		  t[3] = t3[3];
		  lcd_xieping(3, 0, " 密码修改成功 ");
		  flag = 0;
		  for (j = 0; j < 4; j++)
		  {
			  l = j + 1;
			  write(l, t[j]);
			  delay_ms(10);
		  }//24C08写数据
		  delay_ms(1000);
	  }
	  else
	  {
		  lcd_xieping(2, 0, "INPUT PASSWORD");
		  flag = 1;
		  delay_ms(500);
	  }
  }
  }
  //**************************************************************
  // 显示函数
  //**************************************************************
  void xianshi()
  {

	  s_temp = f_temp * 100;
	  temp0[7] = (s_temp / 1000) + 48;
	  temp0[8] = (s_temp % 1000 / 100) + 48;
	  temp0[10] = (s_temp % 100 / 10) + 48;
	  temp0[11] = (s_temp % 10) + 48;
	  num = 0;
  }

  //**************************************************************
  // 主函数
  //**************************************************************
  void main()
  {
	  uchar m;
	  unlock_i = 1;
	  lcd_init(); //液晶初始化
	  //Init1302();
	  kjxs(); //开机显示
	  for (m = 0; m < 4; m++)
	  {
		  t[m] = read(m + 1);
		  delay_ms(10);
	  }//24C08读数据
	  while (1)
	  {
		  reshi();
		  if (!unlock_i)
		  {
			  unlock();//解密函数
		  }

		  if (flag == 1)
		  {
			  num1 = 0;
			  a = keyscan2();

			  if (a == 2)
			  {
				  xiugaimima();//修改密码函数
			  }
		  }
	  }
  }
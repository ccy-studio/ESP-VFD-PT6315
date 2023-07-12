/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 15:36:22
 * @LastEditTime: 2023-07-12 17:01:41
 */

/*
    米字字符图片参考： 
    https://blog.csdn.net/fcz1116/article/details/124371360
    https://zhuanlan.zhihu.com/p/94972448
*/

/*

0
	1- p1,p6,p10,p13,p9,p5,p4,p15,p11
	0-oa

1
	1- p5,p9
	0- other all	

2
	1- p1,p5,p7,p15,p8,p10,p13
	0- oa

3
	1- p1,p5,p7,p15,p8,p9,p13
	o- oa

4
	1- p6,p8,p15,p7,p5,p9
	o- oa

5
	1- p1,p6,p8,p15,p7,p9,p13
	o- oa

6	
	1- p1,p6,p10,p13,p9,p7,p15,p8
	0- oa

7
	1- p6,p1,p5,p9
	0- oa

8
	1- p1,p6,p10,p13,p9,p5,p8,p15,p7
	0- oa

9
	1- p7,p15,p8,p6,p1,p5,p9,p13
	0- oa

A
	1- p10,p6,p1,p5,p9,p8,p15,p7
	0- oa

B
	1- p1,p5,p9,p13,p2,p15,p7
	0-oa

C
	1- p1,p6,p10,p13
	0- oa

D
	1- p1,p5,p9,p13,p2
	0-oa 

E
	1- p1,p6,p10,p13,p8
	0- oa

F
	1- p1,p6,p10,p8,p15,p7
	0- oa

G
	1- p1,p6,p10,p13,p9,p7,p15
	0- oa

H 
	1- p6,p10,p5,p9,p8,p15,p7
	0- oa

I
	1- p1,p13,p2,p15
	0- oa

J
	1- p5,p9,p13,p10
	0-oa

K 
	1- p6,p10,p8,p15,p4,p12
	0- oa

L
	1- p6,p10,p13
	0-oa

M
	1- p10,p6,p3,p15,p4,pp5,p9
	0- oa

N
	1- p10,p6,p3,p15,p12,p9,p5
	0- oa

O
	1- p1,p6,p10,p13,p9,p5
	0- other all

P
	1- p1,p6,p8,p15,p7,p5,p9
	0-oa

Q
	1- p1,p6,p10,p13,p9,p5,p12
	0-oa

R
	1- p1,p5,p7,p15,p8,p6,p10,p12
	0-oa

S
	1- p1,p6,p8,p15,p7,p9,p13
	0-oa

T
	1- p1,p2,p15
	0-oa

U
	1- p6,p10,p13,p9,p5
	0-oa

V
	1- p6,p10,p11,p15,p4
	0-oa

W
	1- p6,p10,p11,p15,p12,p9,p5
	0-oa

X
	1- p3,p15,p12,p11,p4
	0-oa

Y
	1- p3,p15,p4,p11
	0-oa

Z
	1- p1,p4,p15,p11,p13
	0-oa

*/

/*
    Java生成C代码工具

    public class VFD_FontGenerator {

    public static void main(String[] args) {
        File file = new File("C:\\Users\\83503\\Desktop\\0.txt");
        List<String> lines = FileUtil.readLines(file, "utf-8");
        for (int i = 0; i < lines.size(); i += 4) {
            String num = lines.get(i).trim();
            String[] ps = lines.get(i + 1).trim()
                    .replaceAll("1-", "")
                    .trim().replaceAll("p", "")
                    .trim()
                    .split(",");
            byte[] bytes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (String p : ps) {
                Integer index = Integer.valueOf(p) - 1;
                bytes[index] = 1;
            }
            byte[][] split = ArrayUtil.split(bytes, 8);

            String hex1 = toHex(split[0]);
            String hex2 = toHex(split[1]);

            StringBuffer sb = new StringBuffer();
            sb.append("{");
            sb.append("{")
                    .append(hex1)
                    .append(",")
                    .append(hex2)
                    .append("},")
                    .append("\"")
                    .append(num)
                    .append("\"");
            sb.append("},");
            System.out.println(sb);
        }
    }

    public static String toHex(byte[] b) {
        StringBuffer sb = new StringBuffer();
        byte[][] split = ArrayUtil.split(b, 4);
        for (byte b1 : split[1]) {
            sb.append(String.valueOf(b1));
        }
        for (byte b1 : split[0]) {
            sb.append(String.valueOf(b1));
        }
        int i = Integer.parseInt(sb.toString(), 2);
        return "0x" + Integer.toString(i, 16);
    }
}

*/
#include "gui.h"

vfd_gui_fonts fonts[VFD_GUI_FONT_LEN] = {
    {{0xc9, 0xae}, "0"}, {{0x80, 0x8}, "1"},  {{0xb8, 0xa4}, "2"},
    {{0xb8, 0xa8}, "3"}, {{0xf0, 0x28}, "4"}, {{0x78, 0xa8}, "5"},
    {{0x78, 0xac}, "6"}, {{0xc8, 0x8}, "7"},  {{0xf8, 0xac}, "8"},
    {{0xf8, 0xa8}, "9"}, {{0xf8, 0x2c}, "A"}, {{0xac, 0xa8}, "B"},
    {{0x48, 0x84}, "C"}, {{0x8c, 0x88}, "D"}, {{0x58, 0x84}, "E"},
    {{0x78, 0x24}, "F"}, {{0x68, 0xac}, "G"}, {{0xf0, 0x2c}, "H"},
    {{0xc, 0xa0}, "I"},  {{0x80, 0x8c}, "J"}, {{0x51, 0x25}, "K"},
    {{0x40, 0x84}, "L"}, {{0xc3, 0x2c}, "M"}, {{0xc2, 0x2d}, "N"},
    {{0xc8, 0x8c}, "O"}, {{0xf8, 0x28}, "P"}, {{0xc8, 0x8d}, "Q"},
    {{0xf8, 0x25}, "R"}, {{0x78, 0xa8}, "S"}, {{0xc, 0x20}, "T"},
    {{0xc0, 0x8c}, "U"}, {{0x41, 0x26}, "V"}, {{0xc0, 0x2f}, "W"},
    {{0x3, 0x23}, "X"},  {{0x3, 0x22}, "Y"},  {{0x9, 0xa2}, "Z"}};
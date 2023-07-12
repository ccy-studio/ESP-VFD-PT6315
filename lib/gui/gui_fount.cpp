/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-07-12 15:36:22
 * @LastEditTime: 2023-07-12 23:39:25
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
        1- p1,p6,p10,p13,p8,p15,p7
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
        1- p6,p8,p15,p7,p9,p5,p13
        0-oa

Z
        1- p1,p4,p15,p11,p13
        0-oa

*/

/*
    Java生成C代码工具

    
public class Test1 {

    public static void main(String[] args) throws Exception {
        File file = new File("/Users/chenzedeng/Desktop/0.txt");
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
                    .append("'")
                    .append(num)
                    .append("'");
            sb.append("},");
            System.out.println(sb);
        }
    }

    public static String toHex(byte[] b) {
        StringBuffer sb = new StringBuffer();
        for (byte b1 : ArrayUtil.reverse(b)) {
            sb.append(String.valueOf(b1));
        }
        int i = Integer.parseInt(sb.toString(), 2);
        return "0x" + Integer.toString(i, 16);
    }

}

*/
#include "gui.h"

vfd_gui_fonts fonts[VFD_GUI_FONT_LEN] = {
    {{0x00, 0x00}, ' '}, {{0x39, 0x57}, '0'}, {{0x10, 0x1}, '1'},
    {{0xd1, 0x52}, '2'}, {{0xd1, 0x51}, '3'}, {{0xf0, 0x41}, '4'},
    {{0xe1, 0x51}, '5'}, {{0xe1, 0x53}, '6'}, {{0x31, 0x1}, '7'},
    {{0xf1, 0x53}, '8'}, {{0xf1, 0x51}, '9'}, {{0xf1, 0x43}, 'A'},
    {{0x53, 0x51}, 'B'}, {{0x21, 0x12}, 'C'}, {{0x13, 0x11}, 'D'},
    {{0xe1, 0x52}, 'E'}, {{0xe1, 0x42}, 'F'}, {{0x61, 0x53}, 'G'},
    {{0xf0, 0x43}, 'H'}, {{0x3, 0x50}, 'I'},  {{0x10, 0x13}, 'J'},
    {{0xa8, 0x4a}, 'K'}, {{0x20, 0x12}, 'L'}, {{0x3c, 0x43}, 'M'},
    {{0x34, 0x4b}, 'N'}, {{0x31, 0x13}, 'O'}, {{0xf1, 0x41}, 'P'},
    {{0x31, 0x1b}, 'Q'}, {{0xf1, 0x4a}, 'R'}, {{0xe1, 0x51}, 'S'},
    {{0x3, 0x40}, 'T'},  {{0x30, 0x13}, 'U'}, {{0x28, 0x46}, 'V'},
    {{0x30, 0x4f}, 'W'}, {{0xc, 0x4c}, 'X'},  {{0xf0, 0x51}, 'Y'},
    {{0x9, 0x54}, 'Z'},
};
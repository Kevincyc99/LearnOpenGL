使用out关键字把顶点位置输出到片段着色器，并将片段的颜色设置为与顶点位置相等（来看看连顶点位置值都在三角形中被插值的结果）。

做完这些后，尝试回答下面的问题：为什么在三角形的左下角是黑的?



答：

颜色的范围是黑(0.0f, 0.0f, 0.0f)到白(1.0f, 1.0f, 1.0f)

每个分量的范围是0.0f到1.0f，超出该范围会被认为是边界0.0f或者1.0f，即黑色或白色

中心点为(0,0,0)，左下角位于第三象限，x、y均为负，被认为是黑色



效果：

![](https://github.com/Kevincyc99/Images-Store/raw/main/LearnOpenGL/Results/11_Exercise2_3.png)
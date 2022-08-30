目前，我们的光源是静止的，你可以尝试使用sin或cos函数让光源在场景中来回移动。观察光照随时间的改变能让你更容易理解冯氏光照模型。


效果：


![](https://github.com/Kevincyc99/Images-Store/raw/main/LearnOpenGL/Results/39_Exercise7_4.gif)


冯氏光照对比


![](https://github.com/Kevincyc99/Images-Store/raw/main/LearnOpenGL/Results/36_Exercise7_1.gif)



由于Gouraud着色是在顶点着色器中计算光照，其计算的光照只在顶点处有效，其余片段均为顶点在三角形上的插值，而由于插值，导致最后的光照效果也往往以三角形来明显区分。
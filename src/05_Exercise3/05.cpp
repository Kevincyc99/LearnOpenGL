#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//顶点着色器的源代码
const char *vertexShaderSource =    "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                    "gl_PointSize = 10.0f;\n"
                                    "}\0";
//片段着色器的源代码
const char *fragmentShaderSource1 =  "#version 330 core\n"
    								"out vec4 FragColor;\n"
    								"void main()\n"
    								"{\n"
    								"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    								"}\0";

//片段着色器的源代码
const char *fragmentShaderSource2 =  "#version 330 core\n"
    								"out vec4 FragColor;\n"
    								"void main()\n"
    								"{\n"
    								"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    								"}\0";
int main()
{
    //初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建一个窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//设置视口
	glViewport(0, 0, 800, 600);
    glEnable(GL_PROGRAM_POINT_SIZE);
	//注册窗口变化监听
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //创建顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //附加着色器代码并编译着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //检测编译是否成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //若编译失败，返回错误信息
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    //创建片段着色器
    unsigned int fragmentShader1, fragmentShader2;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);

    glCompileShader(fragmentShader1);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    //创建着色器程序
    unsigned int shaderProgram1, shaderProgram2;
    shaderProgram1 = glCreateProgram();
    shaderProgram2 = glCreateProgram();

    //附加着色器对象到着色器程序
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);

    //链接着色器
    glLinkProgram(shaderProgram1);
    //检查编译错误
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n"
                  << infoLog << std::endl;
    }
    //链接着色器
    glLinkProgram(shaderProgram2);
    //检查编译错误
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n"
                  << infoLog << std::endl;
    }


    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    //定义顶点数组
    float vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f
    };

    //创建VBO、VAO
    unsigned int VBOS[2], VAOS[2];
    glGenBuffers(2, VBOS);
    glGenVertexArrays(2, VAOS);

    //绑定VAO
    glBindVertexArray(VAOS[0]);
    //绑定VBO缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
    //填充数据到VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //OpenGL解析顶点数据的规则,设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //绑定VAO
    glBindVertexArray(VAOS[1]);
    //绑定VBO缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
    //填充数据到VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //OpenGL解析顶点数据的规则,设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    //渲染循环
	while(!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        //激活着色器程序
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOS[0]);
        glDrawArrays(GL_POINTS, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

         //激活着色器程序
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOS[1]);
        glDrawArrays(GL_POINTS, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//释放资源
    glDeleteVertexArrays(2, VAOS);
    glDeleteBuffers(2, VBOS);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);

	glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
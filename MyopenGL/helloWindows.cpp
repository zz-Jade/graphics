#include <iostream>

// GLEW
// 定义为静态链接库
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

/*****************
 glew头文件要前于glfw头文件，因为glew头文件会引入许多opengl必要的头文件
 因此，需要先引入glew，再引入glfw
 opengl只是一个标准/规范
 glfw是一个专门针对opengl的c语言库
 glew则是统一化接口，开发者不必要确定opengl对应的正确版本驱动
 glew是用来管理opengl的函数指针，因此调用任何opengl函数都需要初始化glew
*****************/

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    // glfwCreateWindow 参数为 宽、高、窗口名称 etc
    // 窗口对象存放了所有和窗口相关的数据
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the required callback functions
    //通过GLFW注册自定义的回调函数
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    // 设置为true让glew管理opengl指针使用现代化技术
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    /*
    **glviewport参数：前两个为窗口左下角位置，渲染窗口宽度和高度（像素）
    **这里选择从GLFW中获取，不直接设置是为了在高DPI屏幕上也能正常工作
    **设置Viewport是为了告诉opengl渲染窗口的尺寸大小
    ** OpenGL幕后使用glViewport中定义的位置和宽高进行2D坐标的转换
    ** 将OpenGL中的位置坐标转换为你的屏幕坐标
    ** 例如，OpenGL中的坐标(-0.5, 0.5)有可能（最终）被映射为屏幕中的坐标(200,450)
    ** 注意，处理过的OpenGL坐标范围只为-1到1
    ** 因此我们事实上将(-1到1)范围内的坐标映射到(0, 800)和(0, 600)
    */
    glViewport(0, 0, width, height);

    // Game loop
    //游戏循环是为了让程序不断地绘制图像并能够接受用户输入，直到我们选择退出
    /*
    **glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后游戏循环便结束了，之后为我们就可以关闭应用程序了。
    **glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）。我们一般在游戏循环的开始调用事件处理函数。
    **glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
    */
    /*
    ** 双缓冲（double buffer）
    ** 单缓冲绘图会存在图像闪烁的问题，因为图片是从左到右，从上而下逐像素绘制
    ** 会导致渲染结果很不真实，因此前缓冲负责保存最终显示图像
    ** 后缓冲负责计算绘制新的图片
    ** 计算完毕直接交换前后缓冲
     */
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
/*
** 按键回调函数接受一个GLFWwindow指针作为它的第一个参数；
** 第二个整形参数用来表示按下的按键；
** action参数表示这个按键是被按下还是释放；
** 最后一个整形参数表示是否有Ctrl、Shift、Alt、Super等按钮的操作。
** GLFW会在合适的时候调用它，并为各个参数传入适当的值。
*/
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE || action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
